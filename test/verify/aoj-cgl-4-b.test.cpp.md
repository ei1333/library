---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/base.hpp
    title: geometry/base.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon_diameter.hpp
    title: geometry/convex_polygon_diameter.hpp
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
    ERROR: '0.00000001'
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
  bundledCode: "#line 1 \"test/verify/aoj-cgl-4-b.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\"\
    \n#define ERROR 0.00000001\n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\
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
    \ FixPoint< F >{forward< F >(f)};\n}\n#line 5 \"test/verify/aoj-cgl-4-b.test.cpp\"\
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
    \ Point >;\n}\n#line 2 \"geometry/polygon.hpp\"\n\n#line 4 \"geometry/polygon.hpp\"\
    \n\nnamespace geometry {\n  using Polygon = vector< Point >;\n  using Polygons\
    \ = vector< Polygon >;\n}\n#line 3 \"geometry/convex_polygon_diameter.hpp\"\n\n\
    namespace geometry {\n  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\n\
    \  pair< int, int > convex_polygon_diameter(const Polygon &p) {\n    int N = (int)\
    \ p.size();\n    int is = 0, js = 0;\n    for(int i = 1; i < N; i++) {\n     \
    \ if(imag(p[i]) > imag(p[is])) is = i;\n      if(imag(p[i]) < imag(p[js])) js\
    \ = i;\n    }\n    Real maxdis = norm(p[is] - p[js]);\n\n    int maxi, maxj, i,\
    \ j;\n    i = maxi = is;\n    j = maxj = js;\n    do {\n      if(cross(p[(i +\
    \ 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {\n        j = (j + 1) % N;\n \
    \     } else {\n        i = (i + 1) % N;\n      }\n      if(norm(p[i] - p[j])\
    \ > maxdis) {\n        maxdis = norm(p[i] - p[j]);\n        maxi = i;\n      \
    \  maxj = j;\n      }\n    } while(i != is || j != js);\n    return minmax(maxi,\
    \ maxj);\n  }\n}\n#line 7 \"test/verify/aoj-cgl-4-b.test.cpp\"\n\nusing namespace\
    \ geometry;\n\nint main() {\n  int N;\n  cin >> N;\n  Polygon p(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    cin >> p[i];\n  }\n  auto ret = convex_polygon_diameter(p);\n\
    \  cout << abs(p[ret.first] - p[ret.second]) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\"\
    \n#define ERROR 0.00000001\n\n#include \"../../template/template.hpp\"\n\n#include\
    \ \"../../geometry/convex_polygon_diameter.hpp\"\n\nusing namespace geometry;\n\
    \nint main() {\n  int N;\n  cin >> N;\n  Polygon p(N);\n  for(int i = 0; i < N;\
    \ i++) {\n    cin >> p[i];\n  }\n  auto ret = convex_polygon_diameter(p);\n  cout\
    \ << abs(p[ret.first] - p[ret.second]) << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - geometry/convex_polygon_diameter.hpp
  - geometry/point.hpp
  - geometry/base.hpp
  - geometry/polygon.hpp
  isVerificationFile: true
  path: test/verify/aoj-cgl-4-b.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-cgl-4-b.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-cgl-4-b.test.cpp
- /verify/test/verify/aoj-cgl-4-b.test.cpp.html
title: test/verify/aoj-cgl-4-b.test.cpp
---
