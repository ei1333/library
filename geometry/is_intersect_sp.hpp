#include "point.cpp"
#include "segment.cpp"
#include "ccw.cpp"

namespace geometry {
  bool is_intersect_sp(const Segment &s, const Point &p) {
    return ccw(s.a, s.b, p) == ON_SEGMENT;
  }
}
