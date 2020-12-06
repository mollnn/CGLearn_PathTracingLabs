#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "Sphere.hpp"

struct Scene
{
    std::vector<Sphere> sphere_array;

    Scene()
    {
        return;
    }

    Scene(const Scene &scene)
    {
        for (auto i : scene.sphere_array)
        {
            sphere_array.push_back(i);
        }
    }

    Scene(const Sphere &sphere)
    {
        sphere_array.push_back(sphere);
    }

    int Size()
    {
        return sphere_array.size();
    }

    Sphere &operator[](int id)
    {
        return sphere_array[id];
    }

    void Push(const Sphere &sphere)
    {
        sphere_array.push_back(sphere);
    }

    void Pop()
    {
        sphere_array.pop_back();
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        for (auto &i : sphere_array)
        {
            jsonobj.Add(i.ToJsonObject());
        }
        return jsonobj;
    }

    void FromJsonObject(cjsonobj::CJsonObject &jsonobj)
    {
        int size = jsonobj.GetArraySize();
        sphere_array.clear();
        for (int i = 0; i < size; i++)
        {
            cjsonobj::CJsonObject jsonobj_sphere;
            jsonobj.Get(i, jsonobj_sphere);
            sphere_array.push_back(SphereFromJsonObject(jsonobj_sphere));
        }
    }

    friend Scene SceneFromJsonObject(cjsonobj::CJsonObject &jsonobj);
};

Scene SceneFromJsonObject(cjsonobj::CJsonObject &jsonobj)
{
    Scene scene;
    scene.FromJsonObject(jsonobj);
    return scene;
}

#endif
