#include "base.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "cross_point_ll.hpp"

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
