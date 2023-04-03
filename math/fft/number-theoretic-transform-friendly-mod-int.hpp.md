---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: math/fps/formal-power-series-friendly-ntt.hpp
    title: "Formal Power Series Friendly NTT(NTTmod\u7528\u5F62\u5F0F\u7684\u51AA\u7D1A\
      \u6570)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bernoulli-number.test.cpp
    title: test/verify/yosupo-bernoulli-number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-convolution-mod-2.test.cpp
    title: test/verify/yosupo-convolution-mod-2.test.cpp
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
    path: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
    title: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
    title: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Number Theoretic Transform Friendly ModInt
    links: []
  bundledCode: "#line 1 \"math/fft/number-theoretic-transform-friendly-mod-int.hpp\"\
    \n/**\n * @brief Number Theoretic Transform Friendly ModInt\n */\ntemplate< typename\
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
    \ Mint >::max_base = 0;\n"
  code: "/**\n * @brief Number Theoretic Transform Friendly ModInt\n */\ntemplate<\
    \ typename Mint >\nstruct NumberTheoreticTransformFriendlyModInt {\n\n  static\
    \ vector< Mint > roots, iroots, rate3, irate3;\n  static int max_base;\n\n  NumberTheoreticTransformFriendlyModInt()\
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
    \ Mint >::max_base = 0;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fft/number-theoretic-transform-friendly-mod-int.hpp
  requiredBy:
  - math/fps/formal-power-series-friendly-ntt.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - test/verify/yosupo-polynomial-taylor-shift.test.cpp
  - test/verify/yosupo-division-of-polynomials.test.cpp
  - test/verify/yosupo-inv-of-formal-power-series.test.cpp
  - test/verify/yosupo-sharp-p-subset-sum.test.cpp
  - test/verify/yosupo-kth-term-of-linearly-recurrent-sequence.test.cpp
  - test/verify/yosupo-convolution-mod-2.test.cpp
  - test/verify/yosupo-partition-function.test.cpp
  - test/verify/yosupo-log-of-formal-power-series.test.cpp
  - test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
  - test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
  - test/verify/yosupo-polynomial-interpolation.test.cpp
  - test/verify/yosupo-exp-of-formal-power-series.test.cpp
  - test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
  - test/verify/yosupo-multipoint-evaluation.test.cpp
  - test/verify/yosupo-pow-of-formal-power-series.test.cpp
  - test/verify/yosupo-bernoulli-number.test.cpp
  - test/verify/yosupo-find-linear-recurrence.test.cpp
documentation_of: math/fft/number-theoretic-transform-friendly-mod-int.hpp
layout: document
redirect_from:
- /library/math/fft/number-theoretic-transform-friendly-mod-int.hpp
- /library/math/fft/number-theoretic-transform-friendly-mod-int.hpp.html
title: Number Theoretic Transform Friendly ModInt
---
