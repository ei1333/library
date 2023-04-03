---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0294.test.cpp
    title: test/verify/aoj-0294.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dominatortree.test.cpp
    title: test/verify/yosupo-dominatortree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/dominator-tree.md
    document_title: Dominator Tree
    links:
    - http://sigma425.hatenablog.com/entry/2015/12/25/224053
  bundledCode: "#line 2 \"graph/others/dominator-tree.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/others/dominator-tree.hpp\"\
    \n\n/**\n * @brief Dominator Tree\n * @docs docs/dominator-tree.md\n * @see http://sigma425.hatenablog.com/entry/2015/12/25/224053\n\
    \ */\ntemplate< typename T = int >\nstruct DominatorTree : Graph< T > {\npublic:\n\
    \  using Graph< T >::Graph;\n  using Graph< T >::g;\n\n  void build(int root)\
    \ {\n    rg = Graph< T >(g.size());\n    par.assign(g.size(), 0);\n    idom.assign(g.size(),\
    \ -1);\n    semi.assign(g.size(), -1);\n    ord.reserve(g.size());\n    UnionFind\
    \ uf(semi);\n\n    const int N = (int) g.size();\n    dfs(root);\n    for(int\
    \ i = 0; i < N; i++) {\n      for(auto &to : g[i]) {\n        if(~semi[i]) rg.add_directed_edge(to,\
    \ i);\n      }\n    }\n\n    vector< vector< int > > bucket(N);\n    vector< int\
    \ > U(N);\n    for(int i = (int) ord.size() - 1; i >= 0; i--) {\n      int x =\
    \ ord[i];\n      for(int v : rg[x]) {\n        v = uf.eval(v);\n        if(semi[x]\
    \ > semi[v]) semi[x] = semi[v];\n      }\n      bucket[ord[semi[x]]].emplace_back(x);\n\
    \      for(int v : bucket[par[x]]) U[v] = uf.eval(v);\n      bucket[par[x]].clear();\n\
    \      uf.link(par[x], x);\n    }\n    for(int i = 1; i < (int)ord.size(); i++)\
    \ {\n      int x = ord[i], u = U[x];\n      idom[x] = semi[x] == semi[u] ? semi[x]\
    \ : idom[u];\n    }\n    for(int i = 1; i < (int)ord.size(); i++) {\n      int\
    \ x = ord[i];\n      idom[x] = ord[idom[x]];\n    }\n    idom[root] = root;\n\
    \  }\n\n  int operator[](const int &k) const {\n    return idom[k];\n  }\n\nprivate:\n\
    \  Graph< T > rg;\n\n  struct UnionFind {\n    const vector< int > &semi;\n  \
    \  vector< int > par, m;\n\n    explicit UnionFind(const vector< int > &semi)\
    \ : semi(semi), par(semi.size()), m(semi.size()) {\n      iota(begin(par), end(par),\
    \ 0);\n      iota(begin(m), end(m), 0);\n    }\n\n    int find(int v) {\n    \
    \  if(par[v] == v) return v;\n      int r = find(par[v]);\n      if(semi[m[v]]\
    \ > semi[m[par[v]]]) m[v] = m[par[v]];\n      return par[v] = r;\n    }\n\n  \
    \  int eval(int v) {\n      find(v);\n      return m[v];\n    }\n\n    void link(int\
    \ p, int c) {\n      par[c] = p;\n    }\n  };\n\n  vector< int > ord, par;\n \
    \ vector< int > idom, semi;\n\n  void dfs(int idx) {\n    semi[idx] = (int) ord.size();\n\
    \    ord.emplace_back(idx);\n    for(auto &to : g[idx]) {\n      if(~semi[to])\
    \ continue;\n      dfs(to);\n      par[to] = idx;\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Dominator\
    \ Tree\n * @docs docs/dominator-tree.md\n * @see http://sigma425.hatenablog.com/entry/2015/12/25/224053\n\
    \ */\ntemplate< typename T = int >\nstruct DominatorTree : Graph< T > {\npublic:\n\
    \  using Graph< T >::Graph;\n  using Graph< T >::g;\n\n  void build(int root)\
    \ {\n    rg = Graph< T >(g.size());\n    par.assign(g.size(), 0);\n    idom.assign(g.size(),\
    \ -1);\n    semi.assign(g.size(), -1);\n    ord.reserve(g.size());\n    UnionFind\
    \ uf(semi);\n\n    const int N = (int) g.size();\n    dfs(root);\n    for(int\
    \ i = 0; i < N; i++) {\n      for(auto &to : g[i]) {\n        if(~semi[i]) rg.add_directed_edge(to,\
    \ i);\n      }\n    }\n\n    vector< vector< int > > bucket(N);\n    vector< int\
    \ > U(N);\n    for(int i = (int) ord.size() - 1; i >= 0; i--) {\n      int x =\
    \ ord[i];\n      for(int v : rg[x]) {\n        v = uf.eval(v);\n        if(semi[x]\
    \ > semi[v]) semi[x] = semi[v];\n      }\n      bucket[ord[semi[x]]].emplace_back(x);\n\
    \      for(int v : bucket[par[x]]) U[v] = uf.eval(v);\n      bucket[par[x]].clear();\n\
    \      uf.link(par[x], x);\n    }\n    for(int i = 1; i < (int)ord.size(); i++)\
    \ {\n      int x = ord[i], u = U[x];\n      idom[x] = semi[x] == semi[u] ? semi[x]\
    \ : idom[u];\n    }\n    for(int i = 1; i < (int)ord.size(); i++) {\n      int\
    \ x = ord[i];\n      idom[x] = ord[idom[x]];\n    }\n    idom[root] = root;\n\
    \  }\n\n  int operator[](const int &k) const {\n    return idom[k];\n  }\n\nprivate:\n\
    \  Graph< T > rg;\n\n  struct UnionFind {\n    const vector< int > &semi;\n  \
    \  vector< int > par, m;\n\n    explicit UnionFind(const vector< int > &semi)\
    \ : semi(semi), par(semi.size()), m(semi.size()) {\n      iota(begin(par), end(par),\
    \ 0);\n      iota(begin(m), end(m), 0);\n    }\n\n    int find(int v) {\n    \
    \  if(par[v] == v) return v;\n      int r = find(par[v]);\n      if(semi[m[v]]\
    \ > semi[m[par[v]]]) m[v] = m[par[v]];\n      return par[v] = r;\n    }\n\n  \
    \  int eval(int v) {\n      find(v);\n      return m[v];\n    }\n\n    void link(int\
    \ p, int c) {\n      par[c] = p;\n    }\n  };\n\n  vector< int > ord, par;\n \
    \ vector< int > idom, semi;\n\n  void dfs(int idx) {\n    semi[idx] = (int) ord.size();\n\
    \    ord.emplace_back(idx);\n    for(auto &to : g[idx]) {\n      if(~semi[to])\
    \ continue;\n      dfs(to);\n      par[to] = idx;\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/others/dominator-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-dominatortree.test.cpp
  - test/verify/aoj-0294.test.cpp
documentation_of: graph/others/dominator-tree.hpp
layout: document
redirect_from:
- /library/graph/others/dominator-tree.hpp
- /library/graph/others/dominator-tree.hpp.html
title: Dominator Tree
---
## 概要

有向グラフが与えられたとき, 頂点 `root` を根とする Dominator tree を求める.

もとの有向グラフで, 頂点 `root` からある頂点 `i` へ向かうパスを考える. Dominator tree 上の頂点 `root` から `i` までのパス上にある頂点は, 頂点 `i` へ到達するために必ず通る必要のある頂点である(雰囲気的には関節点の有向グラフ版). 特に頂点 `i` の親は直接支配節 `idom(i)` と呼び, 必ず通る必要のある頂点のうち最も `w` に近い頂点を指す.

## 使い方

* `build(root)`: 頂点 `root` を根とする Dominator tree を返す. 各要素にはその要素の親の idx が格納される. ただし `root` には `root` が格納される. 頂点 `root` からその頂点に到達できない場合 `-1`.

## 計算量

$O(E \log V)$
