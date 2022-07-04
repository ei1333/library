#include "point.hpp"
#include "line.hpp"
#include "projection.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
  Point reflection(const Line &l, const Point &p) {
    return p + (projection(l, p) - p) * 2;
  }
}
