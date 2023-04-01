---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/tree/pmormq-lowest-common-ancestor.hpp
    title: "PMORMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/rmq-lowest-common-ancestor.hpp
    title: "RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
  - icon: ':question:'
    path: structure/others/plus-minus-one-rmq.hpp
    title: Plus-Minus-One-RMQ
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c-3.test.cpp
    title: test/verify/aoj-grl-5-c-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c-4.test.cpp
    title: test/verify/aoj-grl-5-c-4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-2.test.cpp
    title: test/verify/yosupo-lca-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca.test.cpp
    title: test/verify/yosupo-lca.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-staticrmq-4.test.cpp
    title: test/verify/yosupo-staticrmq-4.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-staticrmq.test.cpp
    title: test/verify/yosupo-staticrmq.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/sparse-table.md
    document_title: "Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB\
      )"
    links: []
  bundledCode: "#line 1 \"structure/others/sparse-table.hpp\"\n/**\n * @brief Sparse-Table(\u30B9\
    \u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/sparse-table.md\n */\n\
    template< typename T, typename F >\nstruct SparseTable {\n  F f;\n  vector< vector<\
    \ T > > st;\n  vector< int > lookup;\n\n  SparseTable() = default;\n\n  explicit\
    \ SparseTable(const vector< T > &v, const F &f) : f(f) {\n    const int n = (int)\
    \ v.size();\n    const int b = 32 - __builtin_clz(n);\n    st.assign(b, vector<\
    \ T >(n));\n    for(int i = 0; i < v.size(); i++) {\n      st[0][i] = v[i];\n\
    \    }\n    for(int i = 1; i < b; i++) {\n      for(int j = 0; j + (1 << i) <=\
    \ n; j++) {\n        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);\n\
    \      }\n    }\n    lookup.resize(v.size() + 1);\n    for(int i = 2; i < lookup.size();\
    \ i++) {\n      lookup[i] = lookup[i >> 1] + 1;\n    }\n  }\n\n  inline T fold(int\
    \ l, int r) const {\n    int b = lookup[r - l];\n    return f(st[b][l], st[b][r\
    \ - (1 << b)]);\n  }\n};\n\ntemplate< typename T, typename F >\nSparseTable< T,\
    \ F > get_sparse_table(const vector< T > &v, const F &f) {\n  return SparseTable<\
    \ T, F >(v, f);\n}\n"
  code: "/**\n * @brief Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB\
    )\n * @docs docs/sparse-table.md\n */\ntemplate< typename T, typename F >\nstruct\
    \ SparseTable {\n  F f;\n  vector< vector< T > > st;\n  vector< int > lookup;\n\
    \n  SparseTable() = default;\n\n  explicit SparseTable(const vector< T > &v, const\
    \ F &f) : f(f) {\n    const int n = (int) v.size();\n    const int b = 32 - __builtin_clz(n);\n\
    \    st.assign(b, vector< T >(n));\n    for(int i = 0; i < v.size(); i++) {\n\
    \      st[0][i] = v[i];\n    }\n    for(int i = 1; i < b; i++) {\n      for(int\
    \ j = 0; j + (1 << i) <= n; j++) {\n        st[i][j] = f(st[i - 1][j], st[i -\
    \ 1][j + (1 << (i - 1))]);\n      }\n    }\n    lookup.resize(v.size() + 1);\n\
    \    for(int i = 2; i < lookup.size(); i++) {\n      lookup[i] = lookup[i >> 1]\
    \ + 1;\n    }\n  }\n\n  inline T fold(int l, int r) const {\n    int b = lookup[r\
    \ - l];\n    return f(st[b][l], st[b][r - (1 << b)]);\n  }\n};\n\ntemplate< typename\
    \ T, typename F >\nSparseTable< T, F > get_sparse_table(const vector< T > &v,\
    \ const F &f) {\n  return SparseTable< T, F >(v, f);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/others/sparse-table.hpp
  requiredBy:
  - structure/others/plus-minus-one-rmq.hpp
  - graph/tree/pmormq-lowest-common-ancestor.hpp
  - graph/tree/rmq-lowest-common-ancestor.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-lca-2.test.cpp
  - test/verify/yosupo-staticrmq-4.test.cpp
  - test/verify/yosupo-staticrmq.test.cpp
  - test/verify/yosupo-lca.test.cpp
  - test/verify/aoj-grl-5-c-4.test.cpp
  - test/verify/aoj-grl-5-c-3.test.cpp
documentation_of: structure/others/sparse-table.hpp
layout: document
redirect_from:
- /library/structure/others/sparse-table.hpp
- /library/structure/others/sparse-table.hpp.html
title: "Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)"
---
## 概要

冪等半群に対する区間クエリを, 前計算 $\Theta (n \log n)$, クエリ $\Theta (1)$ で処理する.

* `SparseTable(v, f)`: 配列 `v`, 演算 $f$ で初期化する.
* `fold(l, r)`: 区間 $[l, r)$ の演算結果を返す.

## 計算量

* `SparseTable(v)`: $\Theta (N \log N)$
* `fold(l, r)`: $\Theta (1)$
