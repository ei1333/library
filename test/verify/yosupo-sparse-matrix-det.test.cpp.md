---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':question:'
    path: math/fft/arbitrary-mod-convolution.hpp
    title: "Arbitrary Mod Convolution(\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F)"
  - icon: ':question:'
    path: math/fft/fast-fourier-transform.hpp
    title: math/fft/fast-fourier-transform.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/berlekamp-massey.hpp
    title: Berlekamp Massey
  - icon: ':question:'
    path: math/fps/formal-power-series.hpp
    title: "Formal Power Series(\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570)"
  - icon: ':heavy_check_mark:'
    path: math/fps/sparse-matrix.hpp
    title: math/fps/sparse-matrix.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/sparse_matrix_det
    links:
    - https://judge.yosupo.jp/problem/sparse_matrix_det
  bundledCode: "#line 1 \"test/verify/yosupo-sparse-matrix-det.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n#line 1 \"\
    template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing\
    \ int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL <<\
    \ 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n\
    \    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed <<\
    \ setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-sparse-matrix-det.test.cpp\"\
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
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/yosupo-sparse-matrix-det.test.cpp\"\
    \n\n#line 1 \"math/fft/fast-fourier-transform.hpp\"\nnamespace FastFourierTransform\
    \ {\n  using real = double;\n\n  struct C {\n    real x, y;\n\n    C() : x(0),\
    \ y(0) {}\n\n    C(real x, real y) : x(x), y(y) {}\n\n    inline C operator+(const\
    \ C &c) const { return C(x + c.x, y + c.y); }\n\n    inline C operator-(const\
    \ C &c) const { return C(x - c.x, y - c.y); }\n\n    inline C operator*(const\
    \ C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }\n\n    inline\
    \ C conj() const { return C(x, -y); }\n  };\n\n  const real PI = acosl(-1);\n\
    \  int base = 1;\n  vector< C > rts = { {0, 0},\n                     {1, 0} };\n\
    \  vector< int > rev = {0, 1};\n\n\n  void ensure_base(int nbase) {\n    if(nbase\
    \ <= base) return;\n    rev.resize(1 << nbase);\n    rts.resize(1 << nbase);\n\
    \    for(int i = 0; i < (1 << nbase); i++) {\n      rev[i] = (rev[i >> 1] >> 1)\
    \ + ((i & 1) << (nbase - 1));\n    }\n    while(base < nbase) {\n      real angle\
    \ = PI * 2.0 / (1 << (base + 1));\n      for(int i = 1 << (base - 1); i < (1 <<\
    \ base); i++) {\n        rts[i << 1] = rts[i];\n        real angle_i = angle *\
    \ (2 * i + 1 - (1 << base));\n        rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));\n\
    \      }\n      ++base;\n    }\n  }\n\n  void fft(vector< C > &a, int n) {\n \
    \   assert((n & (n - 1)) == 0);\n    int zeros = __builtin_ctz(n);\n    ensure_base(zeros);\n\
    \    int shift = base - zeros;\n    for(int i = 0; i < n; i++) {\n      if(i <\
    \ (rev[i] >> shift)) {\n        swap(a[i], a[rev[i] >> shift]);\n      }\n   \
    \ }\n    for(int k = 1; k < n; k <<= 1) {\n      for(int i = 0; i < n; i += 2\
    \ * k) {\n        for(int j = 0; j < k; j++) {\n          C z = a[i + j + k] *\
    \ rts[j + k];\n          a[i + j + k] = a[i + j] - z;\n          a[i + j] = a[i\
    \ + j] + z;\n        }\n      }\n    }\n  }\n\n  vector< int64_t > multiply(const\
    \ vector< int > &a, const vector< int > &b) {\n    int need = (int) a.size() +\
    \ (int) b.size() - 1;\n    int nbase = 1;\n    while((1 << nbase) < need) nbase++;\n\
    \    ensure_base(nbase);\n    int sz = 1 << nbase;\n    vector< C > fa(sz);\n\
    \    for(int i = 0; i < sz; i++) {\n      int x = (i < (int) a.size() ? a[i] :\
    \ 0);\n      int y = (i < (int) b.size() ? b[i] : 0);\n      fa[i] = C(x, y);\n\
    \    }\n    fft(fa, sz);\n    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);\n\
    \    for(int i = 0; i <= (sz >> 1); i++) {\n      int j = (sz - i) & (sz - 1);\n\
    \      C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;\n      fa[j] = (fa[i]\
    \ * fa[i] - (fa[j] * fa[j]).conj()) * r;\n      fa[i] = z;\n    }\n    for(int\
    \ i = 0; i < (sz >> 1); i++) {\n      C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;\n\
    \      C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];\n      fa[i]\
    \ = A0 + A1 * s;\n    }\n    fft(fa, sz >> 1);\n    vector< int64_t > ret(need);\n\
    \    for(int i = 0; i < need; i++) {\n      ret[i] = llround(i & 1 ? fa[i >> 1].y\
    \ : fa[i >> 1].x);\n    }\n    return ret;\n  }\n};\n#line 2 \"math/fft/arbitrary-mod-convolution.hpp\"\
    \n\n/*\n * @brief Arbitrary Mod Convolution(\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F\
    )\n */\ntemplate< typename T >\nstruct ArbitraryModConvolution {\n  using real\
    \ = FastFourierTransform::real;\n  using C = FastFourierTransform::C;\n\n  ArbitraryModConvolution()\
    \ = default;\n\n  static vector< T > multiply(const vector< T > &a, const vector<\
    \ T > &b, int need = -1) {\n    if(need == -1) need = a.size() + b.size() - 1;\n\
    \    int nbase = 0;\n    while((1 << nbase) < need) nbase++;\n    FastFourierTransform::ensure_base(nbase);\n\
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
    \  }\n};\n#line 2 \"math/fps/formal-power-series.hpp\"\n\n/**\n * @brief Formal\
    \ Power Series(\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570)\n */\ntemplate< typename\
    \ T >\nstruct FormalPowerSeries : vector< T > {\n  using vector< T >::vector;\n\
    \  using P = FormalPowerSeries;\n  using Conv = ArbitraryModConvolution< T >;\n\
    \n  P pre(int deg) const {\n    return P(begin(*this), begin(*this) + min((int)\
    \ this->size(), deg));\n  }\n\n  P rev(int deg = -1) const {\n    P ret(*this);\n\
    \    if(deg != -1) ret.resize(deg, T(0));\n    reverse(begin(ret), end(ret));\n\
    \    return ret;\n  }\n\n  void shrink() {\n    while(this->size() && this->back()\
    \ == T(0)) this->pop_back();\n  }\n\n  P operator+(const P &r) const { return\
    \ P(*this) += r; }\n\n  P operator+(const T &v) const { return P(*this) += v;\
    \ }\n\n  P operator-(const P &r) const { return P(*this) -= r; }\n\n  P operator-(const\
    \ T &v) const { return P(*this) -= v; }\n\n  P operator*(const P &r) const { return\
    \ P(*this) *= r; }\n\n  P operator*(const T &v) const { return P(*this) *= v;\
    \ }\n\n  P operator/(const P &r) const { return P(*this) /= r; }\n\n  P operator%(const\
    \ P &r) const { return P(*this) %= r; }\n\n  P &operator+=(const P &r) {\n   \
    \ if(r.size() > this->size()) this->resize(r.size());\n    for(int i = 0; i <\
    \ r.size(); i++) (*this)[i] += r[i];\n    return *this;\n  }\n\n  P &operator-=(const\
    \ P &r) {\n    if(r.size() > this->size()) this->resize(r.size());\n    for(int\
    \ i = 0; i < r.size(); i++) (*this)[i] -= r[i];\n    return *this;\n  }\n\n  //\
    \ https://judge.yosupo.jp/problem/convolution_mod\n  P &operator*=(const P &r)\
    \ {\n    if(this->empty() || r.empty()) {\n      this->clear();\n      return\
    \ *this;\n    }\n    auto ret = Conv::multiply(*this, r);\n    return *this =\
    \ {begin(ret), end(ret)};\n  }\n\n  P &operator/=(const P &r) {\n    if(this->size()\
    \ < r.size()) {\n      this->clear();\n      return *this;\n    }\n    int n =\
    \ this->size() - r.size() + 1;\n    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\
    \  }\n\n  P &operator%=(const P &r) {\n    return *this -= *this / r * r;\n  }\n\
    \n  // https://judge.yosupo.jp/problem/division_of_polynomials\n  pair< P, P >\
    \ div_mod(const P &r) {\n    P q = *this / r;\n    return make_pair(q, *this -\
    \ q * r);\n  }\n\n  P operator-() const {\n    P ret(this->size());\n    for(int\
    \ i = 0; i < this->size(); i++) ret[i] = -(*this)[i];\n    return ret;\n  }\n\n\
    \  P &operator+=(const T &r) {\n    if(this->empty()) this->resize(1);\n    (*this)[0]\
    \ += r;\n    return *this;\n  }\n\n  P &operator-=(const T &r) {\n    if(this->empty())\
    \ this->resize(1);\n    (*this)[0] -= r;\n    return *this;\n  }\n\n  P &operator*=(const\
    \ T &v) {\n    for(int i = 0; i < this->size(); i++) (*this)[i] *= v;\n    return\
    \ *this;\n  }\n\n  P dot(P r) const {\n    P ret(min(this->size(), r.size()));\n\
    \    for(int i = 0; i < ret.size(); i++) ret[i] = (*this)[i] * r[i];\n    return\
    \ ret;\n  }\n\n  P operator>>(int sz) const {\n    if(this->size() <= sz) return\
    \ {};\n    P ret(*this);\n    ret.erase(ret.begin(), ret.begin() + sz);\n    return\
    \ ret;\n  }\n\n  P operator<<(int sz) const {\n    P ret(*this);\n    ret.insert(ret.begin(),\
    \ sz, T(0));\n    return ret;\n  }\n\n  T operator()(T x) const {\n    T r = 0,\
    \ w = 1;\n    for(auto &v : *this) {\n      r += w * v;\n      w *= x;\n    }\n\
    \    return r;\n  }\n\n  P diff() const {\n    const int n = (int) this->size();\n\
    \    P ret(max(0, n - 1));\n    for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i]\
    \ * T(i);\n    return ret;\n  }\n\n  P integral() const {\n    const int n = (int)\
    \ this->size();\n    P ret(n + 1);\n    ret[0] = T(0);\n    for(int i = 0; i <\
    \ n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/inv_of_formal_power_series\n\
    \  // F(0) must not be 0\n  P inv(int deg = -1) const {\n    assert(((*this)[0])\
    \ != T(0));\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    P ret({T(1) / (*this)[0]});\n    for(int i = 1; i < deg; i <<= 1) {\n   \
    \   ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);\n    }\n    return\
    \ ret.pre(deg);\n  }\n\n  // https://judge.yosupo.jp/problem/log_of_formal_power_series\n\
    \  // F(0) must be 1\n  P log(int deg = -1) const {\n    assert((*this)[0] ==\
    \ T(1));\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();\n  }\n\n\
    \  // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series\n  P sqrt(int\
    \ deg = -1, const function< T(T) > &get_sqrt = [](T) { return T(1); }) const {\n\
    \    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n    if((*this)[0]\
    \ == T(0)) {\n      for(int i = 1; i < n; i++) {\n        if((*this)[i] != T(0))\
    \ {\n          if(i & 1) return {};\n          if(deg - i / 2 <= 0) break;\n \
    \         auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);\n          if(ret.empty())\
    \ return {};\n          ret = ret << (i / 2);\n          if(ret.size() < deg)\
    \ ret.resize(deg, T(0));\n          return ret;\n        }\n      }\n      return\
    \ P(deg, 0);\n    }\n    auto sqr = T(get_sqrt((*this)[0]));\n    if(sqr * sqr\
    \ != (*this)[0]) return {};\n    P ret{sqr};\n    T inv2 = T(1) / T(2);\n    for(int\
    \ i = 1; i < deg; i <<= 1) {\n      ret = (ret + pre(i << 1) * ret.inv(i << 1))\
    \ * inv2;\n    }\n    return ret.pre(deg);\n  }\n\n  P sqrt(const function< T(T)\
    \ > &get_sqrt, int deg = -1) const {\n    return sqrt(deg, get_sqrt);\n  }\n\n\
    \  // https://judge.yosupo.jp/problem/exp_of_formal_power_series\n  // F(0) must\
    \ be 0\n  P exp(int deg = -1) const {\n    if(deg == -1) deg = this->size();\n\
    \    assert((*this)[0] == T(0));\n    const int n = (int) this->size();\n    if(deg\
    \ == -1) deg = n;\n    P ret({T(1)});\n    for(int i = 1; i < deg; i <<= 1) {\n\
    \      ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);\n   \
    \ }\n    return ret.pre(deg);\n  }\n\n  // https://judge.yosupo.jp/problem/pow_of_formal_power_series\n\
    \  P pow(int64_t k, int deg = -1) const {\n    const int n = (int) this->size();\n\
    \    if(deg == -1) deg = n;\n    for(int i = 0; i < n; i++) {\n      if((*this)[i]\
    \ != T(0)) {\n        T rev = T(1) / (*this)[i];\n        P ret = (((*this * rev)\
    \ >> i).log() * k).exp() * ((*this)[i].pow(k));\n        if(i * k > deg) return\
    \ P(deg, T(0));\n        ret = (ret << (i * k)).pre(deg);\n        if(ret.size()\
    \ < deg) ret.resize(deg, T(0));\n        return ret;\n      }\n    }\n    return\
    \ *this;\n  }\n\n  // https://yukicoder.me/problems/no/215\n  P mod_pow(int64_t\
    \ k, P g) const {\n    P modinv = g.rev().inv();\n    auto get_div = [&](P base)\
    \ {\n      if(base.size() < g.size()) {\n        base.clear();\n        return\
    \ base;\n      }\n      int n = base.size() - g.size() + 1;\n      return (base.rev().pre(n)\
    \ * modinv.pre(n)).pre(n).rev(n);\n    };\n    P x(*this), ret{1};\n    while(k\
    \ > 0) {\n      if(k & 1) {\n        ret *= x;\n        ret -= get_div(ret) *\
    \ g;\n        ret.shrink();\n      }\n      x *= x;\n      x -= get_div(x) * g;\n\
    \      x.shrink();\n      k >>= 1;\n    }\n    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/polynomial_taylor_shift\n\
    \  P taylor_shift(T c) const {\n    int n = (int) this->size();\n    vector< T\
    \ > fact(n), rfact(n);\n    fact[0] = rfact[0] = T(1);\n    for(int i = 1; i <\
    \ n; i++) fact[i] = fact[i - 1] * T(i);\n    rfact[n - 1] = T(1) / fact[n - 1];\n\
    \    for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);\n    P p(*this);\n\
    \    for(int i = 0; i < n; i++) p[i] *= fact[i];\n    p = p.rev();\n    P bs(n,\
    \ T(1));\n    for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i\
    \ - 1];\n    p = (p * bs).pre(n);\n    p = p.rev();\n    for(int i = 0; i < n;\
    \ i++) p[i] *= rfact[i];\n    return p;\n  }\n};\n\n\ntemplate< typename Mint\
    \ >\nusing FPS = FormalPowerSeries< Mint >;\n#line 8 \"test/verify/yosupo-sparse-matrix-det.test.cpp\"\
    \n\n#line 1 \"math/fps/berlekamp-massey.hpp\"\n/**\n * @brief Berlekamp Massey\n\
    \ */\ntemplate< template< typename > class FPS, typename Mint >\nFPS< Mint > berlekamp_massey(const\
    \ FPS< Mint > &s) {\n  const int N = (int) s.size();\n  FPS< Mint > b = {Mint(-1)},\
    \ c = {Mint(-1)};\n  Mint y = Mint(1);\n  for(int ed = 1; ed <= N; ed++) {\n \
    \   int l = int(c.size()), m = int(b.size());\n    Mint x = 0;\n    for(int i\
    \ = 0; i < l; i++) x += c[i] * s[ed - l + i];\n    b.emplace_back(0);\n    m++;\n\
    \    if(x == Mint(0)) continue;\n    Mint freq = x / y;\n    if(l < m) {\n   \
    \   auto tmp = c;\n      c.insert(begin(c), m - l, Mint(0));\n      for(int i\
    \ = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];\n      b = tmp;\n    \
    \  y = x;\n    } else {\n      for(int i = 0; i < m; i++) c[l - 1 - i] -= freq\
    \ * b[m - 1 - i];\n    }\n  }\n  return c;\n}\n#line 1 \"math/fps/sparse-matrix.hpp\"\
    \ntemplate< typename T >\nusing FPSGraph = vector< vector< pair< int, T > > >;\n\
    \ntemplate< typename T >\nFormalPowerSeries< T > random_poly(int n) {\n  mt19937\
    \ mt(1333333);\n  FormalPowerSeries< T > res(n);\n  uniform_int_distribution<\
    \ int > rand(0, T::get_mod() - 1);\n  for(int i = 0; i < n; i++) res[i] = rand(mt);\n\
    \  return res;\n}\n\ntemplate< typename T >\nFormalPowerSeries< T > next_poly(const\
    \ FormalPowerSeries< T > &dp, const FPSGraph< T > &g) {\n  const int N = (int)\
    \ dp.size();\n  FormalPowerSeries< T > nxt(N);\n  for(int i = 0; i < N; i++) {\n\
    \    for(auto &p : g[i]) nxt[p.first] += p.second * dp[i];\n  }\n  return nxt;\n\
    }\n\ntemplate< typename T >\nFormalPowerSeries< T > minimum_poly(const FPSGraph<\
    \ T > &g) {\n  const int N = (int) g.size();\n  auto dp = random_poly< T >(N),\
    \ u = random_poly< T >(N);\n  FormalPowerSeries< T > f(2 * N);\n  for(int i =\
    \ 0; i < 2 * N; i++) {\n    for(auto &p : u.dot(dp)) f[i] += p;\n    dp = next_poly(dp,\
    \ g);\n  }\n  return berlekamp_massey(f);\n}\n\n/* O(N(N+S) + N log N log Q) (O(S):\
    \ time complexity of nex) */\ntemplate< typename T >\nFormalPowerSeries< T > sparse_pow(int64_t\
    \ Q, FormalPowerSeries< T > dp, const FPSGraph< T > &g) {\n  const int N = (int)\
    \ dp.size();\n  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly(g));\n\
    \  FormalPowerSeries< T > res(N);\n  for(int i = 0; i < A.size(); i++) {\n   \
    \ res += dp * A[i];\n    dp = next_poly(dp, g);\n  }\n  return res;\n}\n\n/* O(N(N+S))\
    \ (S: none-zero elements)*/\ntemplate< typename T >\nT sparse_determinant(FPSGraph<\
    \ T > g) {\n  using FPS = FormalPowerSeries< T >;\n  int N = (int) g.size();\n\
    \  auto C = random_poly< T >(N);\n  for(int i = 0; i < N; i++) for(auto &p : g[i])\
    \ p.second *= C[i];\n  auto u = minimum_poly(g);\n  T acdet = u[0];\n  if(N %\
    \ 2 == 0) acdet *= -1;\n  T cdet = 1;\n  for(int i = 0; i < N; i++) cdet *= C[i];\n\
    \  return acdet / cdet;\n}\n#line 11 \"test/verify/yosupo-sparse-matrix-det.test.cpp\"\
    \n\nconst int MOD = 998244353;\nusing mint = ModInt< MOD >;\n\nint main() {\n\
    \  int N, K;\n  cin >> N >> K;\n  FPSGraph< mint > g(N);\n  for(int i = 0; i <\
    \ K; i++) {\n    int a, b, c;\n    cin >> a >> b >> c;\n    g[a].emplace_back(b,\
    \ c);\n  }\n  cout << sparse_determinant(g) << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../math/fps/formal-power-series.hpp\"\n\n#include \"../../math/fps/berlekamp-massey.hpp\"\
    \n#include \"../../math/fps/sparse-matrix.hpp\"\n\nconst int MOD = 998244353;\n\
    using mint = ModInt< MOD >;\n\nint main() {\n  int N, K;\n  cin >> N >> K;\n \
    \ FPSGraph< mint > g(N);\n  for(int i = 0; i < K; i++) {\n    int a, b, c;\n \
    \   cin >> a >> b >> c;\n    g[a].emplace_back(b, c);\n  }\n  cout << sparse_determinant(g)\
    \ << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - math/fps/formal-power-series.hpp
  - math/fft/arbitrary-mod-convolution.hpp
  - math/fft/fast-fourier-transform.hpp
  - math/fps/berlekamp-massey.hpp
  - math/fps/sparse-matrix.hpp
  isVerificationFile: true
  path: test/verify/yosupo-sparse-matrix-det.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-sparse-matrix-det.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-sparse-matrix-det.test.cpp
- /verify/test/verify/yosupo-sparse-matrix-det.test.cpp.html
title: test/verify/yosupo-sparse-matrix-det.test.cpp
---
