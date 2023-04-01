---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/bi-connected-components.hpp
    title: "Bi Connected Components(\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\
      \u5206\u89E3)"
  - icon: ':x:'
    path: graph/connected-components/two-edge-connected-components.hpp
    title: "Two Edge Connected Components(\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\
      \u5206\u89E3)"
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
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-3-a.test.cpp
    title: test/verify/aoj-grl-3-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-3-b.test.cpp
    title: test/verify/aoj-grl-3-b.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-two-edge-connected-components.test.cpp
    title: test/verify/yosupo-two-edge-connected-components.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/low-link.md
    document_title: "Low Link(\u6A4B/\u95A2\u7BC0\u70B9)"
    links:
    - http://kagamiz.hatenablog.com/entry/2013/10/05/005213
  bundledCode: "#line 2 \"graph/others/low-link.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/others/low-link.hpp\"\
    \n\n/**\n * @brief Low Link(\u6A4B/\u95A2\u7BC0\u70B9)\n * @see http://kagamiz.hatenablog.com/entry/2013/10/05/005213\n\
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
    \  if(is_articulation) articulation.push_back(idx);\n    return k;\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Low\
    \ Link(\u6A4B/\u95A2\u7BC0\u70B9)\n * @see http://kagamiz.hatenablog.com/entry/2013/10/05/005213\n\
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
    \  if(is_articulation) articulation.push_back(idx);\n    return k;\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/others/low-link.hpp
  requiredBy:
  - graph/connected-components/two-edge-connected-components.hpp
  - graph/connected-components/bi-connected-components.hpp
  - graph/others/block-cut-tree.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/aoj-3022.test.cpp
  - test/verify/yosupo-two-edge-connected-components.test.cpp
  - test/verify/aoj-3139.test.cpp
  - test/verify/aoj-grl-3-b.test.cpp
  - test/verify/aoj-grl-3-a.test.cpp
documentation_of: graph/others/low-link.hpp
layout: document
redirect_from:
- /library/graph/others/low-link.hpp
- /library/graph/others/low-link.hpp.html
title: "Low Link(\u6A4B/\u95A2\u7BC0\u70B9)"
---
## 概要
橋や関節点などを効率的に求める際に有効なアルゴリズム.

グラフをDFSして各頂点 `idx` について, `ord[idx]` := DFS で頂点に訪れた順番, `low[idx]` := 頂点 $idx$ からDFS木の葉方向の辺を $0$ 回以上, 後退辺を $1$ 回以下通って到達可能な頂点の `ord` の最小値 を求める.

ある頂点 $u$ が関節点であるとき, DFS木の根については子が $2$ つ以上, それ以外の頂点については 頂点 $u$ のある子 $v$ について `ord[u]` $\le$ `low[v]` を満たす.

ある辺 $(u, v)$ が橋であるとき, `ord[u]` $\lt$ `low[v]` を満たす.

## 使い方

* `build()`: LowLink を構築する. 構築後, `articulation` には関節点, `bridge` には橋が格納される. 非連結でも多重辺を含んでいてもOK.


## 計算量

$O(V + E)$
