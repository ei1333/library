#include "line.cpp"
#include "is_parallel.cpp"

namespace geometry {
  bool is_intersect_ll(const Line &l, const Line &m) {
    Real A = cross(l.b - l.a, m.b - m.a);
    Real B = cross(l.b - l.a, l.b - m.a);
    if(equals(abs(A), 0) && equals(abs(B), 0)) return true;
    return !is_parallel(l, m);
  }
}
