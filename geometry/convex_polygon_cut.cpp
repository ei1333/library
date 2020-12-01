#include "base.cpp"
#include "point.cpp"
#include "line.cpp"
#include "polygon.cpp"
#include "cross_point_ll.cpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
  // cut with a straight line l and return a convex polygon on the left
  Polygon convex_polygon_cut(const Polygon &U, const Line &l) {
    Polygon ret;
    for(int i = 0; i < U.size(); i++) {
      const Point &now = U[i];
      const Point &nxt = U[(i + 1) % U.size()];
      auto cf = cross(l.a - now, l.b - now);
      auto cs = cross(l.a - nxt, l.b - nxt);
      if(sign(cf) >= 0) {
        ret.emplace_back(now);
      }
      if(sign(cf) * sign(cs) < 0) {
        ret.emplace_back(cross_point_ll(Line(now, nxt), l));
      }
    }
    return ret;
  }
}
