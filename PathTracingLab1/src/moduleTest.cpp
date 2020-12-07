#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Random.hpp"
#include "Timer.hpp"
#include "Image.hpp"

void ImageTest()
{
    Image image(512, 512);
    for (int i = 0; i < image.size_x; i++)
    {
        for (int j = 0; j < image.size_y; j++)
        {
            image.SetPixel(i, j, (j % 10) / 9.0);
        }
    }
    image.WriteToPPM("test.ppm");
}

int main()
{
    ImageTest();
}