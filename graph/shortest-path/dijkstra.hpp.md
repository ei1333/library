---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0275.test.cpp
    title: test/verify/aoj-0275.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-1-a.test.cpp
    title: test/verify/aoj-grl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-k-shortest-walk.test.cpp
    title: test/verify/yosupo-k-shortest-walk.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-shortest-path.test.cpp
    title: test/verify/yosupo-shortest-path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/dijkstra.md
    document_title: "Dijkstra(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/dijkstra.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/dijkstra.hpp\"\
    \n\n/**\n * @brief Dijkstra(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n * @docs\
    \ docs/dijkstra.md\n */\ntemplate< typename T >\nstruct ShortestPath {\n  vector<\
    \ T > dist;\n  vector< int > from, id;\n};\n\ntemplate< typename T >\nShortestPath<\
    \ T > dijkstra(const Graph< T > &g, int s) {\n  const auto INF = numeric_limits<\
    \ T >::max();\n  vector< T > dist(g.size(), INF);\n  vector< int > from(g.size(),\
    \ -1), id(g.size(), -1);\n  using Pi = pair< T, int >;\n  priority_queue< Pi,\
    \ vector< Pi >, greater<> > que;\n  dist[s] = 0;\n  que.emplace(dist[s], s);\n\
    \  while(!que.empty()) {\n    T cost;\n    int idx;\n    tie(cost, idx) = que.top();\n\
    \    que.pop();\n    if(dist[idx] < cost) continue;\n    for(auto &e : g[idx])\
    \ {\n      auto next_cost = cost + e.cost;\n      if(dist[e.to] <= next_cost)\
    \ continue;\n      dist[e.to] = next_cost;\n      from[e.to] = idx;\n      id[e.to]\
    \ = e.idx;\n      que.emplace(dist[e.to], e.to);\n    }\n  }\n  return {dist,\
    \ from, id};\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Dijkstra(\u5358\
    \u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n * @docs docs/dijkstra.md\n */\ntemplate<\
    \ typename T >\nstruct ShortestPath {\n  vector< T > dist;\n  vector< int > from,\
    \ id;\n};\n\ntemplate< typename T >\nShortestPath< T > dijkstra(const Graph< T\
    \ > &g, int s) {\n  const auto INF = numeric_limits< T >::max();\n  vector< T\
    \ > dist(g.size(), INF);\n  vector< int > from(g.size(), -1), id(g.size(), -1);\n\
    \  using Pi = pair< T, int >;\n  priority_queue< Pi, vector< Pi >, greater<> >\
    \ que;\n  dist[s] = 0;\n  que.emplace(dist[s], s);\n  while(!que.empty()) {\n\
    \    T cost;\n    int idx;\n    tie(cost, idx) = que.top();\n    que.pop();\n\
    \    if(dist[idx] < cost) continue;\n    for(auto &e : g[idx]) {\n      auto next_cost\
    \ = cost + e.cost;\n      if(dist[e.to] <= next_cost) continue;\n      dist[e.to]\
    \ = next_cost;\n      from[e.to] = idx;\n      id[e.to] = e.idx;\n      que.emplace(dist[e.to],\
    \ e.to);\n    }\n  }\n  return {dist, from, id};\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/dijkstra.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-1-a.test.cpp
  - test/verify/yosupo-k-shortest-walk.test.cpp
  - test/verify/yosupo-shortest-path.test.cpp
  - test/verify/aoj-0275.test.cpp
documentation_of: graph/shortest-path/dijkstra.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/dijkstra.hpp
- /library/graph/shortest-path/dijkstra.hpp.html
title: "Dijkstra(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
---
## 概要

負辺のないグラフで単一始点全点間最短路を求めるアルゴリズム. 各地点でもっとも近い頂点から距離が確定していく. 距離順でソートされたヒープを用いると, 効率よく距離を確定していくことができる.

* `dijkstra(g, s)`: 重み付きグラフ `g` で, 頂点 `s` から全点間の最短コストを求める. `dist` には最短コスト(到達できないとき型の最大値), `from` にはその頂点の直前に訪れた頂点(頂点 `s` または到達できない頂点は $-1$), `id` はその頂点の直前に使った辺番号が格納される.

## 計算量

* $O(E \log V)$ 
