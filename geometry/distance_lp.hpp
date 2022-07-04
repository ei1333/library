#include "line.cpp"
#include "projection.cpp"

namespace geometry {
  Real distance_lp(const Line &l, const Point &p) {
    return abs(p - projection(l, p));
  }
}
