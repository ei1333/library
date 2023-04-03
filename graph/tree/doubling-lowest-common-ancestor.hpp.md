---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c.test.cpp
    title: test/verify/aoj-grl-5-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-3.test.cpp
    title: test/verify/yosupo-lca-3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/doubling-lowest-common-ancestor.md
    document_title: "Doubling-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\
      \u5148)"
    links: []
  bundledCode: "#line 2 \"graph/tree/doubling-lowest-common-ancestor.hpp\"\n\n#line\
    \ 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\u30E9\
    \u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T = int >\n\
    struct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
    \n  Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost),\
    \ idx(idx) {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename\
    \ T = int >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n\
    \  Graph() = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t\
    \ size() const {\n    return g.size();\n  }\n\n  void add_directed_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\
    \n  void add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from,\
    \ to, cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void\
    \ read(int M, int padding = -1, bool weighted = false, bool directed = false)\
    \ {\n    for(int i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n\
    \      a += padding;\n      b += padding;\n      T c = T(1);\n      if(weighted)\
    \ cin >> c;\n      if(directed) add_directed_edge(a, b, c);\n      else add_edge(a,\
    \ b, c);\n    }\n  }\n\n  inline vector< Edge< T > > &operator[](const int &k)\
    \ {\n    return g[k];\n  }\n\n  inline const vector< Edge< T > > &operator[](const\
    \ int &k) const {\n    return g[k];\n  }\n};\n\ntemplate< typename T = int >\n\
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/doubling-lowest-common-ancestor.hpp\"\
    \n\n/**\n * @brief Doubling-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\
    \u5148)\n * @docs docs/doubling-lowest-common-ancestor.md\n */\ntemplate< typename\
    \ T >\nstruct DoublingLowestCommonAncestor : Graph< T > {\npublic:\n  using Graph<\
    \ T >::g;\n  vector< int > dep;\n  vector< T > sum;\n  vector< vector< int > >\
    \ table;\n  const int LOG;\n\n  explicit DoublingLowestCommonAncestor(int n)\n\
    \      : Graph< T >(n), LOG(32 - __builtin_clz(g.size())) {}\n\n  explicit DoublingLowestCommonAncestor(const\
    \ Graph< T > &g)\n      : LOG(32 - __builtin_clz(g.size())), Graph< T >(g) {}\n\
    \n  void build(int root = 0) {\n    dep.assign(g.size(), 0);\n    sum.assign(g.size(),\
    \ 0);\n    table.assign(LOG, vector< int >(g.size(), -1));\n    dfs(root, -1,\
    \ 0);\n    for(int k = 0; k + 1 < LOG; k++) {\n      for(int i = 0; i < (int)table[k].size();\
    \ i++) {\n        if(table[k][i] == -1) table[k + 1][i] = -1;\n        else table[k\
    \ + 1][i] = table[k][table[k][i]];\n      }\n    }\n  }\n\n  int lca(int u, int\
    \ v) {\n    if(dep[u] > dep[v]) swap(u, v);\n    v = climb(v, dep[v] - dep[u]);\n\
    \    if(u == v) return u;\n    for(int i = LOG - 1; i >= 0; i--) {\n      if(table[i][u]\
    \ != table[i][v]) {\n        u = table[i][u];\n        v = table[i][v];\n    \
    \  }\n    }\n    return table[0][u];\n  }\n\n  int climb(int u, int k) {\n   \
    \ if(dep[u] < k) return -1;\n    for(int i = LOG - 1; i >= 0; i--) {\n      if((k\
    \ >> i) & 1) u = table[i][u];\n    }\n    return u;\n  }\n\n  T dist(int u, int\
    \ v) {\n    return sum[u] + sum[v] - 2 * sum[lca(u, v)];\n  }\n\nprivate:\n  void\
    \ dfs(int idx, int par, int d) {\n    table[0][idx] = par;\n    dep[idx] = d;\n\
    \    for(auto &to : g[idx]) {\n      if(to != par) {\n        sum[to] = sum[idx]\
    \ + to.cost;\n        dfs(to, idx, d + 1);\n      }\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Doubling-Lowest-Common-Ancestor(\u6700\
    \u5C0F\u5171\u901A\u7956\u5148)\n * @docs docs/doubling-lowest-common-ancestor.md\n\
    \ */\ntemplate< typename T >\nstruct DoublingLowestCommonAncestor : Graph< T >\
    \ {\npublic:\n  using Graph< T >::g;\n  vector< int > dep;\n  vector< T > sum;\n\
    \  vector< vector< int > > table;\n  const int LOG;\n\n  explicit DoublingLowestCommonAncestor(int\
    \ n)\n      : Graph< T >(n), LOG(32 - __builtin_clz(g.size())) {}\n\n  explicit\
    \ DoublingLowestCommonAncestor(const Graph< T > &g)\n      : LOG(32 - __builtin_clz(g.size())),\
    \ Graph< T >(g) {}\n\n  void build(int root = 0) {\n    dep.assign(g.size(), 0);\n\
    \    sum.assign(g.size(), 0);\n    table.assign(LOG, vector< int >(g.size(), -1));\n\
    \    dfs(root, -1, 0);\n    for(int k = 0; k + 1 < LOG; k++) {\n      for(int\
    \ i = 0; i < (int)table[k].size(); i++) {\n        if(table[k][i] == -1) table[k\
    \ + 1][i] = -1;\n        else table[k + 1][i] = table[k][table[k][i]];\n     \
    \ }\n    }\n  }\n\n  int lca(int u, int v) {\n    if(dep[u] > dep[v]) swap(u,\
    \ v);\n    v = climb(v, dep[v] - dep[u]);\n    if(u == v) return u;\n    for(int\
    \ i = LOG - 1; i >= 0; i--) {\n      if(table[i][u] != table[i][v]) {\n      \
    \  u = table[i][u];\n        v = table[i][v];\n      }\n    }\n    return table[0][u];\n\
    \  }\n\n  int climb(int u, int k) {\n    if(dep[u] < k) return -1;\n    for(int\
    \ i = LOG - 1; i >= 0; i--) {\n      if((k >> i) & 1) u = table[i][u];\n    }\n\
    \    return u;\n  }\n\n  T dist(int u, int v) {\n    return sum[u] + sum[v] -\
    \ 2 * sum[lca(u, v)];\n  }\n\nprivate:\n  void dfs(int idx, int par, int d) {\n\
    \    table[0][idx] = par;\n    dep[idx] = d;\n    for(auto &to : g[idx]) {\n \
    \     if(to != par) {\n        sum[to] = sum[idx] + to.cost;\n        dfs(to,\
    \ idx, d + 1);\n      }\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/doubling-lowest-common-ancestor.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-lca-3.test.cpp
  - test/verify/aoj-grl-5-c.test.cpp
documentation_of: graph/tree/doubling-lowest-common-ancestor.hpp
layout: document
redirect_from:
- /library/graph/tree/doubling-lowest-common-ancestor.hpp
- /library/graph/tree/doubling-lowest-common-ancestor.hpp.html
title: "Doubling-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
---
## 概要
ダブリングによって最小共通祖先を求める.

頂点 $u$, $v$ の最小共通祖先を求めたいとする. $dep[i]$ をある頂点を根とする根付き木としてみたときの深さとし, $dep[u] \leq dep[v]$ を仮定する. まず $dep[v] - dep[u]$ 個だけ頂点 $v$ を親に遡らせて, 頂点 $u, v$ の深さを揃える. このとき深さが一致したらそれが最小共通祖先. それ以外のとき, 上位 bit から頂点 $u, v$ 双方の $2^k$ 個先の親を見て, 異なれば遡ることを繰り返し, 双方の親ではない直前の頂点を求める. するとその親が最小共通祖先であることがわかる.

## 使い方

* `build()`: 構築する.
* `lca(u, v)`: 頂点 `u`, `v` の最小共通祖先(LCA)を返す.
* `climb(u, k)`: 頂点 `u` から `k` 個親に遡った頂点を返す.
* `dist(u, v)`: 頂点 `u`, `v` 間のパスの辺の本数を返す.

## 計算量

* `build()`: $O(V)$
* `lca()`, `climb(u, k)`, `dist()`: $O(\log V)$
