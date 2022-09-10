#include "point.hpp"
#include "line.hpp"
#include "ccw.hpp"

namespace geometry {
  bool is_intersect_lp(const Line &l, const Point &p) {
    return abs(ccw(l.a, l.b, p)) != 1;
  }
}
