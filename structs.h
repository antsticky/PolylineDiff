#ifndef STRUCT_HPP_INCLUDED
#define STRUCT_HPP_INCLUDED

#include <iostream>
#include <vector>

struct sPoint2D
{
    sPoint2D(float xValue, float yValue)
    {
        x = xValue;
        y = yValue;
    }
    float x;
    float y;
};

#endif