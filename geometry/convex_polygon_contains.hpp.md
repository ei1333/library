---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/base.hpp
    title: geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: geometry/point.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: geometry/polygon.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0412.test.cpp
    title: test/verify/aoj-0412.test.cpp
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
    \ < imag(b);\n  }\n\n  using Points = vector< Point >;\n}\n#line 2 \"geometry/polygon.hpp\"\
    \n\n#line 4 \"geometry/polygon.hpp\"\n\nnamespace geometry {\n  using Polygon\
    \ = vector< Point >;\n  using Polygons = vector< Polygon >;\n}\n#line 4 \"geometry/convex_polygon_contains.hpp\"\
    \n\nnamespace geometry {\n  int convex_polygon_contains(const Polygon &Q, const\
    \ Point &p) {\n    int N = (int) Q.size();\n    Point g = (Q[0] + Q[N / 3] + Q[N\
    \ * 2 / 3]) / 3.0;\n    if(equals(imag(g), imag(p)) && equals(real(g), real(p)))\
    \ return IN;\n    Point gp = p - g;\n    int l = 0, r = N;\n    while(r - l >\
    \ 1) {\n      int mid = (l + r) / 2;\n      Point gl = Q[l] - g;\n      Point\
    \ gm = Q[mid] - g;\n      if(cross(gl, gm) > 0) {\n        if(cross(gl, gp) >=\
    \ 0 && cross(gm, gp) <= 0) r = mid;\n        else l = mid;\n      } else {\n \
    \       if(cross(gl, gp) <= 0 && cross(gm, gp) >= 0) l = mid;\n        else r\
    \ = mid;\n      }\n    }\n    r %= N;\n    Real v = cross(Q[l] - p, Q[r] - p);\n\
    \    return sign(v) == 0 ? ON : sign(v) == -1 ? OUT : IN;\n  }\n}\n"
  code: "#include \"base.hpp\"\n#include \"point.hpp\"\n#include \"polygon.hpp\"\n\
    \nnamespace geometry {\n  int convex_polygon_contains(const Polygon &Q, const\
    \ Point &p) {\n    int N = (int) Q.size();\n    Point g = (Q[0] + Q[N / 3] + Q[N\
    \ * 2 / 3]) / 3.0;\n    if(equals(imag(g), imag(p)) && equals(real(g), real(p)))\
    \ return IN;\n    Point gp = p - g;\n    int l = 0, r = N;\n    while(r - l >\
    \ 1) {\n      int mid = (l + r) / 2;\n      Point gl = Q[l] - g;\n      Point\
    \ gm = Q[mid] - g;\n      if(cross(gl, gm) > 0) {\n        if(cross(gl, gp) >=\
    \ 0 && cross(gm, gp) <= 0) r = mid;\n        else l = mid;\n      } else {\n \
    \       if(cross(gl, gp) <= 0 && cross(gm, gp) >= 0) l = mid;\n        else r\
    \ = mid;\n      }\n    }\n    r %= N;\n    Real v = cross(Q[l] - p, Q[r] - p);\n\
    \    return sign(v) == 0 ? ON : sign(v) == -1 ? OUT : IN;\n  }\n}\n"
  dependsOn:
  - geometry/base.hpp
  - geometry/point.hpp
  - geometry/polygon.hpp
  isVerificationFile: false
  path: geometry/convex_polygon_contains.hpp
  requiredBy: []
  timestamp: '2023-04-01 23:11:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-0412.test.cpp
documentation_of: geometry/convex_polygon_contains.hpp
layout: document
redirect_from:
- /library/geometry/convex_polygon_contains.hpp
- /library/geometry/convex_polygon_contains.hpp.html
title: geometry/convex_polygon_contains.hpp
---
