#include "point.hpp"
#include "polygon.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
  Real area(const Polygon &p) {
    int n = (int) p.size();
    Real A = 0;
    for(int i = 0; i < n; ++i) {
      A += cross(p[i], p[(i + 1) % n]);
    }
    return A * 0.5;
  }
}
