---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/others/low-link.hpp
    title: "Low Link(\u6A4B/\u95A2\u7BC0\u70B9)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-two-edge-connected-components.test.cpp
    title: test/verify/yosupo-two-edge-connected-components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/connected-components/two-edge-connected-components.hpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"graph/others/low-link.hpp\"\n\n\
    #line 4 \"graph/others/low-link.hpp\"\n\n/**\n * @brief Low Link(\u6A4B/\u95A2\
    \u7BC0\u70B9)\n * @see http://kagamiz.hatenablog.com/entry/2013/10/05/005213\n\
    \ * @docs docs/low-link.md\n */\ntemplate< typename T = int >\nstruct LowLink\
    \ : Graph< T > {\npublic:\n  using Graph< T >::Graph;\n  vector< int > ord, low,\
    \ articulation;\n  vector< Edge< T > > bridge;\n  using Graph< T >::g;\n\n  virtual\
    \ void build() {\n    used.assign(g.size(), 0);\n    ord.assign(g.size(), 0);\n\
    \    low.assign(g.size(), 0);\n    int k = 0;\n    for(int i = 0; i < (int) g.size();\
    \ i++) {\n      if(!used[i]) k = dfs(i, k, -1);\n    }\n  }\n\n  explicit LowLink(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  vector< int > used;\n\n  int\
    \ dfs(int idx, int k, int par) {\n    used[idx] = true;\n    ord[idx] = k++;\n\
    \    low[idx] = ord[idx];\n    bool is_articulation = false, beet = false;\n \
    \   int cnt = 0;\n    for(auto &to : g[idx]) {\n      if(to == par && !exchange(beet,\
    \ true)) {\n        continue;\n      }\n      if(!used[to]) {\n        ++cnt;\n\
    \        k = dfs(to, k, idx);\n        low[idx] = min(low[idx], low[to]);\n  \
    \      is_articulation |= par >= 0 && low[to] >= ord[idx];\n        if(ord[idx]\
    \ < low[to]) bridge.emplace_back(to);\n      } else {\n        low[idx] = min(low[idx],\
    \ ord[to]);\n      }\n    }\n    is_articulation |= par == -1 && cnt > 1;\n  \
    \  if(is_articulation) articulation.push_back(idx);\n    return k;\n  }\n};\n\
    #line 5 \"graph/connected-components/two-edge-connected-components.hpp\"\n\ntemplate<\
    \ typename T = int >\nstruct TwoEdgeConnectedComponents : LowLink< T > {\npublic:\n\
    \  using LowLink< T >::LowLink;\n  using LowLink< T >::g;\n  using LowLink< T\
    \ >::ord;\n  using LowLink< T >::low;\n  using LowLink< T >::bridge;\n\n  vector<\
    \ int > comp;\n  Graph< T > tree;\n  vector< vector< int > > group;\n\n  int operator[](const\
    \ int &k) const {\n    return comp[k];\n  }\n\n  void build() override {\n   \
    \ LowLink< T >::build();\n    comp.assign(g.size(), -1);\n    int k = 0;\n   \
    \ for(int i = 0; i < (int) comp.size(); i++) {\n      if(comp[i] == -1) dfs(i,\
    \ -1, k);\n    }\n    group.resize(k);\n    for(int i = 0; i < (int) g.size();\
    \ i++) {\n      group[comp[i]].emplace_back(i);\n    }\n    tree = Graph< T >(k);\n\
    \    for(auto &e : bridge) {\n      tree.add_edge(comp[e.from], comp[e.to], e.cost);\n\
    \    }\n  }\n\n  explicit TwoEdgeConnectedComponents(const Graph< T > &g) : Graph<\
    \ T >(g) {}\n\nprivate:\n  void dfs(int idx, int par, int &k) {\n    if(par >=\
    \ 0 && ord[par] >= low[idx]) comp[idx] = comp[par];\n    else comp[idx] = k++;\n\
    \    for(auto &to : g[idx]) {\n      if(comp[to] == -1) dfs(to, idx, k);\n   \
    \ }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"../others/low-link.hpp\"\
    \n\ntemplate< typename T = int >\nstruct TwoEdgeConnectedComponents : LowLink<\
    \ T > {\npublic:\n  using LowLink< T >::LowLink;\n  using LowLink< T >::g;\n \
    \ using LowLink< T >::ord;\n  using LowLink< T >::low;\n  using LowLink< T >::bridge;\n\
    \n  vector< int > comp;\n  Graph< T > tree;\n  vector< vector< int > > group;\n\
    \n  int operator[](const int &k) const {\n    return comp[k];\n  }\n\n  void build()\
    \ override {\n    LowLink< T >::build();\n    comp.assign(g.size(), -1);\n   \
    \ int k = 0;\n    for(int i = 0; i < (int) comp.size(); i++) {\n      if(comp[i]\
    \ == -1) dfs(i, -1, k);\n    }\n    group.resize(k);\n    for(int i = 0; i < (int)\
    \ g.size(); i++) {\n      group[comp[i]].emplace_back(i);\n    }\n    tree = Graph<\
    \ T >(k);\n    for(auto &e : bridge) {\n      tree.add_edge(comp[e.from], comp[e.to],\
    \ e.cost);\n    }\n  }\n\n  explicit TwoEdgeConnectedComponents(const Graph< T\
    \ > &g) : Graph< T >(g) {}\n\nprivate:\n  void dfs(int idx, int par, int &k) {\n\
    \    if(par >= 0 && ord[par] >= low[idx]) comp[idx] = comp[par];\n    else comp[idx]\
    \ = k++;\n    for(auto &to : g[idx]) {\n      if(comp[to] == -1) dfs(to, idx,\
    \ k);\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/others/low-link.hpp
  isVerificationFile: false
  path: graph/connected-components/two-edge-connected-components.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-two-edge-connected-components.test.cpp
documentation_of: graph/connected-components/two-edge-connected-components.hpp
layout: document
title: "Two Edge Connected Components(\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u5206\
  \u89E3)"
---

## 概要

二辺連結成分分解とも. 二重辺連結成分とは, $1$ 本の辺を取り除いても連結である部分グラフである. つまり, 橋を含まない部分グラフなので, 橋を列挙することで二重辺連結成分を列挙できる.

二重辺連結成分で縮約後の頂点と橋からなるグラフは森になっている.


* `build()`: 二重辺連結成分分解する. `tree` には縮約後の頂点からなる森が格納される. `comp` には各頂点が属する二重辺連結成分の頂点番号が格納される. `group` には各二重辺連結成分について, それに属する頂点が格納される.

## 計算量

* $O(E + V)$
