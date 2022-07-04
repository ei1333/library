#include "base.hpp"
#include "point.hpp"
#include "circle.hpp"

namespace geometry {
  bool is_intersect_cp(const Circle &c, const Point &p) {
    return equals(abs(p - c.p) - c.r, 0);
  }
}
