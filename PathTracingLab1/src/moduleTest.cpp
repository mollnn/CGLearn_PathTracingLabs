#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

void sphere_ray_intersection_test()
{
    Sphere sphere(Vector3D(0, 0, 0), 1);
    Ray ray(Vector3D(-2, 0, 0), Vector3D(1, 0, 0));
    Ray ray2(Vector3D(-3, 0, 0), Vector3D(1, 0, 0));
    Ray ray3(Vector3D(2, 0, 0), Vector3D(1, 0, 0));
    Ray ray4(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    std::cout << GetIntersectionDistance(sphere, ray) << std::endl;
    std::cout << GetIntersectionDistance(sphere, ray2) << std::endl;
    std::cout << GetIntersectionDistance(sphere, ray3) << std::endl;
    std::cout << GetIntersectionDistance(sphere, ray4) << std::endl;
}

void sphere_ray_intersection_test_2()
{
    Sphere sphere(Vector3D(-1, 0, 0), 2);
    Ray ray(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    Ray ray2(Vector3D(0, 0, 0), Vector3D(0, 1, 1).Unit());
    std::cout << GetIntersectionDistance(sphere, ray) << std::endl;
    std::cout << GetIntersectionDistance(sphere, ray2) << std::endl;
}

int main()
{
    sphere_ray_intersection_test();
    sphere_ray_intersection_test_2();
}