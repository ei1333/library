---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/fft/arbitrary-mod-convolution.hpp
    title: "Arbitrary Mod Convolution(\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F)"
  - icon: ':x:'
    path: math/fps/formal-power-series.hpp
    title: "Formal Power Series(\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
    title: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-sparse-matrix-det.test.cpp
    title: test/verify/yosupo-sparse-matrix-det.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-215.test.cpp
    title: test/verify/yukicoder-215.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-3046.test.cpp
    title: test/verify/yukicoder-3046.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-502.test.cpp
    title: test/verify/yukicoder-502.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fft/fast-fourier-transform.hpp\"\nnamespace FastFourierTransform\
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
    \ : fa[i >> 1].x);\n    }\n    return ret;\n  }\n};\n"
  code: "namespace FastFourierTransform {\n  using real = double;\n\n  struct C {\n\
    \    real x, y;\n\n    C() : x(0), y(0) {}\n\n    C(real x, real y) : x(x), y(y)\
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
    \ & 1 ? fa[i >> 1].y : fa[i >> 1].x);\n    }\n    return ret;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fft/fast-fourier-transform.hpp
  requiredBy:
  - math/fft/arbitrary-mod-convolution.hpp
  - math/fps/formal-power-series.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yukicoder-502.test.cpp
  - test/verify/yukicoder-215.test.cpp
  - test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
  - test/verify/yosupo-sparse-matrix-det.test.cpp
  - test/verify/yukicoder-3046.test.cpp
documentation_of: math/fft/fast-fourier-transform.hpp
layout: document
redirect_from:
- /library/math/fft/fast-fourier-transform.hpp
- /library/math/fft/fast-fourier-transform.hpp.html
title: math/fft/fast-fourier-transform.hpp
---
