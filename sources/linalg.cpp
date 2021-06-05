#include "structs.h"

float DotProduct2D(const sPoint2D P1, const sPoint2D P2)
{
    return P1.x * P2.x + P1.y * P2.y;
}

sPoint2D PointDiff2D(const sPoint2D P1, const sPoint2D P2)
{
    return sPoint2D(P2.x - P1.x, P2.y - P1.y);
}