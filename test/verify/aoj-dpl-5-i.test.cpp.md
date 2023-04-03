---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/enumeration.hpp
    title: "Enumeration(\u7D44\u307F\u5408\u308F\u305B)"
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/stirling-number-second.hpp
    title: "Stirling Number Second(\u7B2C2\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\
      \u6570)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I
  bundledCode: "#line 1 \"test/verify/aoj-dpl-5-i.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll\
    \ = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dpl-5-i.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-int.hpp\"\ntemplate< int mod >\nstruct ModInt\
    \ {\n  int x;\n\n  ModInt() : x(0) {}\n\n  ModInt(int64_t y) : x(y >= 0 ? y %\
    \ mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt &operator+=(const ModInt &p)\
    \ {\n    if((x += p.x) >= mod) x -= mod;\n    return *this;\n  }\n\n  ModInt &operator-=(const\
    \ ModInt &p) {\n    if((x += mod - p.x) >= mod) x -= mod;\n    return *this;\n\
    \  }\n\n  ModInt &operator*=(const ModInt &p) {\n    x = (int) (1LL * x * p.x\
    \ % mod);\n    return *this;\n  }\n\n  ModInt &operator/=(const ModInt &p) {\n\
    \    *this *= p.inverse();\n    return *this;\n  }\n\n  ModInt operator-() const\
    \ { return ModInt(-x); }\n\n  ModInt operator+(const ModInt &p) const { return\
    \ ModInt(*this) += p; }\n\n  ModInt operator-(const ModInt &p) const { return\
    \ ModInt(*this) -= p; }\n\n  ModInt operator*(const ModInt &p) const { return\
    \ ModInt(*this) *= p; }\n\n  ModInt operator/(const ModInt &p) const { return\
    \ ModInt(*this) /= p; }\n\n  bool operator==(const ModInt &p) const { return x\
    \ == p.x; }\n\n  bool operator!=(const ModInt &p) const { return x != p.x; }\n\
    \n  ModInt inverse() const {\n    int a = x, b = mod, u = 1, v = 0, t;\n    while(b\
    \ > 0) {\n      t = a / b;\n      swap(a -= t * b, b);\n      swap(u -= t * v,\
    \ v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt pow(int64_t n) const {\n\
    \    ModInt ret(1), mul(x);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream\
    \ &operator<<(ostream &os, const ModInt &p) {\n    return os << p.x;\n  }\n\n\
    \  friend istream &operator>>(istream &is, ModInt &a) {\n    int64_t t;\n    is\
    \ >> t;\n    a = ModInt< mod >(t);\n    return (is);\n  }\n\n  static int get_mod()\
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/aoj-dpl-5-i.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/enumeration.hpp\"\n/**\n * @brief Enumeration(\u7D44\
    \u307F\u5408\u308F\u305B)\n */\ntemplate< typename T >\nstruct Enumeration {\n\
    private:\n  static vector< T > _fact, _finv, _inv;\n\n  inline static void expand(size_t\
    \ sz) {\n    if(_fact.size() < sz + 1) {\n      int pre_sz = max(1, (int) _fact.size());\n\
    \      _fact.resize(sz + 1, T(1));\n      _finv.resize(sz + 1, T(1));\n      _inv.resize(sz\
    \ + 1, T(1));\n      for(int i = pre_sz; i <= (int) sz; i++) {\n        _fact[i]\
    \ = _fact[i - 1] * T(i);\n      }\n      _finv[sz] = T(1) / _fact[sz];\n     \
    \ for(int i = (int) sz - 1; i >= pre_sz; i--) {\n        _finv[i] = _finv[i +\
    \ 1] * T(i + 1);\n      }\n      for(int i = pre_sz; i <= (int) sz; i++) {\n \
    \       _inv[i] = _finv[i] * _fact[i - 1];\n      }\n    }\n  }\n\npublic:\n \
    \ explicit Enumeration(size_t sz = 0) { expand(sz); }\n\n  static inline T fact(int\
    \ k) {\n    expand(k);\n    return _fact[k];\n  }\n\n  static inline T finv(int\
    \ k) {\n    expand(k);\n    return _finv[k];\n  }\n\n  static inline T inv(int\
    \ k) {\n    expand(k);\n    return _inv[k];\n  }\n\n  static T P(int n, int r)\
    \ {\n    if(r < 0 || n < r) return 0;\n    return fact(n) * finv(n - r);\n  }\n\
    \n  static T C(int p, int q) {\n    if(q < 0 || p < q) return 0;\n    return fact(p)\
    \ * finv(q) * finv(p - q);\n  }\n\n  static T H(int n, int r) {\n    if(n < 0\
    \ || r < 0) return 0;\n    return r == 0 ? 1 : C(n + r - 1, r);\n  }\n};\n\ntemplate<\
    \ typename T >\nvector< T > Enumeration< T >::_fact = vector< T >();\ntemplate<\
    \ typename T >\nvector< T > Enumeration< T >::_finv = vector< T >();\ntemplate<\
    \ typename T >\nvector< T > Enumeration< T >::_inv = vector< T >();\n#line 2 \"\
    math/combinatorics/stirling-number-second.hpp\"\n\n/**\n * @brief Stirling Number\
    \ Second(\u7B2C2\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570)\n * @docs docs/stirling-number-second.md\n\
    \ */\ntemplate< typename T >\nT stirling_number_second(int n, int k) {\n  Enumeration<\
    \ T > table(k);\n  T ret = 0;\n  for(int i = 0; i <= k; i++) {\n    auto add =\
    \ T(i).pow(n) * table.C(k, i);\n    if((k - i) & 1) ret -= add;\n    else ret\
    \ += add;\n  }\n  return ret * table.finv(k);\n}\n#line 8 \"test/verify/aoj-dpl-5-i.test.cpp\"\
    \n\nint main() {\n  int N, K;\n  cin >> N >> K;\n  cout << stirling_number_second<\
    \ modint >(N, K) << endl;\n}\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../math/combinatorics/stirling-number-second.hpp\"\n\nint main()\
    \ {\n  int N, K;\n  cin >> N >> K;\n  cout << stirling_number_second< modint >(N,\
    \ K) << endl;\n}\n\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - math/combinatorics/stirling-number-second.hpp
  - math/combinatorics/enumeration.hpp
  isVerificationFile: true
  path: test/verify/aoj-dpl-5-i.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dpl-5-i.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dpl-5-i.test.cpp
- /verify/test/verify/aoj-dpl-5-i.test.cpp.html
title: test/verify/aoj-dpl-5-i.test.cpp
---
