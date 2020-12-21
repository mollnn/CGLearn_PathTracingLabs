#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <bits/stdc++.h>
#include "Json.hpp"

#include "Triangle.hpp"

struct Scene
{
    std::vector<Triangle> triangle_array;

    Scene()
    {
        return;
    }

    Scene(const Scene &scene)
    {
        for (auto i : scene.triangle_array)
        {
            triangle_array.push_back(i);
        }
    }

    Scene(const Triangle &triangle)
    {
        triangle_array.push_back(triangle);
    }

    Scene(cjsonobj::CJsonObject jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    int Size() const
    {
        return triangle_array.size();
    }

    Triangle &operator[](int id) 
    {
        return triangle_array[id];
    }

    const Triangle &operator[](int id) const
    {
        return triangle_array[id];
    }

    void Push(const Triangle &sphere)
    {
        triangle_array.push_back(sphere);
    }

    void Pop()
    {
        triangle_array.pop_back();
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        for (auto &i : triangle_array)
        {
            jsonobj.Add(i.ToJsonObject());
        }
        return jsonobj;
    }

    void FromJsonObject(cjsonobj::CJsonObject &jsonobj)
    {
        int size = jsonobj.GetArraySize();
        triangle_array.clear();
        for (int i = 0; i < size; i++)
        {
            cjsonobj::CJsonObject jsonobj_triangle;
            jsonobj.Get(i, jsonobj_triangle);
            triangle_array.push_back(TriangleFromJsonObject(jsonobj_triangle));
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
