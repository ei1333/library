---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/yosupo-sqrt-mod.test.cpp
    title: test/verify/yosupo-sqrt-mod.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
    title: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Mod Sqrt
    links: []
  bundledCode: "#line 1 \"math/combinatorics/mod-sqrt.hpp\"\n/**\n * @brief Mod Sqrt\n\
    \ */\ntemplate< typename T >\nT mod_sqrt(const T &a, const T &p) {\n  if(a ==\
    \ 0) return 0;\n  if(p == 2) return a;\n  if(mod_pow(a, (p - 1) >> 1, p) != 1)\
    \ return -1;\n  T b = 1;\n  while(mod_pow(b, (p - 1) >> 1, p) == 1) ++b;\n  T\
    \ e = 0, m = p - 1;\n  while(m % 2 == 0) m >>= 1, ++e;\n  T x = mod_pow(a, (m\
    \ - 1) >> 1, p);\n  T y = a * (x * x % p) % p;\n  (x *= a) %= p;\n  T z = mod_pow(b,\
    \ m, p);\n  while(y != 1) {\n    T j = 0, t = y;\n    while(t != 1) {\n      j\
    \ += 1;\n      (t *= t) %= p;\n    }\n    z = mod_pow(z, T(1) << (e - j - 1),\
    \ p);\n    (x *= z) %= p;\n    (z *= z) %= p;\n    (y *= z) %= p;\n    e = j;\n\
    \  }\n  return x;\n}\n"
  code: "/**\n * @brief Mod Sqrt\n */\ntemplate< typename T >\nT mod_sqrt(const T\
    \ &a, const T &p) {\n  if(a == 0) return 0;\n  if(p == 2) return a;\n  if(mod_pow(a,\
    \ (p - 1) >> 1, p) != 1) return -1;\n  T b = 1;\n  while(mod_pow(b, (p - 1) >>\
    \ 1, p) == 1) ++b;\n  T e = 0, m = p - 1;\n  while(m % 2 == 0) m >>= 1, ++e;\n\
    \  T x = mod_pow(a, (m - 1) >> 1, p);\n  T y = a * (x * x % p) % p;\n  (x *= a)\
    \ %= p;\n  T z = mod_pow(b, m, p);\n  while(y != 1) {\n    T j = 0, t = y;\n \
    \   while(t != 1) {\n      j += 1;\n      (t *= t) %= p;\n    }\n    z = mod_pow(z,\
    \ T(1) << (e - j - 1), p);\n    (x *= z) %= p;\n    (z *= z) %= p;\n    (y *=\
    \ z) %= p;\n    e = j;\n  }\n  return x;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics/mod-sqrt.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - test/verify/yosupo-sqrt-mod.test.cpp
documentation_of: math/combinatorics/mod-sqrt.hpp
layout: document
redirect_from:
- /library/math/combinatorics/mod-sqrt.hpp
- /library/math/combinatorics/mod-sqrt.hpp.html
title: Mod Sqrt
---
