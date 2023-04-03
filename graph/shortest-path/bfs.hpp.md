---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-alds-1-11-c.test.cpp
    title: test/verify/aoj-alds-1-11-c.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "BFS(\u5E45\u512A\u5148\u63A2\u7D22)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/bfs.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/bfs.hpp\"\
    \n\n/**\n * @brief BFS(\u5E45\u512A\u5148\u63A2\u7D22)\n */\ntemplate< typename\
    \ T >\nvector< T > bfs(const Graph< T > &g, int s) {\n  T max_cost = 0, beet =\
    \ 0;\n  for(auto &es : g.g) {\n    for(auto &e : es) max_cost = max(max_cost,\
    \ e.cost);\n  }\n  ++max_cost;\n  const auto INF = numeric_limits< T >::max();\n\
    \  vector< T > dist(g.size(), INF);\n  vector< queue< int > > ques(max_cost +\
    \ 1);\n  dist[s] = 0;\n  ques[0].emplace(s);\n  for(T cost = 0; cost <= beet;\
    \ cost++) {\n    auto &que = ques[cost % max_cost];\n    while(!que.empty()) {\n\
    \      int idx = que.front();\n      que.pop();\n      if(dist[idx] < cost) continue;\n\
    \      for(auto &e : g[idx]) {\n        auto next_cost = cost + e.cost;\n    \
    \    if(dist[e.to] <= next_cost) continue;;\n        dist[e.to] = next_cost;\n\
    \        beet = max(beet, dist[e.to]);\n        ques[dist[e.to] % max_cost].emplace(e.to);\n\
    \      }\n    }\n  }\n  return dist;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief BFS(\u5E45\
    \u512A\u5148\u63A2\u7D22)\n */\ntemplate< typename T >\nvector< T > bfs(const\
    \ Graph< T > &g, int s) {\n  T max_cost = 0, beet = 0;\n  for(auto &es : g.g)\
    \ {\n    for(auto &e : es) max_cost = max(max_cost, e.cost);\n  }\n  ++max_cost;\n\
    \  const auto INF = numeric_limits< T >::max();\n  vector< T > dist(g.size(),\
    \ INF);\n  vector< queue< int > > ques(max_cost + 1);\n  dist[s] = 0;\n  ques[0].emplace(s);\n\
    \  for(T cost = 0; cost <= beet; cost++) {\n    auto &que = ques[cost % max_cost];\n\
    \    while(!que.empty()) {\n      int idx = que.front();\n      que.pop();\n \
    \     if(dist[idx] < cost) continue;\n      for(auto &e : g[idx]) {\n        auto\
    \ next_cost = cost + e.cost;\n        if(dist[e.to] <= next_cost) continue;;\n\
    \        dist[e.to] = next_cost;\n        beet = max(beet, dist[e.to]);\n    \
    \    ques[dist[e.to] % max_cost].emplace(e.to);\n      }\n    }\n  }\n  return\
    \ dist;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/bfs.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-alds-1-11-c.test.cpp
documentation_of: graph/shortest-path/bfs.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/bfs.hpp
- /library/graph/shortest-path/bfs.hpp.html
title: "BFS(\u5E45\u512A\u5148\u63A2\u7D22)"
---
