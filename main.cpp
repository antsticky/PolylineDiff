#include <iostream>

#include "structs.h"
#include "distances.h"
#include "polyline.h"

const float DISTANCE_THRESHOLD = 1.5F;

bool arePolylinesCloserThanThreshold(std::vector<sPoint2D> &polyline1,
                                     std::vector<sPoint2D> &polyline2)
{
  bool closerThanThreshold = false;

  float distance_i = distanceBetweenPolyline2D(polyline1, polyline2);
  float distance_ip1 = -std::numeric_limits<float>::max();

  if (distance_i > DISTANCE_THRESHOLD)
  {
    std::cout << "They are not closer than "
              << distance_i
              << " for each other\n";

    return closerThanThreshold;
  }

  int optIndex = -1;
  float optDistance = -1.0;
  bool inIteration = true;
  while (inIteration)
  {

    std::array<std::array<std::vector<sPoint2D>, 2>, 4> myTensor = tensorPolyline(polyline1, polyline2);
    getOptimalTensorIndexAndDistance(myTensor, optIndex, optDistance);

    distance_i = distance_ip1;
    distance_ip1 = optDistance;

    if (polyline1.size() == 2 || polyline2.size() == 2 || distance_ip1 >= distance_i)
      inIteration = false;

    if (distance_ip1 < DISTANCE_THRESHOLD)
    {
      closerThanThreshold = true;
      inIteration = false;
    }

    polyline1 = myTensor[optIndex][0];
    polyline2 = myTensor[optIndex][1];
  }

  std::cout << "They are at least "
            << distance_ip1
            << " close to each other\n";

  return closerThanThreshold;
}

int main()
{
  std::vector<sPoint2D> polyline1{sPoint2D(2.0F, 3.0F), sPoint2D(3.0F, 4.0F),
                                  sPoint2D(2.0F, 6.0F)};
  std::vector<sPoint2D> polyline2{sPoint2D(5.0F, 6.0F), sPoint2D(5.0F, 4.0F),
                                  sPoint2D(7.0F, 4.0F), sPoint2D(7.0F, 2.0F)};

  bool isCloser = arePolylinesCloserThanThreshold(polyline1, polyline2);
  std::cout << "closerThanThreshold = " << std::boolalpha << isCloser << " (threshold = " << DISTANCE_THRESHOLD << ")\n";

  return 0;
}