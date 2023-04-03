---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-manhattanmst.test.cpp
    title: test/verify/yosupo-manhattanmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Manhattan MST
    links: []
  bundledCode: "#line 2 \"graph/mst/manhattan-mst.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/mst/manhattan-mst.hpp\"\
    \n\n/**\n * @brief Manhattan MST\n */\ntemplate< typename T >\nEdges< T > manhattan_mst(vector<\
    \ T > xs, vector< T > ys) {\n  assert(xs.size() == ys.size());\n  Edges< T > ret;\n\
    \  int n = (int) xs.size();\n\n  vector< int > ord(n);\n  iota(ord.begin(), ord.end(),\
    \ 0);\n\n  for(int s = 0; s < 2; s++) {\n    for(int t = 0; t < 2; t++) {\n  \
    \    auto cmp = [&](int i, int j) -> bool {\n        return xs[i] + ys[i] < xs[j]\
    \ + ys[j];\n      };\n      sort(ord.begin(), ord.end(), cmp);\n\n      map< T,\
    \ int > idx;\n      for(int i:ord) {\n        for(auto it = idx.lower_bound(-ys[i]);\n\
    \            it != idx.end(); it = idx.erase(it)) {\n          int j = it->second;\n\
    \          if(xs[i] - xs[j] < ys[i] - ys[j]) break;\n          ret.emplace_back(i,\
    \ j, abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]));\n        }\n        idx[-ys[i]]\
    \ = i;\n      }\n      swap(xs, ys);\n    }\n    for(int i = 0; i < n; i++) xs[i]\
    \ *= -1;\n  }\n  return ret;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Manhattan\
    \ MST\n */\ntemplate< typename T >\nEdges< T > manhattan_mst(vector< T > xs, vector<\
    \ T > ys) {\n  assert(xs.size() == ys.size());\n  Edges< T > ret;\n  int n = (int)\
    \ xs.size();\n\n  vector< int > ord(n);\n  iota(ord.begin(), ord.end(), 0);\n\n\
    \  for(int s = 0; s < 2; s++) {\n    for(int t = 0; t < 2; t++) {\n      auto\
    \ cmp = [&](int i, int j) -> bool {\n        return xs[i] + ys[i] < xs[j] + ys[j];\n\
    \      };\n      sort(ord.begin(), ord.end(), cmp);\n\n      map< T, int > idx;\n\
    \      for(int i:ord) {\n        for(auto it = idx.lower_bound(-ys[i]);\n    \
    \        it != idx.end(); it = idx.erase(it)) {\n          int j = it->second;\n\
    \          if(xs[i] - xs[j] < ys[i] - ys[j]) break;\n          ret.emplace_back(i,\
    \ j, abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]));\n        }\n        idx[-ys[i]]\
    \ = i;\n      }\n      swap(xs, ys);\n    }\n    for(int i = 0; i < n; i++) xs[i]\
    \ *= -1;\n  }\n  return ret;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/mst/manhattan-mst.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-manhattanmst.test.cpp
documentation_of: graph/mst/manhattan-mst.hpp
layout: document
redirect_from:
- /library/graph/mst/manhattan-mst.hpp
- /library/graph/mst/manhattan-mst.hpp.html
title: Manhattan MST
---
