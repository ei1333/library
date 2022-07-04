#pragma once
#include "point.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
  constexpr int COUNTER_CLOCKWISE = +1;
  constexpr int CLOCKWISE = -1;
  constexpr int ONLINE_BACK = +2; // c-a-b
  constexpr int ONLINE_FRONT = -2; // a-b-c
  constexpr int ON_SEGMENT = 0; // a-c-b
  int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if(sign(cross(b, c)) == +1) return COUNTER_CLOCKWISE;
    if(sign(cross(b, c)) == -1) return CLOCKWISE;
    if(sign(dot(b, c)) == -1) return ONLINE_BACK;
    if(norm(b) < norm(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
  }
}
