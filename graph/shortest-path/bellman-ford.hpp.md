---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0304.test.cpp
    title: test/verify/aoj-0304.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-1-b.test.cpp
    title: test/verify/aoj-grl-1-b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/bellman-ford.md
    document_title: "Bellman-Ford(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/bellman-ford.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/bellman-ford.hpp\"\
    \n\n/**\n * @brief Bellman-Ford(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n\
    \ * @docs docs/bellman-ford.md\n */\ntemplate< typename T >\nvector< T > bellman_ford(const\
    \ Edges< T > &edges, int V, int s) {\n  const auto INF = numeric_limits< T >::max();\n\
    \  vector< T > dist(V, INF);\n  dist[s] = 0;\n  for(int i = 0; i < V - 1; i++)\
    \ {\n    for(auto &e : edges) {\n      if(dist[e.from] == INF) continue;\n   \
    \   dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);\n    }\n  }\n  for(auto\
    \ &e : edges) {\n    if(dist[e.from] == INF) continue;\n    if(dist[e.from] +\
    \ e.cost < dist[e.to]) return vector< T >();\n  }\n  return dist;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Bellman-Ford(\u5358\
    \u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n * @docs docs/bellman-ford.md\n */\ntemplate<\
    \ typename T >\nvector< T > bellman_ford(const Edges< T > &edges, int V, int s)\
    \ {\n  const auto INF = numeric_limits< T >::max();\n  vector< T > dist(V, INF);\n\
    \  dist[s] = 0;\n  for(int i = 0; i < V - 1; i++) {\n    for(auto &e : edges)\
    \ {\n      if(dist[e.from] == INF) continue;\n      dist[e.to] = min(dist[e.to],\
    \ dist[e.from] + e.cost);\n    }\n  }\n  for(auto &e : edges) {\n    if(dist[e.from]\
    \ == INF) continue;\n    if(dist[e.from] + e.cost < dist[e.to]) return vector<\
    \ T >();\n  }\n  return dist;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/bellman-ford.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-0304.test.cpp
  - test/verify/aoj-grl-1-b.test.cpp
documentation_of: graph/shortest-path/bellman-ford.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/bellman-ford.hpp
- /library/graph/shortest-path/bellman-ford.hpp.html
title: "Bellman-Ford(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
---
## 概要

単一始点全点間最短路を求めるアルゴリズム. 負辺があっても動作する. また負閉路も検出する.

負閉路がない場合, 全ての頂点への最短路に含まれる辺の本数は $V - 1$ 本以下である. したがって $V - 1$ 回すべての辺を走査して最短路を更新すると, 最終的な最短路が求まる.

負閉路がある場合 $V$ 回目に更新があるときだが, 始点とある頂点との $2$ 点間のパスに負閉路が含まれることと同値ではないので注意すること(これを判定した場合は負閉路からその頂点に到達可能か判定するか, 始点とある頂点から到達できない頂点を予め削除しておく必要がある, 実装しなさーい！).

## 使い方
* `bellman_ford(g, V, s)`: `V` 頂点の重み付きグラフ `g` で, 頂点 `s` から全点間の最短コストを求める.

## 計算量

* $O(VE)$
