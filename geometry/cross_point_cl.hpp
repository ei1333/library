#include "base.cpp"
#include "point.cpp"
#include "line.cpp"
#include "circle.cpp"
#include "projection.cpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
  Points cross_point_cl(const Circle &c, const Line &l) {
    Point pr = projection(l, c.p);
    if(equals(abs(pr - c.p), c.r)) return {pr};
    Point e = (l.b - l.a) / abs(l.b - l.a);
    auto k = sqrt(norm(c.r) - norm(pr - c.p));
    return {pr - e * k, pr + e * k};
  }
}
