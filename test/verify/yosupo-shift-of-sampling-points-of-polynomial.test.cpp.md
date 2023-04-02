---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/lagrange-polynomial-3.hpp
    title: "Lagrange Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024)"
  - icon: ':question:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':question:'
    path: math/fft/number-theoretic-transform-friendly-mod-int.hpp
    title: Number Theoretic Transform Friendly ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
    links:
    - https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
  bundledCode: "#line 1 \"test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp\"\
    \n\n#line 1 \"math/fft/number-theoretic-transform-friendly-mod-int.hpp\"\n/**\n\
    \ * @brief Number Theoretic Transform Friendly ModInt\n */\ntemplate< typename\
    \ Mint >\nstruct NumberTheoreticTransformFriendlyModInt {\n\n  static vector<\
    \ Mint > roots, iroots, rate3, irate3;\n  static int max_base;\n\n  NumberTheoreticTransformFriendlyModInt()\
    \ = default;\n\n  static void init() {\n    if(roots.empty()) {\n      const unsigned\
    \ mod = Mint::get_mod();\n      assert(mod >= 3 && mod % 2 == 1);\n      auto\
    \ tmp = mod - 1;\n      max_base = 0;\n      while(tmp % 2 == 0) tmp >>= 1, max_base++;\n\
    \      Mint root = 2;\n      while(root.pow((mod - 1) >> 1) == 1) {\n        root\
    \ += 1;\n      }\n      assert(root.pow(mod - 1) == 1);\n\n      roots.resize(max_base\
    \ + 1);\n      iroots.resize(max_base + 1);\n      rate3.resize(max_base + 1);\n\
    \      irate3.resize(max_base + 1);\n\n      roots[max_base] = root.pow((mod -\
    \ 1) >> max_base);\n      iroots[max_base] = Mint(1) / roots[max_base];\n    \
    \  for(int i = max_base - 1; i >= 0; i--) {\n        roots[i] = roots[i + 1] *\
    \ roots[i + 1];\n        iroots[i] = iroots[i + 1] * iroots[i + 1];\n      }\n\
    \      {\n        Mint prod = 1, iprod = 1;\n        for(int i = 0; i <= max_base\
    \ - 3; i++) {\n          rate3[i] = roots[i + 3] * prod;\n          irate3[i]\
    \ = iroots[i + 3] * iprod;\n          prod *= iroots[i + 3];\n          iprod\
    \ *= roots[i + 3];\n        }\n      }\n    }\n  }\n\n  static void ntt(vector<\
    \ Mint > &a) {\n    init();\n    const int n = (int) a.size();\n    assert((n\
    \ & (n - 1)) == 0);\n    int h = __builtin_ctz(n);\n    assert(h <= max_base);\n\
    \    int len = 0;\n    Mint imag = roots[2];\n    if(h & 1) {\n      int p = 1\
    \ << (h - 1);\n      Mint rot = 1;\n      for(int i = 0; i < p; i++) {\n     \
    \   auto r = a[i + p];\n        a[i + p] = a[i] - r;\n        a[i] += r;\n   \
    \   }\n      len++;\n    }\n    for(; len + 1 < h; len += 2) {\n      int p =\
    \ 1 << (h - len - 2);\n      { // s = 0\n        for(int i = 0; i < p; i++) {\n\
    \          auto a0 = a[i];\n          auto a1 = a[i + p];\n          auto a2 =\
    \ a[i + 2 * p];\n          auto a3 = a[i + 3 * p];\n          auto a1na3imag =\
    \ (a1 - a3) * imag;\n          auto a0a2 = a0 + a2;\n          auto a1a3 = a1\
    \ + a3;\n          auto a0na2 = a0 - a2;\n          a[i] = a0a2 + a1a3;\n    \
    \      a[i + 1 * p] = a0a2 - a1a3;\n          a[i + 2 * p] = a0na2 + a1na3imag;\n\
    \          a[i + 3 * p] = a0na2 - a1na3imag;\n        }\n      }\n      Mint rot\
    \ = rate3[0];\n      for(int s = 1; s < (1 << len); s++) {\n        int offset\
    \ = s << (h - len);\n        Mint rot2 = rot * rot;\n        Mint rot3 = rot2\
    \ * rot;\n        for(int i = 0; i < p; i++) {\n          auto a0 = a[i + offset];\n\
    \          auto a1 = a[i + offset + p] * rot;\n          auto a2 = a[i + offset\
    \ + 2 * p] * rot2;\n          auto a3 = a[i + offset + 3 * p] * rot3;\n      \
    \    auto a1na3imag = (a1 - a3) * imag;\n          auto a0a2 = a0 + a2;\n    \
    \      auto a1a3 = a1 + a3;\n          auto a0na2 = a0 - a2;\n          a[i +\
    \ offset] = a0a2 + a1a3;\n          a[i + offset + 1 * p] = a0a2 - a1a3;\n   \
    \       a[i + offset + 2 * p] = a0na2 + a1na3imag;\n          a[i + offset + 3\
    \ * p] = a0na2 - a1na3imag;\n        }\n        rot *= rate3[__builtin_ctz(~s)];\n\
    \      }\n    }\n  }\n\n  static void intt(vector< Mint > &a, bool f = true) {\n\
    \    init();\n    const int n = (int) a.size();\n    assert((n & (n - 1)) == 0);\n\
    \    int h = __builtin_ctz(n);\n    assert(h <= max_base);\n    int len = h;\n\
    \    Mint iimag = iroots[2];\n    for(; len > 1; len -= 2) {\n      int p = 1\
    \ << (h - len);\n      { // s = 0\n        for(int i = 0; i < p; i++) {\n    \
    \      auto a0 = a[i];\n          auto a1 = a[i + 1 * p];\n          auto a2 =\
    \ a[i + 2 * p];\n          auto a3 = a[i + 3 * p];\n          auto a2na3iimag\
    \ = (a2 - a3) * iimag;\n          auto a0na1 = a0 - a1;\n          auto a0a1 =\
    \ a0 + a1;\n          auto a2a3 = a2 + a3;\n          a[i] = a0a1 + a2a3;\n  \
    \        a[i + 1 * p] = (a0na1 + a2na3iimag);\n          a[i + 2 * p] = (a0a1\
    \ - a2a3);\n          a[i + 3 * p] = (a0na1 - a2na3iimag);\n        }\n      }\n\
    \      Mint irot = irate3[0];\n      for(int s = 1; s < (1 << (len - 2)); s++)\
    \ {\n        int offset = s << (h - len + 2);\n        Mint irot2 = irot * irot;\n\
    \        Mint irot3 = irot2 * irot;\n        for(int i = 0; i < p; i++) {\n  \
    \        auto a0 = a[i + offset];\n          auto a1 = a[i + offset + 1 * p];\n\
    \          auto a2 = a[i + offset + 2 * p];\n          auto a3 = a[i + offset\
    \ + 3 * p];\n          auto a2na3iimag = (a2 - a3) * iimag;\n          auto a0na1\
    \ = a0 - a1;\n          auto a0a1 = a0 + a1;\n          auto a2a3 = a2 + a3;\n\
    \          a[i + offset] = a0a1 + a2a3;\n          a[i + offset + 1 * p] = (a0na1\
    \ + a2na3iimag) * irot;\n          a[i + offset + 2 * p] = (a0a1 - a2a3) * irot2;\n\
    \          a[i + offset + 3 * p] = (a0na1 - a2na3iimag) * irot3;\n        }\n\
    \        irot *= irate3[__builtin_ctz(~s)];\n      }\n    }\n    if(len >= 1)\
    \ {\n      int p = 1 << (h - 1);\n      for(int i = 0; i < p; i++) {\n       \
    \ auto ajp = a[i] - a[i + p];\n        a[i] += a[i + p];\n        a[i + p] = ajp;\n\
    \      }\n    }\n    if(f) {\n      Mint inv_sz = Mint(1) / n;\n      for(int\
    \ i = 0; i < n; i++) a[i] *= inv_sz;\n    }\n  }\n\n  static vector< Mint > multiply(vector<\
    \ Mint > a, vector< Mint > b) {\n    int need = a.size() + b.size() - 1;\n   \
    \ int nbase = 1;\n    while((1 << nbase) < need) nbase++;\n    int sz = 1 << nbase;\n\
    \    a.resize(sz, 0);\n    b.resize(sz, 0);\n    ntt(a);\n    ntt(b);\n    Mint\
    \ inv_sz = Mint(1) / sz;\n    for(int i = 0; i < sz; i++) a[i] *= b[i] * inv_sz;\n\
    \    intt(a, false);\n    a.resize(need);\n    return a;\n  }\n};\n\ntemplate<\
    \ typename Mint >\nvector< Mint > NumberTheoreticTransformFriendlyModInt< Mint\
    \ >::roots = vector< Mint >();\ntemplate< typename Mint >\nvector< Mint > NumberTheoreticTransformFriendlyModInt<\
    \ Mint >::iroots = vector< Mint >();\ntemplate< typename Mint >\nvector< Mint\
    \ > NumberTheoreticTransformFriendlyModInt< Mint >::rate3 = vector< Mint >();\n\
    template< typename Mint >\nvector< Mint > NumberTheoreticTransformFriendlyModInt<\
    \ Mint >::irate3 = vector< Mint >();\ntemplate< typename Mint >\nint NumberTheoreticTransformFriendlyModInt<\
    \ Mint >::max_base = 0;\n#line 6 \"test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/lagrange-polynomial-3.hpp\"\n/**\n * @brief Lagrange\
    \ Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024)\n */\ntemplate< typename\
    \ Mint, typename F >\nvector< Mint > lagrange_polynomial(const vector< Mint >\
    \ &y, int64_t T, const int &m, const F &multiply) {\n  int k = (int) y.size()\
    \ - 1;\n  T %= Mint::get_mod();\n  if(T <= k) {\n    vector< Mint > ret(m);\n\
    \    int ptr = 0;\n    for(int64_t i = T; i <= k and ptr < m; i++) {\n      ret[ptr++]\
    \ = y[i];\n    }\n    if(k + 1 < T + m) {\n      auto suf = lagrange_polynomial(y,\
    \ k + 1, m - ptr, multiply);\n      for(int i = k + 1; i < T + m; i++) {\n   \
    \     ret[ptr++] = suf[i - (k + 1)];\n      }\n    }\n    return ret;\n  }\n \
    \ if(T + m > Mint::get_mod()) {\n    auto pref = lagrange_polynomial(y, T, Mint::get_mod()\
    \ - T, multiply);\n    auto suf = lagrange_polynomial(y, 0, m - pref.size(), multiply);\n\
    \    copy(begin(suf), end(suf), back_inserter(pref));\n    return pref;\n  }\n\
    \  \n  vector< Mint > finv(k + 1, 1), d(k + 1);\n  for(int i = 2; i <= k; i++)\
    \ finv[k] *= i;\n  finv[k] = Mint(1) / finv[k];\n  for(int i = k; i >= 1; i--)\
    \ finv[i - 1] = finv[i] * i;\n  for(int i = 0; i <= k; i++) {\n    d[i] = finv[i]\
    \ * finv[k - i] * y[i];\n    if((k - i) & 1) d[i] = -d[i];\n  }\n\n  vector< Mint\
    \ > h(m + k);\n  for(int i = 0; i < m + k; i++) {\n    h[i] = Mint(1) / (T - k\
    \ + i);\n  }\n\n  auto dh = multiply(d, h);\n\n  vector< Mint > ret(m);\n  Mint\
    \ cur = T;\n  for(int i = 1; i <= k; i++) cur *= T - i;\n  for(int i = 0; i <\
    \ m; i++) {\n    ret[i] = cur * dh[k + i];\n    cur *= T + i + 1;\n    cur *=\
    \ h[i];\n  }\n  return ret;\n}\n#line 8 \"test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp\"\
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
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 10 \"test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp\"\
    \n\nusing mint = ModInt< 998244353 >;\n\nint main() {\n  int N, T, M;\n  cin >>\
    \ N >> T >> M;\n  vector< mint > ys(N);\n  for(int i = 0; i < N; i++) cin >> ys[i];\n\
    \  NumberTheoreticTransformFriendlyModInt< mint > v;\n  auto multiply = [&](const\
    \ vector< mint > &a, const vector< mint > &b) { return v.multiply(a, b); };\n\
    \  cout << lagrange_polynomial(ys, M, T, multiply) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/fft/number-theoretic-transform-friendly-mod-int.hpp\"\
    \n\n#include \"../../math/combinatorics/lagrange-polynomial-3.hpp\"\n\n#include\
    \ \"../../math/combinatorics/mod-int.hpp\"\n\nusing mint = ModInt< 998244353 >;\n\
    \nint main() {\n  int N, T, M;\n  cin >> N >> T >> M;\n  vector< mint > ys(N);\n\
    \  for(int i = 0; i < N; i++) cin >> ys[i];\n  NumberTheoreticTransformFriendlyModInt<\
    \ mint > v;\n  auto multiply = [&](const vector< mint > &a, const vector< mint\
    \ > &b) { return v.multiply(a, b); };\n  cout << lagrange_polynomial(ys, M, T,\
    \ multiply) << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - math/fft/number-theoretic-transform-friendly-mod-int.hpp
  - math/combinatorics/lagrange-polynomial-3.hpp
  - math/combinatorics/mod-int.hpp
  isVerificationFile: true
  path: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
- /verify/test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp.html
title: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
---
