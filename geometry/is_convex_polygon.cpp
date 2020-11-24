#include "point.cpp"
#include "ccw.cpp"
#include "polygon.cpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
  bool is_convex_polygon(const Polygon &p) {
    int n = (int) p.size();
    for(int i = 0; i < n; i++) {
      if(ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == CLOCKWISE) return false;
    }
    return true;
  }
}
