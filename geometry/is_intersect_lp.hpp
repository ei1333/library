#include "ccw.hpp"
#include "line.hpp"
#include "point.hpp"

namespace geometry {
  bool is_intersect_lp(const Line &l, const Point &p) {
    return abs(ccw(l.a, l.b, p)) != 1;
  }
} // namespace geometry
