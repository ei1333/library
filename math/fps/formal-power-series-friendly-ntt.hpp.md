---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft/number-theoretic-transform-friendly-mod-int.hpp
    title: Number Theoretic Transform Friendly ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bernoulli-number.test.cpp
    title: test/verify/yosupo-bernoulli-number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-division-of-polynomials.test.cpp
    title: test/verify/yosupo-division-of-polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-exp-of-formal-power-series.test.cpp
    title: test/verify/yosupo-exp-of-formal-power-series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-find-linear-recurrence.test.cpp
    title: test/verify/yosupo-find-linear-recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-inv-of-formal-power-series.test.cpp
    title: test/verify/yosupo-inv-of-formal-power-series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-kth-term-of-linearly-recurrent-sequence.test.cpp
    title: test/verify/yosupo-kth-term-of-linearly-recurrent-sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-log-of-formal-power-series.test.cpp
    title: test/verify/yosupo-log-of-formal-power-series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-multipoint-evaluation.test.cpp
    title: test/verify/yosupo-multipoint-evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-partition-function.test.cpp
    title: test/verify/yosupo-partition-function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-polynomial-interpolation.test.cpp
    title: test/verify/yosupo-polynomial-interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-polynomial-taylor-shift.test.cpp
    title: test/verify/yosupo-polynomial-taylor-shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-pow-of-formal-power-series.test.cpp
    title: test/verify/yosupo-pow-of-formal-power-series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-sharp-p-subset-sum.test.cpp
    title: test/verify/yosupo-sharp-p-subset-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
    title: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
    - https://judge.yosupo.jp/problem/division_of_polynomials
    - https://judge.yosupo.jp/problem/exp_of_formal_power_series
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
    - https://judge.yosupo.jp/problem/log_of_formal_power_series
    - https://judge.yosupo.jp/problem/polynomial_taylor_shift
    - https://judge.yosupo.jp/problem/pow_of_formal_power_series
    - https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
  bundledCode: "#line 2 \"math/fps/formal-power-series-friendly-ntt.hpp\"\n\n#line\
    \ 1 \"math/fft/number-theoretic-transform-friendly-mod-int.hpp\"\n/**\n * @brief\
    \ Number Theoretic Transform Friendly ModInt\n */\ntemplate< typename Mint >\n\
    struct NumberTheoreticTransformFriendlyModInt {\n\n  static vector< Mint > roots,\
    \ iroots, rate3, irate3;\n  static int max_base;\n\n  NumberTheoreticTransformFriendlyModInt()\
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
    \ Mint >::max_base = 0;\n#line 4 \"math/fps/formal-power-series-friendly-ntt.hpp\"\
    \n\ntemplate< typename T >\nstruct FormalPowerSeriesFriendlyNTT : vector< T >\
    \ {\n  using vector< T >::vector;\n  using P = FormalPowerSeriesFriendlyNTT;\n\
    \  using NTT = NumberTheoreticTransformFriendlyModInt< T >;\n\n  P pre(int deg)\
    \ const {\n    return P(begin(*this), begin(*this) + min((int) this->size(), deg));\n\
    \  }\n\n  P rev(int deg = -1) const {\n    P ret(*this);\n    if(deg != -1) ret.resize(deg,\
    \ T(0));\n    reverse(begin(ret), end(ret));\n    return ret;\n  }\n\n  void shrink()\
    \ {\n    while(this->size() && this->back() == T(0)) this->pop_back();\n  }\n\n\
    \  P operator+(const P &r) const { return P(*this) += r; }\n\n  P operator+(const\
    \ T &v) const { return P(*this) += v; }\n\n  P operator-(const P &r) const { return\
    \ P(*this) -= r; }\n\n  P operator-(const T &v) const { return P(*this) -= v;\
    \ }\n\n  P operator*(const P &r) const { return P(*this) *= r; }\n\n  P operator*(const\
    \ T &v) const { return P(*this) *= v; }\n\n  P operator/(const P &r) const { return\
    \ P(*this) /= r; }\n\n  P operator%(const P &r) const { return P(*this) %= r;\
    \ }\n\n  P &operator+=(const P &r) {\n    if(r.size() > this->size()) this->resize(r.size());\n\
    \    for(int i = 0; i < (int) r.size(); i++) (*this)[i] += r[i];\n    return *this;\n\
    \  }\n\n  P &operator-=(const P &r) {\n    if(r.size() > this->size()) this->resize(r.size());\n\
    \    for(int i = 0; i < (int) r.size(); i++) (*this)[i] -= r[i];\n    return *this;\n\
    \  }\n\n  // https://judge.yosupo.jp/problem/convolution_mod\n  P &operator*=(const\
    \ P &r) {\n    if(this->empty() || r.empty()) {\n      this->clear();\n      return\
    \ *this;\n    }\n    auto ret = NTT::multiply(*this, r);\n    return *this = {begin(ret),\
    \ end(ret)};\n  }\n\n  P &operator/=(const P &r) {\n    if(this->size() < r.size())\
    \ {\n      this->clear();\n      return *this;\n    }\n    int n = this->size()\
    \ - r.size() + 1;\n    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\
    \  }\n\n  P &operator%=(const P &r) {\n    *this -= *this / r * r;\n    shrink();\n\
    \    return *this;\n  }\n\n  // https://judge.yosupo.jp/problem/division_of_polynomials\n\
    \  pair< P, P > div_mod(const P &r) {\n    P q = *this / r;\n    P x = *this -\
    \ q * r;\n    x.shrink();\n    return make_pair(q, x);\n  }\n\n  P operator-()\
    \ const {\n    P ret(this->size());\n    for(int i = 0; i < (int) this->size();\
    \ i++) ret[i] = -(*this)[i];\n    return ret;\n  }\n\n  P &operator+=(const T\
    \ &r) {\n    if(this->empty()) this->resize(1);\n    (*this)[0] += r;\n    return\
    \ *this;\n  }\n\n  P &operator-=(const T &r) {\n    if(this->empty()) this->resize(1);\n\
    \    (*this)[0] -= r;\n    return *this;\n  }\n\n  P &operator*=(const T &v) {\n\
    \    for(int i = 0; i < (int) this->size(); i++) (*this)[i] *= v;\n    return\
    \ *this;\n  }\n\n  P dot(P r) const {\n    P ret(min(this->size(), r.size()));\n\
    \    for(int i = 0; i < (int) ret.size(); i++) ret[i] = (*this)[i] * r[i];\n \
    \   return ret;\n  }\n\n  P operator>>(int sz) const {\n    if((int) this->size()\
    \ <= sz) return {};\n    P ret(*this);\n    ret.erase(ret.begin(), ret.begin()\
    \ + sz);\n    return ret;\n  }\n\n  P operator<<(int sz) const {\n    P ret(*this);\n\
    \    ret.insert(ret.begin(), sz, T(0));\n    return ret;\n  }\n\n  T operator()(T\
    \ x) const {\n    T r = 0, w = 1;\n    for(auto &v : *this) {\n      r += w *\
    \ v;\n      w *= x;\n    }\n    return r;\n  }\n\n  P diff() const {\n    const\
    \ int n = (int) this->size();\n    P ret(max(0, n - 1));\n    for(int i = 1; i\
    \ < n; i++) ret[i - 1] = (*this)[i] * T(i);\n    return ret;\n  }\n\n  P integral()\
    \ const {\n    const int n = (int) this->size();\n    P ret(n + 1);\n    ret[0]\
    \ = T(0);\n    for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n\
    \    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/inv_of_formal_power_series\n\
    \  // F(0) must not be 0\n  P inv(int deg = -1) const {\n    assert(((*this)[0])\
    \ != T(0));\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    P res(deg);\n    res[0] = {T(1) / (*this)[0]};\n    for(int d = 1; d < deg;\
    \ d <<= 1) {\n      P f(2 * d), g(2 * d);\n      for(int j = 0; j < min(n, 2 *\
    \ d); j++) f[j] = (*this)[j];\n      for(int j = 0; j < d; j++) g[j] = res[j];\n\
    \      NTT::ntt(f);\n      NTT::ntt(g);\n      f = f.dot(g);\n      NTT::intt(f);\n\
    \      for(int j = 0; j < d; j++) f[j] = 0;\n      NTT::ntt(f);\n      for(int\
    \ j = 0; j < 2 * d; j++) f[j] *= g[j];\n      NTT::intt(f);\n      for(int j =\
    \ d; j < min(2 * d, deg); j++) res[j] = -f[j];\n    }\n    return res;\n  }\n\n\
    \  // https://judge.yosupo.jp/problem/log_of_formal_power_series\n  // F(0) must\
    \ be 1\n  P log(int deg = -1) const {\n    assert((*this)[0] == T(1));\n    const\
    \ int n = (int) this->size();\n    if(deg == -1) deg = n;\n    return (this->diff()\
    \ * this->inv(deg)).pre(deg - 1).integral();\n  }\n\n  // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series\n\
    \  P sqrt(int deg = -1, const function< T(T) > &get_sqrt = [](T) { return T(1);\
    \ }) const {\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    if((*this)[0] == T(0)) {\n      for(int i = 1; i < n; i++) {\n        if((*this)[i]\
    \ != T(0)) {\n          if(i & 1) return {};\n          if(deg - i / 2 <= 0) break;\n\
    \          auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);\n          if(ret.empty())\
    \ return {};\n          ret = ret << (i / 2);\n          if((int) ret.size() <\
    \ deg) ret.resize(deg, T(0));\n          return ret;\n        }\n      }\n   \
    \   return P(deg, 0);\n    }\n    auto sqr = T(get_sqrt((*this)[0]));\n    if(sqr\
    \ * sqr != (*this)[0]) return {};\n    P ret{sqr};\n    T inv2 = T(1) / T(2);\n\
    \    for(int i = 1; i < deg; i <<= 1) {\n      ret = (ret + pre(i << 1) * ret.inv(i\
    \ << 1)) * inv2;\n    }\n    return ret.pre(deg);\n  }\n\n  P sqrt(const function<\
    \ T(T) > &get_sqrt, int deg = -1) const {\n    return sqrt(deg, get_sqrt);\n \
    \ }\n\n  // https://judge.yosupo.jp/problem/exp_of_formal_power_series\n  // F(0)\
    \ must be 0\n  P exp(int deg = -1) const {\n    if(deg == -1) deg = this->size();\n\
    \    assert((*this)[0] == T(0));\n\n    P inv;\n    inv.reserve(deg + 1);\n  \
    \  inv.push_back(T(0));\n    inv.push_back(T(1));\n\n    auto inplace_integral\
    \ = [&](P &F) -> void {\n      const int n = (int) F.size();\n      auto mod =\
    \ T::get_mod();\n      while((int) inv.size() <= n) {\n        int i = inv.size();\n\
    \        inv.push_back((-inv[mod % i]) * (mod / i));\n      }\n      F.insert(begin(F),\
    \ T(0));\n      for(int i = 1; i <= n; i++) F[i] *= inv[i];\n    };\n\n    auto\
    \ inplace_diff = [](P &F) -> void {\n      if(F.empty()) return;\n      F.erase(begin(F));\n\
    \      T coeff = 1, one = 1;\n      for(int i = 0; i < (int) F.size(); i++) {\n\
    \        F[i] *= coeff;\n        coeff += one;\n      }\n    };\n\n    P b{1,\
    \ 1 < (int) this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};\n    for(int m\
    \ = 2; m < deg; m *= 2) {\n      auto y = b;\n      y.resize(2 * m);\n      NTT::ntt(y);\n\
    \      z1 = z2;\n      P z(m);\n      for(int i = 0; i < m; ++i) z[i] = y[i] *\
    \ z1[i];\n      NTT::intt(z);\n      fill(begin(z), begin(z) + m / 2, T(0));\n\
    \      NTT::ntt(z);\n      for(int i = 0; i < m; ++i) z[i] *= -z1[i];\n      NTT::intt(z);\n\
    \      c.insert(end(c), begin(z) + m / 2, end(z));\n      z2 = c;\n      z2.resize(2\
    \ * m);\n      NTT::ntt(z2);\n      P x(begin(*this), begin(*this) + min< int\
    \ >(this->size(), m));\n      inplace_diff(x);\n      x.push_back(T(0));\n   \
    \   NTT::ntt(x);\n      for(int i = 0; i < m; ++i) x[i] *= y[i];\n      NTT::intt(x);\n\
    \      x -= b.diff();\n      x.resize(2 * m);\n      for(int i = 0; i < m - 1;\
    \ ++i) x[m + i] = x[i], x[i] = T(0);\n      NTT::ntt(x);\n      for(int i = 0;\
    \ i < 2 * m; ++i) x[i] *= z2[i];\n      NTT::intt(x);\n      x.pop_back();\n \
    \     inplace_integral(x);\n      for(int i = m; i < min< int >(this->size(),\
    \ 2 * m); ++i) x[i] += (*this)[i];\n      fill(begin(x), begin(x) + m, T(0));\n\
    \      NTT::ntt(x);\n      for(int i = 0; i < 2 * m; ++i) x[i] *= y[i];\n    \
    \  NTT::intt(x);\n      b.insert(end(b), begin(x) + m, end(x));\n    }\n    return\
    \ P{begin(b), begin(b) + deg};\n  }\n\n  // https://judge.yosupo.jp/problem/pow_of_formal_power_series\n\
    \  P pow(int64_t k, int deg = -1) const {\n    const int n = (int) this->size();\n\
    \    if(deg == -1) deg = n;\n    if(k == 0) {\n      P ret(deg, T(0));\n     \
    \ ret[0] = T(1);\n      return ret;\n    }\n    for(int i = 0; i < n; i++) {\n\
    \      if(i * k > deg) return P(deg, T(0));\n      if((*this)[i] != T(0)) {\n\
    \        T rev = T(1) / (*this)[i];\n        P ret = (((*this * rev) >> i).log()\
    \ * k).exp() * ((*this)[i].pow(k));\n        ret = (ret << (i * k)).pre(deg);\n\
    \        if((int) ret.size() < deg) ret.resize(deg, T(0));\n        return ret;\n\
    \      }\n    }\n    return *this;\n  }\n\n  P mod_pow(int64_t k, P g) const {\n\
    \    P modinv = g.rev().inv();\n    auto get_div = [&](P base) {\n      if(base.size()\
    \ < g.size()) {\n        base.clear();\n        return base;\n      }\n      int\
    \ n = base.size() - g.size() + 1;\n      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);\n\
    \    };\n    P x(*this), ret{1};\n    while(k > 0) {\n      if(k & 1) {\n    \
    \    ret *= x;\n        ret -= get_div(ret) * g;\n        ret.shrink();\n    \
    \  }\n      x *= x;\n      x -= get_div(x) * g;\n      x.shrink();\n      k >>=\
    \ 1;\n    }\n    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/polynomial_taylor_shift\n\
    \  P taylor_shift(T c) const {\n    int n = (int) this->size();\n    vector< T\
    \ > fact(n), rfact(n);\n    fact[0] = rfact[0] = T(1);\n    for(int i = 1; i <\
    \ n; i++) fact[i] = fact[i - 1] * T(i);\n    rfact[n - 1] = T(1) / fact[n - 1];\n\
    \    for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);\n    P p(*this);\n\
    \    for(int i = 0; i < n; i++) p[i] *= fact[i];\n    p = p.rev();\n    P bs(n,\
    \ T(1));\n    for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i\
    \ - 1];\n    p = (p * bs).pre(n);\n    p = p.rev();\n    for(int i = 0; i < n;\
    \ i++) p[i] *= rfact[i];\n    return p;\n  }\n};\n\ntemplate< typename Mint >\n\
    using FPS = FormalPowerSeriesFriendlyNTT< Mint >;\n"
  code: "#pragma once\n\n#include \"../fft/number-theoretic-transform-friendly-mod-int.hpp\"\
    \n\ntemplate< typename T >\nstruct FormalPowerSeriesFriendlyNTT : vector< T >\
    \ {\n  using vector< T >::vector;\n  using P = FormalPowerSeriesFriendlyNTT;\n\
    \  using NTT = NumberTheoreticTransformFriendlyModInt< T >;\n\n  P pre(int deg)\
    \ const {\n    return P(begin(*this), begin(*this) + min((int) this->size(), deg));\n\
    \  }\n\n  P rev(int deg = -1) const {\n    P ret(*this);\n    if(deg != -1) ret.resize(deg,\
    \ T(0));\n    reverse(begin(ret), end(ret));\n    return ret;\n  }\n\n  void shrink()\
    \ {\n    while(this->size() && this->back() == T(0)) this->pop_back();\n  }\n\n\
    \  P operator+(const P &r) const { return P(*this) += r; }\n\n  P operator+(const\
    \ T &v) const { return P(*this) += v; }\n\n  P operator-(const P &r) const { return\
    \ P(*this) -= r; }\n\n  P operator-(const T &v) const { return P(*this) -= v;\
    \ }\n\n  P operator*(const P &r) const { return P(*this) *= r; }\n\n  P operator*(const\
    \ T &v) const { return P(*this) *= v; }\n\n  P operator/(const P &r) const { return\
    \ P(*this) /= r; }\n\n  P operator%(const P &r) const { return P(*this) %= r;\
    \ }\n\n  P &operator+=(const P &r) {\n    if(r.size() > this->size()) this->resize(r.size());\n\
    \    for(int i = 0; i < (int) r.size(); i++) (*this)[i] += r[i];\n    return *this;\n\
    \  }\n\n  P &operator-=(const P &r) {\n    if(r.size() > this->size()) this->resize(r.size());\n\
    \    for(int i = 0; i < (int) r.size(); i++) (*this)[i] -= r[i];\n    return *this;\n\
    \  }\n\n  // https://judge.yosupo.jp/problem/convolution_mod\n  P &operator*=(const\
    \ P &r) {\n    if(this->empty() || r.empty()) {\n      this->clear();\n      return\
    \ *this;\n    }\n    auto ret = NTT::multiply(*this, r);\n    return *this = {begin(ret),\
    \ end(ret)};\n  }\n\n  P &operator/=(const P &r) {\n    if(this->size() < r.size())\
    \ {\n      this->clear();\n      return *this;\n    }\n    int n = this->size()\
    \ - r.size() + 1;\n    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\
    \  }\n\n  P &operator%=(const P &r) {\n    *this -= *this / r * r;\n    shrink();\n\
    \    return *this;\n  }\n\n  // https://judge.yosupo.jp/problem/division_of_polynomials\n\
    \  pair< P, P > div_mod(const P &r) {\n    P q = *this / r;\n    P x = *this -\
    \ q * r;\n    x.shrink();\n    return make_pair(q, x);\n  }\n\n  P operator-()\
    \ const {\n    P ret(this->size());\n    for(int i = 0; i < (int) this->size();\
    \ i++) ret[i] = -(*this)[i];\n    return ret;\n  }\n\n  P &operator+=(const T\
    \ &r) {\n    if(this->empty()) this->resize(1);\n    (*this)[0] += r;\n    return\
    \ *this;\n  }\n\n  P &operator-=(const T &r) {\n    if(this->empty()) this->resize(1);\n\
    \    (*this)[0] -= r;\n    return *this;\n  }\n\n  P &operator*=(const T &v) {\n\
    \    for(int i = 0; i < (int) this->size(); i++) (*this)[i] *= v;\n    return\
    \ *this;\n  }\n\n  P dot(P r) const {\n    P ret(min(this->size(), r.size()));\n\
    \    for(int i = 0; i < (int) ret.size(); i++) ret[i] = (*this)[i] * r[i];\n \
    \   return ret;\n  }\n\n  P operator>>(int sz) const {\n    if((int) this->size()\
    \ <= sz) return {};\n    P ret(*this);\n    ret.erase(ret.begin(), ret.begin()\
    \ + sz);\n    return ret;\n  }\n\n  P operator<<(int sz) const {\n    P ret(*this);\n\
    \    ret.insert(ret.begin(), sz, T(0));\n    return ret;\n  }\n\n  T operator()(T\
    \ x) const {\n    T r = 0, w = 1;\n    for(auto &v : *this) {\n      r += w *\
    \ v;\n      w *= x;\n    }\n    return r;\n  }\n\n  P diff() const {\n    const\
    \ int n = (int) this->size();\n    P ret(max(0, n - 1));\n    for(int i = 1; i\
    \ < n; i++) ret[i - 1] = (*this)[i] * T(i);\n    return ret;\n  }\n\n  P integral()\
    \ const {\n    const int n = (int) this->size();\n    P ret(n + 1);\n    ret[0]\
    \ = T(0);\n    for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n\
    \    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/inv_of_formal_power_series\n\
    \  // F(0) must not be 0\n  P inv(int deg = -1) const {\n    assert(((*this)[0])\
    \ != T(0));\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    P res(deg);\n    res[0] = {T(1) / (*this)[0]};\n    for(int d = 1; d < deg;\
    \ d <<= 1) {\n      P f(2 * d), g(2 * d);\n      for(int j = 0; j < min(n, 2 *\
    \ d); j++) f[j] = (*this)[j];\n      for(int j = 0; j < d; j++) g[j] = res[j];\n\
    \      NTT::ntt(f);\n      NTT::ntt(g);\n      f = f.dot(g);\n      NTT::intt(f);\n\
    \      for(int j = 0; j < d; j++) f[j] = 0;\n      NTT::ntt(f);\n      for(int\
    \ j = 0; j < 2 * d; j++) f[j] *= g[j];\n      NTT::intt(f);\n      for(int j =\
    \ d; j < min(2 * d, deg); j++) res[j] = -f[j];\n    }\n    return res;\n  }\n\n\
    \  // https://judge.yosupo.jp/problem/log_of_formal_power_series\n  // F(0) must\
    \ be 1\n  P log(int deg = -1) const {\n    assert((*this)[0] == T(1));\n    const\
    \ int n = (int) this->size();\n    if(deg == -1) deg = n;\n    return (this->diff()\
    \ * this->inv(deg)).pre(deg - 1).integral();\n  }\n\n  // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series\n\
    \  P sqrt(int deg = -1, const function< T(T) > &get_sqrt = [](T) { return T(1);\
    \ }) const {\n    const int n = (int) this->size();\n    if(deg == -1) deg = n;\n\
    \    if((*this)[0] == T(0)) {\n      for(int i = 1; i < n; i++) {\n        if((*this)[i]\
    \ != T(0)) {\n          if(i & 1) return {};\n          if(deg - i / 2 <= 0) break;\n\
    \          auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);\n          if(ret.empty())\
    \ return {};\n          ret = ret << (i / 2);\n          if((int) ret.size() <\
    \ deg) ret.resize(deg, T(0));\n          return ret;\n        }\n      }\n   \
    \   return P(deg, 0);\n    }\n    auto sqr = T(get_sqrt((*this)[0]));\n    if(sqr\
    \ * sqr != (*this)[0]) return {};\n    P ret{sqr};\n    T inv2 = T(1) / T(2);\n\
    \    for(int i = 1; i < deg; i <<= 1) {\n      ret = (ret + pre(i << 1) * ret.inv(i\
    \ << 1)) * inv2;\n    }\n    return ret.pre(deg);\n  }\n\n  P sqrt(const function<\
    \ T(T) > &get_sqrt, int deg = -1) const {\n    return sqrt(deg, get_sqrt);\n \
    \ }\n\n  // https://judge.yosupo.jp/problem/exp_of_formal_power_series\n  // F(0)\
    \ must be 0\n  P exp(int deg = -1) const {\n    if(deg == -1) deg = this->size();\n\
    \    assert((*this)[0] == T(0));\n\n    P inv;\n    inv.reserve(deg + 1);\n  \
    \  inv.push_back(T(0));\n    inv.push_back(T(1));\n\n    auto inplace_integral\
    \ = [&](P &F) -> void {\n      const int n = (int) F.size();\n      auto mod =\
    \ T::get_mod();\n      while((int) inv.size() <= n) {\n        int i = inv.size();\n\
    \        inv.push_back((-inv[mod % i]) * (mod / i));\n      }\n      F.insert(begin(F),\
    \ T(0));\n      for(int i = 1; i <= n; i++) F[i] *= inv[i];\n    };\n\n    auto\
    \ inplace_diff = [](P &F) -> void {\n      if(F.empty()) return;\n      F.erase(begin(F));\n\
    \      T coeff = 1, one = 1;\n      for(int i = 0; i < (int) F.size(); i++) {\n\
    \        F[i] *= coeff;\n        coeff += one;\n      }\n    };\n\n    P b{1,\
    \ 1 < (int) this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};\n    for(int m\
    \ = 2; m < deg; m *= 2) {\n      auto y = b;\n      y.resize(2 * m);\n      NTT::ntt(y);\n\
    \      z1 = z2;\n      P z(m);\n      for(int i = 0; i < m; ++i) z[i] = y[i] *\
    \ z1[i];\n      NTT::intt(z);\n      fill(begin(z), begin(z) + m / 2, T(0));\n\
    \      NTT::ntt(z);\n      for(int i = 0; i < m; ++i) z[i] *= -z1[i];\n      NTT::intt(z);\n\
    \      c.insert(end(c), begin(z) + m / 2, end(z));\n      z2 = c;\n      z2.resize(2\
    \ * m);\n      NTT::ntt(z2);\n      P x(begin(*this), begin(*this) + min< int\
    \ >(this->size(), m));\n      inplace_diff(x);\n      x.push_back(T(0));\n   \
    \   NTT::ntt(x);\n      for(int i = 0; i < m; ++i) x[i] *= y[i];\n      NTT::intt(x);\n\
    \      x -= b.diff();\n      x.resize(2 * m);\n      for(int i = 0; i < m - 1;\
    \ ++i) x[m + i] = x[i], x[i] = T(0);\n      NTT::ntt(x);\n      for(int i = 0;\
    \ i < 2 * m; ++i) x[i] *= z2[i];\n      NTT::intt(x);\n      x.pop_back();\n \
    \     inplace_integral(x);\n      for(int i = m; i < min< int >(this->size(),\
    \ 2 * m); ++i) x[i] += (*this)[i];\n      fill(begin(x), begin(x) + m, T(0));\n\
    \      NTT::ntt(x);\n      for(int i = 0; i < 2 * m; ++i) x[i] *= y[i];\n    \
    \  NTT::intt(x);\n      b.insert(end(b), begin(x) + m, end(x));\n    }\n    return\
    \ P{begin(b), begin(b) + deg};\n  }\n\n  // https://judge.yosupo.jp/problem/pow_of_formal_power_series\n\
    \  P pow(int64_t k, int deg = -1) const {\n    const int n = (int) this->size();\n\
    \    if(deg == -1) deg = n;\n    if(k == 0) {\n      P ret(deg, T(0));\n     \
    \ ret[0] = T(1);\n      return ret;\n    }\n    for(int i = 0; i < n; i++) {\n\
    \      if(i * k > deg) return P(deg, T(0));\n      if((*this)[i] != T(0)) {\n\
    \        T rev = T(1) / (*this)[i];\n        P ret = (((*this * rev) >> i).log()\
    \ * k).exp() * ((*this)[i].pow(k));\n        ret = (ret << (i * k)).pre(deg);\n\
    \        if((int) ret.size() < deg) ret.resize(deg, T(0));\n        return ret;\n\
    \      }\n    }\n    return *this;\n  }\n\n  P mod_pow(int64_t k, P g) const {\n\
    \    P modinv = g.rev().inv();\n    auto get_div = [&](P base) {\n      if(base.size()\
    \ < g.size()) {\n        base.clear();\n        return base;\n      }\n      int\
    \ n = base.size() - g.size() + 1;\n      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);\n\
    \    };\n    P x(*this), ret{1};\n    while(k > 0) {\n      if(k & 1) {\n    \
    \    ret *= x;\n        ret -= get_div(ret) * g;\n        ret.shrink();\n    \
    \  }\n      x *= x;\n      x -= get_div(x) * g;\n      x.shrink();\n      k >>=\
    \ 1;\n    }\n    return ret;\n  }\n\n  // https://judge.yosupo.jp/problem/polynomial_taylor_shift\n\
    \  P taylor_shift(T c) const {\n    int n = (int) this->size();\n    vector< T\
    \ > fact(n), rfact(n);\n    fact[0] = rfact[0] = T(1);\n    for(int i = 1; i <\
    \ n; i++) fact[i] = fact[i - 1] * T(i);\n    rfact[n - 1] = T(1) / fact[n - 1];\n\
    \    for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);\n    P p(*this);\n\
    \    for(int i = 0; i < n; i++) p[i] *= fact[i];\n    p = p.rev();\n    P bs(n,\
    \ T(1));\n    for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i\
    \ - 1];\n    p = (p * bs).pre(n);\n    p = p.rev();\n    for(int i = 0; i < n;\
    \ i++) p[i] *= rfact[i];\n    return p;\n  }\n};\n\ntemplate< typename Mint >\n\
    using FPS = FormalPowerSeriesFriendlyNTT< Mint >;\n"
  dependsOn:
  - math/fft/number-theoretic-transform-friendly-mod-int.hpp
  isVerificationFile: false
  path: math/fps/formal-power-series-friendly-ntt.hpp
  requiredBy: []
  timestamp: '2023-04-03 20:38:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - test/verify/yosupo-polynomial-taylor-shift.test.cpp
  - test/verify/yosupo-division-of-polynomials.test.cpp
  - test/verify/yosupo-inv-of-formal-power-series.test.cpp
  - test/verify/yosupo-sharp-p-subset-sum.test.cpp
  - test/verify/yosupo-kth-term-of-linearly-recurrent-sequence.test.cpp
  - test/verify/yosupo-partition-function.test.cpp
  - test/verify/yosupo-log-of-formal-power-series.test.cpp
  - test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
  - test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
  - test/verify/yosupo-polynomial-interpolation.test.cpp
  - test/verify/yosupo-exp-of-formal-power-series.test.cpp
  - test/verify/yosupo-multipoint-evaluation.test.cpp
  - test/verify/yosupo-pow-of-formal-power-series.test.cpp
  - test/verify/yosupo-bernoulli-number.test.cpp
  - test/verify/yosupo-find-linear-recurrence.test.cpp
documentation_of: math/fps/formal-power-series-friendly-ntt.hpp
layout: document
title: "Formal Power Series Friendly NTT(NTTmod\u7528\u5F62\u5F0F\u7684\u51AA\u7D1A\
  \u6570)"
---

## 概要

NTT を利用可能な mod のもとで、形式的べき級数の各演算を効率的に行う。

TODO 解説


## 使い方

通常はテンプレートの型として Modint 構造体を渡す。また static  な関数として `ntt` と `intt` が実装された構造体が必要である。この構造体は `NumberTheoreticTransformFriendlyModInt< T >` に対応しているが、他のライブラリを使いたい場合は必要に応じてこの部分を書き換えること。

計算量が書かれていない演算は $O(n \log n)$ で動作する。引数で `deg` を渡すことで, `deg` 項まで計算して返すものもある(デフォルトでは基本的に $\mathrm{deg}(f)$ 項で打ち切る)。

* `+`: $f(x) + g(x)$ を返す。$O(n)$
* `-`: $f(x) - g(x)$ を返す。$O(n)$
* `*`: $f(x) \times g(x)$ を返す。
* `/`: $f(x) = q(x) \times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $q(x)$ を返す。
* `%`: $f(x) = q(x) \times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $r(x)$ を返す。
* `div_mod()`: 剰余を返す。`/` と `%` をそれぞれ呼び出すよりも効率的。
* `operator(x)`: $f(x)$ の値を評価して返す。$O(n)$
* `diff()`: $f(x)'$ を返す。$O(n)$
* `integral()`: $\int f(x) dx$ を返す。$O(n)$
* `inv()`: $\frac {1} {f(x)}$ を返す。$f(0) \neq 0$ を要求する。
* `log()`: $\log f(x)$ を返す。$f(0) = 1$ を要求する。
* `sqrt(get_sqrt)`: $\sqrt {f(x)}$、つまり $f(x) = g(x)^2$ を満たす $g(x)$ を返す。存在しない場合空配列を返す。`get_sqrt` はあるmodint $y$ が与えられたときに $y = x^2$ を満たす modint $x$ を返すラムダ式で, これを渡さない場合は非 $0$ な最初の項が $1$ であることを要求する。存在しない場合は適当な値を返すように実装すると、空配列が返される。
* `exp()`: $e^{f} (x)$ を返す。$f(0) = 0$ を要求する。
* `pow(k)`: $f^{k} (x)$ を返す。
* `mod_pow(k, g)`: $f^{k} (x) \pmod {g(x)}$ を返す。$O(n \log k \log \mathrm{deg}(f))$
* `taylor_shift(c)`: $g(x) = f(x + c)$ を満たす $g(x)$ を返す。
