#pragma once

namespace geometry {
  using Real = double;
  const Real EPS = 1e-8;
  const Real PI = acos(static_cast< Real >(-1));

  enum {
    OUT, ON, IN
  };

  inline int sign(const Real &r) {
    return r <= -EPS ? -1 : r >= EPS ? 1 : 0;
  }

  inline bool equals(const Real &a, const Real &b) {
    return sign(a - b) == 0;
  }
}
