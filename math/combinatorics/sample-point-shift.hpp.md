---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/enumeration.hpp
    title: "Enumeration(\u7D44\u307F\u5408\u308F\u305B)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/factorial.hpp
    title: "Factorial(\u968E\u4E57)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-502.test.cpp
    title: test/verify/yukicoder-502.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Sample Point Shift(\u6A19\u672C\u70B9\u30B7\u30D5\u30C8)"
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
    math/combinatorics/sample-point-shift.hpp\"\n\n/**\n * @brief Sample Point Shift(\u6A19\
    \u672C\u70B9\u30B7\u30D5\u30C8)\n */\ntemplate< typename Mint, typename F >\n\
    vector< Mint > sample_point_shift(const vector< Mint > &ys, const Mint &m, const\
    \ F &multiply) {\n  Enumeration< Mint > comb;\n  int d = (int) ys.size() - 1;\n\
    \  vector< Mint > f(d + 1), g(d * 2 + 1);\n  for(int i = 0; i <= d; i++) {\n \
    \   f[i] = ys[i] * comb.finv(i) * comb.finv(d - i);\n    if((d - i) & 1) f[i]\
    \ = -f[i];\n  }\n  for(int i = 0; i <= 2 * d; i++) {\n    g[i] = Mint(1) / (m\
    \ - d + i);\n  }\n  auto h = multiply(f, g);\n  Mint coef = 1;\n  for(int i =\
    \ 0; i <= d; i++) {\n    coef *= (m - d + i);\n  }\n  for(int i = 0; i <= d; i++)\
    \ {\n    h[i + d] *= coef;\n    coef *= (m + i + 1) * g[i];\n  }\n  return vector<\
    \ Mint >{begin(h) + d, begin(h) + 2 * d + 1};\n}\n"
  code: "#include \"enumeration.hpp\"\n\n/**\n * @brief Sample Point Shift(\u6A19\u672C\
    \u70B9\u30B7\u30D5\u30C8)\n */\ntemplate< typename Mint, typename F >\nvector<\
    \ Mint > sample_point_shift(const vector< Mint > &ys, const Mint &m, const F &multiply)\
    \ {\n  Enumeration< Mint > comb;\n  int d = (int) ys.size() - 1;\n  vector< Mint\
    \ > f(d + 1), g(d * 2 + 1);\n  for(int i = 0; i <= d; i++) {\n    f[i] = ys[i]\
    \ * comb.finv(i) * comb.finv(d - i);\n    if((d - i) & 1) f[i] = -f[i];\n  }\n\
    \  for(int i = 0; i <= 2 * d; i++) {\n    g[i] = Mint(1) / (m - d + i);\n  }\n\
    \  auto h = multiply(f, g);\n  Mint coef = 1;\n  for(int i = 0; i <= d; i++) {\n\
    \    coef *= (m - d + i);\n  }\n  for(int i = 0; i <= d; i++) {\n    h[i + d]\
    \ *= coef;\n    coef *= (m + i + 1) * g[i];\n  }\n  return vector< Mint >{begin(h)\
    \ + d, begin(h) + 2 * d + 1};\n}\n"
  dependsOn:
  - math/combinatorics/enumeration.hpp
  isVerificationFile: false
  path: math/combinatorics/sample-point-shift.hpp
  requiredBy:
  - math/combinatorics/factorial.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-502.test.cpp
documentation_of: math/combinatorics/sample-point-shift.hpp
layout: document
redirect_from:
- /library/math/combinatorics/sample-point-shift.hpp
- /library/math/combinatorics/sample-point-shift.hpp.html
title: "Sample Point Shift(\u6A19\u672C\u70B9\u30B7\u30D5\u30C8)"
---
