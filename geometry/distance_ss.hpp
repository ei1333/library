#include "segment.hpp"
#include "is_intersect_ss.hpp"
#include "distance_sp.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
  Real distance_ss(const Segment &a, const Segment &b) {
    if(is_intersect_ss(a, b)) return 0;
    return min({distance_sp(a, b.a), distance_sp(a, b.b), distance_sp(b, a.a), distance_sp(b, a.b)});
  }
}

