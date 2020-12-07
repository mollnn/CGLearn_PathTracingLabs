#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Random.hpp"
#include "Timer.hpp"

void TimerTest()
{
    Timer timer;
    for (int i = 1; i <= 1e9; i++)
        i = i;
    std::cout << timer.End() << std::endl;
    timer.Print();
}

int main()
{
    TimerTest();
}