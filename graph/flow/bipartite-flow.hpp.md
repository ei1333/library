---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/others/bipartite-graph-edge-coloring.hpp
    title: "Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u8FBA\
      \u5F69\u8272)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-0334.test.cpp
    title: test/verify/aoj-0334.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-3198.test.cpp
    title: test/verify/aoj-3198.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bipartite-edge-coloring.test.cpp
    title: test/verify/yosupo-bipartite-edge-coloring.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bipartitematching.test.cpp
    title: test/verify/yosupo-bipartitematching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/bipartite-flow.md
    document_title: "Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\
      \u30FC)"
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198
    - https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11
  bundledCode: "#line 1 \"graph/flow/bipartite-flow.hpp\"\n/**\n * @brief Bipartite\
    \ Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC)\n * @docs docs/bipartite-flow.md\n\
    \ */\nstruct BipartiteFlow {\n  size_t n, m, time_stamp;\n  vector< vector< int\
    \ > > g, rg;\n  vector< int > match_l, match_r, dist, used, alive;\n  bool matched;\n\
    \npublic:\n  explicit BipartiteFlow(size_t n, size_t m) :\n      n(n), m(m), time_stamp(0),\
    \ g(n), rg(m), match_l(n, -1), match_r(m, -1), used(n), alive(n, 1), matched(false)\
    \ {}\n\n  void add_edge(int u, int v) {\n    g[u].push_back(v);\n    rg[v].emplace_back(u);\n\
    \  }\n\n  vector< pair< int, int > > max_matching() {\n    matched = true;\n \
    \   for(;;) {\n      build_augment_path();\n      ++time_stamp;\n      int flow\
    \ = 0;\n      for(int i = 0; i < (int)n; i++) {\n        if(match_l[i] == -1)\
    \ flow += find_min_dist_augment_path(i);\n      }\n      if(flow == 0) break;\n\
    \    }\n    vector< pair< int, int > > ret;\n    for(int i = 0; i < (int)n; i++)\
    \ {\n      if(match_l[i] >= 0) ret.emplace_back(i, match_l[i]);\n    }\n    return\
    \ ret;\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198\
    \ */\n  void erase_edge(int a, int b) {\n    if(match_l[a] == b) {\n      match_l[a]\
    \ = -1;\n      match_r[b] = -1;\n    }\n    g[a].erase(find(begin(g[a]), end(g[a]),\
    \ b));\n    rg[b].erase(find(begin(rg[b]), end(rg[b]), a));\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334\
    \ */\n  vector< pair< int, int > > lex_max_matching() {\n    if(!matched) max_matching();\n\
    \    for(auto &vs : g) sort(begin(vs), end(vs));\n    vector< pair< int, int >\
    \ > es;\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1 || alive[i]\
    \ == 0) {\n        continue;\n      }\n      match_r[match_l[i]] = -1;\n     \
    \ match_l[i] = -1;\n      ++time_stamp;\n      find_augment_path(i);\n      alive[i]\
    \ = 0;\n      es.emplace_back(i, match_l[i]);\n    }\n    return es;\n  }\n\n\
    \  vector< int > min_vertex_cover() {\n    auto visited = find_residual_path();\n\
    \    vector< int > ret;\n    for(int i = 0; i < (int)(n + m); i++) {\n      if(visited[i]\
    \ ^ (i < (int)n)) {\n        ret.emplace_back(i);\n      }\n    }\n    return\
    \ ret;\n  }\n\n  /* https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11 */\n\
    \  vector< int > lex_min_vertex_cover(const vector< int > &ord) {\n    assert(ord.size()\
    \ == n + m);\n    auto res = build_risidual_graph();\n    vector< vector< int\
    \ > > r_res(n + m + 2);\n    for(int i = 0; i < (int)(n + m + 2); i++) {\n   \
    \   for(auto &j : res[i]) r_res[j].emplace_back(i);\n    }\n    queue< int > que;\n\
    \    vector< int > visited(n + m + 2, -1);\n    auto expand_left = [&](int t)\
    \ {\n      if(visited[t] != -1) return;\n      que.emplace(t);\n      visited[t]\
    \ = 1;\n      while(!que.empty()) {\n        int idx = que.front();\n        que.pop();\n\
    \        for(auto &to : r_res[idx]) {\n          if(visited[to] != -1) continue;\n\
    \          visited[to] = 1;\n          que.emplace(to);\n        }\n      }\n\
    \    };\n    auto expand_right = [&](int t) {\n      if(visited[t] != -1) return;\n\
    \      que.emplace(t);\n      visited[t] = 0;\n      while(!que.empty()) {\n \
    \       int idx = que.front();\n        que.pop();\n        for(auto &to : res[idx])\
    \ {\n          if(visited[to] != -1) continue;\n          visited[to] = 0;\n \
    \         que.emplace(to);\n        }\n      }\n    };\n    expand_right(n + m);\n\
    \    expand_left(n + m + 1);\n    vector< int > ret;\n    for(auto &t : ord) {\n\
    \      if(t < (int)n) {\n        expand_left(t);\n        if(visited[t] & 1) ret.emplace_back(t);\n\
    \      } else {\n        expand_right(t);\n        if(~visited[t] & 1) ret.emplace_back(t);\n\
    \      }\n    }\n    return ret;\n  }\n\n\n  vector< int > max_independent_set()\
    \ {\n    auto visited = find_residual_path();\n    vector< int > ret;\n    for(int\
    \ i = 0; i < (int)(n + m); i++) {\n      if(visited[i] ^ (i >= (int)n)) {\n  \
    \      ret.emplace_back(i);\n      }\n    }\n    return ret;\n  }\n\n  vector<\
    \ pair< int, int > > min_edge_cover() {\n    auto es = max_matching();\n    for(int\
    \ i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) {\n        continue;\n\
    \      }\n      if(g[i].empty()) {\n        return {};\n      }\n      es.emplace_back(i,\
    \ g[i][0]);\n    }\n    for(int i = 0; i < (int)m; i++) {\n      if(match_r[i]\
    \ >= 0) {\n        continue;\n      }\n      if(rg[i].empty()) {\n        return\
    \ {};\n      }\n      es.emplace_back(rg[i][0], i);\n    }\n    return es;\n \
    \ }\n\n  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1\n  vector< vector< int\
    \ > > build_risidual_graph() {\n    if(!matched) max_matching();\n    const size_t\
    \ S = n + m;\n    const size_t T = n + m + 1;\n    vector< vector< int > > ris(n\
    \ + m + 2);\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1)\
    \ ris[S].emplace_back(i);\n      else ris[i].emplace_back(S);\n    }\n    for(int\
    \ i = 0; i < (int)m; i++) {\n      if(match_r[i] == -1) ris[i + n].emplace_back(T);\n\
    \      else ris[T].emplace_back(i + n);\n    }\n    for(int i = 0; i < (int)n;\
    \ i++) {\n      for(auto &j : g[i]) {\n        if(match_l[i] == j) ris[j + n].emplace_back(i);\n\
    \        else ris[i].emplace_back(j + n);\n      }\n    }\n    return ris;\n \
    \ }\n\nprivate:\n  vector< int > find_residual_path() {\n    auto res = build_risidual_graph();\n\
    \    queue< int > que;\n    vector< int > visited(n + m + 2);\n    que.emplace(n\
    \ + m);\n    visited[n + m] = true;\n    while(!que.empty()) {\n      int idx\
    \ = que.front();\n      que.pop();\n      for(auto &to : res[idx]) {\n       \
    \ if(visited[to]) continue;\n        visited[to] = true;\n        que.emplace(to);\n\
    \      }\n    }\n    return visited;\n  }\n\n  void build_augment_path() {\n \
    \   queue< int > que;\n    dist.assign(g.size(), -1);\n    for(int i = 0; i <\
    \ (int)n; i++) {\n      if(match_l[i] == -1) {\n        que.emplace(i);\n    \
    \    dist[i] = 0;\n      }\n    }\n    while(!que.empty()) {\n      int a = que.front();\n\
    \      que.pop();\n      for(auto &b : g[a]) {\n        int c = match_r[b];\n\
    \        if(c >= 0 && dist[c] == -1) {\n          dist[c] = dist[a] + 1;\n   \
    \       que.emplace(c);\n        }\n      }\n    }\n  }\n\n  bool find_min_dist_augment_path(int\
    \ a) {\n    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 && find_min_dist_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n\n  bool find_augment_path(int a) {\n\
    \    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp && find_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n};\n"
  code: "/**\n * @brief Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\
    \u30FC)\n * @docs docs/bipartite-flow.md\n */\nstruct BipartiteFlow {\n  size_t\
    \ n, m, time_stamp;\n  vector< vector< int > > g, rg;\n  vector< int > match_l,\
    \ match_r, dist, used, alive;\n  bool matched;\n\npublic:\n  explicit BipartiteFlow(size_t\
    \ n, size_t m) :\n      n(n), m(m), time_stamp(0), g(n), rg(m), match_l(n, -1),\
    \ match_r(m, -1), used(n), alive(n, 1), matched(false) {}\n\n  void add_edge(int\
    \ u, int v) {\n    g[u].push_back(v);\n    rg[v].emplace_back(u);\n  }\n\n  vector<\
    \ pair< int, int > > max_matching() {\n    matched = true;\n    for(;;) {\n  \
    \    build_augment_path();\n      ++time_stamp;\n      int flow = 0;\n      for(int\
    \ i = 0; i < (int)n; i++) {\n        if(match_l[i] == -1) flow += find_min_dist_augment_path(i);\n\
    \      }\n      if(flow == 0) break;\n    }\n    vector< pair< int, int > > ret;\n\
    \    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) ret.emplace_back(i,\
    \ match_l[i]);\n    }\n    return ret;\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198\
    \ */\n  void erase_edge(int a, int b) {\n    if(match_l[a] == b) {\n      match_l[a]\
    \ = -1;\n      match_r[b] = -1;\n    }\n    g[a].erase(find(begin(g[a]), end(g[a]),\
    \ b));\n    rg[b].erase(find(begin(rg[b]), end(rg[b]), a));\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334\
    \ */\n  vector< pair< int, int > > lex_max_matching() {\n    if(!matched) max_matching();\n\
    \    for(auto &vs : g) sort(begin(vs), end(vs));\n    vector< pair< int, int >\
    \ > es;\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1 || alive[i]\
    \ == 0) {\n        continue;\n      }\n      match_r[match_l[i]] = -1;\n     \
    \ match_l[i] = -1;\n      ++time_stamp;\n      find_augment_path(i);\n      alive[i]\
    \ = 0;\n      es.emplace_back(i, match_l[i]);\n    }\n    return es;\n  }\n\n\
    \  vector< int > min_vertex_cover() {\n    auto visited = find_residual_path();\n\
    \    vector< int > ret;\n    for(int i = 0; i < (int)(n + m); i++) {\n      if(visited[i]\
    \ ^ (i < (int)n)) {\n        ret.emplace_back(i);\n      }\n    }\n    return\
    \ ret;\n  }\n\n  /* https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11 */\n\
    \  vector< int > lex_min_vertex_cover(const vector< int > &ord) {\n    assert(ord.size()\
    \ == n + m);\n    auto res = build_risidual_graph();\n    vector< vector< int\
    \ > > r_res(n + m + 2);\n    for(int i = 0; i < (int)(n + m + 2); i++) {\n   \
    \   for(auto &j : res[i]) r_res[j].emplace_back(i);\n    }\n    queue< int > que;\n\
    \    vector< int > visited(n + m + 2, -1);\n    auto expand_left = [&](int t)\
    \ {\n      if(visited[t] != -1) return;\n      que.emplace(t);\n      visited[t]\
    \ = 1;\n      while(!que.empty()) {\n        int idx = que.front();\n        que.pop();\n\
    \        for(auto &to : r_res[idx]) {\n          if(visited[to] != -1) continue;\n\
    \          visited[to] = 1;\n          que.emplace(to);\n        }\n      }\n\
    \    };\n    auto expand_right = [&](int t) {\n      if(visited[t] != -1) return;\n\
    \      que.emplace(t);\n      visited[t] = 0;\n      while(!que.empty()) {\n \
    \       int idx = que.front();\n        que.pop();\n        for(auto &to : res[idx])\
    \ {\n          if(visited[to] != -1) continue;\n          visited[to] = 0;\n \
    \         que.emplace(to);\n        }\n      }\n    };\n    expand_right(n + m);\n\
    \    expand_left(n + m + 1);\n    vector< int > ret;\n    for(auto &t : ord) {\n\
    \      if(t < (int)n) {\n        expand_left(t);\n        if(visited[t] & 1) ret.emplace_back(t);\n\
    \      } else {\n        expand_right(t);\n        if(~visited[t] & 1) ret.emplace_back(t);\n\
    \      }\n    }\n    return ret;\n  }\n\n\n  vector< int > max_independent_set()\
    \ {\n    auto visited = find_residual_path();\n    vector< int > ret;\n    for(int\
    \ i = 0; i < (int)(n + m); i++) {\n      if(visited[i] ^ (i >= (int)n)) {\n  \
    \      ret.emplace_back(i);\n      }\n    }\n    return ret;\n  }\n\n  vector<\
    \ pair< int, int > > min_edge_cover() {\n    auto es = max_matching();\n    for(int\
    \ i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) {\n        continue;\n\
    \      }\n      if(g[i].empty()) {\n        return {};\n      }\n      es.emplace_back(i,\
    \ g[i][0]);\n    }\n    for(int i = 0; i < (int)m; i++) {\n      if(match_r[i]\
    \ >= 0) {\n        continue;\n      }\n      if(rg[i].empty()) {\n        return\
    \ {};\n      }\n      es.emplace_back(rg[i][0], i);\n    }\n    return es;\n \
    \ }\n\n  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1\n  vector< vector< int\
    \ > > build_risidual_graph() {\n    if(!matched) max_matching();\n    const size_t\
    \ S = n + m;\n    const size_t T = n + m + 1;\n    vector< vector< int > > ris(n\
    \ + m + 2);\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1)\
    \ ris[S].emplace_back(i);\n      else ris[i].emplace_back(S);\n    }\n    for(int\
    \ i = 0; i < (int)m; i++) {\n      if(match_r[i] == -1) ris[i + n].emplace_back(T);\n\
    \      else ris[T].emplace_back(i + n);\n    }\n    for(int i = 0; i < (int)n;\
    \ i++) {\n      for(auto &j : g[i]) {\n        if(match_l[i] == j) ris[j + n].emplace_back(i);\n\
    \        else ris[i].emplace_back(j + n);\n      }\n    }\n    return ris;\n \
    \ }\n\nprivate:\n  vector< int > find_residual_path() {\n    auto res = build_risidual_graph();\n\
    \    queue< int > que;\n    vector< int > visited(n + m + 2);\n    que.emplace(n\
    \ + m);\n    visited[n + m] = true;\n    while(!que.empty()) {\n      int idx\
    \ = que.front();\n      que.pop();\n      for(auto &to : res[idx]) {\n       \
    \ if(visited[to]) continue;\n        visited[to] = true;\n        que.emplace(to);\n\
    \      }\n    }\n    return visited;\n  }\n\n  void build_augment_path() {\n \
    \   queue< int > que;\n    dist.assign(g.size(), -1);\n    for(int i = 0; i <\
    \ (int)n; i++) {\n      if(match_l[i] == -1) {\n        que.emplace(i);\n    \
    \    dist[i] = 0;\n      }\n    }\n    while(!que.empty()) {\n      int a = que.front();\n\
    \      que.pop();\n      for(auto &b : g[a]) {\n        int c = match_r[b];\n\
    \        if(c >= 0 && dist[c] == -1) {\n          dist[c] = dist[a] + 1;\n   \
    \       que.emplace(c);\n        }\n      }\n    }\n  }\n\n  bool find_min_dist_augment_path(int\
    \ a) {\n    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 && find_min_dist_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n\n  bool find_augment_path(int a) {\n\
    \    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp && find_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/flow/bipartite-flow.hpp
  requiredBy:
  - graph/others/bipartite-graph-edge-coloring.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-0334.test.cpp
  - test/verify/yosupo-bipartite-edge-coloring.test.cpp
  - test/verify/aoj-3198.test.cpp
  - test/verify/yosupo-bipartitematching.test.cpp
documentation_of: graph/flow/bipartite-flow.hpp
layout: document
redirect_from:
- /library/graph/flow/bipartite-flow.hpp
- /library/graph/flow/bipartite-flow.hpp.html
title: "Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC)"
---
## 概要

二部グラフに対するフロー. 

最大マッチングは Hopcroft-Karp に基づく実装. 最大流を求める Dinic と同じアルゴリズムだが, Hopcroft-Karp はこれを二部グラフ用に書き換えたもので定数倍が軽い. 残余グラフをBFSして各頂点までの最短距離を計算し, 最短距離のパスをDFSで見つけてフローを流す.

計算量が良いため基本的にはこれを使うと良い.

## 残余グラフについて
左側の頂点を $[0, n)$, 右側の頂点を $[n, n+m)$, 始点を $n+m$, 終点を $n+m+1$ としたグラフの残余グラフを用いると, いろいろできる.

このグラフを強連結成分分解する. すると各辺 $(u, v)$ (実際には $(u, v+n)$ なので注意すること) について, その辺が最大マッチングに必ず使うか, 必ず使わないか, それ以外かが分かり, 以下の手順で確認できる.

1. 頂点 $u, v$ が同じ強連結成分に含まれる → それ以外
2. 辺 $(u, v)$ が最大マッチングに含まれる → 必ず使う
3. それ以外(頂点 $u, v$ が異なる連結成分) → 必ず使わない

残余グラフについて始点から到達できる頂点をBFSなどにより全列挙する. 最小頂点被覆は, 左側かつ到達できない頂点 または 右側かつ到達できる点である. 最大安定集合はその補集合である. また残余グラフを見て頑張ると同じ計算量で辞書順最小頂点被覆も求まる.

## DAG の最小パス被覆

グラフ $G = (V, E)$ において, そのグラフの全ての頂点が $1$ つ以上のパスに含まれるようなパスの集合をを パス被覆 という.

特に, パス被覆の中でパスの数が最小のものを 最小パス被覆 という.

DAGの最小パス被覆は二部グラフの最大マッチング問題に帰着できる. 頂点を倍長して, 始点を左側に, 終点を右側に配置したグラフを考える. $V$ 本のパスがあれば被覆できることは自明. このグラフのマッチング一組に対して必要なパスを $1$ つ減らすことができるため, $V - $ (二部グラフの最大マッチング) が最小パス被覆となる.

## 使い方

* `BipartiteFlow(n, m)`:= 左側の頂点数 `n`, 右側の頂点数 `m` で初期化する.
* `add_edge(u, v)`:= 頂点 `u`, `v` 間に辺を張る.
* `max_matching()`:= 最大マッチングを返す.
* `erase_edge(a, b)`:= 頂点 `u`, `v` 間にある辺を削除する.
* `min_vertex_cover()`:= 最小頂点被覆を返す.
* `max_independent_set()`:= 最大安定集合を返す.
* `min_edge_cover()`:= 最小辺被覆を返す.
* `lex_max_matching()`:= 辞書順最小の最大マッチングを返す.
* `lex_min_vertex_cover(ord)`:= `ord` は左側の頂点を $[0, n)$, 右側の頂点を $[n, n + m)$ で表すとき, 優先度が高い順に頂点番号を並べた長さ $n + m$ の数列. このときの辞書順(優先度順)最小頂点被覆を返す.
* `build_residual_graph()`:= 左側の頂点を $[0, n)$, 右側の頂点を $[n, n+m)$, 始点を $n+m$, 終点を $n+m+1$ としたグラフを考えたとき, 残余グラフを返す.

## 計算量

* `add_edge(a, b)`: $O(1)$
* `erase_edge(a, b)`: $O(V)$
* `max_matching()`: $O(E \sqrt V)$
* `min_vertex_cover()`: $O(E \sqrt V)$
* `max_independent_cover()`: $O(E \sqrt V)$
* `min_edge_cover()`: $O(E \sqrt V)$
* `lex_max_matching()`: $O(E V)$ だと思うが早くできるのかも
* `lex_min_vertex_cover(ord)`: $O(E \sqrt V)$
* `build_residual_graph()`: $O(E + V)$
