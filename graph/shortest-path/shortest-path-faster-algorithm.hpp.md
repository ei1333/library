---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-1-b-2.test.cpp
    title: test/verify/aoj-grl-1-b-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Shortest-Path-Faster-Algorithm(\u5358\u4E00\u59CB\u70B9\u6700\
      \u77ED\u8DEF)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/shortest-path-faster-algorithm.hpp\"\
    \n\n#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
    \u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T =\
    \ int >\nstruct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
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
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/shortest-path-faster-algorithm.hpp\"\
    \n\n/**\n * @brief Shortest-Path-Faster-Algorithm(\u5358\u4E00\u59CB\u70B9\u6700\
    \u77ED\u8DEF)\n */\ntemplate< typename T >\nvector< T > shortest_path_faster_algorithm(const\
    \ Graph< T > &g, int s) {\n  const auto INF = numeric_limits< T >::max();\n  vector<\
    \ T > dist(g.size(), INF);\n  vector< int > pending(g.size(), 0), times(g.size(),\
    \ 0);\n  queue< int > que;\n\n  que.emplace(s);\n  pending[s] = true;\n  ++times[s];\n\
    \  dist[s] = 0;\n\n  while(!que.empty()) {\n    int p = que.front();\n    que.pop();\n\
    \    pending[p] = false;\n    for(auto &e : g[p]) {\n      T next_cost = dist[p]\
    \ + e.cost;\n      if(next_cost >= dist[e.to]) continue;\n      dist[e.to] = next_cost;\n\
    \      if(!pending[e.to]) {\n        if(++times[e.to] >= (int)g.size()) return\
    \ vector< T >();\n        pending[e.to] = true;\n        que.emplace(e.to);\n\
    \      }\n    }\n  }\n  return dist;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Shortest-Path-Faster-Algorithm(\u5358\
    \u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n */\ntemplate< typename T >\nvector< T\
    \ > shortest_path_faster_algorithm(const Graph< T > &g, int s) {\n  const auto\
    \ INF = numeric_limits< T >::max();\n  vector< T > dist(g.size(), INF);\n  vector<\
    \ int > pending(g.size(), 0), times(g.size(), 0);\n  queue< int > que;\n\n  que.emplace(s);\n\
    \  pending[s] = true;\n  ++times[s];\n  dist[s] = 0;\n\n  while(!que.empty())\
    \ {\n    int p = que.front();\n    que.pop();\n    pending[p] = false;\n    for(auto\
    \ &e : g[p]) {\n      T next_cost = dist[p] + e.cost;\n      if(next_cost >= dist[e.to])\
    \ continue;\n      dist[e.to] = next_cost;\n      if(!pending[e.to]) {\n     \
    \   if(++times[e.to] >= (int)g.size()) return vector< T >();\n        pending[e.to]\
    \ = true;\n        que.emplace(e.to);\n      }\n    }\n  }\n  return dist;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/shortest-path-faster-algorithm.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-1-b-2.test.cpp
documentation_of: graph/shortest-path/shortest-path-faster-algorithm.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/shortest-path-faster-algorithm.hpp
- /library/graph/shortest-path/shortest-path-faster-algorithm.hpp.html
title: "Shortest-Path-Faster-Algorithm(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
---
