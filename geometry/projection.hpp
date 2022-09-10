#pragma once

#include "point.hpp"
#include "line.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
  Point projection(const Line &l, const Point &p) {
    auto t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
  }
}
