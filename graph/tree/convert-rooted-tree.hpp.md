---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "Convert-Rooted-Tree(\u6839\u4ED8\u304D\u6728\u306B\u5909\u63DB\
      )"
    links: []
  bundledCode: "#line 2 \"graph/tree/convert-rooted-tree.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/convert-rooted-tree.hpp\"\
    \n\n/**\n * @brief Convert-Rooted-Tree(\u6839\u4ED8\u304D\u6728\u306B\u5909\u63DB\
    )\n */\ntemplate< typename T >\nGraph< T > convert_rooted_tree(const Graph< T\
    \ > &g, int r = 0) {\n  int N = (int) g.size();\n  Graph< T > rg(N);\n  vector<\
    \ int > v(N);\n  v[r] = 1;\n  queue< int > que;\n  que.emplace(r);\n  while(!que.empty())\
    \ {\n    auto p = que.front();\n    que.pop();\n    for(auto &to : g[p]) {\n \
    \     if(v[to] == 0) {\n        v[to] = 1;\n        que.emplace(to);\n       \
    \ rg.add_directed_edge(p, to, to.cost);\n      }\n    }\n  }\n  return rg;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Convert-Rooted-Tree(\u6839\
    \u4ED8\u304D\u6728\u306B\u5909\u63DB)\n */\ntemplate< typename T >\nGraph< T >\
    \ convert_rooted_tree(const Graph< T > &g, int r = 0) {\n  int N = (int) g.size();\n\
    \  Graph< T > rg(N);\n  vector< int > v(N);\n  v[r] = 1;\n  queue< int > que;\n\
    \  que.emplace(r);\n  while(!que.empty()) {\n    auto p = que.front();\n    que.pop();\n\
    \    for(auto &to : g[p]) {\n      if(v[to] == 0) {\n        v[to] = 1;\n    \
    \    que.emplace(to);\n        rg.add_directed_edge(p, to, to.cost);\n      }\n\
    \    }\n  }\n  return rg;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/convert-rooted-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/tree/convert-rooted-tree.hpp
layout: document
redirect_from:
- /library/graph/tree/convert-rooted-tree.hpp
- /library/graph/tree/convert-rooted-tree.hpp.html
title: "Convert-Rooted-Tree(\u6839\u4ED8\u304D\u6728\u306B\u5909\u63DB)"
---
