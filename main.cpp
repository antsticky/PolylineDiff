#include <iostream>
#include <chrono>

#include "headers/structs.h"
#include "headers/distances.h"

int main()
{
  std::vector<sPoint2D> polyline1{sPoint2D(2.0F, 3.0F), sPoint2D(3.0F, 4.0F),
                                  sPoint2D(2.0F, 6.0F)};
  std::vector<sPoint2D> polyline2{sPoint2D(5.0F, 6.0F), sPoint2D(5.0F, 4.0F),
                                  sPoint2D(7.0F, 4.0F), sPoint2D(7.0F, 2.0F)};

  bool isCloserBruteforce = arePolylinesCloserThanThresholdBruteforce(polyline1, polyline2);
  std::cout << "closerThanThreshold = " << std::boolalpha << isCloserBruteforce << " (threshold = " << DISTANCE_THRESHOLD << ")\n";

  bool isCloser = arePolylinesCloserThanThreshold(polyline1, polyline2);
  std::cout << "closerThanThreshold = " << std::boolalpha << isCloser << " (threshold = " << DISTANCE_THRESHOLD << ")\n";

  return 0;
}
