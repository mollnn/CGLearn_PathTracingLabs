#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "Json.hpp"

#include "Vector3D.hpp"

struct Camera
{
    Vector3D position;
    Vector3D direction;
    Vector3D up;

    double film_size_x = 0.036;
    double film_size_y = 0.024;
    double focus_distance = 0.001 * 24; // 相机焦距

    Camera(Vector3D position, Vector3D direction, Vector3D up, double film_size_x = 0.036, double film_size_y = 0.024, double focus_distance = 0.001 * 24)
        : position(position), direction(direction), up(up), film_size_x(film_size_x), film_size_y(film_size_y), focus_distance(focus_distance)
    {
        return;
    }

    Camera(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    void CorrectByHorizontal(Vector3D horizon, bool is_up = 1)
    {
        up = Cross(direction, horizon);
        if ((up.z > 0) != is_up)
        {
            up = -up;
        }
        up = up.Unit();
    }

    void CorrectByVertical(Vector3D vertical)
    {
        up = vertical.Unit();
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("position", position.ToJsonObject());
        jsonobj.Add("direction", direction.ToJsonObject());
        jsonobj.Add("up", up.ToJsonObject());
        jsonobj.Add("film_size_x", film_size_x);
        jsonobj.Add("film_size_y", film_size_y);
        jsonobj.Add("focus_distance", focus_distance);
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        cjsonobj::CJsonObject jsonobj_position;
        cjsonobj::CJsonObject jsonobj_direction;
        cjsonobj::CJsonObject jsonobj_up;
        jsonobj.Get("position", jsonobj_position);
        jsonobj.Get("direction", jsonobj_direction);
        jsonobj.Get("up", jsonobj_up);
        jsonobj.Get("film_size_x", film_size_x);
        jsonobj.Get("film_size_y", film_size_y);
        jsonobj.Get("focus_distance", focus_distance);
        position.FromJsonObject(jsonobj_position);
        direction.FromJsonObject(jsonobj_direction);
        up.FromJsonObject(jsonobj_up);
    }
};

#endif