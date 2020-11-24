#include "point.cpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
  int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if(sign(cross(b, c)) == +1) return +1; // "COUNTER_CLOCKWISE"
    if(sign(cross(b, c)) == -1) return -1; // "CLOCKWISE"
    if(sign(dot(b, c)) == -1) return +2;   // "ONLINE_BACK" c-a-b
    if(norm(b) < norm(c)) return -2;       // "ONLINE_FRONT" a-b-c
    return 0;                              // "ON_SEGMENT" a-c-b
  }
}
