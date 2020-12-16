#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "Vector3D.hpp"

struct Camera
{
    Vector3D position;
    Vector3D direction;
    Vector3D up;

    Camera(Vector3D position, Vector3D direction, Vector3D up) : position(position), direction(direction), up(up)
    {
        return;
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
};

#endif