---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree-isomorphism.hpp
    title: "Tree-Isomorphism(\u6728\u306E\u540C\u578B\u6027\u5224\u5B9A)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2821.test.cpp
    title: test/verify/aoj-2821.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/centroid.md
    document_title: "Centroid(\u6728\u306E\u91CD\u5FC3)"
    links: []
  bundledCode: "#line 2 \"graph/tree/centroid.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/centroid.hpp\"\
    \n\n/**\n * @brief Centroid(\u6728\u306E\u91CD\u5FC3)\n * @docs docs/centroid.md\n\
    \ */\ntemplate< typename T >\nvector< int > centroid(const Graph< T > &g) {\n\
    \  const int N = (int) g.size();\n\n  stack< pair< int, int > > st;\n  st.emplace(0,\
    \ -1);\n  vector< int > sz(N), par(N);\n  while(!st.empty()) {\n    auto p = st.top();\n\
    \    if(sz[p.first] == 0) {\n      sz[p.first] = 1;\n      for(auto &to : g[p.first])\
    \ if(to != p.second) st.emplace(to, p.first);\n    } else {\n      for(auto &to\
    \ : g[p.first]) if(to != p.second) sz[p.first] += sz[to];\n      par[p.first]\
    \ = p.second;\n      st.pop();\n    }\n  }\n\n  vector< int > ret;\n  int size\
    \ = N;\n  for(int i = 0; i < N; i++) {\n    int val = N - sz[i];\n    for(auto\
    \ &to : g[i]) if(to != par[i]) val = max(val, sz[to]);\n    if(val < size) size\
    \ = val, ret.clear();\n    if(val == size) ret.emplace_back(i);\n  }\n\n  return\
    \ ret;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Centroid(\u6728\
    \u306E\u91CD\u5FC3)\n * @docs docs/centroid.md\n */\ntemplate< typename T >\n\
    vector< int > centroid(const Graph< T > &g) {\n  const int N = (int) g.size();\n\
    \n  stack< pair< int, int > > st;\n  st.emplace(0, -1);\n  vector< int > sz(N),\
    \ par(N);\n  while(!st.empty()) {\n    auto p = st.top();\n    if(sz[p.first]\
    \ == 0) {\n      sz[p.first] = 1;\n      for(auto &to : g[p.first]) if(to != p.second)\
    \ st.emplace(to, p.first);\n    } else {\n      for(auto &to : g[p.first]) if(to\
    \ != p.second) sz[p.first] += sz[to];\n      par[p.first] = p.second;\n      st.pop();\n\
    \    }\n  }\n\n  vector< int > ret;\n  int size = N;\n  for(int i = 0; i < N;\
    \ i++) {\n    int val = N - sz[i];\n    for(auto &to : g[i]) if(to != par[i])\
    \ val = max(val, sz[to]);\n    if(val < size) size = val, ret.clear();\n    if(val\
    \ == size) ret.emplace_back(i);\n  }\n\n  return ret;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/centroid.hpp
  requiredBy:
  - graph/tree/tree-isomorphism.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-2821.test.cpp
documentation_of: graph/tree/centroid.hpp
layout: document
redirect_from:
- /library/graph/tree/centroid.hpp
- /library/graph/tree/centroid.hpp.html
title: "Centroid(\u6728\u306E\u91CD\u5FC3)"
---
## 概要

木の重心を求める.  その頂点を取り除いたときにできる部分木たちの頂点数がすべて半分以下になる頂点を木の重心と呼び, 重心は $1$ 個か $2$ 個存在する.

* `centroid(g)`: 木 `g` の重心となる頂点をすべて返す.

## 計算量

* $O(V)$
