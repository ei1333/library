---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/others/topological-sort.hpp
    title: "Topological Sort(\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8\
      )"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0275.test.cpp
    title: test/verify/aoj-0275.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/offline-dag-reachability.md
    document_title: "Offline Dag Reachability(DAG\u306E\u5230\u9054\u53EF\u80FD\u6027\
      \u30AF\u30A8\u30EA)"
    links: []
  bundledCode: "#line 2 \"graph/others/offline-dag-reachability.hpp\"\n\n#line 2 \"\
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
    \ Edge< T > >;\n#line 2 \"graph/others/topological-sort.hpp\"\n\n#line 4 \"graph/others/topological-sort.hpp\"\
    \n\n/**\n * @brief Topological Sort(\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\
    \u30FC\u30C8)\n * @docs docs/topological-sort.md\n */\ntemplate< typename T >\n\
    vector< int > topological_sort(const Graph< T > &g) {\n  const int N = (int) g.size();\n\
    \  vector< int > deg(N);\n  for(int i = 0; i < N; i++) {\n    for(auto &to : g[i])\
    \ ++deg[to];\n  }\n  stack< int > st;\n  for(int i = 0; i < N; i++) {\n    if(deg[i]\
    \ == 0) st.emplace(i);\n  }\n  vector< int > ord;\n  while(!st.empty()) {\n  \
    \  auto p = st.top();\n    st.pop();\n    ord.emplace_back(p);\n    for(auto &to\
    \ : g[p]) {\n      if(--deg[to] == 0) st.emplace(to);\n    }\n  }\n  return ord;\n\
    }\n#line 5 \"graph/others/offline-dag-reachability.hpp\"\n\n/**\n * @brief Offline\
    \ Dag Reachability(DAG\u306E\u5230\u9054\u53EF\u80FD\u6027\u30AF\u30A8\u30EA)\n\
    \ * @docs docs/offline-dag-reachability.md\n */\n\ntemplate< typename T >\nvector<\
    \ int > offline_dag_reachability(const Graph< T > &g, vector< pair< int, int >\
    \ > &qs) {\n  const int N = (int) g.size();\n  const int Q = (int) qs.size();\n\
    \  auto ord = topological_sort(g);\n  vector< int > ans(Q);\n  for(int l = 0;\
    \ l < Q; l += 64) {\n    int r = min(Q, l + 64);\n    vector< int64_t > dp(N);\n\
    \    for(int k = l; k < r; k++) {\n      dp[qs[k].first] |= int64_t(1) << (k -\
    \ l);\n    }\n    for(auto &idx : ord) {\n      for(auto &to : g[idx]) dp[to]\
    \ |= dp[idx];\n    }\n    for(int k = l; k < r; k++) {\n      ans[k] = (dp[qs[k].second]\
    \ >> (k - l)) & 1;\n    }\n  }\n  return ans;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"topological-sort.hpp\"\
    \n\n/**\n * @brief Offline Dag Reachability(DAG\u306E\u5230\u9054\u53EF\u80FD\u6027\
    \u30AF\u30A8\u30EA)\n * @docs docs/offline-dag-reachability.md\n */\n\ntemplate<\
    \ typename T >\nvector< int > offline_dag_reachability(const Graph< T > &g, vector<\
    \ pair< int, int > > &qs) {\n  const int N = (int) g.size();\n  const int Q =\
    \ (int) qs.size();\n  auto ord = topological_sort(g);\n  vector< int > ans(Q);\n\
    \  for(int l = 0; l < Q; l += 64) {\n    int r = min(Q, l + 64);\n    vector<\
    \ int64_t > dp(N);\n    for(int k = l; k < r; k++) {\n      dp[qs[k].first] |=\
    \ int64_t(1) << (k - l);\n    }\n    for(auto &idx : ord) {\n      for(auto &to\
    \ : g[idx]) dp[to] |= dp[idx];\n    }\n    for(int k = l; k < r; k++) {\n    \
    \  ans[k] = (dp[qs[k].second] >> (k - l)) & 1;\n    }\n  }\n  return ans;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/others/topological-sort.hpp
  isVerificationFile: false
  path: graph/others/offline-dag-reachability.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-0275.test.cpp
documentation_of: graph/others/offline-dag-reachability.hpp
layout: document
redirect_from:
- /library/graph/others/offline-dag-reachability.hpp
- /library/graph/others/offline-dag-reachability.hpp.html
title: "Offline Dag Reachability(DAG\u306E\u5230\u9054\u53EF\u80FD\u6027\u30AF\u30A8\
  \u30EA)"
---
## 概要

DAG(閉路のない有向グラフ) が与えられたとき, ある頂点からある頂点に到達できるかどうかを調べるクエリをビット並列により処理する. ちなみに, 閉路のあるグラフの場合は強連結成分分解して, 各強連結成分を縮約することで DAG に帰着される.

トポロジカルソートして頂点をトポロジカル順に見ると, ある頂点からどの頂点に到達できるかを判定できる. このとき, 各 bit を $1$ つのクエリに対応させて到達可能性を判定すると, ビット並列により処理できることとなり高速化が見込める.

## 使い方

* `offline_dag_reachability(g, qs)`: DAG `g` について, `qs` の各クエリについて頂点 `qs[i].first` から `qs[i].second` に到達できるか判定し, 到達できる場合は `1`, できない場合は `0` を格納して返す.

## 計算量

$O(\frac {(E + V) Q} {B})$

$V$: 頂点数, $E$: 辺の本数, $Q$ クエリの個数, $B$: ワードサイズ 
