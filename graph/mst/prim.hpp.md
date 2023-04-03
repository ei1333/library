---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-2-a.test.cpp
    title: test/verify/aoj-grl-2-a.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/prim.md
    document_title: "Prim(\u6700\u5C0F\u5168\u57DF\u6728)"
    links: []
  bundledCode: "#line 2 \"graph/mst/prim.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/mst/prim.hpp\"\
    \n\n/**\n * @brief Prim(\u6700\u5C0F\u5168\u57DF\u6728)\n * @docs docs/prim.md\n\
    \ */\ntemplate< typename T >\nstruct MinimumSpanningTree {\n  T cost;\n  Edges<\
    \ T > edges;\n};\n\ntemplate< typename T >\nMinimumSpanningTree< T > prim(const\
    \ Graph< T > &g) {\n  T total = T();\n  vector< int > used(g.size());\n  vector<\
    \ Edge< T > * > dist(g.size());\n  using pi = pair< T, int >;\n  priority_queue<\
    \ pi, vector< pi >, greater<> > que;\n  que.emplace(T(), 0);\n  Edges< T > edges;\n\
    \  while(!que.empty()) {\n    auto p = que.top();\n    que.pop();\n    if(used[p.second])\
    \ continue;\n    used[p.second] = true;\n    total += p.first;\n    if(dist[p.second])\
    \ edges.emplace_back(*dist[p.second]);\n    for(auto &e : g[p.second]) {\n   \
    \   if(used[e.to] || (dist[e.to] && dist[e.to]->cost <= e.cost)) continue;\n \
    \     que.emplace(e.cost, e.to);\n    }\n  }\n  return {total, edges};\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Prim(\u6700\
    \u5C0F\u5168\u57DF\u6728)\n * @docs docs/prim.md\n */\ntemplate< typename T >\n\
    struct MinimumSpanningTree {\n  T cost;\n  Edges< T > edges;\n};\n\ntemplate<\
    \ typename T >\nMinimumSpanningTree< T > prim(const Graph< T > &g) {\n  T total\
    \ = T();\n  vector< int > used(g.size());\n  vector< Edge< T > * > dist(g.size());\n\
    \  using pi = pair< T, int >;\n  priority_queue< pi, vector< pi >, greater<> >\
    \ que;\n  que.emplace(T(), 0);\n  Edges< T > edges;\n  while(!que.empty()) {\n\
    \    auto p = que.top();\n    que.pop();\n    if(used[p.second]) continue;\n \
    \   used[p.second] = true;\n    total += p.first;\n    if(dist[p.second]) edges.emplace_back(*dist[p.second]);\n\
    \    for(auto &e : g[p.second]) {\n      if(used[e.to] || (dist[e.to] && dist[e.to]->cost\
    \ <= e.cost)) continue;\n      que.emplace(e.cost, e.to);\n    }\n  }\n  return\
    \ {total, edges};\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/mst/prim.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-2-a.test.cpp
documentation_of: graph/mst/prim.hpp
layout: document
redirect_from:
- /library/graph/mst/prim.hpp
- /library/graph/mst/prim.hpp.html
title: "Prim(\u6700\u5C0F\u5168\u57DF\u6728)"
---
## 概要

最小全域木(全域木のうち, その辺群の重みの総和が最小になる木)を求める. 既に到達した頂点集合からまだ到達していない頂点集合への辺のうち, コストが最小のものを選んでいくことによって, 最小全域木を構成している.

* `prim(g)`: 連結な重み付きグラフ `g` の最小全域木を求める. `cost` には辺の重みの総和, `edges` にはそれを構成する辺が格納される.

## 計算量

* $O(E \log V)$ 
