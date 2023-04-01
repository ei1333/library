---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: graph/flow/burn-bury.hpp
    title: "Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\u308B)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1615.test.cpp
    title: test/verify/aoj-1615.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-6-a.test.cpp
    title: test/verify/aoj-grl-6-a.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/dinic.md
    document_title: "Dinic(\u6700\u5927\u6D41)"
    links: []
  bundledCode: "#line 1 \"graph/flow/dinic.hpp\"\n/**\n * @brief Dinic(\u6700\u5927\
    \u6D41)\n * @docs docs/dinic.md\n */\ntemplate< typename flow_t >\nstruct Dinic\
    \ {\n  const flow_t INF;\n\n  struct edge {\n    int to;\n    flow_t cap;\n  \
    \  int rev;\n    bool isrev;\n    int idx;\n  };\n\n  vector< vector< edge > >\
    \ graph;\n  vector< int > min_cost, iter;\n\n  explicit Dinic(int V) : INF(numeric_limits<\
    \ flow_t >::max()), graph(V) {}\n\n  void add_edge(int from, int to, flow_t cap,\
    \ int idx = -1) {\n    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(),\
    \ false, idx});\n    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size()\
    \ - 1, true, idx});\n  }\n\n  bool build_augment_path(int s, int t) {\n    min_cost.assign(graph.size(),\
    \ -1);\n    queue< int > que;\n    min_cost[s] = 0;\n    que.push(s);\n    while(!que.empty()\
    \ && min_cost[t] == -1) {\n      int p = que.front();\n      que.pop();\n    \
    \  for(auto &e: graph[p]) {\n        if(e.cap > 0 && min_cost[e.to] == -1) {\n\
    \          min_cost[e.to] = min_cost[p] + 1;\n          que.push(e.to);\n    \
    \    }\n      }\n    }\n    return min_cost[t] != -1;\n  }\n\n  flow_t find_min_dist_augment_path(int\
    \ idx, const int t, flow_t flow) {\n    if(idx == t) return flow;\n    for(int\
    \ &i = iter[idx]; i < (int) graph[idx].size(); i++) {\n      edge &e = graph[idx][i];\n\
    \      if(e.cap > 0 && min_cost[idx] < min_cost[e.to]) {\n        flow_t d = find_min_dist_augment_path(e.to,\
    \ t, min(flow, e.cap));\n        if(d > 0) {\n          e.cap -= d;\n        \
    \  graph[e.to][e.rev].cap += d;\n          return d;\n        }\n      }\n   \
    \ }\n    return 0;\n  }\n\n  flow_t max_flow(int s, int t) {\n    flow_t flow\
    \ = 0;\n    while(build_augment_path(s, t)) {\n      iter.assign(graph.size(),\
    \ 0);\n      flow_t f;\n      while((f = find_min_dist_augment_path(s, t, INF))\
    \ > 0) flow += f;\n    }\n    return flow;\n  }\n\n  void output() {\n    for(int\
    \ i = 0; i < graph.size(); i++) {\n      for(auto &e: graph[i]) {\n        if(e.isrev)\
    \ continue;\n        auto &rev_e = graph[e.to][e.rev];\n        cout << i << \"\
    ->\" << e.to << \" (flow: \" << rev_e.cap << \"/\" << e.cap + rev_e.cap << \"\
    )\" << endl;\n      }\n    }\n  }\n\n  vector< bool > min_cut(int s) {\n    vector<\
    \ bool > used(graph.size());\n    queue< int > que;\n    que.emplace(s);\n   \
    \ used[s] = true;\n    while(not que.empty()) {\n      int p = que.front();\n\
    \      que.pop();\n      for(auto &e: graph[p]) {\n        if(e.cap > 0 and not\
    \ used[e.to]) {\n          used[e.to] = true;\n          que.emplace(e.to);\n\
    \        }\n      }\n    }\n    return used;\n  }\n};\n"
  code: "/**\n * @brief Dinic(\u6700\u5927\u6D41)\n * @docs docs/dinic.md\n */\ntemplate<\
    \ typename flow_t >\nstruct Dinic {\n  const flow_t INF;\n\n  struct edge {\n\
    \    int to;\n    flow_t cap;\n    int rev;\n    bool isrev;\n    int idx;\n \
    \ };\n\n  vector< vector< edge > > graph;\n  vector< int > min_cost, iter;\n\n\
    \  explicit Dinic(int V) : INF(numeric_limits< flow_t >::max()), graph(V) {}\n\
    \n  void add_edge(int from, int to, flow_t cap, int idx = -1) {\n    graph[from].emplace_back((edge)\
    \ {to, cap, (int) graph[to].size(), false, idx});\n    graph[to].emplace_back((edge)\
    \ {from, 0, (int) graph[from].size() - 1, true, idx});\n  }\n\n  bool build_augment_path(int\
    \ s, int t) {\n    min_cost.assign(graph.size(), -1);\n    queue< int > que;\n\
    \    min_cost[s] = 0;\n    que.push(s);\n    while(!que.empty() && min_cost[t]\
    \ == -1) {\n      int p = que.front();\n      que.pop();\n      for(auto &e: graph[p])\
    \ {\n        if(e.cap > 0 && min_cost[e.to] == -1) {\n          min_cost[e.to]\
    \ = min_cost[p] + 1;\n          que.push(e.to);\n        }\n      }\n    }\n \
    \   return min_cost[t] != -1;\n  }\n\n  flow_t find_min_dist_augment_path(int\
    \ idx, const int t, flow_t flow) {\n    if(idx == t) return flow;\n    for(int\
    \ &i = iter[idx]; i < (int) graph[idx].size(); i++) {\n      edge &e = graph[idx][i];\n\
    \      if(e.cap > 0 && min_cost[idx] < min_cost[e.to]) {\n        flow_t d = find_min_dist_augment_path(e.to,\
    \ t, min(flow, e.cap));\n        if(d > 0) {\n          e.cap -= d;\n        \
    \  graph[e.to][e.rev].cap += d;\n          return d;\n        }\n      }\n   \
    \ }\n    return 0;\n  }\n\n  flow_t max_flow(int s, int t) {\n    flow_t flow\
    \ = 0;\n    while(build_augment_path(s, t)) {\n      iter.assign(graph.size(),\
    \ 0);\n      flow_t f;\n      while((f = find_min_dist_augment_path(s, t, INF))\
    \ > 0) flow += f;\n    }\n    return flow;\n  }\n\n  void output() {\n    for(int\
    \ i = 0; i < graph.size(); i++) {\n      for(auto &e: graph[i]) {\n        if(e.isrev)\
    \ continue;\n        auto &rev_e = graph[e.to][e.rev];\n        cout << i << \"\
    ->\" << e.to << \" (flow: \" << rev_e.cap << \"/\" << e.cap + rev_e.cap << \"\
    )\" << endl;\n      }\n    }\n  }\n\n  vector< bool > min_cut(int s) {\n    vector<\
    \ bool > used(graph.size());\n    queue< int > que;\n    que.emplace(s);\n   \
    \ used[s] = true;\n    while(not que.empty()) {\n      int p = que.front();\n\
    \      que.pop();\n      for(auto &e: graph[p]) {\n        if(e.cap > 0 and not\
    \ used[e.to]) {\n          used[e.to] = true;\n          que.emplace(e.to);\n\
    \        }\n      }\n    }\n    return used;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/flow/dinic.hpp
  requiredBy:
  - graph/flow/burn-bury.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-1615.test.cpp
  - test/verify/aoj-grl-6-a.test.cpp
documentation_of: graph/flow/dinic.hpp
layout: document
redirect_from:
- /library/graph/flow/dinic.hpp
- /library/graph/flow/dinic.hpp.html
title: "Dinic(\u6700\u5927\u6D41)"
---
## 概要

最大流を求めるアルゴリズム.

残余グラフ上の辺数最小のパスを BFS により探して, DFS により増加パスがとれなくなるまでフローを流すことを繰り返し, 流せなくなったら終了する.

## 使い方

* `Dinic(V)`: 頂点数 `V` で初期化する.
* `add_edge(from, to, cap, idx = -1)`: 頂点 `from` から `to` に容量 `cap` の辺を追加する.
* `max_flow(s, t)`: 頂点 `s` から `t` に最大流を流し, その流量を返す.

## 計算量

$O(EV^2)$

実測では高速に動作することが多いが, ネットワークが直接入力で与えられるなど最悪ケースを構成できる場合は遅いのでその場合は Push-Relabel などの別の最大流アルゴリズムを検討する必要がある.
 
$2$ 部グラフの最大マッチングのとき $O(E \sqrt V)$, 辺容量が全て同じ場合 $O(\min (V^{\frac {2} {3}}, E^{\frac {1} {2}}) E)$ となる.
