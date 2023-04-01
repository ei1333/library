---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/subproduct-tree.hpp
    title: Subproduct Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-multipoint-evaluation.test.cpp
    title: test/verify/yosupo-multipoint-evaluation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Multipoint Evaluation
    links: []
  bundledCode: "#line 1 \"math/fps/subproduct-tree.hpp\"\n/**\n * @brief Subproduct\
    \ Tree\n */\ntemplate< template< typename > class FPS, typename Mint >\nvector<\
    \ FPS< Mint > > subproduct_tree(const FPS< Mint > &xs) {\n  int n = (int) xs.size();\n\
    \  int k = 1;\n  while(k < n) k <<= 1;\n  vector< FPS< Mint > > g(2 * k, {1});\n\
    \  for(int i = 0; i < n; i++) g[k + i] = {-xs[i], Mint(1)};\n  for(int i = k;\
    \ i-- > 1;) g[i] = g[i << 1] * g[i << 1 | 1];\n  return g;\n}\n#line 2 \"math/fps/multipoint-evaluation.hpp\"\
    \n\n/**\n * @brief Multipoint Evaluation\n */\ntemplate< template< typename >\
    \ class FPS, typename Mint >\nFPS< Mint > multipoint_evaluation(const FPS< Mint\
    \ > &f, const FPS< Mint > &xs) {\n  auto g = subproduct_tree(xs);\n  int m = (int)\
    \ xs.size(), k = (int) g.size() / 2;\n  g[1] = f % g[1];\n  for(int i = 2; i <\
    \ k + m; i++) g[i] = g[i >> 1] % g[i];\n  FPS< Mint > ys(m);\n  for(int i = 0;\
    \ i < m; i++) ys[i] = (g[k + i].empty() ? Mint(0) : g[k + i][0]);\n  return ys;\n\
    }\n"
  code: "#include \"subproduct-tree.hpp\"\n\n/**\n * @brief Multipoint Evaluation\n\
    \ */\ntemplate< template< typename > class FPS, typename Mint >\nFPS< Mint > multipoint_evaluation(const\
    \ FPS< Mint > &f, const FPS< Mint > &xs) {\n  auto g = subproduct_tree(xs);\n\
    \  int m = (int) xs.size(), k = (int) g.size() / 2;\n  g[1] = f % g[1];\n  for(int\
    \ i = 2; i < k + m; i++) g[i] = g[i >> 1] % g[i];\n  FPS< Mint > ys(m);\n  for(int\
    \ i = 0; i < m; i++) ys[i] = (g[k + i].empty() ? Mint(0) : g[k + i][0]);\n  return\
    \ ys;\n}\n"
  dependsOn:
  - math/fps/subproduct-tree.hpp
  isVerificationFile: false
  path: math/fps/multipoint-evaluation.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-multipoint-evaluation.test.cpp
documentation_of: math/fps/multipoint-evaluation.hpp
layout: document
redirect_from:
- /library/math/fps/multipoint-evaluation.hpp
- /library/math/fps/multipoint-evaluation.hpp.html
title: Multipoint Evaluation
---
