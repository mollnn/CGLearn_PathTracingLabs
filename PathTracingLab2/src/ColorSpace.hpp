#ifndef _COLORSPACE_HPP_
#define _COLORSPACE_HPP_

#include <bits/stdc++.h>
#include "Vector3D.hpp"
#include "Json.hpp"

double Clamp(double x)
{
    x = std::min(x, 1.0);
    x = std::max(x, 0.0);
    return x;
}

double IntensityToBrightness(double x, double gamma = 2.2)
{
    return pow(x, 1.0 / gamma);
}

Radiance3 Clamp(Radiance3 x)
{
    return {Clamp(x.x), Clamp(x.y), Clamp(x.z)};
}

Radiance3 IntensityToBrightness(Radiance3 x, double gamma = 2.2)
{
    return {IntensityToBrightness(x.x, gamma), IntensityToBrightness(x.y, gamma), IntensityToBrightness(x.z, gamma)};
}

#endif