#include "base.hpp"
#include "point.hpp"
#include "polygon.hpp"

namespace geometry {
  int convex_polygon_contains(const Polygon &Q, const Point &p) {
    int N = (int) Q.size();
    Point g = (Q[0] + Q[N / 3] + Q[N * 2 / 3]) / 3.0;
    if(equals(imag(g), imag(p)) && equals(real(g), imag(g))) return IN;
    Point gp = p - g;
    int l = 0, r = N;
    while(r - l > 1) {
      int mid = (l + r) / 2;
      Point gl = Q[l] - g;
      Point gm = Q[mid] - g;
      if(cross(gl, gm) > 0) {
        if(cross(gl, gp) >= 0 && cross(gm, gp) <= 0) r = mid;
        else l = mid;
      } else {
        if(cross(gl, gp) <= 0 && cross(gm, gp) >= 0) l = mid;
        else r = mid;
      }
    }
    r %= N;
    Real v = cross(Q[l] - p, Q[r] - p);
    return sign(v) == 0 ? ON : sign(v) == -1 ? OUT : IN;
  }
}
