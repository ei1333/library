#pragma once
#include "point.cpp"

namespace geometry {
  struct Circle {
    Point p;
    Real r{};

    Circle() = default;

    Circle(const Point &p, const Real &r) : p(p), r(r) {}
  };

  using Circles = vector< Circle >;
}
