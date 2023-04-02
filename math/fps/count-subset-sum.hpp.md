---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-sharp-p-subset-sum.test.cpp
    title: test/verify/yosupo-sharp-p-subset-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Count Subset Sum
    links: []
  bundledCode: "#line 1 \"math/fps/count-subset-sum.hpp\"\n/**\n * @brief Count Subset\
    \ Sum\n */\ntemplate< template< typename > class FPS, typename Mint >\nFPS< Mint\
    \ > count_subset_sum(vector< Mint > &c) {\n  const int n = (int) c.size();\n \
    \ vector< Mint > inv(n);\n  inv[0] = Mint(0);\n  inv[1] = Mint(1);\n  auto mod\
    \ = Mint::get_mod();\n  for(int i = 2; i < n; i++) {\n    inv[i] = -inv[mod %\
    \ i] * (mod / i);\n  }\n  FPS< Mint > f(n);\n  for(int i = 1; i < n; i++) {\n\
    \    for(int j = 1, d = i; d < n; j++, d += i) {\n      if(j & 1) f[d] += c[i]\
    \ * inv[j];\n      else f[d] -= c[i] * inv[j];\n    }\n  }\n  return f.exp();\n\
    }\n"
  code: "/**\n * @brief Count Subset Sum\n */\ntemplate< template< typename > class\
    \ FPS, typename Mint >\nFPS< Mint > count_subset_sum(vector< Mint > &c) {\n  const\
    \ int n = (int) c.size();\n  vector< Mint > inv(n);\n  inv[0] = Mint(0);\n  inv[1]\
    \ = Mint(1);\n  auto mod = Mint::get_mod();\n  for(int i = 2; i < n; i++) {\n\
    \    inv[i] = -inv[mod % i] * (mod / i);\n  }\n  FPS< Mint > f(n);\n  for(int\
    \ i = 1; i < n; i++) {\n    for(int j = 1, d = i; d < n; j++, d += i) {\n    \
    \  if(j & 1) f[d] += c[i] * inv[j];\n      else f[d] -= c[i] * inv[j];\n    }\n\
    \  }\n  return f.exp();\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/count-subset-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-sharp-p-subset-sum.test.cpp
documentation_of: math/fps/count-subset-sum.hpp
layout: document
redirect_from:
- /library/math/fps/count-subset-sum.hpp
- /library/math/fps/count-subset-sum.hpp.html
title: Count Subset Sum
---
