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

    Sphere(): center(Vector3D(0,0,0)), radius(0),  material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Sphere(Vector3D center, double radius): center(center), radius(radius),  material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Sphere(Vector3D center, double radius, Material material): center(center), radius(radius), material(material)
    {
        return;
    }


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

        double equation_coefficient_a = direction.Dot(direction);
        double equation_coefficient_b = 2 * center_to_origin.Dot(direction);
        double equation_coefficient_c = center_to_origin.Dot(center_to_origin) - radius * radius;

        double equation_delta = sqrt(equation_coefficient_b * equation_coefficient_b - 4 * equation_coefficient_a * equation_coefficient_c);
        double equation_root1 = (-equation_coefficient_b - equation_delta) / 2;
        double equation_root2 = (-equation_coefficient_b + equation_delta) / 2;

        if (equation_root1 >= 0)
        {
            return equation_root1;
        }
        else
        {
            return equation_root2;
        }
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("center", center.ToJsonObject());
        jsonobj.Add("radius", radius);
        jsonobj.Add("material", material.ToJsonObject());
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_center, jsonobj_material;
        jsonobj.Get("center",jsonobj_center);
        jsonobj.Get("radius",radius);
        jsonobj.Get("material",jsonobj_material);
        center.FromJsonObject(jsonobj_center);
        material.FromJsonObject(jsonobj_material);
    }

    friend Sphere SphereFromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        Sphere ans;
        ans.FromJsonObject(jsonobj);
        return ans;
    }

};

#endif