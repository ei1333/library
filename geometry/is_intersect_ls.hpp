#include "base.hpp"
#include "point.hpp"
#include "line.hpp"
#include "segment.hpp"

namespace geometry {
  bool is_intersect_ls(const Line &l, const Segment &s) {
    return sign(cross(l.b - l.a, s.a - l.a)) * sign(cross(l.b - l.a, s.b - l.a)) <= 0;
  }
}
