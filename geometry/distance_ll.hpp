#include "distance_lp.hpp"
#include "is_intersect_ll.hpp"
#include "line.hpp"

namespace geometry {
Real distance_ll(const Line &l, const Line &m) {
  return is_intersect_ll(l, m) ? 0 : distance_lp(l, m.a);
}
}  // namespace geometry
