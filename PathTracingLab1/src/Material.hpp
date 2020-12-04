#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"

// 默认材质种类
#define MATERIAL_BITMASK_DIFFUSE 1
#define MATERIAL_BITMASK_SPECULAR 2
#define MATERIAL_BITMASK_REFRECTION 4
#define MATERIAL_BITMASK_EMISSION 8

#define MATERIAL_STD_ABSORB 0
#define MATERIAL_STD_DIFFUSE 1
#define MATERIAL_STD_SPECULAR 2
#define MATERIAL_STD_DIFFUSESPECULAR 3
#define MATERIAL_STD_REFRECTION 4
#define MATERIAL_STD_DIFFUSEREFRECTION 5
#define MATERIAL_STD_SPECULARREFRECTION 6
#define MATERIAL_STD_DIFFUSESPECULARREFRECTION 7
#define MATERIAL_EMISSION_ABSORB 8
#define MATERIAL_EMISSION_DIFFUSE 9
#define MATERIAL_EMISSION_SPECULAR 10
#define MATERIAL_EMISSION_DIFFUSESPECULAR 11
#define MATERIAL_EMISSION_REFRECTION 12
#define MATERIAL_EMISSION_DIFFUSEREFRECTION 13
#define MATERIAL_EMISSION_SPECULARREFRECTION 14
#define MATERIAL_EMISSION_DIFFUSESPECULARREFRECTION 15

struct Material
{
    double diffuse;       // 漫反射强度
    double specular;      // 高光反射强度
    double refrection;    // 折射强度
    double emission;      // 自发光强度
    double refrect_index; // 折射率

    Material(int std_material_id = MATERIAL_STD_DIFFUSE)
    {
        diffuse = 0;
        specular = 0;
        refrection = 0;
        emission = 0;
        refrect_index = 1.5;

        if (std_material_id & MATERIAL_BITMASK_DIFFUSE)
            diffuse += 1.0;
        if (std_material_id & MATERIAL_BITMASK_SPECULAR)
            specular += 1.0;
        if (std_material_id & MATERIAL_BITMASK_REFRECTION)
            refrection += 1.0;
        if (std_material_id & MATERIAL_BITMASK_EMISSION)
            emission += 1.0;

        double intensity_sum = 0;
        intensity_sum += diffuse;
        intensity_sum += specular;
        intensity_sum += refrection;

        diffuse /= intensity_sum;
        specular /= intensity_sum;
        refrection /= intensity_sum;
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("diffuse", diffuse);
        jsonobj.Add("specular", specular);
        jsonobj.Add("refrection", refrection);
        jsonobj.Add("emission", emission);
        jsonobj.Add("refrect_index", refrect_index);
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        jsonobj.Get("diffuse", diffuse);
        jsonobj.Get("specular", specular);
        jsonobj.Get("refrection", refrection);
        jsonobj.Get("emission", emission);
        jsonobj.Get("refrect_index", refrect_index);
    }

    friend Material MaterialFromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        Material ans;
        ans.FromJsonObject(jsonobj);
        return ans;
    }
};

#endif