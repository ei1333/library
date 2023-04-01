---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/bi-connected-components.hpp
    title: "Bi Connected Components(\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\
      \u5206\u89E3)"
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':question:'
    path: graph/others/low-link.hpp
    title: "Low Link(\u6A4B/\u95A2\u7BC0\u70B9)"
  _extendedRequiredBy: []
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
    document_title: Block Cut Tree
    links:
    - https://ei1333.hateblo.jp/entry/2020/03/25/010057
  bundledCode: "#line 2 \"graph/others/block-cut-tree.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 2 \"graph/others/low-link.hpp\"\
    \n\n#line 4 \"graph/others/low-link.hpp\"\n\n/**\n * @brief Low Link(\u6A4B/\u95A2\
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
    \ }\n  }\n};\n#line 5 \"graph/others/block-cut-tree.hpp\"\n\n/**\n * @brief Block\
    \ Cut Tree\n * @see https://ei1333.hateblo.jp/entry/2020/03/25/010057\n */\ntemplate<\
    \ typename T = int >\nstruct BlockCutTree : BiConnectedComponents< T > {\npublic:\n\
    \  using BiConnectedComponents< T >::BiConnectedComponents;\n  using BiConnectedComponents<\
    \ T >::g;\n  using BiConnectedComponents< T >::articulation;\n  using BiConnectedComponents<\
    \ T >::bc;\n\n  vector< int > rev;\n  vector< vector< int > > group;\n  Graph<\
    \ T > tree;\n\n  explicit BlockCutTree(const Graph< T > &g) : Graph< T >(g) {}\n\
    \n  int operator[](const int &k) const {\n    return rev[k];\n  }\n\n  void build()\
    \ override {\n    BiConnectedComponents< T >::build();\n    rev.assign(g.size(),\
    \ -1);\n    int ptr = (int) bc.size();\n    for(auto &idx : articulation) {\n\
    \      rev[idx] = ptr++;\n    }\n    vector< int > last(ptr, -1);\n    tree =\
    \ Graph< T >(ptr);\n    for(int i = 0; i < (int) bc.size(); i++) {\n      for(auto\
    \ &e : bc[i]) {\n        for(auto &ver : {e.from, e.to}) {\n          if(rev[ver]\
    \ >= (int) bc.size()) {\n            if(exchange(last[rev[ver]], i) != i) {\n\
    \              tree.add_edge(rev[ver], i, e.cost);\n            }\n          }\
    \ else {\n            rev[ver] = i;\n          }\n        }\n      }\n    }\n\
    \    group.resize(ptr);\n    for(int i = 0; i < (int) g.size(); i++) {\n     \
    \ group[rev[i]].emplace_back(i);\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"../connected-components/bi-connected-components.hpp\"\
    \n\n/**\n * @brief Block Cut Tree\n * @see https://ei1333.hateblo.jp/entry/2020/03/25/010057\n\
    \ */\ntemplate< typename T = int >\nstruct BlockCutTree : BiConnectedComponents<\
    \ T > {\npublic:\n  using BiConnectedComponents< T >::BiConnectedComponents;\n\
    \  using BiConnectedComponents< T >::g;\n  using BiConnectedComponents< T >::articulation;\n\
    \  using BiConnectedComponents< T >::bc;\n\n  vector< int > rev;\n  vector< vector<\
    \ int > > group;\n  Graph< T > tree;\n\n  explicit BlockCutTree(const Graph< T\
    \ > &g) : Graph< T >(g) {}\n\n  int operator[](const int &k) const {\n    return\
    \ rev[k];\n  }\n\n  void build() override {\n    BiConnectedComponents< T >::build();\n\
    \    rev.assign(g.size(), -1);\n    int ptr = (int) bc.size();\n    for(auto &idx\
    \ : articulation) {\n      rev[idx] = ptr++;\n    }\n    vector< int > last(ptr,\
    \ -1);\n    tree = Graph< T >(ptr);\n    for(int i = 0; i < (int) bc.size(); i++)\
    \ {\n      for(auto &e : bc[i]) {\n        for(auto &ver : {e.from, e.to}) {\n\
    \          if(rev[ver] >= (int) bc.size()) {\n            if(exchange(last[rev[ver]],\
    \ i) != i) {\n              tree.add_edge(rev[ver], i, e.cost);\n            }\n\
    \          } else {\n            rev[ver] = i;\n          }\n        }\n     \
    \ }\n    }\n    group.resize(ptr);\n    for(int i = 0; i < (int) g.size(); i++)\
    \ {\n      group[rev[i]].emplace_back(i);\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/connected-components/bi-connected-components.hpp
  - graph/others/low-link.hpp
  isVerificationFile: false
  path: graph/others/block-cut-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-3022.test.cpp
  - test/verify/aoj-3139.test.cpp
documentation_of: graph/others/block-cut-tree.hpp
layout: document
redirect_from:
- /library/graph/others/block-cut-tree.hpp
- /library/graph/others/block-cut-tree.hpp.html
title: Block Cut Tree
---
