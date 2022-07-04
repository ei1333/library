#include "segment.cpp"
#include "is_intersect_ss.cpp"
#include "distance_sp.cpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
  Real distance_ss(const Segment &a, const Segment &b) {
    if(is_intersect_ss(a, b)) return 0;
    return min({distance_sp(a, b.a), distance_sp(a, b.b), distance_sp(b, a.a), distance_sp(b, a.b)});
  }
}

