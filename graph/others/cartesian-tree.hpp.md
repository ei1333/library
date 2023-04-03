---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-cartesian-tree.test.cpp
    title: test/verify/yosupo-cartesian-tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-4.test.cpp
    title: test/verify/yosupo-staticrmq-4.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/cartesian-tree.md
    document_title: Cartesian Tree
    links:
    - https://kimiyuki.net/blog/2020/07/27/recursion-on-cartesian-tree/
  bundledCode: "#line 2 \"graph/others/cartesian-tree.hpp\"\n/**\n * @brief Cartesian\
    \ Tree\n * @docs docs/cartesian-tree.md\n * @see https://kimiyuki.net/blog/2020/07/27/recursion-on-cartesian-tree/\n\
    \ */\ntemplate< typename T >\nvector< int > cartesian_tree(const vector< T > &v)\
    \ {\n  int n = (int) v.size();\n  vector< int > par(n, -1);\n  stack< int > st;\n\
    \  for(int i = 0; i < n; i++) {\n    int last = -1;\n    while(!st.empty() &&\
    \ v[st.top()] >= v[i]) {\n      last = st.top();\n      st.pop();\n    }\n   \
    \ if(!st.empty()) par[i] = st.top();\n    if(last >= 0) par[last] = i;\n    st.emplace(i);\n\
    \  }\n  return par;\n}\n"
  code: "#pragma once\n/**\n * @brief Cartesian Tree\n * @docs docs/cartesian-tree.md\n\
    \ * @see https://kimiyuki.net/blog/2020/07/27/recursion-on-cartesian-tree/\n */\n\
    template< typename T >\nvector< int > cartesian_tree(const vector< T > &v) {\n\
    \  int n = (int) v.size();\n  vector< int > par(n, -1);\n  stack< int > st;\n\
    \  for(int i = 0; i < n; i++) {\n    int last = -1;\n    while(!st.empty() &&\
    \ v[st.top()] >= v[i]) {\n      last = st.top();\n      st.pop();\n    }\n   \
    \ if(!st.empty()) par[i] = st.top();\n    if(last >= 0) par[last] = i;\n    st.emplace(i);\n\
    \  }\n  return par;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/others/cartesian-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-staticrmq-4.test.cpp
  - test/verify/yosupo-cartesian-tree.test.cpp
documentation_of: graph/others/cartesian-tree.hpp
layout: document
redirect_from:
- /library/graph/others/cartesian-tree.hpp
- /library/graph/others/cartesian-tree.hpp.html
title: Cartesian Tree
---
## 概要

数列に対応する Cartesian tree を求める.

## 使い方

* `cartesian_tree(v)`: 数列 `v` に対応する Cartesian tree を返す. 各要素にはその要素の親の idx が格納される. ただし根は `-1`.

## 計算量

* $O(N)$
