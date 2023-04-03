---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/enumeration.hpp
    title: "Enumeration(\u7D44\u307F\u5408\u308F\u305B)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dpl-5-g.test.cpp
    title: test/verify/aoj-dpl-5-g.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/bell-number.md
    document_title: "Bell Number(\u30D9\u30EB\u6570)"
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
    math/combinatorics/bell-number.hpp\"\n\n/**\n * @brief Bell Number(\u30D9\u30EB\
    \u6570)\n * @docs docs/bell-number.md\n */\ntemplate< typename T >\nT bell_number(int\
    \ n, int k) {\n  if(n == 0) return 1;\n  k = min(k, n);\n  Enumeration< T > uku(k);\n\
    \  T ret = 0;\n  vector< T > pref(k + 1);\n  pref[0] = 1;\n  for(int i = 1; i\
    \ <= k; i++) {\n    if(i & 1) pref[i] = pref[i - 1] - uku.finv(i);\n    else pref[i]\
    \ = pref[i - 1] + uku.finv(i);\n  }\n  for(int i = 1; i <= k; i++) {\n    ret\
    \ += T(i).pow(n) * uku.finv(i) * pref[k - i];\n  }\n  return ret;\n}\n"
  code: "#include \"enumeration.hpp\"\n\n/**\n * @brief Bell Number(\u30D9\u30EB\u6570\
    )\n * @docs docs/bell-number.md\n */\ntemplate< typename T >\nT bell_number(int\
    \ n, int k) {\n  if(n == 0) return 1;\n  k = min(k, n);\n  Enumeration< T > uku(k);\n\
    \  T ret = 0;\n  vector< T > pref(k + 1);\n  pref[0] = 1;\n  for(int i = 1; i\
    \ <= k; i++) {\n    if(i & 1) pref[i] = pref[i - 1] - uku.finv(i);\n    else pref[i]\
    \ = pref[i - 1] + uku.finv(i);\n  }\n  for(int i = 1; i <= k; i++) {\n    ret\
    \ += T(i).pow(n) * uku.finv(i) * pref[k - i];\n  }\n  return ret;\n}\n"
  dependsOn:
  - math/combinatorics/enumeration.hpp
  isVerificationFile: false
  path: math/combinatorics/bell-number.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-dpl-5-g.test.cpp
documentation_of: math/combinatorics/bell-number.hpp
layout: document
redirect_from:
- /library/math/combinatorics/bell-number.hpp
- /library/math/combinatorics/bell-number.hpp.html
title: "Bell Number(\u30D9\u30EB\u6570)"
---
## 概要

ベル数 $B(n,k)$ を求める.

区別できる $n$ 個のボールを区別できない $k$ 個以下の箱に分割する方法の数を与える.

特に $B(n,n)$ は $n$ 個のボールを任意個のグループに分割する方法の数である.

* `bell_number(n, k)`: $B(n, k)$ を返す.

## 計算量

* $O(\min(n, k) \log n)$
