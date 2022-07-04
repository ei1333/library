#include "point.hpp"
#include "line.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
  bool is_parallel(const Line &a, const Line &b) {
    return equals(cross(a.b - a.a, b.b - b.a), 0.0);
  }
}
