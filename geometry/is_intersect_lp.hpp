#include "point.cpp"
#include "line.cpp"
#include "ccw.cpp"

namespace geometry {
  bool is_intersect_lp(const Line &l, const Point &p) {
    return abs(ccw(l.a, l.b, p)) != 1;
  }
}
