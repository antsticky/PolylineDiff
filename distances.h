#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include <cmath>
#include <cassert>

#include "structs.h"
#include "linalg.h"
#include "misc.h"

float distanceBetweenTwoPoint2D(const sPoint2D P1, const sPoint2D P2)
{
    float work1 = pow(P2.x - P1.x, 2.0);
    float work2 = pow(P2.y - P1.y, 2.0);
    return sqrt(work1 + work2);
}

// https://www.randygaul.net/2014/07/23/distance-point-to-line-segment/
float distanceBetweenPointSegment2D(const sPoint2D P, const std::vector<sPoint2D> Segment)
{
    assert(Segment.size() == 2);

    sPoint2D n = PointDiff2D(Segment[0], Segment[1]);
    sPoint2D pa = PointDiff2D(P, Segment[0]);
    sPoint2D pb = PointDiff2D(Segment[1], P);

    float c = DotProduct2D(n, pa);

    // Closest point is the start of the segment
    if (c > 0.0f)
        return sqrt(DotProduct2D(pa, pa));

    // Closest point is the end of the segment
    if (DotProduct2D(n, pb) > 0.0f)
        return sqrt(DotProduct2D(pb, pb));

    // Closest point on the segment
    float norm_n = (c / DotProduct2D(n, n));
    sPoint2D n_normed = sPoint2D(n.x * norm_n, n.y * norm_n);
    sPoint2D e = PointDiff2D(n_normed, pa);

    return sqrt(DotProduct2D(e, e));
}

float distanceBetweenTwoSegment2D(const std::vector<sPoint2D> Segment1, const std::vector<sPoint2D> Segment2)
{
    assert(Segment1.size() == 2);
    assert(Segment2.size() == 2);

    float dist1 = distanceBetweenPointSegment2D(Segment1[0], Segment2);
    float dist2 = distanceBetweenPointSegment2D(Segment1[1], Segment2);

    return fmin(dist1, dist2);
}

// https://gamedev.stackexchange.com/questions/154036/efficient-minimum-distance-between-two-axis-aligned-squares
float minimalDistanceOfTwoAABB(const std::vector<sPoint2D> Box1, const std::vector<sPoint2D> Box2)
{
    assert(Box1.size() == 2);
    assert(Box2.size() == 2);

    float x_corrds[4] = {Box1[0].x,
                         Box1[1].x,
                         Box2[0].x,
                         Box2[1].x};

    float y_corrds[4] = {Box1[0].y,
                         Box1[1].y,
                         Box2[0].y,
                         Box2[1].y};

    float x_min = minimum(x_corrds);
    float y_min = minimum(y_corrds);

    float x_max = maximum(x_corrds);
    float y_max = maximum(y_corrds);

    float inner_width = (x_max - x_min) - abs(Box1[1].x - Box1[0].x) - abs(Box2[1].x - Box2[0].x);
    float inner_height = (y_max - y_min) - abs(Box1[1].y - Box1[0].y) - abs(Box2[1].y - Box2[0].y);

    inner_width = fmax(inner_width, 0);
    inner_height = fmax(inner_height, 0);

    return sqrt(pow(inner_width, 2) + pow(inner_height, 2));
}

float distanceBetweenSegmentPolyline2D(const std::vector<sPoint2D> Segment, const std::vector<sPoint2D> Polyline)
{
    assert(Segment.size() == 2);

    if (Polyline.size() == 2)
        return distanceBetweenTwoSegment2D(Segment, Polyline);

    float min_distance = std::numeric_limits<float>::max();
    for (int i = 0; i < Polyline.size() - 1; i++)
    {

        std::vector<sPoint2D> Segment_i{Polyline[i], Polyline[i + 1]};
        float distance_i = distanceBetweenTwoSegment2D(Segment, Segment_i);

        if (distance_i < min_distance)
            min_distance = distance_i;
    }

    return min_distance;
}

#endif