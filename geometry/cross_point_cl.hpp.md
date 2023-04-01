---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/base.hpp
    title: geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/circle.hpp
    title: geometry/circle.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: geometry/line.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: geometry/point.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/projection.hpp
    title: geometry/projection.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/common_area_cp.hpp
    title: geometry/common_area_cp.hpp
  - icon: ':warning:'
    path: geometry/cross_point_cs.hpp
    title: geometry/cross_point_cs.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-7-d.test.cpp
    title: test/verify/aoj-cgl-7-d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-7-h.test.cpp
    title: test/verify/aoj-cgl-7-h.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
  bundledCode: "#line 2 \"geometry/base.hpp\"\n\nnamespace geometry {\n  using Real\
    \ = double;\n  const Real EPS = 1e-8;\n  const Real PI = acos(static_cast< Real\
    \ >(-1));\n\n  enum {\n    OUT, ON, IN\n  };\n\n  inline int sign(const Real &r)\
    \ {\n    return r <= -EPS ? -1 : r >= EPS ? 1 : 0;\n  }\n\n  inline bool equals(const\
    \ Real &a, const Real &b) {\n    return sign(a - b) == 0;\n  }\n}\n#line 3 \"\
    geometry/point.hpp\"\n\nnamespace geometry {\n  using Point = complex< Real >;\n\
    \n  istream &operator>>(istream &is, Point &p) {\n    Real a, b;\n    is >> a\
    \ >> b;\n    p = Point(a, b);\n    return is;\n  }\n\n  ostream &operator<<(ostream\
    \ &os, const Point &p) {\n    return os << real(p) << \" \" << imag(p);\n  }\n\
    \n  Point operator*(const Point &p, const Real &d) {\n    return Point(real(p)\
    \ * d, imag(p) * d);\n  }\n\n  // rotate point p counterclockwise by theta rad\n\
    \  Point rotate(Real theta, const Point &p) {\n    return Point(cos(theta) * real(p)\
    \ - sin(theta) * imag(p), sin(theta) * real(p) + cos(theta) * imag(p));\n  }\n\
    \n  Real cross(const Point &a, const Point &b) {\n    return real(a) * imag(b)\
    \ - imag(a) * real(b);\n  }\n\n  Real dot(const Point &a, const Point &b) {\n\
    \    return real(a) * real(b) + imag(a) * imag(b);\n  }\n\n  bool compare_x(const\
    \ Point &a, const Point &b) {\n    return equals(real(a), real(b)) ? imag(a) <\
    \ imag(b) : real(a) < real(b);\n  }\n\n  bool compare_y(const Point &a, const\
    \ Point &b) {\n    return equals(imag(a), imag(b)) ? real(a) < real(b) : imag(a)\
    \ < imag(b);\n  }\n\n  using Points = vector< Point >;\n}\n#line 3 \"geometry/line.hpp\"\
    \n\nnamespace geometry {\n  struct Line {\n    Point a, b;\n\n    Line() = default;\n\
    \n    Line(const Point &a, const Point &b) : a(a), b(b) {}\n\n    Line(const Real\
    \ &A, const Real &B, const Real &C) { // Ax+By=C\n      if(equals(A, 0)) {\n \
    \       assert(!equals(B, 0));\n        a = Point(0, C / B);\n        b = Point(1,\
    \ C / B);\n      } else if(equals(B, 0)) {\n        a = Point(C / A, 0);\n   \
    \     b = Point(C / A, 1);\n      } else {\n        a = Point(0, C / B);\n   \
    \     b = Point(C / A, 0);\n      }\n    }\n\n    friend ostream &operator<<(ostream\
    \ &os, Line &l) {\n      return os << l.a << \" to \" << l.b;\n    }\n\n    friend\
    \ istream &operator>>(istream &is, Line &l) {\n      return is >> l.a >> l.b;\n\
    \    }\n  };\n\n  using Lines = vector< Line >;\n}\n#line 3 \"geometry/circle.hpp\"\
    \n\nnamespace geometry {\n  struct Circle {\n    Point p;\n    Real r{};\n\n \
    \   Circle() = default;\n\n    Circle(const Point &p, const Real &r) : p(p), r(r)\
    \ {}\n  };\n\n  using Circles = vector< Circle >;\n}\n#line 2 \"geometry/projection.hpp\"\
    \n\n#line 5 \"geometry/projection.hpp\"\n\nnamespace geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A\n\
    \  Point projection(const Line &l, const Point &p) {\n    auto t = dot(p - l.a,\
    \ l.a - l.b) / norm(l.a - l.b);\n    return l.a + (l.a - l.b) * t;\n  }\n}\n#line\
    \ 6 \"geometry/cross_point_cl.hpp\"\n\nnamespace geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D\n\
    \  Points cross_point_cl(const Circle &c, const Line &l) {\n    Point pr = projection(l,\
    \ c.p);\n    if(equals(abs(pr - c.p), c.r)) return {pr};\n    Point e = (l.b -\
    \ l.a) / abs(l.b - l.a);\n    auto k = sqrt(norm(c.r) - norm(pr - c.p));\n   \
    \ return {pr - e * k, pr + e * k};\n  }\n}\n"
  code: "#include \"base.hpp\"\n#include \"point.hpp\"\n#include \"line.hpp\"\n#include\
    \ \"circle.hpp\"\n#include \"projection.hpp\"\n\nnamespace geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D\n\
    \  Points cross_point_cl(const Circle &c, const Line &l) {\n    Point pr = projection(l,\
    \ c.p);\n    if(equals(abs(pr - c.p), c.r)) return {pr};\n    Point e = (l.b -\
    \ l.a) / abs(l.b - l.a);\n    auto k = sqrt(norm(c.r) - norm(pr - c.p));\n   \
    \ return {pr - e * k, pr + e * k};\n  }\n}\n"
  dependsOn:
  - geometry/base.hpp
  - geometry/point.hpp
  - geometry/line.hpp
  - geometry/circle.hpp
  - geometry/projection.hpp
  isVerificationFile: false
  path: geometry/cross_point_cl.hpp
  requiredBy:
  - geometry/common_area_cp.hpp
  - geometry/cross_point_cs.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-cgl-7-d.test.cpp
  - test/verify/aoj-cgl-7-h.test.cpp
documentation_of: geometry/cross_point_cl.hpp
layout: document
redirect_from:
- /library/geometry/cross_point_cl.hpp
- /library/geometry/cross_point_cl.hpp.html
title: geometry/cross_point_cl.hpp
---
