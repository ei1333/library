#include "base.cpp"
#include "line.cpp"
#include "circle.cpp"
#include "distance_lp.cpp"

namespace geometry {
  bool is_intersect_cl(const Circle &c, const Line &l) {
    return sign(c.r - distance_lp(l, c.p)) >= 0;
  }
}
