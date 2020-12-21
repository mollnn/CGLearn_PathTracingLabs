#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_

#include "Json.hpp"

struct Sensor
{
    int image_size_x;
    int image_size_y;
    int samples_per_pixel;

    Sensor(int image_size_x = 300, int image_size_y = 200, int samples_per_pixel = 32)
    {
        return;
    }

    Sensor(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("image_size_x", image_size_x);
        jsonobj.Add("image_size_y", image_size_y);
        jsonobj.Add("samples_per_pixel", samples_per_pixel);
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        jsonobj.Get("image_size_x", image_size_x);
        jsonobj.Get("image_size_y", image_size_y);
        jsonobj.Get("samples_per_pixel", samples_per_pixel);
    }
};

#endif
