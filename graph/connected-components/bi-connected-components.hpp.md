---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':question:'
    path: graph/others/low-link.hpp
    title: "Low Link(\u6A4B/\u95A2\u7BC0\u70B9)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/others/block-cut-tree.hpp
    title: Block Cut Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-3022.test.cpp
    title: test/verify/aoj-3022.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-3139.test.cpp
    title: test/verify/aoj-3139.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
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
    #line 3 \"graph/connected-components/bi-connected-components.hpp\"\n\ntemplate<\
    \ typename T = int >\nstruct BiConnectedComponents : LowLink< T > {\npublic:\n\
    \  using LowLink< T >::LowLink;\n  using LowLink< T >::g;\n  using LowLink< T\
    \ >::ord;\n  using LowLink< T >::low;\n\n  vector< vector< Edge< T > > > bc;\n\
    \n  void build() override {\n    LowLink< T >::build();\n    used.assign(g.size(),\
    \ 0);\n    for(int i = 0; i < (int)used.size(); i++) {\n      if(!used[i]) dfs(i,\
    \ -1);\n    }\n  }\n\n  explicit BiConnectedComponents(const Graph< T > &g) :\
    \ Graph< T >(g) {}\n\nprivate:\n  vector< int > used;\n  vector< Edge< T > > tmp;\n\
    \n  void dfs(int idx, int par) {\n    used[idx] = true;\n    bool beet = false;\n\
    \    for(auto &to : g[idx]) {\n      if(to == par && !exchange(beet, true)) continue;\n\
    \      if(!used[to] || ord[to] < ord[idx]) {\n        tmp.emplace_back(to);\n\
    \      }\n      if(!used[to]) {\n        dfs(to, idx);\n        if(low[to] >=\
    \ ord[idx]) {\n          bc.emplace_back();\n          for(;;) {\n           \
    \ auto e = tmp.back();\n            bc.back().emplace_back(e);\n            tmp.pop_back();\n\
    \            if(e.idx == to.idx) break;\n          }\n        }\n      }\n   \
    \ }\n  }\n};\n"
  code: "#include \"../graph-template.hpp\"\n#include \"../others/low-link.hpp\"\n\
    \ntemplate< typename T = int >\nstruct BiConnectedComponents : LowLink< T > {\n\
    public:\n  using LowLink< T >::LowLink;\n  using LowLink< T >::g;\n  using LowLink<\
    \ T >::ord;\n  using LowLink< T >::low;\n\n  vector< vector< Edge< T > > > bc;\n\
    \n  void build() override {\n    LowLink< T >::build();\n    used.assign(g.size(),\
    \ 0);\n    for(int i = 0; i < (int)used.size(); i++) {\n      if(!used[i]) dfs(i,\
    \ -1);\n    }\n  }\n\n  explicit BiConnectedComponents(const Graph< T > &g) :\
    \ Graph< T >(g) {}\n\nprivate:\n  vector< int > used;\n  vector< Edge< T > > tmp;\n\
    \n  void dfs(int idx, int par) {\n    used[idx] = true;\n    bool beet = false;\n\
    \    for(auto &to : g[idx]) {\n      if(to == par && !exchange(beet, true)) continue;\n\
    \      if(!used[to] || ord[to] < ord[idx]) {\n        tmp.emplace_back(to);\n\
    \      }\n      if(!used[to]) {\n        dfs(to, idx);\n        if(low[to] >=\
    \ ord[idx]) {\n          bc.emplace_back();\n          for(;;) {\n           \
    \ auto e = tmp.back();\n            bc.back().emplace_back(e);\n            tmp.pop_back();\n\
    \            if(e.idx == to.idx) break;\n          }\n        }\n      }\n   \
    \ }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/others/low-link.hpp
  isVerificationFile: false
  path: graph/connected-components/bi-connected-components.hpp
  requiredBy:
  - graph/others/block-cut-tree.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-3022.test.cpp
  - test/verify/aoj-3139.test.cpp
documentation_of: graph/connected-components/bi-connected-components.hpp
layout: document
title: "Bi Connected Components(\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\
  \u89E3)"
---

## 概要

二重連結成分分解とも. 二重頂点連結成分とは, $1$ 個の頂点を取り除いても連結である部分グラフである. 

関節点は, その頂点とそれを端点とする辺を削除したときの部分グラフが非連結になるような頂点を指す. したがって, 関節点を列挙した後に頑張ると列挙できる.


* `build()`: 二重頂点連結成分分解する. `bc` には各二重頂点連結成分に属する辺が格納される.

## 計算量

* $O(E + V)$
