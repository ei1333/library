---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/dinic.hpp
    title: "Dinic(\u6700\u5927\u6D41)"
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\u308B)"
    links: []
  bundledCode: "#line 2 \"graph/flow/burn-bury.hpp\"\n\n#line 2 \"structure/union-find/union-find.hpp\"\
    \n\nstruct UnionFind {\n  vector< int > data;\n\n  UnionFind() = default;\n\n\
    \  explicit UnionFind(size_t sz) : data(sz, -1) {}\n\n  bool unite(int x, int\
    \ y) {\n    x = find(x), y = find(y);\n    if(x == y) return false;\n    if(data[x]\
    \ > data[y]) swap(x, y);\n    data[x] += data[y];\n    data[y] = x;\n    return\
    \ true;\n  }\n\n  int find(int k) {\n    if(data[k] < 0) return (k);\n    return\
    \ data[k] = find(data[k]);\n  }\n\n  int size(int k) {\n    return -data[find(k)];\n\
    \  }\n\n  bool same(int x, int y) {\n    return find(x) == find(y);\n  }\n\n \
    \ vector< vector< int > > groups() {\n    int n = (int) data.size();\n    vector<\
    \ vector< int > > ret(n);\n    for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n\
    \    }\n    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int >\
    \ &v) {\n      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n\
    #line 1 \"graph/flow/dinic.hpp\"\n/**\n * @brief Dinic(\u6700\u5927\u6D41)\n *\
    \ @docs docs/dinic.md\n */\ntemplate< typename flow_t >\nstruct Dinic {\n  const\
    \ flow_t INF;\n\n  struct edge {\n    int to;\n    flow_t cap;\n    int rev;\n\
    \    bool isrev;\n    int idx;\n  };\n\n  vector< vector< edge > > graph;\n  vector<\
    \ int > min_cost, iter;\n\n  explicit Dinic(int V) : INF(numeric_limits< flow_t\
    \ >::max()), graph(V) {}\n\n  void add_edge(int from, int to, flow_t cap, int\
    \ idx = -1) {\n    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(),\
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
    \        }\n      }\n    }\n    return used;\n  }\n};\n#line 5 \"graph/flow/burn-bury.hpp\"\
    \n\n/**\n * @brief Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\u308B)\n */\ntemplate<\
    \ typename T, bool minimize = true >\nstruct BurnBury {\nprivate:\n  using MaxFlow\
    \ = Dinic< T >;\n  using UF = UnionFind;\n  using arr2 = array< T, 2 >;\n  using\
    \ arr4 = array< T, 4 >;\n\n  int n;\n  T alpha;\n  vector< arr2 > theta;\n  vector<\
    \ map< int, arr4 > > phi;\n  map< vector< int >, T > zeta;\n\npublic:\n  explicit\
    \ BurnBury(int n) : n{n}, alpha{}, theta(n), phi(n) {}\n\n  void add_cost(T cost)\
    \ {\n    if(not minimize) cost *= -1;\n    alpha += cost;\n  }\n\n  void add_cost(int\
    \ x, T cost) {\n    if(not minimize) cost *= -1;\n    int a = max(~x, x);\n  \
    \  theta[a][x >= 0] += cost;\n  }\n\n  void add_cost(int x, int y, T cost) {\n\
    \    assert(x != y);\n    if(not minimize) cost *= -1;\n    int a = max(~x, x),\
    \ b = max(~y, y);\n    if(a < b) phi[a][b][((x >= 0) << 1) | (y >= 0)] += cost;\n\
    \    else phi[b][a][((y >= 0) << 1) | (x >= 0)] += cost;\n  }\n\n  void add_cost(vector<\
    \ int > xs, T cost) {\n    assert(not xs.empty());\n    if(xs.size() == 1) {\n\
    \      add_cost(xs[0], cost);\n    } else if(xs.size() == 2) {\n      add_cost(xs[0],\
    \ xs[1], cost);\n    } else {\n      int m = (int) xs.size();\n      sort(xs.begin(),\
    \ xs.end());\n      xs.erase(unique(xs.begin(), xs.end()), xs.end());\n      assert(m\
    \ == (int) xs.size());\n      if(not minimize) cost *= -1;\n      zeta[xs] +=\
    \ cost;\n    }\n  }\n\n  optional< pair< T, vector< bool > > > solve() {\n   \
    \ vector< int > flip(2 * n, -1);\n    {\n      UF uf(n + n);\n      for(int i\
    \ = 0; i < n; i++) {\n        for(auto&[j, cs]: phi[i]) {\n          T c = -cs[0]\
    \ + cs[1] + cs[2] - cs[3];\n          if(c < 0) {\n            uf.unite(i, j +\
    \ n);\n            uf.unite(i + n, j);\n          }\n          if(c > 0) {\n \
    \           uf.unite(i, j);\n            uf.unite(i + n, j + n);\n          }\n\
    \        }\n      }\n      for(auto&[vs, c]: zeta) {\n        if(c > 0) return\
    \ nullopt;\n        if(c < 0) {\n          for(int i = 1; i < (int) vs.size();\
    \ i++) {\n            int x = vs[i - 1], y = vs[i];\n            int a = max(x,\
    \ ~x), b = max(y, ~y);\n            if((x >= 0) ^ (y >= 0)) {\n              uf.unite(a,\
    \ b + n);\n              uf.unite(a + n, b);\n            } else {\n         \
    \     uf.unite(a, b);\n              uf.unite(a + n, b + n);\n            }\n\
    \          }\n        }\n      }\n      for(int i = 0; i < n; i++) {\n       \
    \ int x = uf.find(i);\n        int y = uf.find(i + n);\n        if(x == y) return\
    \ nullopt;\n        if(flip[x] < 0) {\n          flip[x] = 0;\n          flip[y]\
    \ = 1;\n        }\n      }\n      for(int i = 0; i < n; i++) {\n        if(flip[i]\
    \ < 0) {\n          flip[i] = flip[uf.find(i)];\n        }\n      }\n      flip.resize(n);\n\
    \    }\n    {\n      for(int i = 0; i < n; i++) {\n        for(auto&[j, cs]: phi[i])\
    \ {\n          if(flip[i]) {\n            swap(cs[0], cs[2]);\n            swap(cs[1],\
    \ cs[3]);\n          }\n          if(flip[j]) {\n            swap(cs[0], cs[1]);\n\
    \            swap(cs[2], cs[3]);\n          }\n          T c = -cs[0] + cs[1]\
    \ + cs[2] - cs[3];\n          alpha += cs[0];\n          theta[i][not flip[i]]\
    \ += cs[2] - cs[0];\n          theta[j][not flip[j]] += cs[3] - cs[2];\n     \
    \     cs[1] = c;\n          cs[0] = cs[2] = cs[3] = 0;\n        }\n      }\n \
    \   }\n    {\n      for(int i = 0; i < n; i++) {\n        auto &cs = theta[i];\n\
    \        if(flip[i]) {\n          swap(cs[0], cs[1]);\n        }\n        if(cs[0]\
    \ <= cs[1]) {\n          alpha += cs[0];\n          cs[1] -= cs[0];\n        \
    \  cs[0] = 0;\n        } else {\n          alpha += cs[1];\n          cs[0] -=\
    \ cs[1];\n          cs[1] = 0;\n        }\n      }\n    }\n\n    MaxFlow flow(n\
    \ + 2 + zeta.size());\n    int s = n, t = n + 1;\n    {\n      for(int i = 0;\
    \ i < n; i++) {\n        auto &cs = theta[i];\n        if(cs[1] > 0) {\n     \
    \     flow.add_edge(i, t, cs[1]);\n        }\n        if(cs[0] > 0) {\n      \
    \    flow.add_edge(s, i, cs[0]);\n        }\n      }\n      for(int i = 0; i <\
    \ n; i++) {\n        for(auto&[j, cs]: phi[i]) {\n          if(cs[2] > 0) {\n\
    \            flow.add_edge(i, j, cs[2]);\n          }\n          if(cs[1] > 0)\
    \ {\n            flow.add_edge(j, i, cs[1]);\n          }\n        }\n      }\n\
    \      int u = t + 1;\n      for(auto&[vs, c]: zeta) {\n        if(c < 0) {\n\
    \          if((vs[0] >= 0) ^ flip[max(~vs[0], vs[0])]) {\n            flow.add_edge(s,\
    \ u, -c);\n            for(auto &p: vs) flow.add_edge(u, max(p, ~p), -c);\n  \
    \        } else {\n            for(auto &p: vs) flow.add_edge(max(p, ~p), u, -c);\n\
    \            flow.add_edge(u, t, -c);\n          }\n          alpha += c;\n  \
    \        u++;\n        }\n      }\n    }\n    T ans = flow.max_flow(s, t) + alpha;\n\
    \    vector< bool > cut = flow.min_cut(s);\n    for(int i = 0; i < n; i++) {\n\
    \      if(flip[i]) cut[i] = 1 - cut[i];\n    }\n    cut.resize(n);\n    return\
    \ make_pair(minimize ? ans : -ans, cut);\n  }\n};\n"
  code: "#pragma once\n\n#include \"../../structure/union-find/union-find.hpp\"\n\
    #include \"dinic.hpp\"\n\n/**\n * @brief Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\
    \u308B)\n */\ntemplate< typename T, bool minimize = true >\nstruct BurnBury {\n\
    private:\n  using MaxFlow = Dinic< T >;\n  using UF = UnionFind;\n  using arr2\
    \ = array< T, 2 >;\n  using arr4 = array< T, 4 >;\n\n  int n;\n  T alpha;\n  vector<\
    \ arr2 > theta;\n  vector< map< int, arr4 > > phi;\n  map< vector< int >, T >\
    \ zeta;\n\npublic:\n  explicit BurnBury(int n) : n{n}, alpha{}, theta(n), phi(n)\
    \ {}\n\n  void add_cost(T cost) {\n    if(not minimize) cost *= -1;\n    alpha\
    \ += cost;\n  }\n\n  void add_cost(int x, T cost) {\n    if(not minimize) cost\
    \ *= -1;\n    int a = max(~x, x);\n    theta[a][x >= 0] += cost;\n  }\n\n  void\
    \ add_cost(int x, int y, T cost) {\n    assert(x != y);\n    if(not minimize)\
    \ cost *= -1;\n    int a = max(~x, x), b = max(~y, y);\n    if(a < b) phi[a][b][((x\
    \ >= 0) << 1) | (y >= 0)] += cost;\n    else phi[b][a][((y >= 0) << 1) | (x >=\
    \ 0)] += cost;\n  }\n\n  void add_cost(vector< int > xs, T cost) {\n    assert(not\
    \ xs.empty());\n    if(xs.size() == 1) {\n      add_cost(xs[0], cost);\n    }\
    \ else if(xs.size() == 2) {\n      add_cost(xs[0], xs[1], cost);\n    } else {\n\
    \      int m = (int) xs.size();\n      sort(xs.begin(), xs.end());\n      xs.erase(unique(xs.begin(),\
    \ xs.end()), xs.end());\n      assert(m == (int) xs.size());\n      if(not minimize)\
    \ cost *= -1;\n      zeta[xs] += cost;\n    }\n  }\n\n  optional< pair< T, vector<\
    \ bool > > > solve() {\n    vector< int > flip(2 * n, -1);\n    {\n      UF uf(n\
    \ + n);\n      for(int i = 0; i < n; i++) {\n        for(auto&[j, cs]: phi[i])\
    \ {\n          T c = -cs[0] + cs[1] + cs[2] - cs[3];\n          if(c < 0) {\n\
    \            uf.unite(i, j + n);\n            uf.unite(i + n, j);\n          }\n\
    \          if(c > 0) {\n            uf.unite(i, j);\n            uf.unite(i +\
    \ n, j + n);\n          }\n        }\n      }\n      for(auto&[vs, c]: zeta) {\n\
    \        if(c > 0) return nullopt;\n        if(c < 0) {\n          for(int i =\
    \ 1; i < (int) vs.size(); i++) {\n            int x = vs[i - 1], y = vs[i];\n\
    \            int a = max(x, ~x), b = max(y, ~y);\n            if((x >= 0) ^ (y\
    \ >= 0)) {\n              uf.unite(a, b + n);\n              uf.unite(a + n, b);\n\
    \            } else {\n              uf.unite(a, b);\n              uf.unite(a\
    \ + n, b + n);\n            }\n          }\n        }\n      }\n      for(int\
    \ i = 0; i < n; i++) {\n        int x = uf.find(i);\n        int y = uf.find(i\
    \ + n);\n        if(x == y) return nullopt;\n        if(flip[x] < 0) {\n     \
    \     flip[x] = 0;\n          flip[y] = 1;\n        }\n      }\n      for(int\
    \ i = 0; i < n; i++) {\n        if(flip[i] < 0) {\n          flip[i] = flip[uf.find(i)];\n\
    \        }\n      }\n      flip.resize(n);\n    }\n    {\n      for(int i = 0;\
    \ i < n; i++) {\n        for(auto&[j, cs]: phi[i]) {\n          if(flip[i]) {\n\
    \            swap(cs[0], cs[2]);\n            swap(cs[1], cs[3]);\n          }\n\
    \          if(flip[j]) {\n            swap(cs[0], cs[1]);\n            swap(cs[2],\
    \ cs[3]);\n          }\n          T c = -cs[0] + cs[1] + cs[2] - cs[3];\n    \
    \      alpha += cs[0];\n          theta[i][not flip[i]] += cs[2] - cs[0];\n  \
    \        theta[j][not flip[j]] += cs[3] - cs[2];\n          cs[1] = c;\n     \
    \     cs[0] = cs[2] = cs[3] = 0;\n        }\n      }\n    }\n    {\n      for(int\
    \ i = 0; i < n; i++) {\n        auto &cs = theta[i];\n        if(flip[i]) {\n\
    \          swap(cs[0], cs[1]);\n        }\n        if(cs[0] <= cs[1]) {\n    \
    \      alpha += cs[0];\n          cs[1] -= cs[0];\n          cs[0] = 0;\n    \
    \    } else {\n          alpha += cs[1];\n          cs[0] -= cs[1];\n        \
    \  cs[1] = 0;\n        }\n      }\n    }\n\n    MaxFlow flow(n + 2 + zeta.size());\n\
    \    int s = n, t = n + 1;\n    {\n      for(int i = 0; i < n; i++) {\n      \
    \  auto &cs = theta[i];\n        if(cs[1] > 0) {\n          flow.add_edge(i, t,\
    \ cs[1]);\n        }\n        if(cs[0] > 0) {\n          flow.add_edge(s, i, cs[0]);\n\
    \        }\n      }\n      for(int i = 0; i < n; i++) {\n        for(auto&[j,\
    \ cs]: phi[i]) {\n          if(cs[2] > 0) {\n            flow.add_edge(i, j, cs[2]);\n\
    \          }\n          if(cs[1] > 0) {\n            flow.add_edge(j, i, cs[1]);\n\
    \          }\n        }\n      }\n      int u = t + 1;\n      for(auto&[vs, c]:\
    \ zeta) {\n        if(c < 0) {\n          if((vs[0] >= 0) ^ flip[max(~vs[0], vs[0])])\
    \ {\n            flow.add_edge(s, u, -c);\n            for(auto &p: vs) flow.add_edge(u,\
    \ max(p, ~p), -c);\n          } else {\n            for(auto &p: vs) flow.add_edge(max(p,\
    \ ~p), u, -c);\n            flow.add_edge(u, t, -c);\n          }\n          alpha\
    \ += c;\n          u++;\n        }\n      }\n    }\n    T ans = flow.max_flow(s,\
    \ t) + alpha;\n    vector< bool > cut = flow.min_cut(s);\n    for(int i = 0; i\
    \ < n; i++) {\n      if(flip[i]) cut[i] = 1 - cut[i];\n    }\n    cut.resize(n);\n\
    \    return make_pair(minimize ? ans : -ans, cut);\n  }\n};\n"
  dependsOn:
  - structure/union-find/union-find.hpp
  - graph/flow/dinic.hpp
  isVerificationFile: false
  path: graph/flow/burn-bury.hpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/flow/burn-bury.hpp
layout: document
redirect_from:
- /library/graph/flow/burn-bury.hpp
- /library/graph/flow/burn-bury.hpp.html
title: "Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\u308B)"
---
