#include <iostream>
#include <vector>

#include "structs.h"
#include "distances.h"
#include "polyline.h"

bool arePolylinesCloserThanThreshold(std::vector<sPoint2D> &polyline1,
                                     std::vector<sPoint2D> &polyline2)
{
  bool closerThanThreshold = false;
  // Implement your code here (C++11)!
  // ...
  return closerThanThreshold;
}

int main()
{
  std::vector<sPoint2D> polyline1{sPoint2D(2.0F, 3.0F), sPoint2D(3.0F, 4.0F),
                                  sPoint2D(2.0F, 6.0F)};
  std::vector<sPoint2D> polyline2{sPoint2D(5.0F, 6.0F), sPoint2D(5.0F, 4.0F),
                                  sPoint2D(7.0F, 4.0F), sPoint2D(7.0F, 2.0F)};

  std::vector<sPoint2D> polyline3{sPoint2D(5.0F, 6.0F), sPoint2D(5.0F, 4.0F),
                                  sPoint2D(7.0F, 4.0F), sPoint2D(7.0F, 2.0F), sPoint2D(8.0F, 1.0F)};

  std::vector<sPoint2D> segment1{sPoint2D(5.0F, 7.0F), sPoint2D(8.0F, 2.0F)};
  sPoint2D P1 = sPoint2D(-1.0F, 6.0F);

  float generalDist = distanceBetweenPolyline2D(polyline1, polyline3);

  return 0;
}