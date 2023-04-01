---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/base.hpp
    title: geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: geometry/point.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/common_area_cp.hpp
    title: geometry/common_area_cp.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon_cut.hpp
    title: geometry/convex_polygon_cut.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/cross_point_cl.hpp
    title: geometry/cross_point_cl.hpp
  - icon: ':warning:'
    path: geometry/cross_point_cs.hpp
    title: geometry/cross_point_cs.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/cross_point_ll.hpp
    title: geometry/cross_point_ll.hpp
  - icon: ':warning:'
    path: geometry/distance_ll.hpp
    title: geometry/distance_ll.hpp
  - icon: ':warning:'
    path: geometry/distance_lp.hpp
    title: geometry/distance_lp.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/distance_sp.hpp
    title: geometry/distance_sp.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/distance_ss.hpp
    title: geometry/distance_ss.hpp
  - icon: ':warning:'
    path: geometry/is_intersect_cl.hpp
    title: geometry/is_intersect_cl.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/is_intersect_cs.hpp
    title: geometry/is_intersect_cs.hpp
  - icon: ':warning:'
    path: geometry/is_intersect_ll.hpp
    title: geometry/is_intersect_ll.hpp
  - icon: ':warning:'
    path: geometry/is_intersect_lp.hpp
    title: geometry/is_intersect_lp.hpp
  - icon: ':warning:'
    path: geometry/is_intersect_ls.hpp
    title: geometry/is_intersect_ls.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/is_intersect_sp.hpp
    title: geometry/is_intersect_sp.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/is_intersect_ss.hpp
    title: geometry/is_intersect_ss.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/is_orthogonal.hpp
    title: geometry/is_orthogonal.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/is_parallel.hpp
    title: geometry/is_parallel.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/projection.hpp
    title: geometry/projection.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/reflection.hpp
    title: geometry/reflection.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/segment.hpp
    title: geometry/segment.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-1-a.test.cpp
    title: test/verify/aoj-cgl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-1-b.test.cpp
    title: test/verify/aoj-cgl-1-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-2-a.test.cpp
    title: test/verify/aoj-cgl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-2-b.test.cpp
    title: test/verify/aoj-cgl-2-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-2-c.test.cpp
    title: test/verify/aoj-cgl-2-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-2-d.test.cpp
    title: test/verify/aoj-cgl-2-d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-cgl-4-c.test.cpp
    title: test/verify/aoj-cgl-4-c.test.cpp
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
    links: []
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
    \    }\n  };\n\n  using Lines = vector< Line >;\n}\n"
  code: "#pragma once\n#include \"point.hpp\"\n\nnamespace geometry {\n  struct Line\
    \ {\n    Point a, b;\n\n    Line() = default;\n\n    Line(const Point &a, const\
    \ Point &b) : a(a), b(b) {}\n\n    Line(const Real &A, const Real &B, const Real\
    \ &C) { // Ax+By=C\n      if(equals(A, 0)) {\n        assert(!equals(B, 0));\n\
    \        a = Point(0, C / B);\n        b = Point(1, C / B);\n      } else if(equals(B,\
    \ 0)) {\n        a = Point(C / A, 0);\n        b = Point(C / A, 1);\n      } else\
    \ {\n        a = Point(0, C / B);\n        b = Point(C / A, 0);\n      }\n   \
    \ }\n\n    friend ostream &operator<<(ostream &os, Line &l) {\n      return os\
    \ << l.a << \" to \" << l.b;\n    }\n\n    friend istream &operator>>(istream\
    \ &is, Line &l) {\n      return is >> l.a >> l.b;\n    }\n  };\n\n  using Lines\
    \ = vector< Line >;\n}\n"
  dependsOn:
  - geometry/point.hpp
  - geometry/base.hpp
  isVerificationFile: false
  path: geometry/line.hpp
  requiredBy:
  - geometry/cross_point_ll.hpp
  - geometry/segment.hpp
  - geometry/common_area_cp.hpp
  - geometry/cross_point_cs.hpp
  - geometry/is_intersect_cs.hpp
  - geometry/distance_ll.hpp
  - geometry/distance_ss.hpp
  - geometry/is_intersect_ls.hpp
  - geometry/projection.hpp
  - geometry/convex_polygon_cut.hpp
  - geometry/reflection.hpp
  - geometry/is_intersect_ll.hpp
  - geometry/is_parallel.hpp
  - geometry/is_intersect_ss.hpp
  - geometry/is_intersect_sp.hpp
  - geometry/is_intersect_lp.hpp
  - geometry/is_intersect_cl.hpp
  - geometry/distance_sp.hpp
  - geometry/is_orthogonal.hpp
  - geometry/cross_point_cl.hpp
  - geometry/distance_lp.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-cgl-1-b.test.cpp
  - test/verify/aoj-cgl-2-c.test.cpp
  - test/verify/aoj-cgl-2-a.test.cpp
  - test/verify/aoj-cgl-1-a.test.cpp
  - test/verify/aoj-cgl-7-d.test.cpp
  - test/verify/aoj-cgl-2-d.test.cpp
  - test/verify/aoj-cgl-7-h.test.cpp
  - test/verify/aoj-cgl-2-b.test.cpp
  - test/verify/aoj-cgl-4-c.test.cpp
documentation_of: geometry/line.hpp
layout: document
redirect_from:
- /library/geometry/line.hpp
- /library/geometry/line.hpp.html
title: geometry/line.hpp
---
