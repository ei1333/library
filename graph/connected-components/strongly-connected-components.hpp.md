---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy:
  - icon: ':x:'
    path: graph/others/two-satisfiability.hpp
    title: Two Satisfiability(2-SAT)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-3-c.test.cpp
    title: test/verify/aoj-grl-3-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-scc.test.cpp
    title: test/verify/yosupo-scc.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-two-sat.test.cpp
    title: test/verify/yosupo-two-sat.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/connected-components/strongly-connected-components.hpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/connected-components/strongly-connected-components.hpp\"\
    \n\ntemplate< typename T = int >\nstruct StronglyConnectedComponents : Graph<\
    \ T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > comp;\n  Graph< T > dag;\n  vector< vector< int > > group;\n\n  void build()\
    \ {\n    rg = Graph< T >(g.size());\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      for(auto &e : g[i]) {\n        rg.add_directed_edge(e.to, e.from, e.cost);\n\
    \      }\n    }\n    comp.assign(g.size(), -1);\n    used.assign(g.size(), 0);\n\
    \    for(size_t i = 0; i < g.size(); i++) dfs(i);\n    reverse(begin(order), end(order));\n\
    \    int ptr = 0;\n    for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;\n\
    \    dag = Graph< T >(ptr);\n    for(size_t i = 0; i < g.size(); i++) {\n    \
    \  for(auto &e : g[i]) {\n        int x = comp[e.from], y = comp[e.to];\n    \
    \    if(x == y) continue;\n        dag.add_directed_edge(x, y, e.cost);\n    \
    \  }\n    }\n    group.resize(ptr);\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      group[comp[i]].emplace_back(i);\n    }\n  }\n\n  int operator[](int\
    \ k) const {\n    return comp[k];\n  }\n\nprivate:\n  vector< int > order, used;\n\
    \  Graph< T > rg;\n\n  void dfs(int idx) {\n    if(exchange(used[idx], true))\
    \ return;\n    for(auto &to : g[idx]) dfs(to);\n    order.push_back(idx);\n  }\n\
    \n  void rdfs(int idx, int cnt) {\n    if(comp[idx] != -1) return;\n    comp[idx]\
    \ = cnt;\n    for(auto &to : rg.g[idx]) rdfs(to, cnt);\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\ntemplate< typename\
    \ T = int >\nstruct StronglyConnectedComponents : Graph< T > {\npublic:\n  using\
    \ Graph< T >::Graph;\n  using Graph< T >::g;\n  vector< int > comp;\n  Graph<\
    \ T > dag;\n  vector< vector< int > > group;\n\n  void build() {\n    rg = Graph<\
    \ T >(g.size());\n    for(size_t i = 0; i < g.size(); i++) {\n      for(auto &e\
    \ : g[i]) {\n        rg.add_directed_edge(e.to, e.from, e.cost);\n      }\n  \
    \  }\n    comp.assign(g.size(), -1);\n    used.assign(g.size(), 0);\n    for(size_t\
    \ i = 0; i < g.size(); i++) dfs(i);\n    reverse(begin(order), end(order));\n\
    \    int ptr = 0;\n    for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;\n\
    \    dag = Graph< T >(ptr);\n    for(size_t i = 0; i < g.size(); i++) {\n    \
    \  for(auto &e : g[i]) {\n        int x = comp[e.from], y = comp[e.to];\n    \
    \    if(x == y) continue;\n        dag.add_directed_edge(x, y, e.cost);\n    \
    \  }\n    }\n    group.resize(ptr);\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      group[comp[i]].emplace_back(i);\n    }\n  }\n\n  int operator[](int\
    \ k) const {\n    return comp[k];\n  }\n\nprivate:\n  vector< int > order, used;\n\
    \  Graph< T > rg;\n\n  void dfs(int idx) {\n    if(exchange(used[idx], true))\
    \ return;\n    for(auto &to : g[idx]) dfs(to);\n    order.push_back(idx);\n  }\n\
    \n  void rdfs(int idx, int cnt) {\n    if(comp[idx] != -1) return;\n    comp[idx]\
    \ = cnt;\n    for(auto &to : rg.g[idx]) rdfs(to, cnt);\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/connected-components/strongly-connected-components.hpp
  requiredBy:
  - graph/others/two-satisfiability.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/aoj-grl-3-c.test.cpp
  - test/verify/yosupo-two-sat.test.cpp
  - test/verify/yosupo-scc.test.cpp
documentation_of: graph/connected-components/strongly-connected-components.hpp
layout: document
title: "Strongly Connected Components(\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3)"
---

## 概要

与えられた有向グラフを強連結成分分解する.

グラフの任意の $2$ 頂点間に有効路が存在するとき, 有向グラフが強連結であるとよぶ. 強連結成分は, 極大で強連結な部分グラフである.

適当な頂点からDFSをして, 帰りがけ順に頂点を列挙することを, 未訪問の頂点がある間繰り返す. 次に辺をすべて逆向きにしたグラフについて, 列挙した頂点の逆順にDFS する. $1$ 回の DFS で到達できた頂点が $1$ つの強連結成分となる.

強連結成分を縮約後の頂点とそれらを結ぶ辺からなるグラフはDAGになっている.

* `build()`: 強連結成分分解する. `dag` には縮約後の頂点と辺からなるDAGが格納される. `comp` には各頂点が属する強連結成分の頂点番号が格納される. `group` には各強連結成分について, それに属する頂点が格納される.

## 計算量

* $O(E + V)$
