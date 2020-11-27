#include "point.cpp"

namespace geometry {
  Real distance(const Point &a, const Point &b) {
    return abs(a - b);
  }
}
