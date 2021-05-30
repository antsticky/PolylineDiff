# Minimal distance between two polylines

## Task
Given 2 [polylines](https://en.wikipedia.org/wiki/Polygonal_chain) as `std::vector` of points, the `arePolylinesCloserThanThreshold` in *distance.h* checks that if the
two polylines are closer to each other than a given distance threshold. It returns true if they are closer, and false if they are not. The distance threshold `DISTANCE_THRESHOLD` is set to 1.5F.

![Example](png/polylinedistance.png)


## Structure
Polylines are defined as
```cpp
std::vector<sPoint2D> polyline{sPoint2D(2.0F, 3.0F), sPoint2D(3.0F, 4.0F), sPoint2D(2.0F, 6.0F)};
```
a vector of 2D dimensional point structures
```cpp
struct sPoint2D
{
  sPoint2D(float xValue, float yValue)
  {
    x = xValue;
    y = yValue;
  }
  float x;
  float y;
};
```

### Folder structure
The root folder contains the *main.cpp* file with a minimal example, while the *headers* folder collects all the necessary functions, more precisely: 
- **misc.h**: general min and max functions
- **structs.h**: definition of sPoint2D
- **linalg.h**: basic vector operations between polyline segments
- **polyline.h**: basic, non-mathematical operations between polyline (e.g.: split, tensor product)
- **distance.h**: lists all the possible distances (e.g.: distance of two points, point-segment distance, distance of two segments)

## Algorithms
The task was solved by two different approach:
- **brute-force**: Calculates the distance for all segment pairs. If it found a smaller distance as the pre-defined treshold, then it breaks the iteration.
- **advanced**: In every step it splits the polylines and with a bounding box techniques checks that if the possible achievable distance is smaller then the pre-defined threshold. If the given distance is smaller, then for further process, it takes the polyline pair in the queue. If not then discards them. Each iteration stops when one of the iterational polyline is not a polyline (i.e. it is a segment) or the possible achievable distance is bigger than the aimed one.

## Runtime complexity
The **brute-force** algorithm scales with O(N<sup>2</sup>) since it calculates all the possible pairing. Furthermore, if there is no segment where they are within the threshold then it really calculates all the pairs. Remark, if there are multiple segments along the two polyine, where they are close enough, then the algorithm is still scales with O(N<sup>2</sup>). It only introduces a scaling by the average ratio of the "good" segments.

In the case of the **advanced** approach, in average, the complexity is O(N * log N), but in the worst case it still scales by O(N<sup>2</sup>). The algorithm could be slow if there are a lot of overlapping bounding boxes between the polylines. To understand this behaviour I played with polylines where their trend lines were *parallel* and *orthogonal* to each other. In both cases the points were selected with different probabilities, but the lines were generated differently, e.g. for orthogonal case:

```cpp
std::vector<sPoint2D> ntest1;
std::vector<sPoint2D> ntest2;
for (int i = 0; i < polyline_length_max; i++)
{
    r = ((double)rand() / (RAND_MAX));

    if (r < drop_1)
        ntest1.push_back(sPoint2D(x_running, r));

    if (r < drop_2)
        ntest2.push_back(sPoint2D(r + polyline_length_max - 1, y_running));

    x_running += 1.0;
    y_running += 1.0;
}
```


### Further improvement
In the **advanced** approach only the basic idea was implemented, but the code itself might not effective; it contains declaration beside for loops, there remained some unnecessary debugging calculations, not well structured which in some cases require unnecessary data transformations...

A further improved can be, if we totaly rid off the `sqrt` function. It is costly (compare to the basic arithmetrics). We can easily eliminate it from the code, since it only appears in the distance calculations. Thus, we can simply use the square distance and compare them to the square of the threshold level `DISTANCE_THRESHOLD`.

As a side note, if we really need the `sqrt` function then we could replace it with an approximation which is much faster, e.g. for `1/sqrt(x)` see [A Quake III Algorithm](https://www.youtube.com/watch?v=p8u_k2LIZyo&t=957s).

## Links
- [**Randy Gaul's Game Programming Blog**: Distance Point to Line Segment](https://www.randygaul.net/2014/07/23/distance-point-to-line-segment/)
- [**GameDev**: Efficient minimum distance between two axis aligned squares?](https://gamedev.stackexchange.com/questions/154036/efficient-minimum-distance-between-two-axis-aligned-squares)
- [**StackOverflow**: Distance between two polylines](https://stackoverflow.com/questions/45861488/distance-between-two-polylines)