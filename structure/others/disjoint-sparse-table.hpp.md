---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-2.test.cpp
    title: test/verify/yosupo-staticrmq-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/disjoint-sparse-table.md
    document_title: Disjoint-Sparse-Table
    links: []
  bundledCode: "#line 1 \"structure/others/disjoint-sparse-table.hpp\"\n/**\n * @brief\
    \ Disjoint-Sparse-Table\n * @docs docs/disjoint-sparse-table.md\n */\ntemplate<\
    \ typename Semigroup, typename F >\nstruct DisjointSparseTable {\n  const F f;\n\
    \  vector< vector< Semigroup > > st;\n  vector< int > lookup;\n\n  DisjointSparseTable(const\
    \ vector< Semigroup > &v, const F &f) : f(f) {\n    int b = 0;\n    while((1 <<\
    \ b) <= v.size()) ++b;\n    st.resize(b, vector< Semigroup >(v.size(), Semigroup()));\n\
    \    for(int i = 0; i < v.size(); i++) st[0][i] = v[i];\n    for(int i = 1; i\
    \ < b; i++) {\n      int shift = 1 << i;\n      for(int j = 0; j < v.size(); j\
    \ += shift << 1) {\n        int t = min(j + shift, (int) v.size());\n        st[i][t\
    \ - 1] = v[t - 1];\n        for(int k = t - 2; k >= j; k--) st[i][k] = f(v[k],\
    \ st[i][k + 1]);\n        if(v.size() <= t) break;\n        st[i][t] = v[t];\n\
    \        int r = min(t + shift, (int) v.size());\n        for(int k = t + 1; k\
    \ < r; k++) st[i][k] = f(st[i][k - 1], v[k]);\n      }\n    }\n    lookup.resize(1\
    \ << b);\n    for(int i = 2; i < lookup.size(); i++) {\n      lookup[i] = lookup[i\
    \ >> 1] + 1;\n    }\n  }\n\n  Semigroup fold(int l, int r) {\n    if(l >= --r)\
    \ return st[0][l];\n    int p = lookup[l ^ r];\n    return f(st[p][l], st[p][r]);\n\
    \  }\n};\n\ntemplate< typename SemiGroup, typename F >\nDisjointSparseTable< SemiGroup,\
    \ F > get_disjoint_sparse_table(const vector< SemiGroup >& v, const F& f) {\n\
    \  return {v, f};\n}\n"
  code: "/**\n * @brief Disjoint-Sparse-Table\n * @docs docs/disjoint-sparse-table.md\n\
    \ */\ntemplate< typename Semigroup, typename F >\nstruct DisjointSparseTable {\n\
    \  const F f;\n  vector< vector< Semigroup > > st;\n  vector< int > lookup;\n\n\
    \  DisjointSparseTable(const vector< Semigroup > &v, const F &f) : f(f) {\n  \
    \  int b = 0;\n    while((1 << b) <= v.size()) ++b;\n    st.resize(b, vector<\
    \ Semigroup >(v.size(), Semigroup()));\n    for(int i = 0; i < v.size(); i++)\
    \ st[0][i] = v[i];\n    for(int i = 1; i < b; i++) {\n      int shift = 1 << i;\n\
    \      for(int j = 0; j < v.size(); j += shift << 1) {\n        int t = min(j\
    \ + shift, (int) v.size());\n        st[i][t - 1] = v[t - 1];\n        for(int\
    \ k = t - 2; k >= j; k--) st[i][k] = f(v[k], st[i][k + 1]);\n        if(v.size()\
    \ <= t) break;\n        st[i][t] = v[t];\n        int r = min(t + shift, (int)\
    \ v.size());\n        for(int k = t + 1; k < r; k++) st[i][k] = f(st[i][k - 1],\
    \ v[k]);\n      }\n    }\n    lookup.resize(1 << b);\n    for(int i = 2; i < lookup.size();\
    \ i++) {\n      lookup[i] = lookup[i >> 1] + 1;\n    }\n  }\n\n  Semigroup fold(int\
    \ l, int r) {\n    if(l >= --r) return st[0][l];\n    int p = lookup[l ^ r];\n\
    \    return f(st[p][l], st[p][r]);\n  }\n};\n\ntemplate< typename SemiGroup, typename\
    \ F >\nDisjointSparseTable< SemiGroup, F > get_disjoint_sparse_table(const vector<\
    \ SemiGroup >& v, const F& f) {\n  return {v, f};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/others/disjoint-sparse-table.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-staticrmq-2.test.cpp
documentation_of: structure/others/disjoint-sparse-table.hpp
layout: document
redirect_from:
- /library/structure/others/disjoint-sparse-table.hpp
- /library/structure/others/disjoint-sparse-table.hpp.html
title: Disjoint-Sparse-Table
---
## 概要

更新がない場合の半群に対する区間クエリを, 前計算 $O(n \log n)$, クエリ $O(1)$ で処理する.

## 使い方

* `DisjointSparseTable(v, f)`: 配列 `v` で初期化する. `f` は半群をマージする二項演算である.
* `fold(l, r)`: 区間 $[l, r)$ を演算した結果を返す.

## 計算量

* `DisjointSparseTable(v, f)`: $O(N \log N)$
* `fold(l, r)`: $O(1)$
