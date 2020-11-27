#include "base.cpp"
#include "point.cpp"
#include "circle.cpp"

namespace geometry {
  bool is_intersect_cp(const Circle &c, const Point &p) {
    return equals(abs(p - c.p) - c.r, 0);
  }
}
