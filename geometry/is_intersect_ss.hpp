#include "point.cpp"
#include "ccw.cpp"
#include "segment.cpp"


namespace geometry {
  bool is_intersect_ss(const Segment &s, const Segment &t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
           ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
  }
}
