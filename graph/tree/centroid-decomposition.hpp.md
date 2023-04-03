---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-3139.test.cpp
    title: test/verify/aoj-3139.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
    title: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1002.test.cpp
    title: test/verify/yukicoder-1002.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Centroid-Decomosition(\u91CD\u5FC3\u5206\u89E3)"
    links: []
  bundledCode: "#line 2 \"graph/tree/centroid-decomposition.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/centroid-decomposition.hpp\"\
    \n\n/**\n * @brief Centroid-Decomosition(\u91CD\u5FC3\u5206\u89E3)\n */\ntemplate<\
    \ typename T >\nstruct CentroidDecomposition : Graph< T > {\npublic:\n  using\
    \ Graph< T >::Graph;\n  using Graph< T >::g;\n  Graph< int > tree;\n\n  int build(int\
    \ t = 0) {\n    sub.assign(g.size(), 0);\n    v.assign(g.size(), 0);\n    tree\
    \ = Graph< int >(g.size());\n    return build_dfs(0);\n  }\n\n  explicit CentroidDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  vector< int > sub;\n  vector<\
    \ int > v;\n\n  inline int build_dfs(int idx, int par) {\n    sub[idx] = 1;\n\
    \    for(auto &to : g[idx]) {\n      if(to == par || v[to]) continue;\n      sub[idx]\
    \ += build_dfs(to, idx);\n    }\n    return sub[idx];\n  }\n\n  inline int search_centroid(int\
    \ idx, int par, const int mid) {\n    for(auto &to : g[idx]) {\n      if(to ==\
    \ par || v[to]) continue;\n      if(sub[to] > mid) return search_centroid(to,\
    \ idx, mid);\n    }\n    return idx;\n  }\n\n  inline int build_dfs(int idx) {\n\
    \    int centroid = search_centroid(idx, -1, build_dfs(idx, -1) / 2);\n    v[centroid]\
    \ = true;\n    for(auto &to : g[centroid]) {\n      if(!v[to]) tree.add_directed_edge(centroid,\
    \ build_dfs(to));\n    }\n    v[centroid] = false;\n    return centroid;\n  }\n\
    };\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Centroid-Decomosition(\u91CD\
    \u5FC3\u5206\u89E3)\n */\ntemplate< typename T >\nstruct CentroidDecomposition\
    \ : Graph< T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n\
    \  Graph< int > tree;\n\n  int build(int t = 0) {\n    sub.assign(g.size(), 0);\n\
    \    v.assign(g.size(), 0);\n    tree = Graph< int >(g.size());\n    return build_dfs(0);\n\
    \  }\n\n  explicit CentroidDecomposition(const Graph< T > &g) : Graph< T >(g)\
    \ {}\n\nprivate:\n  vector< int > sub;\n  vector< int > v;\n\n  inline int build_dfs(int\
    \ idx, int par) {\n    sub[idx] = 1;\n    for(auto &to : g[idx]) {\n      if(to\
    \ == par || v[to]) continue;\n      sub[idx] += build_dfs(to, idx);\n    }\n \
    \   return sub[idx];\n  }\n\n  inline int search_centroid(int idx, int par, const\
    \ int mid) {\n    for(auto &to : g[idx]) {\n      if(to == par || v[to]) continue;\n\
    \      if(sub[to] > mid) return search_centroid(to, idx, mid);\n    }\n    return\
    \ idx;\n  }\n\n  inline int build_dfs(int idx) {\n    int centroid = search_centroid(idx,\
    \ -1, build_dfs(idx, -1) / 2);\n    v[centroid] = true;\n    for(auto &to : g[centroid])\
    \ {\n      if(!v[to]) tree.add_directed_edge(centroid, build_dfs(to));\n    }\n\
    \    v[centroid] = false;\n    return centroid;\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/centroid-decomposition.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1002.test.cpp
  - test/verify/aoj-3139.test.cpp
  - test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
documentation_of: graph/tree/centroid-decomposition.hpp
layout: document
redirect_from:
- /library/graph/tree/centroid-decomposition.hpp
- /library/graph/tree/centroid-decomposition.hpp.html
title: "Centroid-Decomosition(\u91CD\u5FC3\u5206\u89E3)"
---
