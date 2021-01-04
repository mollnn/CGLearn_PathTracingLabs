#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP

#include <bits/stdc++.h>
#include "Json.hpp"

struct Material
{
    Radiance3 diffuse;    // 漫反射强度
    Radiance3 specular;   // 高光反射强度
    Radiance3 refrection; // 折射强度
    Radiance3 emission;   // 自发光强度
    double refrect_index; // 折射率

    Material()
    {
        diffuse = Radiance3();
        specular = Radiance3();
        refrection = Radiance3();
        emission = Radiance3();
        refrect_index = 1.5;
    }

    Material(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("diffuse", diffuse.ToJsonObject());
        jsonobj.Add("specular", specular.ToJsonObject());
        jsonobj.Add("refrection", refrection.ToJsonObject());
        jsonobj.Add("emission", emission.ToJsonObject());
        jsonobj.Add("refrect_index", refrect_index);
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_tmp;

        jsonobj.Get("diffuse", jsonobj_tmp);
        diffuse.FromJsonObject(jsonobj_tmp);

        jsonobj.Get("specular", jsonobj_tmp);
        specular.FromJsonObject(jsonobj_tmp);

        jsonobj.Get("refrection", jsonobj_tmp);
        refrection.FromJsonObject(jsonobj_tmp);

        jsonobj.Get("emission", jsonobj_tmp);
        emission.FromJsonObject(jsonobj_tmp);

        jsonobj.Get("refrect_index", refrect_index);
    }
};

Material MaterialFromJsonObject(cjsonobj::CJsonObject jsonobj)
{
    Material ans;
    ans.FromJsonObject(jsonobj);
    return ans;
}

#endif