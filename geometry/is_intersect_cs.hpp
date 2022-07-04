#include "base.hpp"
#include "point.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "projection.hpp"

namespace geometry {
  int is_intersect_cs(const Circle &c, const Segment &l) {
    Point h = projection(l, c.p);
    if(sign(norm(h - c.p) - norm(c.r)) > 0) return 0;
    auto d1 = abs(c.p - l.a), d2 = abs(c.p - l.b);
    if(sign(c.r - d1) >= 0 && sign(c.r - d2) >= 0) return 0;
    if(sign(c.r - d1) < 0 && sign(d2 - c.r) > 0 || sign(d1 - c.r) > 0 && sign(c.r - d2) < 0) return 1;
    if(sign(dot(l.a - h, l.b - h)) < 0) return 2;
    return 0;
  }
}
