---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1254.test.cpp
    title: test/verify/yukicoder-1254.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/namori-graph.md
    document_title: Namori Graph
    links: []
  bundledCode: "#line 2 \"graph/others/namori-graph.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/others/namori-graph.hpp\"\
    \n\n/**\n * @brief Namori Graph\n * @docs docs/namori-graph.md\n */\ntemplate<\
    \ typename T = int >\nstruct NamoriGraph : Graph< T > {\npublic:\n  using Graph<\
    \ T >::Graph;\n  using Graph< T >::g;\n\n  vector< Graph< T > > forest;\n  Edges<\
    \ T > loop_edges;\n\n  struct Info {\n    int tree_id, id;\n  };\n\n  Info operator[](const\
    \ int &k) const {\n    return (Info) {mark_id[k], id[k]};\n  }\n\n  int inv(int\
    \ tree_id, int k) {\n    return iv[tree_id][k];\n  }\n\n  void build() {\n   \
    \ int n = (int) g.size();\n    vector< int > deg(n), used(n);\n    queue< int\
    \ > que;\n    for(int i = 0; i < n; i++) {\n      deg[i] = (int) g[i].size();\n\
    \      if(deg[i] == 1) {\n        que.emplace(i);\n        used[i] = true;\n \
    \     }\n    }\n    while(not que.empty()) {\n      int idx = que.front();\n \
    \     que.pop();\n      for(auto &e : g[idx]) {\n        if(used[e.to]) {\n  \
    \        continue;\n        }\n        --deg[e.to];\n        if(deg[e.to] == 1)\
    \ {\n          que.emplace(e.to);\n          used[e.to] = true;\n        }\n \
    \     }\n    }\n    int mx = 0;\n    for(auto &edges : g) {\n      for(auto &e\
    \ : edges) mx = max(mx, e.idx);\n    }\n    vector< int > edge_used(mx + 1);\n\
    \    vector< int > loop;\n    for(int v = 0; v < n; v++) {\n      if(!used[v])\
    \ {\n        for(bool update = true; update;) {\n          update = false;\n \
    \         loop.emplace_back(v);\n          for(auto &e : g[v]) {\n           \
    \ if(used[e.to] or edge_used[e.idx]) {\n              continue;\n            }\n\
    \            edge_used[e.idx] = true;\n            loop_edges.emplace_back(v,\
    \ e.to, e.cost, e.idx);\n            v = e.to;\n            update = true;\n \
    \           break;\n          }\n        }\n        break;\n      }\n    }\n \
    \   loop.pop_back();\n    mark_id.resize(n);\n    id.resize(n);\n    for(int i\
    \ = 0; i < (int) loop.size(); i++) {\n      int pre = loop[(i + loop.size() -\
    \ 1) % loop.size()];\n      int nxt = loop[(i + 1) % loop.size()];\n      int\
    \ sz = 0;\n      mark_id[loop[i]] = i;\n      iv.emplace_back();\n      id[loop[i]]\
    \ = sz++;\n      iv.back().emplace_back(loop[i]);\n      for(auto &e : g[loop[i]])\
    \ {\n        if(e.to != pre and e.to != nxt) {\n          mark_dfs(e.to, loop[i],\
    \ i, sz);\n        }\n      }\n      Graph< T > tree(sz);\n      for(auto &e :\
    \ g[loop[i]]) {\n        if(e.to != pre and e.to != nxt) {\n          tree.g[id[loop[i]]].emplace_back(id[loop[i]],\
    \ id[e.to], e.cost, e.idx);\n          tree.g[id[e.to]].emplace_back(id[e.to],\
    \ id[loop[i]], e.cost, e.idx);\n          build_dfs(e.to, loop[i], tree);\n  \
    \      }\n      }\n      forest.emplace_back(tree);\n    }\n  }\n\nprivate:\n\
    \  vector< vector< int > > iv;\n  vector< int > mark_id, id;\n\n  void mark_dfs(int\
    \ idx, int par, int k, int &l) {\n    mark_id[idx] = k;\n    id[idx] = l++;\n\
    \    iv.back().emplace_back(idx);\n    for(auto &e : g[idx]) {\n      if(e.to\
    \ != par) {\n        mark_dfs(e.to, idx, k, l);\n      }\n    }\n  }\n\n  void\
    \ build_dfs(int idx, int par, Graph< T > &tree) {\n    for(auto &e : g[idx]) {\n\
    \      if(e.to != par) {\n        tree.g[id[idx]].emplace_back(id[idx], id[e.to],\
    \ e.cost, e.idx);\n        tree.g[id[e.to]].emplace_back(id[e.to], id[idx], e.cost,\
    \ e.idx);\n        build_dfs(e.to, idx, tree);\n      }\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Namori\
    \ Graph\n * @docs docs/namori-graph.md\n */\ntemplate< typename T = int >\nstruct\
    \ NamoriGraph : Graph< T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph<\
    \ T >::g;\n\n  vector< Graph< T > > forest;\n  Edges< T > loop_edges;\n\n  struct\
    \ Info {\n    int tree_id, id;\n  };\n\n  Info operator[](const int &k) const\
    \ {\n    return (Info) {mark_id[k], id[k]};\n  }\n\n  int inv(int tree_id, int\
    \ k) {\n    return iv[tree_id][k];\n  }\n\n  void build() {\n    int n = (int)\
    \ g.size();\n    vector< int > deg(n), used(n);\n    queue< int > que;\n    for(int\
    \ i = 0; i < n; i++) {\n      deg[i] = (int) g[i].size();\n      if(deg[i] ==\
    \ 1) {\n        que.emplace(i);\n        used[i] = true;\n      }\n    }\n   \
    \ while(not que.empty()) {\n      int idx = que.front();\n      que.pop();\n \
    \     for(auto &e : g[idx]) {\n        if(used[e.to]) {\n          continue;\n\
    \        }\n        --deg[e.to];\n        if(deg[e.to] == 1) {\n          que.emplace(e.to);\n\
    \          used[e.to] = true;\n        }\n      }\n    }\n    int mx = 0;\n  \
    \  for(auto &edges : g) {\n      for(auto &e : edges) mx = max(mx, e.idx);\n \
    \   }\n    vector< int > edge_used(mx + 1);\n    vector< int > loop;\n    for(int\
    \ v = 0; v < n; v++) {\n      if(!used[v]) {\n        for(bool update = true;\
    \ update;) {\n          update = false;\n          loop.emplace_back(v);\n   \
    \       for(auto &e : g[v]) {\n            if(used[e.to] or edge_used[e.idx])\
    \ {\n              continue;\n            }\n            edge_used[e.idx] = true;\n\
    \            loop_edges.emplace_back(v, e.to, e.cost, e.idx);\n            v =\
    \ e.to;\n            update = true;\n            break;\n          }\n       \
    \ }\n        break;\n      }\n    }\n    loop.pop_back();\n    mark_id.resize(n);\n\
    \    id.resize(n);\n    for(int i = 0; i < (int) loop.size(); i++) {\n      int\
    \ pre = loop[(i + loop.size() - 1) % loop.size()];\n      int nxt = loop[(i +\
    \ 1) % loop.size()];\n      int sz = 0;\n      mark_id[loop[i]] = i;\n      iv.emplace_back();\n\
    \      id[loop[i]] = sz++;\n      iv.back().emplace_back(loop[i]);\n      for(auto\
    \ &e : g[loop[i]]) {\n        if(e.to != pre and e.to != nxt) {\n          mark_dfs(e.to,\
    \ loop[i], i, sz);\n        }\n      }\n      Graph< T > tree(sz);\n      for(auto\
    \ &e : g[loop[i]]) {\n        if(e.to != pre and e.to != nxt) {\n          tree.g[id[loop[i]]].emplace_back(id[loop[i]],\
    \ id[e.to], e.cost, e.idx);\n          tree.g[id[e.to]].emplace_back(id[e.to],\
    \ id[loop[i]], e.cost, e.idx);\n          build_dfs(e.to, loop[i], tree);\n  \
    \      }\n      }\n      forest.emplace_back(tree);\n    }\n  }\n\nprivate:\n\
    \  vector< vector< int > > iv;\n  vector< int > mark_id, id;\n\n  void mark_dfs(int\
    \ idx, int par, int k, int &l) {\n    mark_id[idx] = k;\n    id[idx] = l++;\n\
    \    iv.back().emplace_back(idx);\n    for(auto &e : g[idx]) {\n      if(e.to\
    \ != par) {\n        mark_dfs(e.to, idx, k, l);\n      }\n    }\n  }\n\n  void\
    \ build_dfs(int idx, int par, Graph< T > &tree) {\n    for(auto &e : g[idx]) {\n\
    \      if(e.to != par) {\n        tree.g[id[idx]].emplace_back(id[idx], id[e.to],\
    \ e.cost, e.idx);\n        tree.g[id[e.to]].emplace_back(id[e.to], id[idx], e.cost,\
    \ e.idx);\n        build_dfs(e.to, idx, tree);\n      }\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/others/namori-graph.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1254.test.cpp
documentation_of: graph/others/namori-graph.hpp
layout: document
redirect_from:
- /library/graph/others/namori-graph.hpp
- /library/graph/others/namori-graph.hpp.html
title: Namori Graph
---
## 概要

$n$ 頂点 $n$ 辺からなる連結無向グラフは, サイクルが $1$ 個だけあるグラフとなる。

このグラフを, とある漫画家のアイコンにちなんで なもりグラフ と呼ばれることがるが, 学術的には Unicyclic Graph, Pseudoforest が正しい。

ここでは, このグラフを 1 つのサイクル と, サイクル内の頂点に付属する木に分解する。またサイクルに含まれる頂点番号を, サイクルの頂点数を $k$ として $[0, k)$ にふりなおし, これを `tree_id` と呼ぶことにする。

また付属する木も同様に, 木の頂点数を $l$ として $[0, l)$ にふりなおす。


## 使い方

* `build()`: サイクルと木に分解する。頂点数と辺の本数が同じ無向連結グラフである必要がある。
* `forest`: 分解した無向木が `tree_id` の昇順に格納される。木の頂点番号は$0$ から振り直している。辺の `from`, `to` は振り直し後の頂点番号, `cost`,`idx` はもとのグラフの辺の値をコピーする。
* `loop_edges`: サイクルに含まれる辺が順に格納される。$i$ 番目の辺は `tree_id` $i$ と $i+1$ を結ぶ辺である。辺の `from`, `to`, `cost`, `idx` はもとのグラフの辺の値をコピーする。
* `operator[k]`: 頂点 $k$ について, サイクルの `tree_id`, 振り直された木の頂点番号 `id` を返す。
* `inv(tree_id, k)`: サイクルの `tree_id` に付属する頂点 $k$ のもとの頂点番号を返す。特に `inv(tree_id, 0)` はサイクルに含まれていたもとの頂点番号を指す。

## 計算量

* $O(N)$
