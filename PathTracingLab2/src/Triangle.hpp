#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <bits/stdc++.h>
#include "Json.hpp"

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"

#include "Plane.hpp"

struct Triangle
{
    Point3D p[3];
    Material material;

    Triangle() : p({Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)}), material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Triangle(Point3D p0, Point3D p1, Point3D p2) : p({p0, p1, p2}), material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Triangle(Point3D p0, Point3D p1, Point3D p2, Material material) : p({p0, p1, p2}), material(material)
    {
        return;
    }

    Triangle(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    friend double GetIntersectionDistance(const Triangle &triangle, const Ray &ray);

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("p0", p[0].ToJsonObject());
        jsonobj.Add("p1", p[1].ToJsonObject());
        jsonobj.Add("p2", p[2].ToJsonObject());
        jsonobj.Add("material", material.ToJsonObject());
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_p0, jsonobj_p1, jsonobj_p2, jsonobj_material;
        jsonobj.Get("p0", jsonobj_p0);
        jsonobj.Get("p1", jsonobj_p1);
        jsonobj.Get("p2", jsonobj_p2);
        jsonobj.Get("material", jsonobj_material);
        p[0].FromJsonObject(jsonobj_p0);
        p[1].FromJsonObject(jsonobj_p1);
        p[2].FromJsonObject(jsonobj_p2);
        material.FromJsonObject(jsonobj_material);
    }

    Plane GetPlane() const
    {
        Vector3D a = p[1] - p[0];
        Vector3D b = p[2] - p[0];
        Vector3D n = Cross(a, b).Unit();
        return Plane(p[0], n);
    }
};

double GetIntersectionDistance(const Triangle &triangle, const Ray &ray)
{
    Plane plane = triangle.GetPlane();
    double distance = GetIntersectionDistance(plane, ray);
    if (distance < 0)
    {
        return -1; // No intersection
    }
    else
    {
        Point3D hit_point = ray.origin + distance * ray.direction;
        Point3D q = hit_point;
        Vector3D n = plane.normal;

        Vector3D p0_p1 = p[1] - p[0];
        Vector3D p1_p2 = p[2] - p[1];
        Vector3D p2_p0 = p[0] - p[2];

        Vector3D p0_q = q - p[0];
        Vector3D p1_q = q - p[1];
        Vector3D p2_q = q - p[2];

        Vector3D cross_0 = Cross(p0_p1, p0_q);
        Vector3D cross_1 = Cross(p1_p2, p1_q);
        Vector3D cross_2 = Cross(p2_p0, p2_q);

        double dot_0 = Dot(cross_0, n);
        double dot_1 = Dot(cross_1, n);
        double dot_2 = Dot(cross_2, n);

        bool sign_0 = dot_0 > -1e-8;
        bool sign_1 = dot_1 > -1e-8;
        bool sign_2 = dot_2 > -1e-8;

        if (sign_0 == sign_1 && sign_1 == sign_2)
        {
            return distance;
        }
        else
        {
            return -1; // No intersection
        }
    }
}
