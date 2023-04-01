---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/subproduct-tree.hpp
    title: Subproduct Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-polynomial-interpolation.test.cpp
    title: test/verify/yosupo-polynomial-interpolation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Polynomial Interpolation(\u591A\u9805\u5F0F\u88DC\u9593)"
    links: []
  bundledCode: "#line 1 \"math/fps/subproduct-tree.hpp\"\n/**\n * @brief Subproduct\
    \ Tree\n */\ntemplate< template< typename > class FPS, typename Mint >\nvector<\
    \ FPS< Mint > > subproduct_tree(const FPS< Mint > &xs) {\n  int n = (int) xs.size();\n\
    \  int k = 1;\n  while(k < n) k <<= 1;\n  vector< FPS< Mint > > g(2 * k, {1});\n\
    \  for(int i = 0; i < n; i++) g[k + i] = {-xs[i], Mint(1)};\n  for(int i = k;\
    \ i-- > 1;) g[i] = g[i << 1] * g[i << 1 | 1];\n  return g;\n}\n#line 2 \"math/fps/polynomial-interpolation.hpp\"\
    \n\n/**\n * @brief Polynomial Interpolation(\u591A\u9805\u5F0F\u88DC\u9593)\n\
    \ */\ntemplate< template< typename > class FPS, typename Mint >\nFPS< Mint > polynomial_interpolation(const\
    \ FPS< Mint > &xs, const FPS< Mint > &ys) {\n  assert(xs.size() == ys.size());\n\
    \  auto mul = subproduct_tree(xs);\n  int n = (int) xs.size(), k = (int) mul.size()\
    \ / 2;\n  vector< FPS< Mint > > g(2 * k);\n  g[1] = mul[1].diff() % mul[1];\n\
    \  for(int i = 2; i < k + n; i++) g[i] = g[i >> 1] % mul[i];\n  for(int i = 0;\
    \ i < n; i++) g[k + i] = {ys[i] / g[k + i][0]};\n  for(int i = k; i-- > 1;) g[i]\
    \ = g[i << 1] * mul[i << 1 | 1] + g[i << 1 | 1] * mul[i << 1];\n  return g[1];\n\
    }\n"
  code: "#include \"subproduct-tree.hpp\"\n\n/**\n * @brief Polynomial Interpolation(\u591A\
    \u9805\u5F0F\u88DC\u9593)\n */\ntemplate< template< typename > class FPS, typename\
    \ Mint >\nFPS< Mint > polynomial_interpolation(const FPS< Mint > &xs, const FPS<\
    \ Mint > &ys) {\n  assert(xs.size() == ys.size());\n  auto mul = subproduct_tree(xs);\n\
    \  int n = (int) xs.size(), k = (int) mul.size() / 2;\n  vector< FPS< Mint > >\
    \ g(2 * k);\n  g[1] = mul[1].diff() % mul[1];\n  for(int i = 2; i < k + n; i++)\
    \ g[i] = g[i >> 1] % mul[i];\n  for(int i = 0; i < n; i++) g[k + i] = {ys[i] /\
    \ g[k + i][0]};\n  for(int i = k; i-- > 1;) g[i] = g[i << 1] * mul[i << 1 | 1]\
    \ + g[i << 1 | 1] * mul[i << 1];\n  return g[1];\n}\n"
  dependsOn:
  - math/fps/subproduct-tree.hpp
  isVerificationFile: false
  path: math/fps/polynomial-interpolation.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-polynomial-interpolation.test.cpp
documentation_of: math/fps/polynomial-interpolation.hpp
layout: document
redirect_from:
- /library/math/fps/polynomial-interpolation.hpp
- /library/math/fps/polynomial-interpolation.hpp.html
title: "Polynomial Interpolation(\u591A\u9805\u5F0F\u88DC\u9593)"
---
