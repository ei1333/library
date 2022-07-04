#pragma once
#include "point.hpp"

namespace geometry {
  struct Line {
    Point a, b;

    Line() = default;

    Line(const Point &a, const Point &b) : a(a), b(b) {}

    Line(const Real &A, const Real &B, const Real &C) { // Ax+By=C
      if(equals(A, 0)) {
        assert(!equals(B, 0));
        a = Point(0, C / B);
        b = Point(1, C / B);
      } else if(equals(B, 0)) {
        a = Point(C / A, 0);
        b = Point(C / A, 1);
      } else {
        a = Point(0, C / B);
        b = Point(C / A, 0);
      }
    }

    friend ostream &operator<<(ostream &os, Line &l) {
      return os << l.a << " to " << l.b;
    }

    friend istream &operator>>(istream &is, Line &l) {
      return is >> l.a >> l.b;
    }
  };

  using Lines = vector< Line >;
}
