#include <array>
#include <vector>

#include "structs.h"

std::vector<sPoint2D> getBBox(std::vector<sPoint2D> Polyline)
{
    float x1_min = std::numeric_limits<float>::max();
    float y1_min = std::numeric_limits<float>::max();
    float x1_max = std::numeric_limits<float>::min();
    float y1_max = std::numeric_limits<float>::min();
    for (int i = 0; i < Polyline.size(); i++)
    {
        if (Polyline[i].x < x1_min)
            x1_min = Polyline[i].x;

        if (Polyline[i].y < y1_min)
            y1_min = Polyline[i].y;

        if (Polyline[i].x > x1_max)
            x1_max = Polyline[i].x;

        if (Polyline[i].y > y1_max)
            y1_max = Polyline[i].y;
    }

    std::vector<sPoint2D> BBox1{sPoint2D(x1_min, y1_min), sPoint2D(x1_max, y1_max)};
    return BBox1;
}

std::array<std::vector<sPoint2D>, 2> splitPolyline(std::vector<sPoint2D> polyline)
{
    int mySize = polyline.size();

    std::vector<sPoint2D> polyline1(polyline.begin(), polyline.begin() + mySize / 2);
    std::vector<sPoint2D> polyline2(polyline.begin() + mySize / 2, polyline.end());

    std::array<std::vector<sPoint2D>, 2> arr2 = {polyline1, polyline2};
    return arr2;
}

std::array<std::array<std::vector<sPoint2D>, 2>, 4> tensorPolyline(std::vector<sPoint2D> polyline1, std::vector<sPoint2D> polyline2)
{
    std::array<std::array<std::vector<sPoint2D>, 2>, 4> result;

    std::array<std::vector<sPoint2D>, 2> split1 = splitPolyline(polyline1);
    std::array<std::vector<sPoint2D>, 2> split2 = splitPolyline(polyline2);

    result[0] = {split1[0], split2[0]};
    result[1] = {split1[1], split2[1]};
    result[2] = {split1[0], split2[1]};
    result[3] = {split1[1], split2[0]};

    return result;
}