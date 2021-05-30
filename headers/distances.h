#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include <cmath>
#include <cassert>
#include <iostream>

#include "structs.h"
#include "linalg.h"
#include "misc.h"
#include "polyline.h"

const float DISTANCE_THRESHOLD = 1.5F;

float distanceBetweenTwoPoint2D(const sPoint2D P1, const sPoint2D P2)
{
    float work1 = pow(P2.x - P1.x, 2.0);
    float work2 = pow(P2.y - P1.y, 2.0);
    return sqrt(work1 + work2);
}

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

    float dist11 = distanceBetweenPointSegment2D(Segment1[0], Segment2);
    float dist12 = distanceBetweenPointSegment2D(Segment1[1], Segment2);
    float min_1 = fmin(dist11, dist12);

    float dist21 = distanceBetweenPointSegment2D(Segment2[0], Segment1);
    float dist22 = distanceBetweenPointSegment2D(Segment2[1], Segment1);
    float min_2 = fmin(dist21, dist22);

    return fmin(min_1, min_2);
}

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

float distanceBetweenPolyline2D(const std::vector<sPoint2D> Polyline1, const std::vector<sPoint2D> Polyline2)
{
    if (Polyline1.size() == 2 && Polyline2.size() == 2)
        return distanceBetweenTwoSegment2D(Polyline1, Polyline2);

    if (Polyline1.size() == 2 && Polyline2.size() > 2)
        return distanceBetweenSegmentPolyline2D(Polyline1, Polyline2);

    if (Polyline1.size() > 2 && Polyline2.size() == 2)
        return distanceBetweenSegmentPolyline2D(Polyline2, Polyline1);

    std::vector<sPoint2D> BBox1 = getBBox(Polyline1);
    std::vector<sPoint2D> BBox2 = getBBox(Polyline2);

    return minimalDistanceOfTwoAABB(BBox1, BBox2);
}

void getOptimalTensorIndexAndDistance(std::array<std::array<std::vector<sPoint2D>, 2>, 4> Tensor, int &optIndex, float &optDistance)
{
    int optimalIndex = -1;
    float minDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < Tensor.size(); i++)
    {
        float distance_i = distanceBetweenPolyline2D(Tensor[i][0], Tensor[i][1]);
        if (minDistance > distance_i)
        {
            minDistance = distance_i;
            optimalIndex = i;
        }
    }
    optIndex = optimalIndex;
    optDistance = minDistance;
}

bool arePolylinesCloserThanThresholdBruteforce(std::vector<sPoint2D> &polyline1, std::vector<sPoint2D> &polyline2)
{
    bool closerThanThreshold = false;

    for (int i = 0; i < polyline1.size() - 1; i++)
    {
        std::vector<sPoint2D> segment_i{polyline1[i], polyline1[i + 1]};
        float distance_i = distanceBetweenSegmentPolyline2D(segment_i, polyline2);

        if (distance_i < DISTANCE_THRESHOLD)
        {
            closerThanThreshold = true;
            return closerThanThreshold;
        }
    }

    return closerThanThreshold;
}

bool arePolylinesCloserThanThreshold(std::vector<sPoint2D> &polyline1, std::vector<sPoint2D> &polyline2)
{
    bool closerThanThreshold = false;

    float min_distance = distanceBetweenPolyline2D(polyline1, polyline2);
    if (min_distance > DISTANCE_THRESHOLD)
        return closerThanThreshold;

    min_distance = std::numeric_limits<float>::max();
    std::vector<std::array<std::vector<sPoint2D>, 2>> Queue;
    std::array<std::array<std::vector<sPoint2D>, 2>, 4> Tensor = tensorPolyline(polyline1, polyline2);
    Queue.push_back(Tensor[0]);
    Queue.push_back(Tensor[1]);
    Queue.push_back(Tensor[2]);
    Queue.push_back(Tensor[3]);

    std::vector<sPoint2D> polyline_i;
    std::vector<sPoint2D> polyline_j;
    float distance_i;
    while (!Queue.empty())
    {
        polyline_i = Queue[Queue.size() - 1][0];
        polyline_j = Queue[Queue.size() - 1][1];

        distance_i = distanceBetweenPolyline2D(polyline_i, polyline_j);

        if (distance_i < min_distance && (polyline_i.size() == 2 or polyline_j.size() == 2))
            min_distance = distance_i;

        if (min_distance < DISTANCE_THRESHOLD)
        {
            std::cout << "They are at least " << min_distance << " close to each other\n";

            closerThanThreshold = true;
            return closerThanThreshold;
        }

        if (distance_i < DISTANCE_THRESHOLD)
        {
            Tensor = tensorPolyline(polyline_i, polyline_j);
            Queue.push_back(Tensor[0]);
            Queue.push_back(Tensor[1]);
            Queue.push_back(Tensor[2]);
            Queue.push_back(Tensor[3]);
        }

        Queue.pop_back();
    }

    std::cout << "They are at least " << min_distance << " from each other\n";

    return closerThanThreshold;
}

#endif