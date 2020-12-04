#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_



#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"

struct Sphere 
{
    Vector3D center;
    double radius;
    Material material;


    // () <-

    // 设交点为 p
    // (p - center) * (p - center) = radius * radius
    // 设射线为 p = origin + t * direction
    // (origin + t*direction - center) * (origin + t*direction - center) = radius * radius
    // 设 delta = origin - center
    // (delta + t*direction) * (delta + t*direction) = radius * radius
    // delta*delta + 2*delta*direction * t + direction*direction * t^2 = radius * radius
    // (direction*direction) * t^2 + 2*delta*direction * t + delta*delta-radius*radius = 0
    
};


#endif