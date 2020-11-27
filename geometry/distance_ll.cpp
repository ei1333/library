#include "line.cpp"
#include "is_intersect_ll.cpp"
#include "distance_lp.cpp"

namespace geometry {
  Real distance_ll(const Line &l, const Line &m) {
    return is_intersect_ll(l, m) ? 0 : distance_lp(l, m.a);
  }
}
