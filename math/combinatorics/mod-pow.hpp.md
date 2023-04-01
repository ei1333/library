---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/combinatorics/mod-tetration.hpp
    title: "Mod Tetration(\u30C6\u30C8\u30EC\u30FC\u30B7\u30E7\u30F3)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-ntl-1-b.test.cpp
    title: test/verify/aoj-ntl-1-b.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-sqrt-mod.test.cpp
    title: test/verify/yosupo-sqrt-mod.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
    title: test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-tetration-mod.test.cpp
    title: test/verify/yosupo-tetration-mod.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/mod-pow.md
    document_title: "Mod Pow(\u3079\u304D\u4E57)"
    links: []
  bundledCode: "#line 1 \"math/combinatorics/mod-pow.hpp\"\n/**\n * @brief Mod Pow(\u3079\
    \u304D\u4E57)\n * @docs docs/mod-pow.md\n */\ntemplate< typename T >\nT mod_pow(T\
    \ x, int64_t n, const T &p) {\n  T ret = 1;\n  while(n > 0) {\n    if(n & 1) (ret\
    \ *= x) %= p;\n    (x *= x) %= p;\n    n >>= 1;\n  }\n  return ret % p;\n}\n"
  code: "/**\n * @brief Mod Pow(\u3079\u304D\u4E57)\n * @docs docs/mod-pow.md\n */\n\
    template< typename T >\nT mod_pow(T x, int64_t n, const T &p) {\n  T ret = 1;\n\
    \  while(n > 0) {\n    if(n & 1) (ret *= x) %= p;\n    (x *= x) %= p;\n    n >>=\
    \ 1;\n  }\n  return ret % p;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics/mod-pow.hpp
  requiredBy:
  - math/combinatorics/mod-tetration.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-sqrt-of-formal-power-series.test.cpp
  - test/verify/yosupo-tetration-mod.test.cpp
  - test/verify/yosupo-sqrt-mod.test.cpp
  - test/verify/aoj-ntl-1-b.test.cpp
documentation_of: math/combinatorics/mod-pow.hpp
layout: document
redirect_from:
- /library/math/combinatorics/mod-pow.hpp
- /library/math/combinatorics/mod-pow.hpp.html
title: "Mod Pow(\u3079\u304D\u4E57)"
---
## 概要
ある値のべき乗を求める.

## 使い方

* `mod_pow(x, n, p)`: $x^n \bmod p$ を返す. 

## 計算量

* $O(\log n)$
