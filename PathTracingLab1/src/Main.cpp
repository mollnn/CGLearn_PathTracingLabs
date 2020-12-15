#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "ColorSpace.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "PathTracer.hpp"
#include "Random.hpp"
#include "Ray.hpp"
#include "Sampler.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Timer.hpp"
#include "Vector3D.hpp"

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

    // 设置相机方向（这个地方暂时是硬设置，响应的计算尚未处理好）
    Camera camera(Point3D(3, 0, 0), Vector3D(-1, 0, 0)); // 相机（起点，方向）
    Vector3D film_unit_i(0, 1, 0);                       // 胶片的宽度向量
    Vector3D film_unit_j(0, 0, -1);                      // 胶片的高度向量
    double focus_distance = 1.0;                         // 胶片到相机中心的距离

    // 设置输出图像大小
    int image_size_x = 256;
    int image_size_y = 256;
    Image image(image_size_x, image_size_y);

    // 设置采样器并生成采样
    Sampler sampler(image_size_x, image_size_y, 32);
    sampler.MakeSamples();

    int progress_count = 0;
    Timer timer;

    // 并行计算所有采样
// #pragma omp parallel for
    for (int i = 0; i < sampler.samples.size(); i++)
    {
        auto sample = sampler.samples[i]; // 当前正在计算的采样

        Vector3D vec = focus_distance * camera.direction + (sample.film_x - 0.5) * film_unit_i + (sample.film_y - 0.5) * film_unit_j; // 光线起点相对于相机原点的偏离方向
        Point3D origin = camera.origin + vec;                                                                                         // 光线起点
        Vector3D direction = vec.Unit();                                                                                              // 光线方向
        Ray ray(origin, direction);                                                                                                   // 光线

        double radiance = PathTracing(ray, 1, scene); // 计算光线跟踪得到辐射强度
        image.IncPixel(sample.image_x, sample.image_y, radiance * sample.weight);

        // 渲染进度统计与报告
        ++progress_count;

        if (progress_count % 100000 == 0)
        {
            stringstream t_stringstream;
            t_stringstream << 1.0 * progress_count / sampler.samples.size() * 100 << "\%" << endl;
            cout << t_stringstream.str();
        }
    }

    int flag = 0;

    image.WriteToPPM(argv[2]);
}