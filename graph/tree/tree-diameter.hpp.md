---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-a.test.cpp
    title: test/verify/aoj-grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-tree-diameter.test.cpp
    title: test/verify/yosupo-tree-diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/tree-diameter.md
    document_title: "Tree-Diameter(\u6728\u306E\u76F4\u5F84)"
    links: []
  bundledCode: "#line 2 \"graph/tree/tree-diameter.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
    \n\n/**\n * @brief Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\
    \u30C8)\n */\ntemplate< typename T = int >\nstruct Edge {\n  int from, to;\n \
    \ T cost;\n  int idx;\n\n  Edge() = default;\n\n  Edge(int from, int to, T cost\
    \ = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}\n\n  operator\
    \ int() const { return to; }\n};\n\ntemplate< typename T = int >\nstruct Graph\
    \ {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n  Graph() = default;\n\n\
    \  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t size() const {\n    return\
    \ g.size();\n  }\n\n  void add_directed_edge(int from, int to, T cost = 1) {\n\
    \    g[from].emplace_back(from, to, cost, es++);\n  }\n\n  void add_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es);\n    g[to].emplace_back(to,\
    \ from, cost, es++);\n  }\n\n  void read(int M, int padding = -1, bool weighted\
    \ = false, bool directed = false) {\n    for(int i = 0; i < M; i++) {\n      int\
    \ a, b;\n      cin >> a >> b;\n      a += padding;\n      b += padding;\n    \
    \  T c = T(1);\n      if(weighted) cin >> c;\n      if(directed) add_directed_edge(a,\
    \ b, c);\n      else add_edge(a, b, c);\n    }\n  }\n\n  inline vector< Edge<\
    \ T > > &operator[](const int &k) {\n    return g[k];\n  }\n\n  inline const vector<\
    \ Edge< T > > &operator[](const int &k) const {\n    return g[k];\n  }\n};\n\n\
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/tree-diameter.hpp\"\
    \n\n/**\n * @brief Tree-Diameter(\u6728\u306E\u76F4\u5F84)\n * @docs docs/tree-diameter.md\n\
    \ */\ntemplate< typename T = int >\nstruct TreeDiameter : Graph< T > {\npublic:\n\
    \  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector< Edge< T > > path;\n\
    \n  T build() {\n    to.assign(g.size(), -1);\n    auto p = dfs(0, -1);\n    auto\
    \ q = dfs(p.second, -1);\n\n    int now = p.second;\n    while(now != q.second)\
    \ {\n      for(auto &e : g[now]) {\n        if(to[now] == e.to) {\n          path.emplace_back(e);\n\
    \        }\n      }\n      now = to[now];\n    }\n    return q.first;\n  }\n\n\
    \  explicit TreeDiameter(const Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n\
    \  vector< int > to;\n\n  pair< T, int > dfs(int idx, int par) {\n    pair< T,\
    \ int > ret(0, idx);\n    for(auto &e : g[idx]) {\n      if(e.to == par) continue;\n\
    \      auto cost = dfs(e.to, idx);\n      cost.first += e.cost;\n      if(ret\
    \ < cost) {\n        ret = cost;\n        to[idx] = e.to;\n      }\n    }\n  \
    \  return ret;\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Tree-Diameter(\u6728\
    \u306E\u76F4\u5F84)\n * @docs docs/tree-diameter.md\n */\ntemplate< typename T\
    \ = int >\nstruct TreeDiameter : Graph< T > {\npublic:\n  using Graph< T >::Graph;\n\
    \  using Graph< T >::g;\n  vector< Edge< T > > path;\n\n  T build() {\n    to.assign(g.size(),\
    \ -1);\n    auto p = dfs(0, -1);\n    auto q = dfs(p.second, -1);\n\n    int now\
    \ = p.second;\n    while(now != q.second) {\n      for(auto &e : g[now]) {\n \
    \       if(to[now] == e.to) {\n          path.emplace_back(e);\n        }\n  \
    \    }\n      now = to[now];\n    }\n    return q.first;\n  }\n\n  explicit TreeDiameter(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  vector< int > to;\n\n  pair<\
    \ T, int > dfs(int idx, int par) {\n    pair< T, int > ret(0, idx);\n    for(auto\
    \ &e : g[idx]) {\n      if(e.to == par) continue;\n      auto cost = dfs(e.to,\
    \ idx);\n      cost.first += e.cost;\n      if(ret < cost) {\n        ret = cost;\n\
    \        to[idx] = e.to;\n      }\n    }\n    return ret;\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/tree-diameter.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-tree-diameter.test.cpp
  - test/verify/aoj-grl-5-a.test.cpp
documentation_of: graph/tree/tree-diameter.hpp
layout: document
redirect_from:
- /library/graph/tree/tree-diameter.hpp
- /library/graph/tree/tree-diameter.hpp.html
title: "Tree-Diameter(\u6728\u306E\u76F4\u5F84)"
---
## 概要

木の直径を求める.

適当な頂点から DFS して最も遠い点 $u$ を求める, $u$ から DFS して最も遠い点 $v$ を見つけると, そのペア $(u, v)$ が直径の端点.

## 使い方

* `build()`: 木の直径を返す. `path` には直径を構成する辺が格納される.

## 計算量

$O(V)$
