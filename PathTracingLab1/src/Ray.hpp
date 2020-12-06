#ifndef _RAY_HPP_
#define _RAY_HPP_

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "Vector3D.hpp"

struct Ray
{
    Vector3D origin;
    Vector3D direction;

    Ray() : origin(Vector3D(0, 0, 0)), direction(Vector3D(0, 0, 0))
    {
        return;
    }

    Ray(Vector3D origin, Vector3D direction) : origin(origin), direction(direction)
    {
        return;
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("origin", origin.ToJsonObject());
        jsonobj.Add("direction", direction.ToJsonObject());
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_origin;
        cjsonobj::CJsonObject jsonobj_direction;
        jsonobj.Get("origin", jsonobj_origin);
        jsonobj.Get("direction", jsonobj_direction);
        origin.FromJsonObject(jsonobj_origin);
        direction.FromJsonObject(jsonobj_direction);
    }

    friend Ray RayFromJsonObject(const cjsonobj::CJsonObject &jsonobj);
};

Ray RayFromJsonObject(const cjsonobj::CJsonObject &jsonobj)
{
    Ray ans;
    ans.FromJsonObject(jsonobj);
    return ans;
}

#endif