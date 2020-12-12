#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"
#include "ColorSpace.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "PathTracer.hpp"
#include "Random.hpp"
#include "Ray.hpp"
#include "Sampler.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Timer.hpp"
#include "Vector3D.hpp"

using namespace std;

int main()
{
    // Make Scene
    Sphere sphere_light(Point3D(0, 0, 3), 1, MATERIAL_EMISSION_ABSORB);
    Sphere sphere_obj(Point3D(0, 0, 0), 1, MATERIAL_STD_DIFFUSE);
    Scene scene;
    scene.Push(sphere_light);
    scene.Push(sphere_obj);

    // Set Camera
    Camera camera(Point3D(3, 0, 0), Vector3D(-1, 0, 0));
    Vector3D film_unit_i(0, 1, 0);
    Vector3D film_unit_j(0, 0, -1);
    double focus_distance = 1.0;

    // Gen image
    int image_size_x = 256;
    int image_size_y = 256;
    Image image(image_size_x, image_size_y);

    // Gen samples
    Sampler sampler(image_size_x, image_size_y, 128);
    sampler.MakeSamples();

    // Samples to Rays
    int progress_count = 0;
    Timer timer;
    for (auto sample : sampler.samples)
    {
        // cout << sample.image_x << " " << sample.image_y << " " << sample.film_x << " " << sample.film_y << " " << sample.weight << endl;
        Vector3D vec = focus_distance * camera.direction + (sample.film_x - 0.5) * film_unit_i + (sample.film_y - 0.5) * film_unit_j;
        Point3D origin = camera.origin + vec;
        Vector3D direction = vec.Unit();
        Ray ray(origin, direction);

        // cout << ray.ToJsonObject().ToString() << endl;
        double radiance = PathTracing(ray, 1, scene);
        image.IncPixel(sample.image_x, sample.image_y, radiance * sample.weight);

        ++progress_count;
        if (timer.Current() > 1.0)
        {
            cout << "Rendering... " << 1.0 * progress_count / sampler.samples.size() * 100 << "\%" << endl;
            timer.Start();
        }
    }

    image.WriteToPPM("test.ppm");
}