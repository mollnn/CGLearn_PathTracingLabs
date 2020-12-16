#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "ColorSpace.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "PathTracer.hpp"
#include "Random.hpp"
#include "Ray.hpp"
#include "Sample.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Timer.hpp"
#include "Vector3D.hpp"
#include "Camera.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // 检查 OpenMP 是否支持
#ifndef _OPENMP
    cerr << "OpenMP not supported! " << endl;
#endif

    // 从 JSON 文件中读取场景
    Scene scene;
    std::ifstream jsonifs_scene(argv[1]);
    std::stringstream jsonifs_buffer_scene;
    jsonifs_buffer_scene << jsonifs_scene.rdbuf();
    std::string jsonstr_scene(jsonifs_buffer_scene.str());
    cjsonobj::CJsonObject jsonobj_scene;
    jsonobj_scene.Parse(jsonstr_scene);
    scene.FromJsonObject(jsonobj_scene);

    // 135 相机 (底片 36mm * 24mm)
    double film_size_x = 0.036;
    double film_size_y = 0.024;
    double focus_distance = 0.001 * 24; // 相机焦距

    // 设置相机方向（这个地方暂时是硬设置，响应的计算尚未处理好）
    Camera camera(Point3D(8, 0, 3), Vector3D(-1, 0, -0.2).Unit(), Vector3D(0, 0, 1).Unit()); // 相机（起点，方向，上方向）
    camera.CorrectByHorizontal(Vector3D(0, 1, 0).Unit());
    Vector3D film_vec_j = -camera.up * film_size_y;                         // 胶片的高度向量
    Vector3D film_vec_i = Cross(camera.direction, camera.up) * film_size_x; // 胶片的宽度向量

    // 设置输出图像大小
    int image_size_x = 300;
    int image_size_y = 200;
    int samples_per_pixel = 128;
    Image image(image_size_x, image_size_y);

    int progress_count = 0;
    Timer timer;

    // 并行计算所有采样
#pragma omp parallel for
    for (int image_x = 0; image_x < image_size_x; image_x++)
    {
        for (int image_y = 0; image_y < image_size_y; image_y++)
        {
            double film_x_min = 1.0 * image_x / image_size_x;
            double film_x_max = 1.0 * (image_x + 1) / image_size_x;
            double film_y_min = 1.0 * image_y / image_size_y;
            double film_y_max = 1.0 * (image_y + 1) / image_size_y;
            for (int i = 0; i < samples_per_pixel; i++)
            {
                double film_x = RandBetween(film_x_min, film_x_max);
                double film_y = RandBetween(film_y_min, film_y_max);
                Sample sample(film_x, film_y, image_x, image_y, 1.0 / samples_per_pixel);
                Vector3D vec = focus_distance * camera.direction + (sample.film_x - 0.5) * film_vec_i + (sample.film_y - 0.5) * film_vec_j; // 光线起点相对于相机原点的偏离方向
                Point3D origin = camera.position + vec;                                                                                     // 光线起点
                Vector3D direction = vec.Unit();                                                                                            // 光线方向
                Ray ray(origin, direction);                                                                                                 // 光线

                double radiance = PathTracing(ray, 1, scene); // 计算光线跟踪得到辐射强度
                image.IncPixel(sample.image_x, sample.image_y, radiance * sample.weight);

                // 渲染进度统计与报告
                ++progress_count;

                if (progress_count % 100000 == 0)
                {
                    stringstream t_stringstream;
                    t_stringstream << 1.0 * progress_count / image_size_x / image_size_y / samples_per_pixel * 100 << "\%" << endl;
                    cout << t_stringstream.str();
                }
            }
        }
    }

    int flag = 0;

    image.WriteToPPM(argv[2]);
}