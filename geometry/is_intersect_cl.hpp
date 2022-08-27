#include "base.hpp"
#include "circle.hpp"
#include "distance_lp.hpp"
#include "line.hpp"

namespace geometry {
  bool is_intersect_cl(const Circle &c, const Line &l) {
    return sign(c.r - distance_lp(l, c.p)) >= 0;
  }
} // namespace geometry
