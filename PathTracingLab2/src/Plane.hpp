#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include <bits/stdc++.h>
#include "Json.hpp"

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"

struct Plane
{
    Point3D p;
    Vector3D normal;
    Material material;

    Plane() : p(Vector3D(0, 0, 0)), normal(Vector3D(1, 0, 0)), material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Plane(Point3D p, Vector3D normal) : p(p), normal(normal), material(Material(MATERIAL_STD_DIFFUSE))
    {
        return;
    }

    Plane(Point3D p, Vector3D normal, Material material) : p(p), normal(normal), material(material)
    {
        return;
    }

    Plane(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    friend double GetIntersectionDistance(const Plane &plane, const Ray &ray);

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("p", p.ToJsonObject());
        jsonobj.Add("normal", normal.ToJsonObject());
        jsonobj.Add("material", material.ToJsonObject());
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_p, jsonobj_normal, jsonobj_material;
        jsonobj.Get("p", jsonobj_p);
        jsonobj.Get("normal", jsonobj_normal);
        jsonobj.Get("material", jsonobj_material);
        p.FromJsonObject(jsonobj_p);
        normal.FromJsonObject(jsonobj_normal);
        material.FromJsonObject(jsonobj_material);
    }

    friend Plane PlaneFromJsonObject(const cjsonobj::CJsonObject &jsonobj);
};

Plane PlaneFromJsonObject(const cjsonobj::CJsonObject &jsonobj)
{
    Plane ans;
    ans.FromJsonObject(jsonobj);
    return ans;
}

double GetIntersectionDistance(const Plane &plane, const Ray &ray)
{
    Vector3D n = plane.normal;
    Vector3D o = ray.origin;
    Vector3D d = ray.direction;
    Vector3D p = plane.p;
    double x = Dot(n, p) - Dot(n, o);
    double y = Dot(n, d);
    if (abs(y) < 1e-8)
        return -1; // No intersection
    return x / y;
}

#endif