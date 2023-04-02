---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics/enumeration.hpp
    title: "Enumeration(\u7D44\u307F\u5408\u308F\u305B)"
  - icon: ':x:'
    path: math/combinatorics/factorial.hpp
    title: "Factorial(\u968E\u4E57)"
  - icon: ':question:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':x:'
    path: math/combinatorics/sample-point-shift.hpp
    title: "Sample Point Shift(\u6A19\u672C\u70B9\u30B7\u30D5\u30C8)"
  - icon: ':question:'
    path: math/fft/arbitrary-mod-convolution.hpp
    title: "Arbitrary Mod Convolution(\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F)"
  - icon: ':question:'
    path: math/fft/fast-fourier-transform.hpp
    title: math/fft/fast-fourier-transform.hpp
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/502
    links:
    - https://yukicoder.me/problems/no/502
  bundledCode: "#line 1 \"test/verify/yukicoder-502.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/502\"\n\n#line 1 \"template/template.hpp\"\n\
    #include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-502.test.cpp\"\
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
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 1 \"math/combinatorics/enumeration.hpp\"\
    \n/**\n * @brief Enumeration(\u7D44\u307F\u5408\u308F\u305B)\n */\ntemplate< typename\
    \ T >\nstruct Enumeration {\nprivate:\n  static vector< T > _fact, _finv, _inv;\n\
    \n  inline static void expand(size_t sz) {\n    if(_fact.size() < sz + 1) {\n\
    \      int pre_sz = max(1, (int) _fact.size());\n      _fact.resize(sz + 1, T(1));\n\
    \      _finv.resize(sz + 1, T(1));\n      _inv.resize(sz + 1, T(1));\n      for(int\
    \ i = pre_sz; i <= (int) sz; i++) {\n        _fact[i] = _fact[i - 1] * T(i);\n\
    \      }\n      _finv[sz] = T(1) / _fact[sz];\n      for(int i = (int) sz - 1;\
    \ i >= pre_sz; i--) {\n        _finv[i] = _finv[i + 1] * T(i + 1);\n      }\n\
    \      for(int i = pre_sz; i <= (int) sz; i++) {\n        _inv[i] = _finv[i] *\
    \ _fact[i - 1];\n      }\n    }\n  }\n\npublic:\n  explicit Enumeration(size_t\
    \ sz = 0) { expand(sz); }\n\n  static inline T fact(int k) {\n    expand(k);\n\
    \    return _fact[k];\n  }\n\n  static inline T finv(int k) {\n    expand(k);\n\
    \    return _finv[k];\n  }\n\n  static inline T inv(int k) {\n    expand(k);\n\
    \    return _inv[k];\n  }\n\n  static T P(int n, int r) {\n    if(r < 0 || n <\
    \ r) return 0;\n    return fact(n) * finv(n - r);\n  }\n\n  static T C(int p,\
    \ int q) {\n    if(q < 0 || p < q) return 0;\n    return fact(p) * finv(q) * finv(p\
    \ - q);\n  }\n\n  static T H(int n, int r) {\n    if(n < 0 || r < 0) return 0;\n\
    \    return r == 0 ? 1 : C(n + r - 1, r);\n  }\n};\n\ntemplate< typename T >\n\
    vector< T > Enumeration< T >::_fact = vector< T >();\ntemplate< typename T >\n\
    vector< T > Enumeration< T >::_finv = vector< T >();\ntemplate< typename T >\n\
    vector< T > Enumeration< T >::_inv = vector< T >();\n#line 2 \"math/combinatorics/sample-point-shift.hpp\"\
    \n\n/**\n * @brief Sample Point Shift(\u6A19\u672C\u70B9\u30B7\u30D5\u30C8)\n\
    \ */\ntemplate< typename Mint, typename F >\nvector< Mint > sample_point_shift(const\
    \ vector< Mint > &ys, const Mint &m, const F &multiply) {\n  Enumeration< Mint\
    \ > comb;\n  int d = (int) ys.size() - 1;\n  vector< Mint > f(d + 1), g(d * 2\
    \ + 1);\n  for(int i = 0; i <= d; i++) {\n    f[i] = ys[i] * comb.finv(i) * comb.finv(d\
    \ - i);\n    if((d - i) & 1) f[i] = -f[i];\n  }\n  for(int i = 0; i <= 2 * d;\
    \ i++) {\n    g[i] = Mint(1) / (m - d + i);\n  }\n  auto h = multiply(f, g);\n\
    \  Mint coef = 1;\n  for(int i = 0; i <= d; i++) {\n    coef *= (m - d + i);\n\
    \  }\n  for(int i = 0; i <= d; i++) {\n    h[i + d] *= coef;\n    coef *= (m +\
    \ i + 1) * g[i];\n  }\n  return vector< Mint >{begin(h) + d, begin(h) + 2 * d\
    \ + 1};\n}\n#line 2 \"math/combinatorics/factorial.hpp\"\n\n/**\n * @brief Factorial(\u968E\
    \u4E57)\n */\ntemplate< typename Mint, typename F >\nMint factorial(int64_t n,\
    \ const F& multiply) {\n  if(n <= 1) return 1;\n  if(n >= Mint::get_mod()) return\
    \ 0;\n  int64_t v = 1;\n  while(v * v < n) v *= 2;\n  Mint iv = Mint(1) / v;\n\
    \  vector< Mint > G{1, v + 1};\n  for(int64_t d = 1; d != v; d <<= 1) {\n    vector<\
    \ Mint > G1 = sample_point_shift(G, Mint(d) * iv, multiply);\n    vector< Mint\
    \ > G2 = sample_point_shift(G, Mint(d * v + v) * iv, multiply);\n    vector< Mint\
    \ > G3 = sample_point_shift(G, Mint(d * v + d + v) * iv, multiply);\n    for(int\
    \ i = 0; i <= d; i++) G[i] *= G1[i], G2[i] *= G3[i];\n    copy(begin(G2), end(G2)\
    \ - 1, back_inserter(G));\n  }\n  Mint res = 1;\n  int64_t i = 0;\n  while(i +\
    \ v <= n) res *= G[i / v], i += v;\n  while(i < n) res *= ++i;\n  return res;\n\
    }\n#line 7 \"test/verify/yukicoder-502.test.cpp\"\n\n#line 1 \"math/fft/fast-fourier-transform.hpp\"\
    \nnamespace FastFourierTransform {\n  using real = double;\n\n  struct C {\n \
    \   real x, y;\n\n    C() : x(0), y(0) {}\n\n    C(real x, real y) : x(x), y(y)\
    \ {}\n\n    inline C operator+(const C &c) const { return C(x + c.x, y + c.y);\
    \ }\n\n    inline C operator-(const C &c) const { return C(x - c.x, y - c.y);\
    \ }\n\n    inline C operator*(const C &c) const { return C(x * c.x - y * c.y,\
    \ x * c.y + y * c.x); }\n\n    inline C conj() const { return C(x, -y); }\n  };\n\
    \n  const real PI = acosl(-1);\n  int base = 1;\n  vector< C > rts = { {0, 0},\n\
    \                     {1, 0} };\n  vector< int > rev = {0, 1};\n\n\n  void ensure_base(int\
    \ nbase) {\n    if(nbase <= base) return;\n    rev.resize(1 << nbase);\n    rts.resize(1\
    \ << nbase);\n    for(int i = 0; i < (1 << nbase); i++) {\n      rev[i] = (rev[i\
    \ >> 1] >> 1) + ((i & 1) << (nbase - 1));\n    }\n    while(base < nbase) {\n\
    \      real angle = PI * 2.0 / (1 << (base + 1));\n      for(int i = 1 << (base\
    \ - 1); i < (1 << base); i++) {\n        rts[i << 1] = rts[i];\n        real angle_i\
    \ = angle * (2 * i + 1 - (1 << base));\n        rts[(i << 1) + 1] = C(cos(angle_i),\
    \ sin(angle_i));\n      }\n      ++base;\n    }\n  }\n\n  void fft(vector< C >\
    \ &a, int n) {\n    assert((n & (n - 1)) == 0);\n    int zeros = __builtin_ctz(n);\n\
    \    ensure_base(zeros);\n    int shift = base - zeros;\n    for(int i = 0; i\
    \ < n; i++) {\n      if(i < (rev[i] >> shift)) {\n        swap(a[i], a[rev[i]\
    \ >> shift]);\n      }\n    }\n    for(int k = 1; k < n; k <<= 1) {\n      for(int\
    \ i = 0; i < n; i += 2 * k) {\n        for(int j = 0; j < k; j++) {\n        \
    \  C z = a[i + j + k] * rts[j + k];\n          a[i + j + k] = a[i + j] - z;\n\
    \          a[i + j] = a[i + j] + z;\n        }\n      }\n    }\n  }\n\n  vector<\
    \ int64_t > multiply(const vector< int > &a, const vector< int > &b) {\n    int\
    \ need = (int) a.size() + (int) b.size() - 1;\n    int nbase = 1;\n    while((1\
    \ << nbase) < need) nbase++;\n    ensure_base(nbase);\n    int sz = 1 << nbase;\n\
    \    vector< C > fa(sz);\n    for(int i = 0; i < sz; i++) {\n      int x = (i\
    \ < (int) a.size() ? a[i] : 0);\n      int y = (i < (int) b.size() ? b[i] : 0);\n\
    \      fa[i] = C(x, y);\n    }\n    fft(fa, sz);\n    C r(0, -0.25 / (sz >> 1)),\
    \ s(0, 1), t(0.5, 0);\n    for(int i = 0; i <= (sz >> 1); i++) {\n      int j\
    \ = (sz - i) & (sz - 1);\n      C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj())\
    \ * r;\n      fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;\n      fa[i]\
    \ = z;\n    }\n    for(int i = 0; i < (sz >> 1); i++) {\n      C A0 = (fa[i] +\
    \ fa[i + (sz >> 1)]) * t;\n      C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz\
    \ >> 1) + i];\n      fa[i] = A0 + A1 * s;\n    }\n    fft(fa, sz >> 1);\n    vector<\
    \ int64_t > ret(need);\n    for(int i = 0; i < need; i++) {\n      ret[i] = llround(i\
    \ & 1 ? fa[i >> 1].y : fa[i >> 1].x);\n    }\n    return ret;\n  }\n};\n#line\
    \ 2 \"math/fft/arbitrary-mod-convolution.hpp\"\n\n/*\n * @brief Arbitrary Mod\
    \ Convolution(\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F)\n */\ntemplate< typename\
    \ T >\nstruct ArbitraryModConvolution {\n  using real = FastFourierTransform::real;\n\
    \  using C = FastFourierTransform::C;\n\n  ArbitraryModConvolution() = default;\n\
    \n  static vector< T > multiply(const vector< T > &a, const vector< T > &b, int\
    \ need = -1) {\n    if(need == -1) need = a.size() + b.size() - 1;\n    int nbase\
    \ = 0;\n    while((1 << nbase) < need) nbase++;\n    FastFourierTransform::ensure_base(nbase);\n\
    \    int sz = 1 << nbase;\n    vector< C > fa(sz);\n    for(int i = 0; i < a.size();\
    \ i++) {\n      fa[i] = C(a[i].x & ((1 << 15) - 1), a[i].x >> 15);\n    }\n  \
    \  fft(fa, sz);\n    vector< C > fb(sz);\n    if(a == b) {\n      fb = fa;\n \
    \   } else {\n      for(int i = 0; i < b.size(); i++) {\n        fb[i] = C(b[i].x\
    \ & ((1 << 15) - 1), b[i].x >> 15);\n      }\n      fft(fb, sz);\n    }\n    real\
    \ ratio = 0.25 / sz;\n    C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);\n\
    \    for(int i = 0; i <= (sz >> 1); i++) {\n      int j = (sz - i) & (sz - 1);\n\
    \      C a1 = (fa[i] + fa[j].conj());\n      C a2 = (fa[i] - fa[j].conj()) * r2;\n\
    \      C b1 = (fb[i] + fb[j].conj()) * r3;\n      C b2 = (fb[i] - fb[j].conj())\
    \ * r4;\n      if(i != j) {\n        C c1 = (fa[j] + fa[i].conj());\n        C\
    \ c2 = (fa[j] - fa[i].conj()) * r2;\n        C d1 = (fb[j] + fb[i].conj()) * r3;\n\
    \        C d2 = (fb[j] - fb[i].conj()) * r4;\n        fa[i] = c1 * d1 + c2 * d2\
    \ * r5;\n        fb[i] = c1 * d2 + c2 * d1;\n      }\n      fa[j] = a1 * b1 +\
    \ a2 * b2 * r5;\n      fb[j] = a1 * b2 + a2 * b1;\n    }\n    fft(fa, sz);\n \
    \   fft(fb, sz);\n    vector< T > ret(need);\n    for(int i = 0; i < need; i++)\
    \ {\n      int64_t aa = llround(fa[i].x);\n      int64_t bb = llround(fb[i].x);\n\
    \      int64_t cc = llround(fa[i].y);\n      aa = T(aa).x, bb = T(bb).x, cc =\
    \ T(cc).x;\n      ret[i] = aa + (bb << 15) + (cc << 30);\n    }\n    return ret;\n\
    \  }\n};\n#line 9 \"test/verify/yukicoder-502.test.cpp\"\n\nconst int MOD = (int)\
    \ (1e9 + 7);\nusing mint = ModInt< MOD >;\n\nint main() {\n  int N;\n  cin >>\
    \ N;\n  ArbitraryModConvolution< mint > fft;\n  auto f = [&](vector< mint > &a,\
    \ vector< mint > &b) { return fft.multiply(a, b); };\n  cout << factorial< mint\
    \ >(N, f) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/502\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../math/combinatorics/mod-int.hpp\"\n#include \"../../math/combinatorics/factorial.hpp\"\
    \n\n#include \"../../math/fft/arbitrary-mod-convolution.hpp\"\n\nconst int MOD\
    \ = (int) (1e9 + 7);\nusing mint = ModInt< MOD >;\n\nint main() {\n  int N;\n\
    \  cin >> N;\n  ArbitraryModConvolution< mint > fft;\n  auto f = [&](vector< mint\
    \ > &a, vector< mint > &b) { return fft.multiply(a, b); };\n  cout << factorial<\
    \ mint >(N, f) << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - math/combinatorics/factorial.hpp
  - math/combinatorics/sample-point-shift.hpp
  - math/combinatorics/enumeration.hpp
  - math/fft/arbitrary-mod-convolution.hpp
  - math/fft/fast-fourier-transform.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-502.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/verify/yukicoder-502.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-502.test.cpp
- /verify/test/verify/yukicoder-502.test.cpp.html
title: test/verify/yukicoder-502.test.cpp
---
