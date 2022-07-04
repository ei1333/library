#pragma once
#include "base.hpp"

namespace geometry {
  using Point = complex< Real >;

  istream &operator>>(istream &is, Point &p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
  }

  ostream &operator<<(ostream &os, const Point &p) {
    return os << real(p) << " " << imag(p);
  }

  Point operator*(const Point &p, const Real &d) {
    return Point(real(p) * d, imag(p) * d);
  }

  // rotate point p counterclockwise by theta rad
  Point rotate(Real theta, const Point &p) {
    return Point(cos(theta) * real(p) - sin(theta) * imag(p), sin(theta) * real(p) + cos(theta) * imag(p));
  }

  Real cross(const Point &a, const Point &b) {
    return real(a) * imag(b) - imag(a) * real(b);
  }

  Real dot(const Point &a, const Point &b) {
    return real(a) * real(b) + imag(a) * imag(b);
  }

  bool compare_x(const Point &a, const Point &b) {
    return equals(real(a), real(b)) ? imag(a) < imag(b) : real(a) < real(b);
  }

  bool compare_y(const Point &a, const Point &b) {
    return equals(imag(a), imag(b)) ? real(a) < real(b) : imag(a) < imag(b);
  }

  using Points = vector< Point >;
}
