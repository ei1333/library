#include "ccw.hpp"
#include "point.hpp"
#include "segment.hpp"

namespace geometry {
bool is_intersect_sp(const Segment &s, const Point &p) {
  return ccw(s.a, s.b, p) == ON_SEGMENT;
}
}  // namespace geometry
