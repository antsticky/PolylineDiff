#ifndef MISC_HPP_INCLUDED
#define MISC_HPP_INCLUDED

#include <iostream>
#include <limits>

template <size_t S>
float minimum(float (&a)[S])
{
    float myMin = std::numeric_limits<float>::max();

    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        if (a[i] < myMin)
            myMin = a[i];
    }
    return myMin;
}

template <size_t S>
float maximum(float (&a)[S])
{
    float myMax = std::numeric_limits<float>::min();

    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        if (a[i] > myMax)
            myMax = a[i];
    }
    return myMax;
}

#endif