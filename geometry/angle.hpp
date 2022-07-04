#include "point.hpp"

namespace geometry {
  Real radian_to_degree(const Real &theta) {
    return theta * 180.0 / PI;
  }

  Real degree_to_radian(const Real &deg) {
    return deg * PI / 180.0;
  }

  // smaller angle of the a-b-c
  Real get_smaller_angle(const Point &a, const Point &b, const Point &c) {
    const Point v(a - b), w(c - b);
    auto alpha = atan2(imag(v), real(v));
    auto beta = atan2(imag(w), real(w));
    if(alpha > beta) swap(alpha, beta);
    Real theta = (beta - alpha);
    return min(theta, 2 * PI - theta);
  }
}
