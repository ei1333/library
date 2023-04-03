---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1069.test.cpp
    title: test/verify/yukicoder-1069.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/k-shortest-path.md
    document_title: K-Shortest-Path
    links:
    - https://qiita.com/nariaki3551/items/821dc6ffdc552d3d5f22
  bundledCode: "#line 2 \"graph/shortest-path/k-shortest-path.hpp\"\n\n#line 2 \"\
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
    \ Edge< T > >;\n#line 4 \"graph/shortest-path/k-shortest-path.hpp\"\n\n/**\n *\
    \ @brief K-Shortest-Path\n * @docs docs/k-shortest-path.md\n * @see https://qiita.com/nariaki3551/items/821dc6ffdc552d3d5f22\n\
    \ */\ntemplate< typename T >\nvector< pair< T, vector< int > > > k_shortest_path(const\
    \ Graph< T > &g, int s, int t, int k) {\n  assert(s != t);\n  int N = (int) g.size();\n\
    \  int M = 0;\n  for(int i = 0; i < N; i++) M += (int) g[i].size();\n  vector<\
    \ int > latte(M), malta(M);\n  vector< T > cost(M);\n  for(int i = 0; i < N; i++)\
    \ {\n    for(auto &e : g[i]) {\n      latte[e.idx] = i;\n      malta[e.idx] =\
    \ e.to;\n      cost[e.idx] = e.cost;\n    }\n  }\n  const auto INF = numeric_limits<\
    \ T >::max();\n  vector< int > dame(M, -1);\n  int timestamp = 0;\n  auto shortest_path\
    \ = [&](vector< T > &dist, vector< int > &from, vector< int > &id, int st) {\n\
    \    using Pi = pair< T, int >;\n    priority_queue< Pi, vector< Pi >, greater<>\
    \ > que;\n    que.emplace(dist[st], st);\n    while(!que.empty()) {\n      T cost;\n\
    \      int idx;\n      tie(cost, idx) = que.top();\n      que.pop();\n      if(dist[idx]\
    \ < cost) continue;\n      if(idx == t) return;\n      for(auto &e : g[idx]) {\n\
    \        auto next_cost = cost + e.cost;\n        if(dist[e.to] <= next_cost)\
    \ continue;\n        if(dame[e.idx] == timestamp) continue;\n        dist[e.to]\
    \ = next_cost;\n        from[e.to] = idx;\n        id[e.to] = e.idx;\n       \
    \ que.emplace(dist[e.to], e.to);\n      }\n    }\n  };\n  auto restore = [](const\
    \ vector< int > &es, const vector< int > &vs, int from, int to) {\n    vector<\
    \ int > tap;\n    while(to != from) {\n      tap.emplace_back(es[to]);\n     \
    \ to = vs[to];\n    }\n    reverse(begin(tap), end(tap));\n    return tap;\n \
    \ };\n\n  vector< T > dist(g.size(), INF);\n  vector< int > from(g.size(), -1),\
    \ id(g.size(), -1);\n  dist[s] = 0;\n  shortest_path(dist, from, id, s);\n  if(dist[t]\
    \ == INF) return {};\n\n  vector< pair< T, vector< int > > > A;\n  set< pair<\
    \ T, vector< int > > > B;\n  A.emplace_back(dist[t], restore(id, from, s, t));\n\
    \n  for(int i = 1; i < k; i++) {\n    dist.assign(g.size(), INF);\n    from.assign(g.size(),\
    \ -1);\n    id.assign(g.size(), -1);\n    dist[s] = 0;\n    vector< int > candidate(A.size());\n\
    \    iota(begin(candidate), end(candidate), 0);\n    auto &last_path = A.back().second;\n\
    \    int cur = s;\n    for(int j = 0; j < last_path.size(); j++) {\n      for(auto\
    \ &k : candidate) {\n        if(j < A[k].second.size()) dame[A[k].second[j]] =\
    \ timestamp;\n      }\n      vector< T > dist2{dist};\n      vector< int > from2{from},\
    \ id2{id};\n      shortest_path(dist2, from2, id2, cur);\n      ++timestamp;\n\
    \      if(dist2[t] != INF) {\n        auto path = restore(id2, from2, s, t);\n\
    \        bool ok = true;\n        for(auto &p : candidate) {\n          if(path\
    \ == A[p].second) {\n            ok = false;\n            break;\n          }\n\
    \        }\n        if(ok) B.emplace(dist2[t], path);\n      }\n      vector<\
    \ int > accept;\n      for(auto &k : candidate) {\n        if(j < A[k].second.size()\
    \ && A[k].second[j] == last_path[j]) {\n          accept.emplace_back(k);\n  \
    \      }\n      }\n      dist[malta[last_path[j]]] = dist[latte[last_path[j]]]\
    \ + cost[last_path[j]];\n      from[malta[last_path[j]]] = latte[last_path[j]];\n\
    \      id[malta[last_path[j]]] = last_path[j];\n      cur = malta[last_path[j]];\n\
    \      candidate = move(accept);\n    }\n    if(B.size()) {\n      A.emplace_back(*B.begin());\n\
    \      B.erase(B.begin());\n    }\n  }\n  return A;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief K-Shortest-Path\n\
    \ * @docs docs/k-shortest-path.md\n * @see https://qiita.com/nariaki3551/items/821dc6ffdc552d3d5f22\n\
    \ */\ntemplate< typename T >\nvector< pair< T, vector< int > > > k_shortest_path(const\
    \ Graph< T > &g, int s, int t, int k) {\n  assert(s != t);\n  int N = (int) g.size();\n\
    \  int M = 0;\n  for(int i = 0; i < N; i++) M += (int) g[i].size();\n  vector<\
    \ int > latte(M), malta(M);\n  vector< T > cost(M);\n  for(int i = 0; i < N; i++)\
    \ {\n    for(auto &e : g[i]) {\n      latte[e.idx] = i;\n      malta[e.idx] =\
    \ e.to;\n      cost[e.idx] = e.cost;\n    }\n  }\n  const auto INF = numeric_limits<\
    \ T >::max();\n  vector< int > dame(M, -1);\n  int timestamp = 0;\n  auto shortest_path\
    \ = [&](vector< T > &dist, vector< int > &from, vector< int > &id, int st) {\n\
    \    using Pi = pair< T, int >;\n    priority_queue< Pi, vector< Pi >, greater<>\
    \ > que;\n    que.emplace(dist[st], st);\n    while(!que.empty()) {\n      T cost;\n\
    \      int idx;\n      tie(cost, idx) = que.top();\n      que.pop();\n      if(dist[idx]\
    \ < cost) continue;\n      if(idx == t) return;\n      for(auto &e : g[idx]) {\n\
    \        auto next_cost = cost + e.cost;\n        if(dist[e.to] <= next_cost)\
    \ continue;\n        if(dame[e.idx] == timestamp) continue;\n        dist[e.to]\
    \ = next_cost;\n        from[e.to] = idx;\n        id[e.to] = e.idx;\n       \
    \ que.emplace(dist[e.to], e.to);\n      }\n    }\n  };\n  auto restore = [](const\
    \ vector< int > &es, const vector< int > &vs, int from, int to) {\n    vector<\
    \ int > tap;\n    while(to != from) {\n      tap.emplace_back(es[to]);\n     \
    \ to = vs[to];\n    }\n    reverse(begin(tap), end(tap));\n    return tap;\n \
    \ };\n\n  vector< T > dist(g.size(), INF);\n  vector< int > from(g.size(), -1),\
    \ id(g.size(), -1);\n  dist[s] = 0;\n  shortest_path(dist, from, id, s);\n  if(dist[t]\
    \ == INF) return {};\n\n  vector< pair< T, vector< int > > > A;\n  set< pair<\
    \ T, vector< int > > > B;\n  A.emplace_back(dist[t], restore(id, from, s, t));\n\
    \n  for(int i = 1; i < k; i++) {\n    dist.assign(g.size(), INF);\n    from.assign(g.size(),\
    \ -1);\n    id.assign(g.size(), -1);\n    dist[s] = 0;\n    vector< int > candidate(A.size());\n\
    \    iota(begin(candidate), end(candidate), 0);\n    auto &last_path = A.back().second;\n\
    \    int cur = s;\n    for(int j = 0; j < last_path.size(); j++) {\n      for(auto\
    \ &k : candidate) {\n        if(j < A[k].second.size()) dame[A[k].second[j]] =\
    \ timestamp;\n      }\n      vector< T > dist2{dist};\n      vector< int > from2{from},\
    \ id2{id};\n      shortest_path(dist2, from2, id2, cur);\n      ++timestamp;\n\
    \      if(dist2[t] != INF) {\n        auto path = restore(id2, from2, s, t);\n\
    \        bool ok = true;\n        for(auto &p : candidate) {\n          if(path\
    \ == A[p].second) {\n            ok = false;\n            break;\n          }\n\
    \        }\n        if(ok) B.emplace(dist2[t], path);\n      }\n      vector<\
    \ int > accept;\n      for(auto &k : candidate) {\n        if(j < A[k].second.size()\
    \ && A[k].second[j] == last_path[j]) {\n          accept.emplace_back(k);\n  \
    \      }\n      }\n      dist[malta[last_path[j]]] = dist[latte[last_path[j]]]\
    \ + cost[last_path[j]];\n      from[malta[last_path[j]]] = latte[last_path[j]];\n\
    \      id[malta[last_path[j]]] = last_path[j];\n      cur = malta[last_path[j]];\n\
    \      candidate = move(accept);\n    }\n    if(B.size()) {\n      A.emplace_back(*B.begin());\n\
    \      B.erase(B.begin());\n    }\n  }\n  return A;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/k-shortest-path.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1069.test.cpp
documentation_of: graph/shortest-path/k-shortest-path.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/k-shortest-path.hpp
- /library/graph/shortest-path/k-shortest-path.hpp.html
title: K-Shortest-Path
---
## 概要

頂点 $s$ から $t$ へのパス(Path) のうち, 昇順 $k$ 個のパスの長さを Yen's Algorithm により求める. 

パス(Path, 道) は同じ頂点を通らない経路である.

verify が甘いため合っているかかなり不安です

* `k_shotest_path(g, s, t, k)`: 重み付き有向グラフ `g` の頂点 `s` から `t` へのパスのうち, 昇順 `k` 個のパスの長さとそのパスの辺番号の列を返す(パスの個数が `k` 個に満たないとき全てを返す).

## 計算量

* $O(KV ((E + v) \log V))$
