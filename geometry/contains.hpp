#include "base.hpp"
#include "point.hpp"
#include "polygon.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
  int contains(const Polygon &Q, const Point &p) {
    bool in = false;
    for(int i = 0; i < Q.size(); i++) {
      Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
      if(imag(a) > imag(b)) swap(a, b);
      if(sign(imag(a)) <= 0 && 0 < sign(imag(b)) && sign(cross(a, b)) < 0) in = !in;
      if(equals(cross(a, b), 0) && sign(dot(a, b)) <= 0) return ON;
    }
    return in ? IN : OUT;
  }
}
