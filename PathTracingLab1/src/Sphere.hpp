#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"

struct Sphere
{
    Vector3D center;
    double radius;
    Material material;

    // () <-

    // 设交点为 p
    // (p - center) * (p - center) = radius * radius
    // 设射线为 p = origin + t * direction
    // (origin + t*direction - center) * (origin + t*direction - center) = radius * radius
    // 设 delta = origin - center
    // (delta + t*direction) * (delta + t*direction) = radius * radius
    // delta*delta + 2*delta*direction * t + direction*direction * t^2 = radius * radius
    // (direction*direction) * t^2 + 2*delta*direction * t + delta*delta-radius*radius = 0

    double GetIntersectionDistance(const Sphere &sphere, const Ray &ray)
    {
        Vector3D direction = ray.direction;
        Vector3D center_to_origin = ray.origin - sphere.center;
        double radius = sphere.radius;

        double a = direction.Dot(direction);
        double b = 2 * center_to_origin.Dot(direction);
        double c = center_to_origin.Dot(center_to_origin) - radius * radius;

        // (-b +- sqrt(b^2 - 4ac)) / 2

        double delta = sqrt(b * b - 4 * a * c);
        double t1 = (-b - delta) / 2;
        double t2 = (-b + delta) / 2;

        if (t1 >= 0)
        {
            return t1;
        }
        else
        {
            return t2;
        }
    }
};

#endif