#include "base.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "distance_sp.hpp"
#include "cross_point_cl.hpp"
#include "is_intersect_cs.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
  Real ca_cp_impl(const Circle &c, const Point &a, const Point &b) {
    auto va = c.p - a, vb = c.p - b;
    Real f = cross(va, vb), ret = 0;
    if(sign(f) == 0) return ret;
    if(sign(max(abs(va), abs(vb)) - c.r) <= 0) return f;
    if(sign(distance_sp(Segment(a, b), c.p) - c.r) >= 0) return norm(c.r) * arg(vb * conj(va));
    auto tot = cross_point_cl(c, Line(a, b));
    if(is_intersect_cs(c, Segment(a, b)) != 2 and dot(a - tot[0], b - tot[0]) < 0) {
      swap(tot[0], tot[1]);
    }
    tot.emplace(begin(tot), a);
    tot.emplace_back(b);
    for(int i = 1; i < (int) tot.size(); i++) {
      ret += ca_cp_impl(c, tot[i - 1], tot[i]);
    }
    return ret;
  }

  Real common_area_cp(const Circle &c, const Polygon &p) {
    if(p.size() < 3) return 0;
    Real A = 0;
    for(int i = 0; i < p.size(); i++) {
      A += ca_cp_impl(c, p[i], p[(i + 1) % p.size()]);
    }
    return A * 0.5;
  }
}
