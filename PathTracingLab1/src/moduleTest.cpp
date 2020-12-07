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
    Image image(512,512);
    system("pause");
    image.GenerateTestImage();
    system("pause");
    image.WriteToPPM("test.ppm");
}

int main()
{
    ImageTest();
}