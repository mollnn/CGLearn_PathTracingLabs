#ifndef _COLORSPACE_HPP_
#define _COLORSPACE_HPP_

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"

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

#endif