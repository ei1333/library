---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
    title: test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Lagrange Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024)"
    links: []
  bundledCode: "#line 1 \"math/combinatorics/lagrange-polynomial-3.hpp\"\n/**\n *\
    \ @brief Lagrange Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024)\n */\ntemplate<\
    \ typename Mint, typename F >\nvector< Mint > lagrange_polynomial(const vector<\
    \ Mint > &y, int64_t T, const int &m, const F &multiply) {\n  int k = (int) y.size()\
    \ - 1;\n  T %= Mint::get_mod();\n  if(T <= k) {\n    vector< Mint > ret(m);\n\
    \    int ptr = 0;\n    for(int64_t i = T; i <= k and ptr < m; i++) {\n      ret[ptr++]\
    \ = y[i];\n    }\n    if(k + 1 < T + m) {\n      auto suf = lagrange_polynomial(y,\
    \ k + 1, m - ptr, multiply);\n      for(int i = k + 1; i < T + m; i++) {\n   \
    \     ret[ptr++] = suf[i - (k + 1)];\n      }\n    }\n    return ret;\n  }\n \
    \ if(T + m > Mint::get_mod()) {\n    auto pref = lagrange_polynomial(y, T, Mint::get_mod()\
    \ - T, multiply);\n    auto suf = lagrange_polynomial(y, 0, m - pref.size(), multiply);\n\
    \    copy(begin(suf), end(suf), back_inserter(pref));\n    return pref;\n  }\n\
    \  \n  vector< Mint > finv(k + 1, 1), d(k + 1);\n  for(int i = 2; i <= k; i++)\
    \ finv[k] *= i;\n  finv[k] = Mint(1) / finv[k];\n  for(int i = k; i >= 1; i--)\
    \ finv[i - 1] = finv[i] * i;\n  for(int i = 0; i <= k; i++) {\n    d[i] = finv[i]\
    \ * finv[k - i] * y[i];\n    if((k - i) & 1) d[i] = -d[i];\n  }\n\n  vector< Mint\
    \ > h(m + k);\n  for(int i = 0; i < m + k; i++) {\n    h[i] = Mint(1) / (T - k\
    \ + i);\n  }\n\n  auto dh = multiply(d, h);\n\n  vector< Mint > ret(m);\n  Mint\
    \ cur = T;\n  for(int i = 1; i <= k; i++) cur *= T - i;\n  for(int i = 0; i <\
    \ m; i++) {\n    ret[i] = cur * dh[k + i];\n    cur *= T + i + 1;\n    cur *=\
    \ h[i];\n  }\n  return ret;\n}\n"
  code: "/**\n * @brief Lagrange Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024\
    )\n */\ntemplate< typename Mint, typename F >\nvector< Mint > lagrange_polynomial(const\
    \ vector< Mint > &y, int64_t T, const int &m, const F &multiply) {\n  int k =\
    \ (int) y.size() - 1;\n  T %= Mint::get_mod();\n  if(T <= k) {\n    vector< Mint\
    \ > ret(m);\n    int ptr = 0;\n    for(int64_t i = T; i <= k and ptr < m; i++)\
    \ {\n      ret[ptr++] = y[i];\n    }\n    if(k + 1 < T + m) {\n      auto suf\
    \ = lagrange_polynomial(y, k + 1, m - ptr, multiply);\n      for(int i = k + 1;\
    \ i < T + m; i++) {\n        ret[ptr++] = suf[i - (k + 1)];\n      }\n    }\n\
    \    return ret;\n  }\n  if(T + m > Mint::get_mod()) {\n    auto pref = lagrange_polynomial(y,\
    \ T, Mint::get_mod() - T, multiply);\n    auto suf = lagrange_polynomial(y, 0,\
    \ m - pref.size(), multiply);\n    copy(begin(suf), end(suf), back_inserter(pref));\n\
    \    return pref;\n  }\n  \n  vector< Mint > finv(k + 1, 1), d(k + 1);\n  for(int\
    \ i = 2; i <= k; i++) finv[k] *= i;\n  finv[k] = Mint(1) / finv[k];\n  for(int\
    \ i = k; i >= 1; i--) finv[i - 1] = finv[i] * i;\n  for(int i = 0; i <= k; i++)\
    \ {\n    d[i] = finv[i] * finv[k - i] * y[i];\n    if((k - i) & 1) d[i] = -d[i];\n\
    \  }\n\n  vector< Mint > h(m + k);\n  for(int i = 0; i < m + k; i++) {\n    h[i]\
    \ = Mint(1) / (T - k + i);\n  }\n\n  auto dh = multiply(d, h);\n\n  vector< Mint\
    \ > ret(m);\n  Mint cur = T;\n  for(int i = 1; i <= k; i++) cur *= T - i;\n  for(int\
    \ i = 0; i < m; i++) {\n    ret[i] = cur * dh[k + i];\n    cur *= T + i + 1;\n\
    \    cur *= h[i];\n  }\n  return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics/lagrange-polynomial-3.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-shift-of-sampling-points-of-polynomial.test.cpp
documentation_of: math/combinatorics/lagrange-polynomial-3.hpp
layout: document
redirect_from:
- /library/math/combinatorics/lagrange-polynomial-3.hpp
- /library/math/combinatorics/lagrange-polynomial-3.hpp.html
title: "Lagrange Polynomial(\u591A\u9805\u5F0F\u88DC\u9593, \u5024)"
---
