---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-pow.hpp
    title: "Mod Pow(\u3079\u304D\u4E57)"
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-sqrt.hpp
    title: Mod Sqrt
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"test/verify/yosupo-sqrt-mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-sqrt-mod.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-pow.hpp\"\n/**\n * @brief Mod Pow(\u3079\u304D\
    \u4E57)\n * @docs docs/mod-pow.md\n */\ntemplate< typename T >\nT mod_pow(T x,\
    \ int64_t n, const T &p) {\n  T ret = 1;\n  while(n > 0) {\n    if(n & 1) (ret\
    \ *= x) %= p;\n    (x *= x) %= p;\n    n >>= 1;\n  }\n  return ret % p;\n}\n#line\
    \ 1 \"math/combinatorics/mod-sqrt.hpp\"\n/**\n * @brief Mod Sqrt\n */\ntemplate<\
    \ typename T >\nT mod_sqrt(const T &a, const T &p) {\n  if(a == 0) return 0;\n\
    \  if(p == 2) return a;\n  if(mod_pow(a, (p - 1) >> 1, p) != 1) return -1;\n \
    \ T b = 1;\n  while(mod_pow(b, (p - 1) >> 1, p) == 1) ++b;\n  T e = 0, m = p -\
    \ 1;\n  while(m % 2 == 0) m >>= 1, ++e;\n  T x = mod_pow(a, (m - 1) >> 1, p);\n\
    \  T y = a * (x * x % p) % p;\n  (x *= a) %= p;\n  T z = mod_pow(b, m, p);\n \
    \ while(y != 1) {\n    T j = 0, t = y;\n    while(t != 1) {\n      j += 1;\n \
    \     (t *= t) %= p;\n    }\n    z = mod_pow(z, T(1) << (e - j - 1), p);\n   \
    \ (x *= z) %= p;\n    (z *= z) %= p;\n    (y *= z) %= p;\n    e = j;\n  }\n  return\
    \ x;\n}\n#line 7 \"test/verify/yosupo-sqrt-mod.test.cpp\"\n\nint main() {\n  int\
    \ T;\n  cin >> T;\n  while(T--) {\n    int64_t Y, P;\n    cin >> Y >> P;\n   \
    \ cout << mod_sqrt(Y, P) << endl;\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-pow.hpp\"\
    \n#include \"../../math/combinatorics/mod-sqrt.hpp\"\n\nint main() {\n  int T;\n\
    \  cin >> T;\n  while(T--) {\n    int64_t Y, P;\n    cin >> Y >> P;\n    cout\
    \ << mod_sqrt(Y, P) << endl;\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-pow.hpp
  - math/combinatorics/mod-sqrt.hpp
  isVerificationFile: true
  path: test/verify/yosupo-sqrt-mod.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-sqrt-mod.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-sqrt-mod.test.cpp
- /verify/test/verify/yosupo-sqrt-mod.test.cpp.html
title: test/verify/yosupo-sqrt-mod.test.cpp
---
