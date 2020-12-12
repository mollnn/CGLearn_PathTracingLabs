#ifndef _PATH_TRACER_HPP
#define _PATH_TRACER_HPP

#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Random.hpp"
#include "Timer.hpp"
#include "Image.hpp"
#include "Sampler.hpp"
#include "ColorSpace.hpp"

const double PI = acos(-1);

// 求出一条光线与一个特定的物体的交点，返回 <距离，交点>
std::tuple<double, Point> GetIntersection(const Sphere &sphere, const Ray &ray)
{
    double distance = GetIntersectionDistance(sphere, ray);
    Point intersection_point = ray.origin + distance * ray.direction;
    return std::make_tuple(distance, intersection_point);
}

// 求出一条光线在场景中第一个碰撞的物体，返回 <距离，交点，物体编号>
// 若物体编号为 -1，则代表没有交点
std::tuple<double, Point, int> GetIntersection(const Scene &scene, const Ray &ray)
{
    int scene_size = scene.Size();
    // 维护一个答案，扫描所有场景中的物体并更新这个答案
    std::tuple<double, Point, int> answer = std::make_tuple(1e100, Point(0, 0, 0), -1);
    for (int i = 0; i < scene_size; i++)
    {
        const Sphere &sphere = scene[i];
        auto [distance, intersection_point] = GetIntersection(sphere, ray);
        // 如果 distance > 0，则表示交点合法，此时考虑更新答案
        if (distance > 0 && distance < std::get<0>(answer))
        {
            answer = std::make_tuple(distance, intersection_point, i);
        }
    }
    return answer;
}

// 光线追踪主函数
Radiance PathTracing(Ray ray, int depth, const Scene &scene)
{
    // 递归边界条件，这里采用强硬深度限制，如果递归深度超过 10 就停止计算
    if (depth > 5)
    {
        return 0; // 返回背景色
    }

    // 求出光线与场景的交点，如果找不到交点就返回背景色
    auto [hit_distance, hit_point, hit_id] = GetIntersection(scene, ray);
    if (hit_id == -1)
    {
        return 0; // 无交点，返回背景色
    }

    // 准备工作，计算基本信息
    const Sphere &hit_obj = scene[hit_id];                               // 命中物体
    Vector3D normal_outward = (hit_point - hit_obj.center).Unit();       // 外向法线
    bool is_into_sphere = Dot(ray.direction, normal_outward) < 0;        // 是否在射入球体内部
    Vector3D normal = is_into_sphere ? normal_outward : -normal_outward; // 实际光学效应的法线
    double relative_refraction_index = is_into_sphere ? hit_obj.material.refrect_index : 1.0 / hit_obj.material.refrect_index;

    // 预处理镜面反射与折射光线的方向
    Vector3D in_dir = ray.direction;                                // 光线入射方向
    double cos_i = abs(Dot(in_dir, normal));                        // 入射角 cos
    double sin_i = sqrt(1 - cos_i * cos_i);                         // 入射角 sin
    double sin_j = sin_i / relative_refraction_index;               // 折射角 sin
    double cos_j = sqrt(1 - sin_j * sin_j);                         // 折射角 cos
    Vector3D base = (in_dir + Dot(in_dir, normal) * normal).Unit(); // 入射面中表面的切线方向
    Vector3D refl_dir = in_dir + 2 * Dot(in_dir, normal) * normal;  // 反射光线方向
    Vector3D refr_dir = sin_j * base - cos_j * normal;              // 折射光线方向

    // 预处理光强信息
    double refrect_index_in = is_into_sphere ? 1.0 : hit_obj.material.refrect_index;
    double refrect_index_out = is_into_sphere ? hit_obj.material.refrect_index : 1.0;
    double refrect_index_sum = refrect_index_in + refrect_index_out;
    double refrect_index_delta = refrect_index_in - refrect_index_out;
    double fresnel_i0 = refrect_index_delta * refrect_index_delta / refrect_index_sum / refrect_index_sum;
    double fresnel_x = 1 - (is_into_sphere ? cos_i : cos_j);
    const Material &material = hit_obj.material;
    double fresnel_reflection_intensity = fresnel_i0 + (1 - fresnel_i0) * pow(fresnel_x, 5);
    double fresnel_refrection_intensity = 1 - fresnel_reflection_intensity;
    double reflect_intensity = material.specular + material.refrection * fresnel_reflection_intensity;
    double refrect_intensity = material.refrection * fresnel_refrection_intensity;
    double diffuse_intensity = material.diffuse;

    // 按概率随机生成光线，递归计算
    double rand_value = Rand();
    if (rand_value < diffuse_intensity)
    {
        // 预处理漫反射光线的方向
        double diffuse_phi = 2 * PI * Rand();               // 漫反射光线的投影方向
        double diffuse_radius = sqrt(Rand());               // 漫反射光线的投影半径
        double cos_theta = diffuse_radius;                  // 漫反射光线 theta cos
        double sin_theta = sqrt(1 - cos_theta * cos_theta); // 漫反射光线 theta sin
        double cos_phi = cos(diffuse_phi);                  // 漫反射光线 phi cos
        double sin_phi = sin(diffuse_phi);                  // 漫反射光线 phi sin
        Vector3D diffuse_unit_k = normal;                   // 微平面坐标系 k 方向基矢
        Vector3D diffuse_unit_i = Cross(diffuse_unit_k.x > 0.1
                                            ? Vector3D(0, 1, 0)
                                            : Vector3D(1, 0, 0),
                                        diffuse_unit_k)
                                      .Unit();                                // 微平面坐标系 i 方向基矢
        Vector3D diffuse_unit_j = Cross(diffuse_unit_i, diffuse_unit_k);      // 微平面坐标系 j 方向基矢
        double diffuse_proj_i = cos_theta * cos_phi;                          // 漫反射光线在微平面坐标系 k 方向的投影
        double diffuse_proj_j = cos_theta * sin_phi;                          // 漫反射光线在微平面坐标系 i 方向的投影
        double diffuse_proj_k = sin_theta;                                    // 漫反射光线在微平面坐标系 j 方向的投影
        Vector3D diffuse_dir_i = diffuse_proj_i * diffuse_unit_i;             // 漫反射光线在微平面坐标系 i 方向的分量
        Vector3D diffuse_dir_j = diffuse_proj_j * diffuse_unit_j;             // 漫反射光线在微平面坐标系 j 方向的分量
        Vector3D diffuse_dir_k = diffuse_proj_k * diffuse_unit_k;             // 漫反射光线在微平面坐标系 k 方向的分量
        Vector3D diffuse_dir = diffuse_dir_i + diffuse_dir_j + diffuse_dir_k; // 漫反射光线方向
        // 生成漫反射光线
        Ray diffuse_ray(hit_point, diffuse_dir);
        return PathTracing(diffuse_ray, depth + 1, scene) + material.emission;
    }
    else if (rand_value - diffuse_intensity < reflect_intensity)
    {
        // 生成镜面反射光线
        Ray reflection_ray(hit_point, refl_dir);
        return PathTracing(reflection_ray, depth + 1, scene) + material.emission;
    }
    else if (rand_value - diffuse_intensity - reflect_intensity < refrect_intensity)
    {
        // 生成折射光线
        Ray refrection_ray(hit_point, refr_dir);
        return PathTracing(refrection_ray, depth + 1, scene) + material.emission;
    }
    else
    {
        // 吸收
        return material.emission;
    }
}

#endif