#ifndef _SAMPLER_HPP_
#define _SAMPLER_HPP_

#include <bits/stdc++.h>
#include "Random.hpp"

struct Sample
{
    double film_x;
    double film_y;
    int image_x;
    int image_y;
    double weight;

    Sample(double film_x, double film_y, int image_x, int image_y, double weight)
        : film_x(film_x), film_y(film_y), image_x(image_x), image_y(image_y), weight(weight)
    {
        return;
    }
};

struct Sampler
{
    std::vector<Sample> samples;

    int image_size_x;
    int image_size_y;
    int samples_per_pixel;

    Sampler(int image_x, int image_y, int samples_per_pixel)
        : image_size_x(image_x), image_size_y(image_y), samples_per_pixel(samples_per_pixel)
    {
        return;
    }

    void MakeSamples()
    {
        samples.clear();

        for (int image_x = 0; image_x < image_size_x; image_x++)
        {
            for (int image_y = 0; image_y < image_size_y; image_y++)
            {
                double film_x_min = 1.0 * image_x / image_size_x;
                double film_x_max = 1.0 * (image_x + 1) / image_size_x;
                double film_y_min = 1.0 * image_y / image_size_y;
                double film_y_max = 1.0 * (image_y + 1) / image_size_y;
                for (int i = 0; i < samples_per_pixel; i++)
                {
                    double film_x = RandBetween(film_x_min, film_x_max);
                    double film_y = RandBetween(film_y_min, film_y_max);
                    samples.push_back(Sample(film_x, film_y, image_x, image_y, 1.0 / samples_per_pixel));
                }
            }
        }
    }
};

#endif