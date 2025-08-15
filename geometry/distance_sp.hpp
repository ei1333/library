#include "is_intersect_sp.hpp"
#include "point.hpp"
#include "projection.hpp"
#include "segment.hpp"

namespace geometry {
Real distance_sp(const Segment& s, const Point& p) {
  Point r = projection(s, p);
  if (is_intersect_sp(s, r)) return abs(r - p);
  return min(abs(s.a - p), abs(s.b - p));
}
}  // namespace geometry
