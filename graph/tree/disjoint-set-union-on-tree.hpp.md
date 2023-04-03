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
    document_title: Disjoint-Set-Union-On-Tree
    links: []
  bundledCode: "#line 2 \"graph/tree/disjoint-set-union-on-tree.hpp\"\n\n#line 2 \"\
    graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\u30E9\u30D5\
    \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T = int >\nstruct\
    \ Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\n  Edge(int\
    \ from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx)\
    \ {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename T = int\
    \ >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n  Graph()\
    \ = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t size() const\
    \ {\n    return g.size();\n  }\n\n  void add_directed_edge(int from, int to, T\
    \ cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\n  void\
    \ add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from, to,\
    \ cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void read(int\
    \ M, int padding = -1, bool weighted = false, bool directed = false) {\n    for(int\
    \ i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n      a += padding;\n\
    \      b += padding;\n      T c = T(1);\n      if(weighted) cin >> c;\n      if(directed)\
    \ add_directed_edge(a, b, c);\n      else add_edge(a, b, c);\n    }\n  }\n\n \
    \ inline vector< Edge< T > > &operator[](const int &k) {\n    return g[k];\n \
    \ }\n\n  inline const vector< Edge< T > > &operator[](const int &k) const {\n\
    \    return g[k];\n  }\n};\n\ntemplate< typename T = int >\nusing Edges = vector<\
    \ Edge< T > >;\n#line 4 \"graph/tree/disjoint-set-union-on-tree.hpp\"\n\n/**\n\
    \ * @brief Disjoint-Set-Union-On-Tree\n */\ntemplate< typename T >\nstruct DisjointSetUnionOnTree\
    \ : Graph< T > {\n  using F = function< void(int) >;\n  using Graph< T >::g;\n\
    \  vector< int > heavy, sz, in, out, ord;\n  const F expand, shrink, query;\n\
    \ \n  explicit DisjointSetUnionOnTree(int n, F expand, F shrink, F query)\n  \
    \    : Graph< T >(n), expand(move(expand)), shrink(move(shrink)), query(move(query))\
    \ {}\n \nprivate:\n  queue< int > que;\n \n  int build_subtree(int idx) {\n  \
    \  in[idx] = ord.size();\n    ord.emplace_back(idx);\n    for(auto &to : g[idx])\
    \ {\n      int sub = build_subtree(to);\n      sz[idx] += sub;\n      if(heavy[idx]\
    \ == -1 || sz[heavy[idx]] < sub) {\n        heavy[idx] = to;\n      }\n    }\n\
    \    out[idx] = ord.size();\n    return sz[idx];\n  }\n \n  void dfs(int idx,\
    \ bool keep) {\n    for(auto &to : g[idx]) {\n      if(heavy[idx] == to) continue;\n\
    \      dfs(to, false);\n    }\n    if(heavy[idx] != -1) {\n      dfs(heavy[idx],\
    \ true);\n    }\n    for(auto &to : g[idx]) {\n      if(heavy[idx] == to) continue;\n\
    \      for(int p = in[to]; p < out[to]; p++) {\n        expand(ord[p]);\n    \
    \  }\n    }\n    expand(idx);\n    query(idx);\n    if(!keep) {\n      for(int\
    \ p = in[idx]; p < out[idx]; p++) shrink(ord[p]);\n    }\n  }\n \npublic:\n  void\
    \ build(int root = 0) {\n    g = convert_rooted_tree(*this, root).g;\n    sz.assign(g.size(),\
    \ 1);\n    heavy.assign(g.size(), -1);\n    in.resize(g.size());\n    out.resize(g.size());\n\
    \    build_subtree(root);\n    dfs(root, false);\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Disjoint-Set-Union-On-Tree\n\
    \ */\ntemplate< typename T >\nstruct DisjointSetUnionOnTree : Graph< T > {\n \
    \ using F = function< void(int) >;\n  using Graph< T >::g;\n  vector< int > heavy,\
    \ sz, in, out, ord;\n  const F expand, shrink, query;\n \n  explicit DisjointSetUnionOnTree(int\
    \ n, F expand, F shrink, F query)\n      : Graph< T >(n), expand(move(expand)),\
    \ shrink(move(shrink)), query(move(query)) {}\n \nprivate:\n  queue< int > que;\n\
    \ \n  int build_subtree(int idx) {\n    in[idx] = ord.size();\n    ord.emplace_back(idx);\n\
    \    for(auto &to : g[idx]) {\n      int sub = build_subtree(to);\n      sz[idx]\
    \ += sub;\n      if(heavy[idx] == -1 || sz[heavy[idx]] < sub) {\n        heavy[idx]\
    \ = to;\n      }\n    }\n    out[idx] = ord.size();\n    return sz[idx];\n  }\n\
    \ \n  void dfs(int idx, bool keep) {\n    for(auto &to : g[idx]) {\n      if(heavy[idx]\
    \ == to) continue;\n      dfs(to, false);\n    }\n    if(heavy[idx] != -1) {\n\
    \      dfs(heavy[idx], true);\n    }\n    for(auto &to : g[idx]) {\n      if(heavy[idx]\
    \ == to) continue;\n      for(int p = in[to]; p < out[to]; p++) {\n        expand(ord[p]);\n\
    \      }\n    }\n    expand(idx);\n    query(idx);\n    if(!keep) {\n      for(int\
    \ p = in[idx]; p < out[idx]; p++) shrink(ord[p]);\n    }\n  }\n \npublic:\n  void\
    \ build(int root = 0) {\n    g = convert_rooted_tree(*this, root).g;\n    sz.assign(g.size(),\
    \ 1);\n    heavy.assign(g.size(), -1);\n    in.resize(g.size());\n    out.resize(g.size());\n\
    \    build_subtree(root);\n    dfs(root, false);\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/disjoint-set-union-on-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/tree/disjoint-set-union-on-tree.hpp
layout: document
redirect_from:
- /library/graph/tree/disjoint-set-union-on-tree.hpp
- /library/graph/tree/disjoint-set-union-on-tree.hpp.html
title: Disjoint-Set-Union-On-Tree
---
