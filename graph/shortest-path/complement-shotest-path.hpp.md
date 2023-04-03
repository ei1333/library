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
    document_title: "Complement-Shortest-Path(\u88DC\u30B0\u30E9\u30D5\u6700\u77ED\
      \u8DEF)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/complement-shotest-path.hpp\"\n\n#line\
    \ 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\u30E9\
    \u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T = int >\n\
    struct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
    \n  Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost),\
    \ idx(idx) {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename\
    \ T = int >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n\
    \  Graph() = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t\
    \ size() const {\n    return g.size();\n  }\n\n  void add_directed_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\
    \n  void add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from,\
    \ to, cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void\
    \ read(int M, int padding = -1, bool weighted = false, bool directed = false)\
    \ {\n    for(int i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n\
    \      a += padding;\n      b += padding;\n      T c = T(1);\n      if(weighted)\
    \ cin >> c;\n      if(directed) add_directed_edge(a, b, c);\n      else add_edge(a,\
    \ b, c);\n    }\n  }\n\n  inline vector< Edge< T > > &operator[](const int &k)\
    \ {\n    return g[k];\n  }\n\n  inline const vector< Edge< T > > &operator[](const\
    \ int &k) const {\n    return g[k];\n  }\n};\n\ntemplate< typename T = int >\n\
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/complement-shotest-path.hpp\"\
    \n\n/**\n * @brief Complement-Shortest-Path(\u88DC\u30B0\u30E9\u30D5\u6700\u77ED\
    \u8DEF)\n */\ntemplate< typename T >\nstruct ComplementShortestPath : Graph< T\
    \ > {\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n\n  vector< vector<\
    \ T > > dists;\n\n  void build() {\n    for(auto &es : g) {\n      sort(begin(es),\
    \ end(es), [&](const Edge< T > &a, const Edge< T > &b) {\n        return a.to\
    \ < b.to;\n      });\n    }\n    const int N = (int) g.size();\n    dists.resize(N);\n\
    \    for(int i = 0; i < N; i++) {\n      if((int) g[i].size() >= N / 2 - 1) {\n\
    \        dists[i] = complement_bfs(i);\n      }\n    }\n  }\n\n  T query(int s,\
    \ int t) const {\n    if(!dists[s].empty()) {\n      return dists[s][t];\n   \
    \ } else if(!dists[t].empty()) {\n      return dists[t][s];\n    } else if([&]()\
    \ -> bool {\n      int ok = 0, ng = (int) g[s].size();\n      while(ng - ok >\
    \ 1) {\n        int mid = (ok + ng) >> 1;\n        if(g[s][mid].to <= t) ok =\
    \ mid;\n        else ng = mid;\n      }\n      return ok < (int) g[s].size() and\
    \ g[s][ok].to == t;\n    }()) {\n      return 2;\n    } else {\n      return 1;\n\
    \    }\n  }\n\n  vector< T > complement_bfs(int s) {\n    vector< T > dist(g.size(),\
    \ -1);\n    queue< int > que;\n    dist[s] = 0;\n    que.emplace(s);\n    vector<\
    \ int > not_visited;\n    for(int i = 0; i < g.size(); i++) {\n      if(s != i)\
    \ {\n        not_visited.emplace_back(i);\n      }\n    }\n    while(!que.empty())\
    \ {\n      int idx = que.front();\n      que.pop();\n      int ptr = 0;\n    \
    \  vector< int > nxt_visited;\n      for(auto &to : not_visited) {\n        while(ptr\
    \ < (int) g[idx].size() and g[idx][ptr].to < to) {\n          ++ptr;\n       \
    \ }\n        if(ptr < (int) g[idx].size() and to == g[idx][ptr].to) {\n      \
    \    nxt_visited.emplace_back(to);\n        } else {\n          dist[to] = dist[idx]\
    \ + 1;\n          que.emplace(to);\n        }\n      }\n      not_visited = move(nxt_visited);\n\
    \    }\n    return dist;\n  }\n};\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n\n/**\n * @brief Complement-Shortest-Path(\u88DC\
    \u30B0\u30E9\u30D5\u6700\u77ED\u8DEF)\n */\ntemplate< typename T >\nstruct ComplementShortestPath\
    \ : Graph< T > {\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n\n  vector<\
    \ vector< T > > dists;\n\n  void build() {\n    for(auto &es : g) {\n      sort(begin(es),\
    \ end(es), [&](const Edge< T > &a, const Edge< T > &b) {\n        return a.to\
    \ < b.to;\n      });\n    }\n    const int N = (int) g.size();\n    dists.resize(N);\n\
    \    for(int i = 0; i < N; i++) {\n      if((int) g[i].size() >= N / 2 - 1) {\n\
    \        dists[i] = complement_bfs(i);\n      }\n    }\n  }\n\n  T query(int s,\
    \ int t) const {\n    if(!dists[s].empty()) {\n      return dists[s][t];\n   \
    \ } else if(!dists[t].empty()) {\n      return dists[t][s];\n    } else if([&]()\
    \ -> bool {\n      int ok = 0, ng = (int) g[s].size();\n      while(ng - ok >\
    \ 1) {\n        int mid = (ok + ng) >> 1;\n        if(g[s][mid].to <= t) ok =\
    \ mid;\n        else ng = mid;\n      }\n      return ok < (int) g[s].size() and\
    \ g[s][ok].to == t;\n    }()) {\n      return 2;\n    } else {\n      return 1;\n\
    \    }\n  }\n\n  vector< T > complement_bfs(int s) {\n    vector< T > dist(g.size(),\
    \ -1);\n    queue< int > que;\n    dist[s] = 0;\n    que.emplace(s);\n    vector<\
    \ int > not_visited;\n    for(int i = 0; i < g.size(); i++) {\n      if(s != i)\
    \ {\n        not_visited.emplace_back(i);\n      }\n    }\n    while(!que.empty())\
    \ {\n      int idx = que.front();\n      que.pop();\n      int ptr = 0;\n    \
    \  vector< int > nxt_visited;\n      for(auto &to : not_visited) {\n        while(ptr\
    \ < (int) g[idx].size() and g[idx][ptr].to < to) {\n          ++ptr;\n       \
    \ }\n        if(ptr < (int) g[idx].size() and to == g[idx][ptr].to) {\n      \
    \    nxt_visited.emplace_back(to);\n        } else {\n          dist[to] = dist[idx]\
    \ + 1;\n          que.emplace(to);\n        }\n      }\n      not_visited = move(nxt_visited);\n\
    \    }\n    return dist;\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/shortest-path/complement-shotest-path.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/shortest-path/complement-shotest-path.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/complement-shotest-path.hpp
- /library/graph/shortest-path/complement-shotest-path.hpp.html
title: "Complement-Shortest-Path(\u88DC\u30B0\u30E9\u30D5\u6700\u77ED\u8DEF)"
---
