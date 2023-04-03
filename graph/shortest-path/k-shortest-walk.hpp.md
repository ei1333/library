---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-k-shortest-walk.test.cpp
    title: test/verify/yosupo-k-shortest-walk.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/k-shortest-walk.md
    document_title: K-Shortest-Walk
    links:
    - https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e
  bundledCode: "#line 2 \"graph/shortest-path/k-shortest-walk.hpp\"\n\n#line 2 \"\
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
    \ Edge< T > >;\n#line 4 \"graph/shortest-path/k-shortest-walk.hpp\"\n\n/**\n *\
    \ @brief K-Shortest-Walk\n * @docs docs/k-shortest-walk.md\n * @see https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e\n\
    \ */\ntemplate< typename T >\nvector< T > k_shortest_walk(const Graph< T > &g,\
    \ int s, int t, int k) {\n  int N = (int) g.size();\n  Graph< T > rg(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    for(auto &e : g[i]) rg.add_directed_edge(e.to, i,\
    \ e.cost);\n  }\n  auto dist = dijkstra(rg, t);\n  if(dist.from[s] == -1) return\
    \ {};\n  auto &p = dist.dist;\n  vector< vector< int > > ch(N);\n  for(int i =\
    \ 0; i < N; i++) {\n    if(dist.from[i] >= 0) ch[dist.from[i]].emplace_back(i);\n\
    \  }\n  using PHeap = PersistentLeftistHeap< T >;\n  using Node = typename PHeap::Node;\n\
    \  PHeap heap;\n  vector< Node * > h(N, heap.make_root());\n  {\n    queue< int\
    \ > que;\n    que.emplace(t);\n    while(!que.empty()) {\n      int idx = que.front();\n\
    \      que.pop();\n      if(dist.from[idx] >= 0) {\n        h[idx] = heap.meld(h[idx],\
    \ h[dist.from[idx]]);\n      }\n      bool used = true;\n      for(auto &e : g[idx])\
    \ {\n        if(e.to != t && dist.from[e.to] == -1) continue;\n        if(used\
    \ && dist.from[idx] == e.to && p[e.to] + e.cost == p[idx]) {\n          used =\
    \ false;\n          continue;\n        }\n        h[idx] = heap.push(h[idx], e.cost\
    \ - p[idx] + p[e.to], e.to);\n      }\n      for(auto &to : ch[idx]) que.emplace(to);\n\
    \    }\n  }\n  using pi = pair< T, Node * >;\n  auto comp = [](const pi &x, const\
    \ pi &y) { return x.first > y.first; };\n  priority_queue< pi, vector< pi >, decltype(comp)\
    \ > que(comp);\n  Node *root = heap.make_root();\n  root = heap.push(root, p[s],\
    \ s);\n  que.emplace(p[s], root);\n  vector< T > ans;\n  while(!que.empty()) {\n\
    \    T cost;\n    Node *cur;\n    tie(cost, cur) = que.top();\n    que.pop();\n\
    \    ans.emplace_back(cost);\n    if((int)ans.size() == k) break;\n    if(cur->l)\
    \ que.emplace(cost + cur->l->key - cur->key, cur->l);\n    if(cur->r) que.emplace(cost\
    \ + cur->r->key - cur->key, cur->r);\n    if(h[cur->idx]) que.emplace(cost + h[cur->idx]->key,\
    \ h[cur->idx]);\n  }\n  return ans;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief K-Shortest-Walk\n\
    \ * @docs docs/k-shortest-walk.md\n * @see https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e\n\
    \ */\ntemplate< typename T >\nvector< T > k_shortest_walk(const Graph< T > &g,\
    \ int s, int t, int k) {\n  int N = (int) g.size();\n  Graph< T > rg(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    for(auto &e : g[i]) rg.add_directed_edge(e.to, i,\
    \ e.cost);\n  }\n  auto dist = dijkstra(rg, t);\n  if(dist.from[s] == -1) return\
    \ {};\n  auto &p = dist.dist;\n  vector< vector< int > > ch(N);\n  for(int i =\
    \ 0; i < N; i++) {\n    if(dist.from[i] >= 0) ch[dist.from[i]].emplace_back(i);\n\
    \  }\n  using PHeap = PersistentLeftistHeap< T >;\n  using Node = typename PHeap::Node;\n\
    \  PHeap heap;\n  vector< Node * > h(N, heap.make_root());\n  {\n    queue< int\
    \ > que;\n    que.emplace(t);\n    while(!que.empty()) {\n      int idx = que.front();\n\
    \      que.pop();\n      if(dist.from[idx] >= 0) {\n        h[idx] = heap.meld(h[idx],\
    \ h[dist.from[idx]]);\n      }\n      bool used = true;\n      for(auto &e : g[idx])\
    \ {\n        if(e.to != t && dist.from[e.to] == -1) continue;\n        if(used\
    \ && dist.from[idx] == e.to && p[e.to] + e.cost == p[idx]) {\n          used =\
    \ false;\n          continue;\n        }\n        h[idx] = heap.push(h[idx], e.cost\
    \ - p[idx] + p[e.to], e.to);\n      }\n      for(auto &to : ch[idx]) que.emplace(to);\n\
    \    }\n  }\n  using pi = pair< T, Node * >;\n  auto comp = [](const pi &x, const\
    \ pi &y) { return x.first > y.first; };\n  priority_queue< pi, vector< pi >, decltype(comp)\
    \ > que(comp);\n  Node *root = heap.make_root();\n  root = heap.push(root, p[s],\
    \ s);\n  que.emplace(p[s], root);\n  vector< T > ans;\n  while(!que.empty()) {\n\
    \    T cost;\n    Node *cur;\n    tie(cost, cur) = que.top();\n    que.pop();\n\
    \    ans.emplace_back(cost);\n    if((int)ans.size() == k) break;\n    if(cur->l)\
    \ que.emplace(cost + cur->l->key - cur->key, cur->l);\n    if(cur->r) que.emplace(cost\
    \ + cur->r->key - cur->key, cur->r);\n    if(h[cur->idx]) que.emplace(cost + h[cur->idx]->key,\
    \ h[cur->idx]);\n  }\n  return ans;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/k-shortest-walk.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-k-shortest-walk.test.cpp
documentation_of: graph/shortest-path/k-shortest-walk.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/k-shortest-walk.hpp
- /library/graph/shortest-path/k-shortest-walk.hpp.html
title: K-Shortest-Walk
---
## 概要

頂点 $s$ から $t$ へのウォーク(Walk) のうち, 昇順 $k$ 個のウォークの長さを Eppstein's Algorithm により求める. 

ウォーク(Walk, 歩道, 経路) とは重複して頂点や辺が現れることを許容した頂点 $s$ から $t$ への経路を指す.

ちなみにトレイル(Trail) は同じ辺を通らない経路, 道(Path) は同じ頂点を通らない経路である.

* `k_shotest_walk(g, s, t, k)`: 重み付き有向グラフ `g` の頂点 `s` から `t` へのウォークのうち, 昇順 `k` 個のウォークの長さを返す(ウォークの個数が `k` 個に満たないとき全てを返す).

## 計算量

* $O((V + E) \log V + K \log K)$
