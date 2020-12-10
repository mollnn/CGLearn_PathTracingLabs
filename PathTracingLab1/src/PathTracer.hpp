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

// 求出一条光线与一个特定的物体的交点，返回 <距离，交点>
std::tuple<double, Point> GetIntersection(const Sphere &sphere, const Ray &ray)
{
    double distance = GetIntersectionDistance(sphere, ray);
    Point intersection_point = ray.origin + distance * ray.direction;
    return std::make_tuple(distance, intersection_point);
}

// 求出一条光线在场景中第一个碰撞的物体，返回 <距离，交点，物体编号>
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



#endif