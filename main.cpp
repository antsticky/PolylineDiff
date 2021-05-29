#include <iostream>
#include <vector>
#include <tuple>

#include "structs.h"
#include "distances.h"
#include "polyline.h"

const float DISTANCE_THRESHOLD = 1.5F;

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
  std::vector<sPoint2D> polyline1{sPoint2D(1.0F, 5.0F), sPoint2D(1.0F, 2.0F),
                                  sPoint2D(7.0F, 1.0F)};
  std::vector<sPoint2D> polyline2{sPoint2D(5.0F, 6.0F), sPoint2D(5.0F, 4.0F),
                                  sPoint2D(7.0F, 4.0F), sPoint2D(7.0F, 2.0F)};

  std::vector<sPoint2D> polyline3{sPoint2D(6.0F, 8.0F), sPoint2D(5.0F, 7.0F),
                                  sPoint2D(8.0F, 2.0F), sPoint2D(9.0F, 2.0F), sPoint2D(9.0F, 5.0F)};

  std::vector<sPoint2D> segment1{sPoint2D(5.0F, 7.0F), sPoint2D(8.0F, 2.0F)};
  sPoint2D P1 = sPoint2D(-1.0F, 6.0F);

  std::array<std::array<std::vector<sPoint2D>, 2>, 4> myTensor = tensorPolyline(polyline1, polyline3);

  int optIndex;
  float optDistance;
  getOptimalTensorIndexAndDistance(myTensor, optIndex, optDistance);
  polyline1 = myTensor[optIndex][0];
  polyline2 = myTensor[optIndex][1];

  return 0;
}