#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Random.hpp"
#include "Timer.hpp"
#include "Image.hpp"
#include "Sampler.hpp"

void SampleTest()
{
    Sampler sampler(10,10,2);

    sampler.MakeSamples();

    for(auto sample:sampler.samples)
    {
        using namespace std;
        cout<<sample.image_x<<" "<<sample.image_y<<" "<<sample.film_x<<" "<<sample.film_y<<" "<<sample.weight<<endl;
    }
}

int main()
{
    SampleTest();
    
}