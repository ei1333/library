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
    path: geometry/cross_point_cc.hpp
    title: geometry/cross_point_cc.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: geometry/point.hpp
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
    ERROR: '0.000001'
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
  bundledCode: "#line 1 \"test/verify/aoj-cgl-7-e.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E\"\
    \n#define ERROR 0.000001\n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\
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
    \ FixPoint< F >{forward< F >(f)};\n}\n#line 5 \"test/verify/aoj-cgl-7-e.test.cpp\"\
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
    \ Point >;\n}\n#line 3 \"geometry/circle.hpp\"\n\nnamespace geometry {\n  struct\
    \ Circle {\n    Point p;\n    Real r{};\n\n    Circle() = default;\n\n    Circle(const\
    \ Point &p, const Real &r) : p(p), r(r) {}\n  };\n\n  using Circles = vector<\
    \ Circle >;\n}\n#line 4 \"geometry/cross_point_cc.hpp\"\n\nnamespace geometry\
    \ {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E\n \
    \ Points cross_point_cc(const Circle &c1, const Circle &c2) {\n    Real d = abs(c1.p\
    \ - c2.p), r = c1.r + c2.r;\n    if(sign(d - r) > 0 or sign(d + c1.r - c2.r) <\
    \ 0) return {};\n    Real a = acos((norm(c1.r) - norm(c2.r) + norm(d)) / (2 *\
    \ c1.r * d));\n    Real t = arg(c2.p - c1.p);\n    Point p = c1.p + polar(c1.r,\
    \ t + a);\n    Point q = c1.p + polar(c1.r, t - a);\n    if(equals(real(p), real(q))\
    \ && equals(imag(p), imag(q))) return {p};\n    return {p, q};\n  }\n}\n#line\
    \ 7 \"test/verify/aoj-cgl-7-e.test.cpp\"\n\nusing namespace geometry;\n\nint main()\
    \ {\n  Circle x, y;\n  cin >> x.p >> x.r >> y.p >> y.r;\n  auto ret = cross_point_cc(x,\
    \ y);\n  if(ret.size() == 1) ret.emplace_back(ret[0]);\n  if(!compare_x(ret[0],\
    \ ret[1])) swap(ret[0], ret[1]);\n  cout << ret[0] << \" \" << ret[1] << \"\\\
    n\";\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E\"\
    \n#define ERROR 0.000001\n\n#include \"../../template/template.hpp\"\n\n#include\
    \ \"../../geometry/cross_point_cc.hpp\"\n\nusing namespace geometry;\n\nint main()\
    \ {\n  Circle x, y;\n  cin >> x.p >> x.r >> y.p >> y.r;\n  auto ret = cross_point_cc(x,\
    \ y);\n  if(ret.size() == 1) ret.emplace_back(ret[0]);\n  if(!compare_x(ret[0],\
    \ ret[1])) swap(ret[0], ret[1]);\n  cout << ret[0] << \" \" << ret[1] << \"\\\
    n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - geometry/cross_point_cc.hpp
  - geometry/base.hpp
  - geometry/point.hpp
  - geometry/circle.hpp
  isVerificationFile: true
  path: test/verify/aoj-cgl-7-e.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-cgl-7-e.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-cgl-7-e.test.cpp
- /verify/test/verify/aoj-cgl-7-e.test.cpp.html
title: test/verify/aoj-cgl-7-e.test.cpp
---
