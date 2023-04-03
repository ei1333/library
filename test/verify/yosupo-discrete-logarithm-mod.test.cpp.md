---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-log.hpp
    title: "Mod Log(\u96E2\u6563\u5BFE\u6570\u554F\u984C)"
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
    PROBLEM: https://judge.yosupo.jp/problem/discrete_logarithm_mod
    links:
    - https://judge.yosupo.jp/problem/discrete_logarithm_mod
  bundledCode: "#line 1 \"test/verify/yosupo-discrete-logarithm-mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\" \n\n#line\
    \ 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
    \nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL\
    \ << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
    \ {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed\
    \ << setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
    \ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream &os, const\
    \ pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream &is, pair<\
    \ T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename\
    \ T >\nostream &operator<<(ostream &os, const vector< T > &v) {\n  for(int i =\
    \ 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \"\
    \ : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream\
    \ &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate<\
    \ typename T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b &&\
    \ (a = b, true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64\
    \ >\nvector< T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate<\
    \ typename T, typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector<\
    \ decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename\
    \ T, typename V >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T\
    \ &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename\
    \ enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto\
    \ &e : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n\
    \  explicit FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename...\
    \ Args >\n  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-discrete-logarithm-mod.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-log.hpp\"\n/**\n * @brief Mod Log(\u96E2\u6563\
    \u5BFE\u6570\u554F\u984C)\n * @docs docs/mod-log.md\n */\nint64_t mod_log(int64_t\
    \ a, int64_t b, int64_t p) {\n  int64_t g = 1;\n\n  for(int64_t i = p; i; i /=\
    \ 2) (g *= a) %= p;\n  g = __gcd(g, p);\n\n  int64_t t = 1, c = 0;\n  for(; t\
    \ % g; c++) {\n    if(t == b) return c;\n    (t *= a) %= p;\n  }\n  if(b % g)\
    \ return -1;\n\n  t /= g;\n  b /= g;\n\n  int64_t n = p / g, h = 0, gs = 1;\n\n\
    \  for(; h * h < n; h++) (gs *= a) %= n;\n\n  unordered_map< int64_t, int64_t\
    \ > bs;\n  for(int64_t s = 0, e = b; s < h; bs[e] = ++s) {\n    (e *= a) %= n;\n\
    \  }\n\n  for(int64_t s = 0, e = t; s < n;) {\n    (e *= gs) %= n;\n    s += h;\n\
    \    if(bs.count(e)) return c + s - bs[e];\n  }\n  return -1;\n}\n#line 6 \"test/verify/yosupo-discrete-logarithm-mod.test.cpp\"\
    \n\nint main() {\n  int T;\n  cin >> T;\n  while(T--) {\n    int64_t X, Y, M;\n\
    \    cin >> X >> Y >> M;\n    cout << mod_log(X, Y, M) << endl;\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\
    \ \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-log.hpp\"\
    \n\nint main() {\n  int T;\n  cin >> T;\n  while(T--) {\n    int64_t X, Y, M;\n\
    \    cin >> X >> Y >> M;\n    cout << mod_log(X, Y, M) << endl;\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-log.hpp
  isVerificationFile: true
  path: test/verify/yosupo-discrete-logarithm-mod.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-discrete-logarithm-mod.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-discrete-logarithm-mod.test.cpp
- /verify/test/verify/yosupo-discrete-logarithm-mod.test.cpp.html
title: test/verify/yosupo-discrete-logarithm-mod.test.cpp
---
