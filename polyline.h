#ifndef POLYLINE_ARITHM_INCLUDED
#define POLYLINE_ARITHM_INCLUDED

#include <array>
#include "structs.h"

std::array<std::vector<sPoint2D>, 2> splitPolyline(std::vector<sPoint2D> polyline)
{
    int mySize = polyline.size();

    std::vector<sPoint2D> polyline1(polyline.begin(), polyline.begin() + mySize / 2);
    std::vector<sPoint2D> polyline2(polyline.begin() + mySize / 2, polyline.end());

    std::array<std::vector<sPoint2D>, 2> arr2 = {polyline1, polyline2};
    return arr2;
}

#endif