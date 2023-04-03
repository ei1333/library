---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/area.hpp
    title: geometry/area.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/base.hpp
    title: geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon_cut.hpp
    title: geometry/convex_polygon_cut.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/cross_point_ll.hpp
    title: geometry/cross_point_ll.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: geometry/line.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: geometry/point.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: geometry/polygon.hpp
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '0.00001'
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
  bundledCode: "#line 1 \"test/verify/aoj-cgl-4-c.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\"\
    \n#define ERROR 0.00001\n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\
    \nusing namespace std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\
    \nconst int64 infll = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct\
    \ IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    cout << fixed << setprecision(10);\n    cerr << fixed << setprecision(10);\n\
    \  }\n} iosetup;\n\ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream\
    \ &os, const pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return\
    \ os;\n}\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream\
    \ &is, pair< T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\n\
    template< typename T >\nostream &operator<<(ostream &os, const vector< T > &v)\
    \ {\n  for(int i = 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 !=\
    \ v.size() ? \" \" : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\n\
    istream &operator>>(istream &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n\
    \  return is;\n}\n\ntemplate< typename T1, typename T2 >\ninline bool chmax(T1\
    \ &a, T2 b) { return a < b && (a = b, true); }\n\ntemplate< typename T1, typename\
    \ T2 >\ninline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }\n\n\
    template< typename T = int64 >\nvector< T > make_v(size_t a) {\n  return vector<\
    \ T >(a);\n}\n\ntemplate< typename T, typename... Ts >\nauto make_v(size_t a,\
    \ Ts... ts) {\n  return vector< decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n\
    }\n\ntemplate< typename T, typename V >\ntypename enable_if< is_class< T >::value\
    \ == 0 >::type fill_v(T &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T,\
    \ typename V >\ntypename enable_if< is_class< T >::value != 0 >::type fill_v(T\
    \ &t, const V &v) {\n  for(auto &e : t) fill_v(e, v);\n}\n\ntemplate< typename\
    \ F >\nstruct FixPoint : F {\n  explicit FixPoint(F &&f) : F(forward< F >(f))\
    \ {}\n\n  template< typename... Args >\n  decltype(auto) operator()(Args &&...\
    \ args) const {\n    return F::operator()(*this, forward< Args >(args)...);\n\
    \  }\n};\n \ntemplate< typename F >\ninline decltype(auto) MFP(F &&f) {\n  return\
    \ FixPoint< F >{forward< F >(f)};\n}\n#line 5 \"test/verify/aoj-cgl-4-c.test.cpp\"\
    \n\n#line 2 \"geometry/base.hpp\"\n\nnamespace geometry {\n  using Real = double;\n\
    \  const Real EPS = 1e-8;\n  const Real PI = acos(static_cast< Real >(-1));\n\n\
    \  enum {\n    OUT, ON, IN\n  };\n\n  inline int sign(const Real &r) {\n    return\
    \ r <= -EPS ? -1 : r >= EPS ? 1 : 0;\n  }\n\n  inline bool equals(const Real &a,\
    \ const Real &b) {\n    return sign(a - b) == 0;\n  }\n}\n#line 3 \"geometry/point.hpp\"\
    \n\nnamespace geometry {\n  using Point = complex< Real >;\n\n  istream &operator>>(istream\
    \ &is, Point &p) {\n    Real a, b;\n    is >> a >> b;\n    p = Point(a, b);\n\
    \    return is;\n  }\n\n  ostream &operator<<(ostream &os, const Point &p) {\n\
    \    return os << real(p) << \" \" << imag(p);\n  }\n\n  Point operator*(const\
    \ Point &p, const Real &d) {\n    return Point(real(p) * d, imag(p) * d);\n  }\n\
    \n  // rotate point p counterclockwise by theta rad\n  Point rotate(Real theta,\
    \ const Point &p) {\n    return Point(cos(theta) * real(p) - sin(theta) * imag(p),\
    \ sin(theta) * real(p) + cos(theta) * imag(p));\n  }\n\n  Real cross(const Point\
    \ &a, const Point &b) {\n    return real(a) * imag(b) - imag(a) * real(b);\n \
    \ }\n\n  Real dot(const Point &a, const Point &b) {\n    return real(a) * real(b)\
    \ + imag(a) * imag(b);\n  }\n\n  bool compare_x(const Point &a, const Point &b)\
    \ {\n    return equals(real(a), real(b)) ? imag(a) < imag(b) : real(a) < real(b);\n\
    \  }\n\n  bool compare_y(const Point &a, const Point &b) {\n    return equals(imag(a),\
    \ imag(b)) ? real(a) < real(b) : imag(a) < imag(b);\n  }\n\n  using Points = vector<\
    \ Point >;\n}\n#line 3 \"geometry/line.hpp\"\n\nnamespace geometry {\n  struct\
    \ Line {\n    Point a, b;\n\n    Line() = default;\n\n    Line(const Point &a,\
    \ const Point &b) : a(a), b(b) {}\n\n    Line(const Real &A, const Real &B, const\
    \ Real &C) { // Ax+By=C\n      if(equals(A, 0)) {\n        assert(!equals(B, 0));\n\
    \        a = Point(0, C / B);\n        b = Point(1, C / B);\n      } else if(equals(B,\
    \ 0)) {\n        a = Point(C / A, 0);\n        b = Point(C / A, 1);\n      } else\
    \ {\n        a = Point(0, C / B);\n        b = Point(C / A, 0);\n      }\n   \
    \ }\n\n    friend ostream &operator<<(ostream &os, Line &l) {\n      return os\
    \ << l.a << \" to \" << l.b;\n    }\n\n    friend istream &operator>>(istream\
    \ &is, Line &l) {\n      return is >> l.a >> l.b;\n    }\n  };\n\n  using Lines\
    \ = vector< Line >;\n}\n#line 2 \"geometry/polygon.hpp\"\n\n#line 4 \"geometry/polygon.hpp\"\
    \n\nnamespace geometry {\n  using Polygon = vector< Point >;\n  using Polygons\
    \ = vector< Polygon >;\n}\n#line 3 \"geometry/cross_point_ll.hpp\"\n\nnamespace\
    \ geometry {\n  Point cross_point_ll(const Line &l, const Line &m) {\n    Real\
    \ A = cross(l.b - l.a, m.b - m.a);\n    Real B = cross(l.b - l.a, l.b - m.a);\n\
    \    if(equals(abs(A), 0) && equals(abs(B), 0)) return m.a;\n    return m.a +\
    \ (m.b - m.a) * B / A;\n  }\n}\n#line 6 \"geometry/convex_polygon_cut.hpp\"\n\n\
    namespace geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\n\
    \  // cut with a straight line l and return a convex polygon on the left\n  Polygon\
    \ convex_polygon_cut(const Polygon &U, const Line &l) {\n    Polygon ret;\n  \
    \  for(int i = 0; i < U.size(); i++) {\n      const Point &now = U[i];\n     \
    \ const Point &nxt = U[(i + 1) % U.size()];\n      auto cf = cross(l.a - now,\
    \ l.b - now);\n      auto cs = cross(l.a - nxt, l.b - nxt);\n      if(sign(cf)\
    \ >= 0) {\n        ret.emplace_back(now);\n      }\n      if(sign(cf) * sign(cs)\
    \ < 0) {\n        ret.emplace_back(cross_point_ll(Line(now, nxt), l));\n     \
    \ }\n    }\n    return ret;\n  }\n}\n#line 3 \"geometry/area.hpp\"\n\nnamespace\
    \ geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n\
    \  Real area(const Polygon &p) {\n    int n = (int) p.size();\n    Real A = 0;\n\
    \    for(int i = 0; i < n; ++i) {\n      A += cross(p[i], p[(i + 1) % n]);\n \
    \   }\n    return A * 0.5;\n  }\n}\n#line 8 \"test/verify/aoj-cgl-4-c.test.cpp\"\
    \n\nusing namespace geometry;\n\nint main() {\n  int n;\n  cin >> n;\n  Polygon\
    \ poly(n);\n  for(auto &p : poly) {\n    cin >> p;\n  }\n  int q;\n  cin >> q;\n\
    \  while(q--) {\n    Line l;\n    cin >> l;\n    cout << area(convex_polygon_cut(poly,\
    \ l)) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\"\
    \n#define ERROR 0.00001\n\n#include \"../../template/template.hpp\"\n\n#include\
    \ \"../../geometry/convex_polygon_cut.hpp\"\n#include \"../../geometry/area.hpp\"\
    \n\nusing namespace geometry;\n\nint main() {\n  int n;\n  cin >> n;\n  Polygon\
    \ poly(n);\n  for(auto &p : poly) {\n    cin >> p;\n  }\n  int q;\n  cin >> q;\n\
    \  while(q--) {\n    Line l;\n    cin >> l;\n    cout << area(convex_polygon_cut(poly,\
    \ l)) << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - geometry/convex_polygon_cut.hpp
  - geometry/base.hpp
  - geometry/point.hpp
  - geometry/line.hpp
  - geometry/polygon.hpp
  - geometry/cross_point_ll.hpp
  - geometry/area.hpp
  isVerificationFile: true
  path: test/verify/aoj-cgl-4-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-cgl-4-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-cgl-4-c.test.cpp
- /verify/test/verify/aoj-cgl-4-c.test.cpp.html
title: test/verify/aoj-cgl-4-c.test.cpp
---
