---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-pow.hpp
    title: "Mod Pow(\u3079\u304D\u4E57)"
  - icon: ':heavy_check_mark:'
    path: math/number-theory/euler-phi.hpp
    title: "Euler's Phi(\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-tetration-mod.test.cpp
    title: test/verify/yosupo-tetration-mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/mod-tetration.md
    document_title: "Mod Tetration(\u30C6\u30C8\u30EC\u30FC\u30B7\u30E7\u30F3)"
    links: []
  bundledCode: "#line 1 \"math/combinatorics/mod-pow.hpp\"\n/**\n * @brief Mod Pow(\u3079\
    \u304D\u4E57)\n * @docs docs/mod-pow.md\n */\ntemplate< typename T >\nT mod_pow(T\
    \ x, int64_t n, const T &p) {\n  T ret = 1;\n  while(n > 0) {\n    if(n & 1) (ret\
    \ *= x) %= p;\n    (x *= x) %= p;\n    n >>= 1;\n  }\n  return ret % p;\n}\n#line\
    \ 1 \"math/number-theory/euler-phi.hpp\"\n/**\n * @brief Euler's Phi(\u30AA\u30A4\
    \u30E9\u30FC\u306E\u03C6\u95A2\u6570)\n * @docs docs/euler-phi.md\n */\ntemplate<\
    \ typename T >\nT euler_phi(T n) {\n  T ret = n;\n  for(T i = 2; i * i <= n; i++)\
    \ {\n    if(n % i == 0) {\n      ret -= ret / i;\n      while(n % i == 0) n /=\
    \ i;\n    }\n  }\n  if(n > 1) ret -= ret / n;\n  return ret;\n}\n#line 3 \"math/combinatorics/mod-tetration.hpp\"\
    \n\n/**\n * @brief Mod Tetration(\u30C6\u30C8\u30EC\u30FC\u30B7\u30E7\u30F3)\n\
    \ * @docs docs/mod-tetration.md\n */\ntemplate< typename T >\nT mod_tetration(const\
    \ T &a, const T &b, const T &m) {\n  if(m == 1) return 0;\n  if(a == 0) return\
    \ !(b & 1);\n  if(b == 0) return 1;\n  if(b == 1) return a % m;\n  if(b == 2)\
    \ return mod_pow(a, a, m);\n  auto phi = euler_phi(m);\n  auto tmp = mod_tetration(a,\
    \ b - 1, phi);\n  if(tmp == 0) tmp += phi;\n  return mod_pow(a, tmp, m);\n}\n"
  code: "#include \"mod-pow.hpp\"\n#include \"../number-theory/euler-phi.hpp\"\n\n\
    /**\n * @brief Mod Tetration(\u30C6\u30C8\u30EC\u30FC\u30B7\u30E7\u30F3)\n * @docs\
    \ docs/mod-tetration.md\n */\ntemplate< typename T >\nT mod_tetration(const T\
    \ &a, const T &b, const T &m) {\n  if(m == 1) return 0;\n  if(a == 0) return !(b\
    \ & 1);\n  if(b == 0) return 1;\n  if(b == 1) return a % m;\n  if(b == 2) return\
    \ mod_pow(a, a, m);\n  auto phi = euler_phi(m);\n  auto tmp = mod_tetration(a,\
    \ b - 1, phi);\n  if(tmp == 0) tmp += phi;\n  return mod_pow(a, tmp, m);\n}\n"
  dependsOn:
  - math/combinatorics/mod-pow.hpp
  - math/number-theory/euler-phi.hpp
  isVerificationFile: false
  path: math/combinatorics/mod-tetration.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-tetration-mod.test.cpp
documentation_of: math/combinatorics/mod-tetration.hpp
layout: document
redirect_from:
- /library/math/combinatorics/mod-tetration.hpp
- /library/math/combinatorics/mod-tetration.hpp.html
title: "Mod Tetration(\u30C6\u30C8\u30EC\u30FC\u30B7\u30E7\u30F3)"
---
## 概要
${a \uparrow \uparrow b} \bmod m$ を求める. $\uparrow \uparrow$ はテトレーション演算で $a^{a^{a^{a^{\ldots}}}}$ ($a$ が $b$ 個続く) を指す.

## 使い方

* `mod_tetration(a, b, m)`: ${a \uparrow \uparrow b} \bmod m$ を返す. 

## 計算量

* $O(\sqrt m)$
