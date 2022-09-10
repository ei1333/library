#include "point.hpp"
#include "line.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
  bool is_orthogonal(const Line &a, const Line &b) {
    return equals(dot(a.a - a.b, b.a - b.b), 0.0);
  }
}
