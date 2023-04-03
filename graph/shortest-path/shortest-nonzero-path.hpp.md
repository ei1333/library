---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1602.test.cpp
    title: test/verify/yukicoder-1602.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Shortest Nonzero Path(\u7FA4\u30E9\u30D9\u30EB\u5236\u7D04\u4ED8\
      \u304D\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
    links: []
  bundledCode: "#line 1 \"graph/shortest-path/shortest-nonzero-path.hpp\"\n/**\n *\
    \ @brief Shortest Nonzero Path(\u7FA4\u30E9\u30D9\u30EB\u5236\u7D04\u4ED8\u304D\
    \u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n */\ntemplate< typename T, typename\
    \ S, typename F >\nstruct ShortestNonzeroPath {\nprivate:\n  constexpr static\
    \ T INF = numeric_limits< T >::max();\n  struct edge {\n    int to;\n    T cost;\n\
    \    S label;\n  };\n  vector< vector< edge > > g;\n  F f;\n  vector< int > uf;\n\
    \n  int find_uf(int k) {\n    if(uf[k] == -1) return k;\n    return uf[k] = find_uf(uf[k]);\n\
    \  }\n\n  void unite_uf(int r, int c) {\n    uf[c] = r;\n  }\n\npublic:\n  explicit\
    \ ShortestNonzeroPath(int n, const F &f) : g(n), f(f) {}\n\n  void add_undirected_edge(int\
    \ u, int v, const T &cost, const S &label) {\n    add_directed_edge(u, v, cost,\
    \ label);\n    add_directed_edge(v, u, cost, label);\n  }\n\n  void add_directed_edge(int\
    \ u, int v, const T &cost, const S &label) {\n    g[u].emplace_back((edge) {v,\
    \ cost, label});\n  }\n\n  struct SP {\n    vector< T > dist;\n    vector< int\
    \ > depth, parent;\n    vector< S > label;\n  };\n\n  SP dijkstra(int s) {\n \
    \   int n = (int) g.size();\n    using pi = pair< T, int >;\n    vector< T > dist(n,\
    \ INF);\n    vector< int > depth(n, -1), parent(n, -1);\n    vector< S > label(n,\
    \ S());\n    priority_queue< pi, vector< pi >, greater<> > que;\n    dist[s] =\
    \ T(0);\n    depth[s] = 0;\n    que.emplace(0, s);\n    while(not que.empty())\
    \ {\n      T cost;\n      int u;\n      tie(cost, u) = que.top();\n      que.pop();\n\
    \      if(dist[u] < cost) {\n        continue;\n      }\n      for(auto e : g[u])\
    \ {\n        if(cost + e.cost < dist[e.to]) {\n          dist[e.to] = cost + e.cost;\n\
    \          depth[e.to] = depth[u] + 1;\n          parent[e.to] = u;\n        \
    \  label[e.to] = f(label[u], e.label);\n          que.emplace(dist[e.to], e.to);\n\
    \        }\n      }\n    }\n    return {dist, depth, parent, label};\n  }\n\n\
    \  vector< T > build(int s) {\n    int n = (int) g.size();\n    auto sp = dijkstra(s);\n\
    \n    uf.assign(n, -1);\n    using pi = tuple< T, int, int >;\n    priority_queue<\
    \ pi, vector< pi >, greater<> > que;\n    for(int u = 0; u < n; u++) {\n     \
    \ if(sp.dist[u] != INF) {\n        for(int i = 0; i < (int) g[u].size(); i++)\
    \ {\n          auto &e = g[u][i];\n          if(u < e.to and f(sp.label[u], e.label)\
    \ != sp.label[e.to]) {\n            que.emplace(sp.dist[u] + sp.dist[e.to] + e.cost,\
    \ u, i);\n          }\n        }\n      }\n    }\n    vector< T > dist(n, INF);\n\
    \    vector< int > bs;\n    while(not que.empty()) {\n      T cost;\n      int\
    \ u0, i;\n      tie(cost, u0, i) = que.top();\n      que.pop();\n      int v0\
    \ = g[u0][i].to;\n      int u = find_uf(u0), v = find_uf(v0);\n      while(u !=\
    \ v) {\n        if(sp.depth[u] > sp.depth[v]) {\n          bs.emplace_back(u);\n\
    \          u = find_uf(sp.parent[u]);\n        } else {\n          bs.emplace_back(v);\n\
    \          v = find_uf(sp.parent[v]);\n        }\n      }\n      for(auto &x :\
    \ bs) {\n        unite_uf(u, x);\n        dist[x] = cost - sp.dist[x];\n     \
    \   for(int j = 0; j < (int) g[x].size(); j++) {\n          auto &e = g[x][j];\n\
    \          if(f(sp.label[x], e.label) == sp.label[e.to]) {\n            que.emplace(dist[x]\
    \ + sp.dist[e.to] + e.cost, x, j);\n          }\n        }\n      }\n      bs.clear();\n\
    \    }\n    for(int i = 0; i < n; i++) {\n      if(sp.label[i] != S() and sp.dist[i]\
    \ < dist[i]) {\n        dist[i] = sp.dist[i];\n      }\n    }\n    return dist;\n\
    \  }\n};\n\ntemplate< typename T, typename S, typename F >\nShortestNonzeroPath<\
    \ T, S, F > get_shortest_nonzero_path(int N, const F &f) {\n  return ShortestNonzeroPath<\
    \ T, S, F >{N, f};\n}\n"
  code: "/**\n * @brief Shortest Nonzero Path(\u7FA4\u30E9\u30D9\u30EB\u5236\u7D04\
    \u4ED8\u304D\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n */\ntemplate< typename\
    \ T, typename S, typename F >\nstruct ShortestNonzeroPath {\nprivate:\n  constexpr\
    \ static T INF = numeric_limits< T >::max();\n  struct edge {\n    int to;\n \
    \   T cost;\n    S label;\n  };\n  vector< vector< edge > > g;\n  F f;\n  vector<\
    \ int > uf;\n\n  int find_uf(int k) {\n    if(uf[k] == -1) return k;\n    return\
    \ uf[k] = find_uf(uf[k]);\n  }\n\n  void unite_uf(int r, int c) {\n    uf[c] =\
    \ r;\n  }\n\npublic:\n  explicit ShortestNonzeroPath(int n, const F &f) : g(n),\
    \ f(f) {}\n\n  void add_undirected_edge(int u, int v, const T &cost, const S &label)\
    \ {\n    add_directed_edge(u, v, cost, label);\n    add_directed_edge(v, u, cost,\
    \ label);\n  }\n\n  void add_directed_edge(int u, int v, const T &cost, const\
    \ S &label) {\n    g[u].emplace_back((edge) {v, cost, label});\n  }\n\n  struct\
    \ SP {\n    vector< T > dist;\n    vector< int > depth, parent;\n    vector< S\
    \ > label;\n  };\n\n  SP dijkstra(int s) {\n    int n = (int) g.size();\n    using\
    \ pi = pair< T, int >;\n    vector< T > dist(n, INF);\n    vector< int > depth(n,\
    \ -1), parent(n, -1);\n    vector< S > label(n, S());\n    priority_queue< pi,\
    \ vector< pi >, greater<> > que;\n    dist[s] = T(0);\n    depth[s] = 0;\n   \
    \ que.emplace(0, s);\n    while(not que.empty()) {\n      T cost;\n      int u;\n\
    \      tie(cost, u) = que.top();\n      que.pop();\n      if(dist[u] < cost) {\n\
    \        continue;\n      }\n      for(auto e : g[u]) {\n        if(cost + e.cost\
    \ < dist[e.to]) {\n          dist[e.to] = cost + e.cost;\n          depth[e.to]\
    \ = depth[u] + 1;\n          parent[e.to] = u;\n          label[e.to] = f(label[u],\
    \ e.label);\n          que.emplace(dist[e.to], e.to);\n        }\n      }\n  \
    \  }\n    return {dist, depth, parent, label};\n  }\n\n  vector< T > build(int\
    \ s) {\n    int n = (int) g.size();\n    auto sp = dijkstra(s);\n\n    uf.assign(n,\
    \ -1);\n    using pi = tuple< T, int, int >;\n    priority_queue< pi, vector<\
    \ pi >, greater<> > que;\n    for(int u = 0; u < n; u++) {\n      if(sp.dist[u]\
    \ != INF) {\n        for(int i = 0; i < (int) g[u].size(); i++) {\n          auto\
    \ &e = g[u][i];\n          if(u < e.to and f(sp.label[u], e.label) != sp.label[e.to])\
    \ {\n            que.emplace(sp.dist[u] + sp.dist[e.to] + e.cost, u, i);\n   \
    \       }\n        }\n      }\n    }\n    vector< T > dist(n, INF);\n    vector<\
    \ int > bs;\n    while(not que.empty()) {\n      T cost;\n      int u0, i;\n \
    \     tie(cost, u0, i) = que.top();\n      que.pop();\n      int v0 = g[u0][i].to;\n\
    \      int u = find_uf(u0), v = find_uf(v0);\n      while(u != v) {\n        if(sp.depth[u]\
    \ > sp.depth[v]) {\n          bs.emplace_back(u);\n          u = find_uf(sp.parent[u]);\n\
    \        } else {\n          bs.emplace_back(v);\n          v = find_uf(sp.parent[v]);\n\
    \        }\n      }\n      for(auto &x : bs) {\n        unite_uf(u, x);\n    \
    \    dist[x] = cost - sp.dist[x];\n        for(int j = 0; j < (int) g[x].size();\
    \ j++) {\n          auto &e = g[x][j];\n          if(f(sp.label[x], e.label) ==\
    \ sp.label[e.to]) {\n            que.emplace(dist[x] + sp.dist[e.to] + e.cost,\
    \ x, j);\n          }\n        }\n      }\n      bs.clear();\n    }\n    for(int\
    \ i = 0; i < n; i++) {\n      if(sp.label[i] != S() and sp.dist[i] < dist[i])\
    \ {\n        dist[i] = sp.dist[i];\n      }\n    }\n    return dist;\n  }\n};\n\
    \ntemplate< typename T, typename S, typename F >\nShortestNonzeroPath< T, S, F\
    \ > get_shortest_nonzero_path(int N, const F &f) {\n  return ShortestNonzeroPath<\
    \ T, S, F >{N, f};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest-path/shortest-nonzero-path.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1602.test.cpp
documentation_of: graph/shortest-path/shortest-nonzero-path.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/shortest-nonzero-path.hpp
- /library/graph/shortest-path/shortest-nonzero-path.hpp.html
title: "Shortest Nonzero Path(\u7FA4\u30E9\u30D9\u30EB\u5236\u7D04\u4ED8\u304D\u5358\
  \u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
---
