#include <bits/stdc++.h>
#include "ColorSpace.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "PathTracer.hpp"
#include "Random.hpp"
#include "Ray.hpp"
#include "Sample.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "Timer.hpp"
#include "Vector3D.hpp"
#include "Camera.hpp"
#include "Sensor.hpp"
#include "Json.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // 检查 OpenMP 是否支持
#ifndef _OPENMP
    cerr << "OpenMP not supported! " << endl;
#endif

    Scene scene(ReadJSON(argv[2]));   // 从 JSON 文件中读取场景
    Camera camera(ReadJSON(argv[3])); // 从 JSON 文件中读取相机
    Sensor sensor(ReadJSON(argv[4])); // 从 JSON 文件中读取传感器
    Image image(sensor.image_size_x, sensor.image_size_y);

    Vector3D film_vec_j = -camera.up * camera.film_size_y;                         // 胶片的高度向量
    Vector3D film_vec_i = Cross(camera.direction, camera.up) * camera.film_size_x; // 胶片的宽度向量

    int progress_count = 0;
    Timer timer;

    // 并行计算所有采样
#pragma omp parallel for
    for (int image_x = 0; image_x < sensor.image_size_x; image_x++)
    {
        for (int image_y = 0; image_y < sensor.image_size_y; image_y++)
        {
            double film_x_min = 1.0 * image_x / sensor.image_size_x;
            double film_x_max = 1.0 * (image_x + 1) / sensor.image_size_x;
            double film_y_min = 1.0 * image_y / sensor.image_size_y;
            double film_y_max = 1.0 * (image_y + 1) / sensor.image_size_y;
            for (int i = 0; i < sensor.samples_per_pixel; i++)
            {
                double film_x = RandBetween(film_x_min, film_x_max);
                double film_y = RandBetween(film_y_min, film_y_max);
                Sample sample(film_x, film_y, image_x, image_y, 1.0 / sensor.samples_per_pixel);
                Vector3D vec = camera.focus_distance * camera.direction + (sample.film_x - 0.5) * film_vec_i + (sample.film_y - 0.5) * film_vec_j; // 光线起点相对于相机原点的偏离方向
                Point3D origin = camera.position + vec;                                                                                            // 光线起点
                Vector3D direction = vec.Unit();                                                                                                   // 光线方向
                Ray ray(origin, direction);                                                                                                        // 光线

                Radiance3 radiance = PathTracing(ray, 1, scene); // 计算光线跟踪得到辐射强度
                image.IncPixel(sample.image_x, sample.image_y, radiance * sample.weight);

                // 渲染进度统计与报告
                ++progress_count;

                if (progress_count % 100000 == 0)
                {
                    stringstream t_stringstream;
                    t_stringstream << 1.0 * progress_count / sensor.image_size_x / sensor.image_size_y / sensor.samples_per_pixel * 100 << "\%" << endl;
                    cout << t_stringstream.str();
                }
            }
        }
    }

    int flag = 0;

    image.WriteToPPM(argv[1]);
}