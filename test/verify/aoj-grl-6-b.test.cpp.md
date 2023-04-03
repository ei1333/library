---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/primal-dual.hpp
    title: "Primal Dual(\u6700\u5C0F\u8CBB\u7528\u6D41)"
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
  bundledCode: "#line 1 \"test/verify/aoj-grl-6-b.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll\
    \ = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
    \ {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed\
    \ << setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
    \ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream &os, const\
    \ pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream &is, pair<\
    \ T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename\
    \ T >\nostream &operator<<(ostream &os, const vector< T > &v) {\n  for(int i =\
    \ 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \"\
    \ : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream\
    \ &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate<\
    \ typename T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b &&\
    \ (a = b, true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64\
    \ >\nvector< T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate<\
    \ typename T, typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector<\
    \ decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename\
    \ T, typename V >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T\
    \ &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename\
    \ enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto\
    \ &e : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n\
    \  explicit FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename...\
    \ Args >\n  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-6-b.test.cpp\"\
    \n\n#line 1 \"graph/flow/primal-dual.hpp\"\n/**\n * @brief Primal Dual(\u6700\u5C0F\
    \u8CBB\u7528\u6D41)\n * @docs docs/primal-dual.md\n */\ntemplate< typename flow_t,\
    \ typename cost_t >\nstruct PrimalDual {\n  struct edge {\n    int to;\n    flow_t\
    \ cap;\n    cost_t cost;\n    int rev;\n    bool isrev;\n  };\n\n  vector< vector<\
    \ edge > > graph;\n  vector< cost_t > potential, min_cost;\n  vector< int > prevv,\
    \ preve;\n  const cost_t INF;\n\n  PrimalDual(int V) : graph(V), INF(numeric_limits<\
    \ cost_t >::max()) {}\n\n  void add_edge(int from, int to, flow_t cap, cost_t\
    \ cost) {\n    graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(),\
    \ false});\n    graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size()\
    \ - 1, true});\n  }\n\n  cost_t min_cost_flow(int s, int t, flow_t f) {\n    int\
    \ V = (int) graph.size();\n    cost_t ret = 0;\n    using Pi = pair< cost_t, int\
    \ >;\n    priority_queue< Pi, vector< Pi >, greater< Pi > > que;\n    potential.assign(V,\
    \ 0);\n    preve.assign(V, -1);\n    prevv.assign(V, -1);\n\n    while(f > 0)\
    \ {\n      min_cost.assign(V, INF);\n      que.emplace(0, s);\n      min_cost[s]\
    \ = 0;\n      while(!que.empty()) {\n        Pi p = que.top();\n        que.pop();\n\
    \        if(min_cost[p.second] < p.first) continue;\n        for(int i = 0; i\
    \ < (int)graph[p.second].size(); i++) {\n          edge &e = graph[p.second][i];\n\
    \          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second]\
    \ - potential[e.to];\n          if(e.cap > 0 && min_cost[e.to] > nextCost) {\n\
    \            min_cost[e.to] = nextCost;\n            prevv[e.to] = p.second, preve[e.to]\
    \ = i;\n            que.emplace(min_cost[e.to], e.to);\n          }\n        }\n\
    \      }\n      if(min_cost[t] == INF) return -1;\n      for(int v = 0; v < V;\
    \ v++) potential[v] += min_cost[v];\n      flow_t addflow = f;\n      for(int\
    \ v = t; v != s; v = prevv[v]) {\n        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);\n\
    \      }\n      f -= addflow;\n      ret += addflow * potential[t];\n      for(int\
    \ v = t; v != s; v = prevv[v]) {\n        edge &e = graph[prevv[v]][preve[v]];\n\
    \        e.cap -= addflow;\n        graph[v][e.rev].cap += addflow;\n      }\n\
    \    }\n    return ret;\n  }\n\n  void output() {\n    for(int i = 0; i < graph.size();\
    \ i++) {\n      for(auto &e : graph[i]) {\n        if(e.isrev) continue;\n   \
    \     auto &rev_e = graph[e.to][e.rev];\n        cout << i << \"->\" << e.to <<\
    \ \" (flow: \" << rev_e.cap << \"/\" << rev_e.cap + e.cap << \")\" << endl;\n\
    \      }\n    }\n  }\n};\n#line 6 \"test/verify/aoj-grl-6-b.test.cpp\"\n\nint\
    \ main() {\n  int V, E, F;\n  scanf(\"%d %d %d\", &V, &E, &F);\n  PrimalDual<\
    \ int, int > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c, d;\n    scanf(\"\
    %d %d %d %d\", &a, &b, &c, &d);\n    g.add_edge(a, b, c, d);\n  }\n  printf(\"\
    %d\\n\", g.min_cost_flow(0, V - 1, F));\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/primal-dual.hpp\"\
    \n\nint main() {\n  int V, E, F;\n  scanf(\"%d %d %d\", &V, &E, &F);\n  PrimalDual<\
    \ int, int > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c, d;\n    scanf(\"\
    %d %d %d %d\", &a, &b, &c, &d);\n    g.add_edge(a, b, c, d);\n  }\n  printf(\"\
    %d\\n\", g.min_cost_flow(0, V - 1, F));\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/primal-dual.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-6-b.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-6-b.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-6-b.test.cpp
- /verify/test/verify/aoj-grl-6-b.test.cpp.html
title: test/verify/aoj-grl-6-b.test.cpp
---
