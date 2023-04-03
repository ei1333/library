---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/enumeration.hpp
    title: "Enumeration(\u7D44\u307F\u5408\u308F\u305B)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dpl-5-i.test.cpp
    title: test/verify/aoj-dpl-5-i.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/stirling-number-second.md
    document_title: "Stirling Number Second(\u7B2C2\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\
      \u30B0\u6570)"
    links: []
  bundledCode: "#line 1 \"math/combinatorics/enumeration.hpp\"\n/**\n * @brief Enumeration(\u7D44\
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
    \ += add;\n  }\n  return ret * table.finv(k);\n}\n"
  code: "#include \"enumeration.hpp\"\n\n/**\n * @brief Stirling Number Second(\u7B2C\
    2\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570)\n * @docs docs/stirling-number-second.md\n\
    \ */\ntemplate< typename T >\nT stirling_number_second(int n, int k) {\n  Enumeration<\
    \ T > table(k);\n  T ret = 0;\n  for(int i = 0; i <= k; i++) {\n    auto add =\
    \ T(i).pow(n) * table.C(k, i);\n    if((k - i) & 1) ret -= add;\n    else ret\
    \ += add;\n  }\n  return ret * table.finv(k);\n}\n"
  dependsOn:
  - math/combinatorics/enumeration.hpp
  isVerificationFile: false
  path: math/combinatorics/stirling-number-second.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-dpl-5-i.test.cpp
documentation_of: math/combinatorics/stirling-number-second.hpp
layout: document
redirect_from:
- /library/math/combinatorics/stirling-number-second.hpp
- /library/math/combinatorics/stirling-number-second.hpp.html
title: "Stirling Number Second(\u7B2C2\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570\
  )"
---
## 概要

第 2 種スターリング数 $\\{ {n \atop k} \\}$ を求める.

区別できる $n$ 個のボールを区別できない $k$ 個の箱に分割する方法の数を与える.

計算方法は包除原理の考え方に基づく. $k$ 個の箱のうち空箱があったら違反. 違反する個数で包除する. 具体的には $k$ 個の箱から $k-i$ 個選んだとして, それらの箱にボールを入れない方法の数 $({k \atop i})i^{n}$ を足し引きする.

$\displaystyle \\{ {n \atop k} \\} = { \frac {1}{k!} }  \sum_{i=0}^{k} {(-1)^{k-i} ({k \atop i})i^{n} }$

## 使い方

* `stirling_number_second(n, k)`: $\\{ \textstyle {n \atop k} \\}$ を返す.

## 計算量

* $O(k \log n)$
