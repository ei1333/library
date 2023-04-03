---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: structure/others/sparse-table.hpp
    title: "Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c-3.test.cpp
    title: test/verify/aoj-grl-5-c-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-2.test.cpp
    title: test/verify/yosupo-lca-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/rmq-lowest-common-ancestor.md
    document_title: "RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148\
      )"
    links: []
  bundledCode: "#line 2 \"graph/tree/rmq-lowest-common-ancestor.hpp\"\n\n#line 2 \"\
    graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\u30E9\u30D5\
    \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T = int >\nstruct\
    \ Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\n  Edge(int\
    \ from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx)\
    \ {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename T = int\
    \ >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n  Graph()\
    \ = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t size() const\
    \ {\n    return g.size();\n  }\n\n  void add_directed_edge(int from, int to, T\
    \ cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\n  void\
    \ add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from, to,\
    \ cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void read(int\
    \ M, int padding = -1, bool weighted = false, bool directed = false) {\n    for(int\
    \ i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n      a += padding;\n\
    \      b += padding;\n      T c = T(1);\n      if(weighted) cin >> c;\n      if(directed)\
    \ add_directed_edge(a, b, c);\n      else add_edge(a, b, c);\n    }\n  }\n\n \
    \ inline vector< Edge< T > > &operator[](const int &k) {\n    return g[k];\n \
    \ }\n\n  inline const vector< Edge< T > > &operator[](const int &k) const {\n\
    \    return g[k];\n  }\n};\n\ntemplate< typename T = int >\nusing Edges = vector<\
    \ Edge< T > >;\n#line 1 \"structure/others/sparse-table.hpp\"\n/**\n * @brief\
    \ Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/sparse-table.md\n\
    \ */\ntemplate< typename T, typename F >\nstruct SparseTable {\n  F f;\n  vector<\
    \ vector< T > > st;\n  vector< int > lookup;\n\n  SparseTable() = default;\n\n\
    \  explicit SparseTable(const vector< T > &v, const F &f) : f(f) {\n    const\
    \ int n = (int) v.size();\n    const int b = 32 - __builtin_clz(n);\n    st.assign(b,\
    \ vector< T >(n));\n    for(int i = 0; i < v.size(); i++) {\n      st[0][i] =\
    \ v[i];\n    }\n    for(int i = 1; i < b; i++) {\n      for(int j = 0; j + (1\
    \ << i) <= n; j++) {\n        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i\
    \ - 1))]);\n      }\n    }\n    lookup.resize(v.size() + 1);\n    for(int i =\
    \ 2; i < lookup.size(); i++) {\n      lookup[i] = lookup[i >> 1] + 1;\n    }\n\
    \  }\n\n  inline T fold(int l, int r) const {\n    int b = lookup[r - l];\n  \
    \  return f(st[b][l], st[b][r - (1 << b)]);\n  }\n};\n\ntemplate< typename T,\
    \ typename F >\nSparseTable< T, F > get_sparse_table(const vector< T > &v, const\
    \ F &f) {\n  return SparseTable< T, F >(v, f);\n}\n#line 5 \"graph/tree/rmq-lowest-common-ancestor.hpp\"\
    \n\n/**\n * @brief RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148\
    )\n * @docs docs/rmq-lowest-common-ancestor.md\n **/\ntemplate< typename T = int\
    \ >\nstruct RMQLowestCommonAncestor : Graph< T > {\npublic:\n  using Graph< T\
    \ >::Graph;\n  using Graph< T >::g;\n  using F = function< int(int, int) >;\n\n\
    \  void build(int root = 0) {\n    ord.reserve(g.size() * 2 - 1);\n    dep.reserve(g.size()\
    \ * 2 - 1);\n    in.resize(g.size());\n    dfs(root, -1, 0);\n    vector< int\
    \ > vs(g.size() * 2 - 1);\n    iota(begin(vs), end(vs), 0);\n    F f = [&](int\
    \ a, int b) { return dep[a] < dep[b] ? a : b; };\n    st = get_sparse_table(vs,\
    \ f);\n  }\n\n  int lca(int x, int y) const {\n    if(in[x] > in[y]) swap(x, y);\n\
    \    return x == y ? x : ord[st.fold(in[x], in[y])];\n  }\n\nprivate:\n  vector<\
    \ int > ord, dep, in;\n  SparseTable< int, F > st;\n\n  void dfs(int idx, int\
    \ par, int d) {\n    in[idx] = (int) ord.size();\n    ord.emplace_back(idx);\n\
    \    dep.emplace_back(d);\n    for(auto &to : g[idx]) {\n      if(to != par) {\n\
    \        dfs(to, idx, d + 1);\n        ord.emplace_back(idx);\n        dep.emplace_back(d);\n\
    \      }\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"../../structure/others/sparse-table.hpp\"\
    \n\n/**\n * @brief RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148\
    )\n * @docs docs/rmq-lowest-common-ancestor.md\n **/\ntemplate< typename T = int\
    \ >\nstruct RMQLowestCommonAncestor : Graph< T > {\npublic:\n  using Graph< T\
    \ >::Graph;\n  using Graph< T >::g;\n  using F = function< int(int, int) >;\n\n\
    \  void build(int root = 0) {\n    ord.reserve(g.size() * 2 - 1);\n    dep.reserve(g.size()\
    \ * 2 - 1);\n    in.resize(g.size());\n    dfs(root, -1, 0);\n    vector< int\
    \ > vs(g.size() * 2 - 1);\n    iota(begin(vs), end(vs), 0);\n    F f = [&](int\
    \ a, int b) { return dep[a] < dep[b] ? a : b; };\n    st = get_sparse_table(vs,\
    \ f);\n  }\n\n  int lca(int x, int y) const {\n    if(in[x] > in[y]) swap(x, y);\n\
    \    return x == y ? x : ord[st.fold(in[x], in[y])];\n  }\n\nprivate:\n  vector<\
    \ int > ord, dep, in;\n  SparseTable< int, F > st;\n\n  void dfs(int idx, int\
    \ par, int d) {\n    in[idx] = (int) ord.size();\n    ord.emplace_back(idx);\n\
    \    dep.emplace_back(d);\n    for(auto &to : g[idx]) {\n      if(to != par) {\n\
    \        dfs(to, idx, d + 1);\n        ord.emplace_back(idx);\n        dep.emplace_back(d);\n\
    \      }\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  - structure/others/sparse-table.hpp
  isVerificationFile: false
  path: graph/tree/rmq-lowest-common-ancestor.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-lca-2.test.cpp
  - test/verify/aoj-grl-5-c-3.test.cpp
documentation_of: graph/tree/rmq-lowest-common-ancestor.hpp
layout: document
redirect_from:
- /library/graph/tree/rmq-lowest-common-ancestor.hpp
- /library/graph/tree/rmq-lowest-common-ancestor.hpp.html
title: "RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
---
## 概要
オイラーツアーとスパーステーブルによって最小共通祖先を求める.

辺属性のオイラーツアーをする. すべての頂点について, その頂点 $k$ に最初に到達した時刻 $in[k]$ と深さ $dep[k]$ を求めておく. 頂点 $u, v$ の最小共通祖先は区間 $[in[u], in[v]]$ の要素のうち深さが最小となる頂点である. 区間の最小値なのでスパーステーブルにより前計算しておくと, クエリあたり $O(1)$ で処理できる.

## 使い方

* `build()`: 構築する.
* `lca(u, v)`: 頂点 `u`, `v` の最小共通祖先(LCA)を返す.

## 計算量

* `build()`: $O(V \log V)$
* `lca()`: $O(1)$
