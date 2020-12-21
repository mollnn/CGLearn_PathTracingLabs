#ifndef _SAMPLE_HPP_
#define _SAMPLE_HPP_

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

#endif