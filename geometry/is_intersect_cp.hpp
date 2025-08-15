#include "base.hpp"
#include "circle.hpp"
#include "point.hpp"

namespace geometry {
bool is_intersect_cp(const Circle& c, const Point& p) {
  return equals(abs(p - c.p) - c.r, 0);
}
}  // namespace geometry
