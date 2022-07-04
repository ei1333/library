#include "point.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "is_intersect_cs.hpp"
#include "cross_point_cl.hpp"

namespace geometry {
  Points cross_point_cs(const Circle &c, const Segment &s) {
    int num = is_intersect_cs(c, s);
    if(num == 0) return {};
    if(num == 2) return cross_point_cl(c, s);
    auto ret = cross_point_cl(c, s);
    if(dot(s.a - ret[0], s.b - ret[0]) > 0) swap(ret[0], ret[1]);
    return {ret[0]};
  }
}
