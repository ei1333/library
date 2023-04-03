---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2450.test.cpp
    title: test/verify/aoj-2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2667.test.cpp
    title: test/verify/aoj-2667.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c-2.test.cpp
    title: test/verify/aoj-grl-5-c-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-650.test.cpp
    title: test/verify/yukicoder-650.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Heavy-Light-Decomposition(HL\u5206\u89E3)"
    links:
    - https://smijake3.hatenablog.com/entry/2019/09/15/200200
  bundledCode: "#line 2 \"graph/tree/heavy-light-decomposition.hpp\"\n\n#line 2 \"\
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
    \ Edge< T > >;\n#line 4 \"graph/tree/heavy-light-decomposition.hpp\"\n\n/**\n\
    \ * @brief Heavy-Light-Decomposition(HL\u5206\u89E3)\n * @see https://smijake3.hatenablog.com/entry/2019/09/15/200200\n\
    \ */\ntemplate< typename T = int >\nstruct HeavyLightDecomposition : Graph< T\
    \ > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > sz, in, out, head, rev, par, dep;\n\n  void build() {\n    sz.assign(g.size(),\
    \ 0);\n    in.assign(g.size(), 0);\n    out.assign(g.size(), 0);\n    head.assign(g.size(),\
    \ 0);\n    rev.assign(g.size(), 0);\n    par.assign(g.size(), 0);\n    dep.assign(g.size(),\
    \ 0);\n    dfs_sz(0, -1, 0);\n    int t = 0;\n    dfs_hld(0, -1, t);\n  }\n\n\
    \  /* k: 0-indexed */\n  int la(int v, int k) {\n    while(1) {\n      int u =\
    \ head[v];\n      if(in[v] - k >= in[u]) return rev[in[v] - k];\n      k -= in[v]\
    \ - in[u] + 1;\n      v = par[u];\n    }\n  }\n\n  int lca(int u, int v) const\
    \ {\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v);\n   \
    \   if(head[u] == head[v]) return u;\n    }\n  }\n\n  int dist(int u, int v) const\
    \ {\n    return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n  }\n\n  template< typename\
    \ E, typename Q, typename F, typename S >\n  E query(int u, int v, const E &ti,\
    \ const Q &q, const F &f, const S &s, bool edge = false) {\n    E l = ti, r =\
    \ ti;\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v), swap(l,\
    \ r);\n      if(head[u] == head[v]) break;\n      l = f(q(in[head[v]], in[v] +\
    \ 1), l);\n    }\n    return s(f(q(in[u] + edge, in[v] + 1), l), r);\n  }\n\n\
    \  template< typename E, typename Q, typename F >\n  E query(int u, int v, const\
    \ E &ti, const Q &q, const F &f, bool edge = false) {\n    return query(u, v,\
    \ ti, q, f, f, edge);\n  }\n\n  template< typename Q >\n  void add(int u, int\
    \ v, const Q &q, bool edge = false) {\n    for(;; v = par[head[v]]) {\n      if(in[u]\
    \ > in[v]) swap(u, v);\n      if(head[u] == head[v]) break;\n      q(in[head[v]],\
    \ in[v] + 1);\n    }\n    q(in[u] + edge, in[v] + 1);\n  }\n\n  /* {parent, child}\
    \ */\n  vector< pair< int, int > > compress(vector< int > &remark) {\n    auto\
    \ cmp = [&](int a, int b) { return in[a] < in[b]; };\n    sort(begin(remark),\
    \ end(remark), cmp);\n    remark.erase(unique(begin(remark), end(remark)), end(remark));\n\
    \    int K = (int) remark.size();\n    for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k\
    \ - 1], remark[k]));\n    sort(begin(remark), end(remark), cmp);\n    remark.erase(unique(begin(remark),\
    \ end(remark)), end(remark));\n    vector< pair< int, int > > es;\n    stack<\
    \ int > st;\n    for(auto &k : remark) {\n      while(!st.empty() && out[st.top()]\
    \ <= in[k]) st.pop();\n      if(!st.empty()) es.emplace_back(st.top(), k);\n \
    \     st.emplace(k);\n    }\n    return es;\n  }\n\n  explicit HeavyLightDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  void dfs_sz(int idx, int p,\
    \ int d) {\n    dep[idx] = d;\n    par[idx] = p;\n    sz[idx] = 1;\n    if(g[idx].size()\
    \ && g[idx][0] == p) swap(g[idx][0], g[idx].back());\n    for(auto &to : g[idx])\
    \ {\n      if(to == p) continue;\n      dfs_sz(to, idx, d + 1);\n      sz[idx]\
    \ += sz[to];\n      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);\n    }\n \
    \ }\n\n  void dfs_hld(int idx, int p, int &times) {\n    in[idx] = times++;\n\
    \    rev[in[idx]] = idx;\n    for(auto &to : g[idx]) {\n      if(to == p) continue;\n\
    \      head[to] = (g[idx][0] == to ? head[idx] : to);\n      dfs_hld(to, idx,\
    \ times);\n    }\n    out[idx] = times;\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Heavy-Light-Decomposition(HL\u5206\
    \u89E3)\n * @see https://smijake3.hatenablog.com/entry/2019/09/15/200200\n */\n\
    template< typename T = int >\nstruct HeavyLightDecomposition : Graph< T > {\n\
    public:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector< int > sz,\
    \ in, out, head, rev, par, dep;\n\n  void build() {\n    sz.assign(g.size(), 0);\n\
    \    in.assign(g.size(), 0);\n    out.assign(g.size(), 0);\n    head.assign(g.size(),\
    \ 0);\n    rev.assign(g.size(), 0);\n    par.assign(g.size(), 0);\n    dep.assign(g.size(),\
    \ 0);\n    dfs_sz(0, -1, 0);\n    int t = 0;\n    dfs_hld(0, -1, t);\n  }\n\n\
    \  /* k: 0-indexed */\n  int la(int v, int k) {\n    while(1) {\n      int u =\
    \ head[v];\n      if(in[v] - k >= in[u]) return rev[in[v] - k];\n      k -= in[v]\
    \ - in[u] + 1;\n      v = par[u];\n    }\n  }\n\n  int lca(int u, int v) const\
    \ {\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v);\n   \
    \   if(head[u] == head[v]) return u;\n    }\n  }\n\n  int dist(int u, int v) const\
    \ {\n    return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n  }\n\n  template< typename\
    \ E, typename Q, typename F, typename S >\n  E query(int u, int v, const E &ti,\
    \ const Q &q, const F &f, const S &s, bool edge = false) {\n    E l = ti, r =\
    \ ti;\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v), swap(l,\
    \ r);\n      if(head[u] == head[v]) break;\n      l = f(q(in[head[v]], in[v] +\
    \ 1), l);\n    }\n    return s(f(q(in[u] + edge, in[v] + 1), l), r);\n  }\n\n\
    \  template< typename E, typename Q, typename F >\n  E query(int u, int v, const\
    \ E &ti, const Q &q, const F &f, bool edge = false) {\n    return query(u, v,\
    \ ti, q, f, f, edge);\n  }\n\n  template< typename Q >\n  void add(int u, int\
    \ v, const Q &q, bool edge = false) {\n    for(;; v = par[head[v]]) {\n      if(in[u]\
    \ > in[v]) swap(u, v);\n      if(head[u] == head[v]) break;\n      q(in[head[v]],\
    \ in[v] + 1);\n    }\n    q(in[u] + edge, in[v] + 1);\n  }\n\n  /* {parent, child}\
    \ */\n  vector< pair< int, int > > compress(vector< int > &remark) {\n    auto\
    \ cmp = [&](int a, int b) { return in[a] < in[b]; };\n    sort(begin(remark),\
    \ end(remark), cmp);\n    remark.erase(unique(begin(remark), end(remark)), end(remark));\n\
    \    int K = (int) remark.size();\n    for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k\
    \ - 1], remark[k]));\n    sort(begin(remark), end(remark), cmp);\n    remark.erase(unique(begin(remark),\
    \ end(remark)), end(remark));\n    vector< pair< int, int > > es;\n    stack<\
    \ int > st;\n    for(auto &k : remark) {\n      while(!st.empty() && out[st.top()]\
    \ <= in[k]) st.pop();\n      if(!st.empty()) es.emplace_back(st.top(), k);\n \
    \     st.emplace(k);\n    }\n    return es;\n  }\n\n  explicit HeavyLightDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  void dfs_sz(int idx, int p,\
    \ int d) {\n    dep[idx] = d;\n    par[idx] = p;\n    sz[idx] = 1;\n    if(g[idx].size()\
    \ && g[idx][0] == p) swap(g[idx][0], g[idx].back());\n    for(auto &to : g[idx])\
    \ {\n      if(to == p) continue;\n      dfs_sz(to, idx, d + 1);\n      sz[idx]\
    \ += sz[to];\n      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);\n    }\n \
    \ }\n\n  void dfs_hld(int idx, int p, int &times) {\n    in[idx] = times++;\n\
    \    rev[in[idx]] = idx;\n    for(auto &to : g[idx]) {\n      if(to == p) continue;\n\
    \      head[to] = (g[idx][0] == to ? head[idx] : to);\n      dfs_hld(to, idx,\
    \ times);\n    }\n    out[idx] = times;\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/tree/heavy-light-decomposition.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-5-c-2.test.cpp
  - test/verify/aoj-2667.test.cpp
  - test/verify/yukicoder-650.test.cpp
  - test/verify/aoj-2450.test.cpp
documentation_of: graph/tree/heavy-light-decomposition.hpp
layout: document
redirect_from:
- /library/graph/tree/heavy-light-decomposition.hpp
- /library/graph/tree/heavy-light-decomposition.hpp.html
title: "Heavy-Light-Decomposition(HL\u5206\u89E3)"
---
