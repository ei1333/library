---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/dinic-capacity-scaling.hpp
    title: "Dinic Capacity Scaling(\u6700\u5927\u6D41)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
  bundledCode: "#line 1 \"test/verify/aoj-grl-6-a-4.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\n\n#line 1\
    \ \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
    \nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL\
    \ << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-6-a-4.test.cpp\"\
    \n\n#line 1 \"graph/flow/dinic-capacity-scaling.hpp\"\n/**\n * @brief Dinic Capacity\
    \ Scaling(\u6700\u5927\u6D41)\n * @docs docs/dinic-capacity-scaling.md\n */\n\
    template< typename flow_t >\nstruct DinicCapacityScaling {\n  static_assert(is_integral<\
    \ flow_t >::value, \"template parameter flow_t must be integral type\");\n\n \
    \ const flow_t INF;\n\n  struct edge {\n    int to;\n    flow_t cap;\n    int\
    \ rev;\n    bool isrev;\n    int idx;\n  };\n\n  vector< vector< edge > > graph;\n\
    \  vector< int > min_cost, iter;\n  flow_t max_cap;\n\n  explicit DinicCapacityScaling(int\
    \ V) : INF(numeric_limits< flow_t >::max()), graph(V), max_cap(0) {}\n\n  void\
    \ add_edge(int from, int to, flow_t cap, int idx = -1) {\n    max_cap = max(max_cap,\
    \ cap);\n    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(),\
    \ false, idx});\n    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size()\
    \ - 1, true, idx});\n  }\n\n  bool build_augment_path(int s, int t, const flow_t\
    \ &base) {\n    min_cost.assign(graph.size(), -1);\n    queue< int > que;\n  \
    \  min_cost[s] = 0;\n    que.push(s);\n    while(!que.empty() && min_cost[t] ==\
    \ -1) {\n      int p = que.front();\n      que.pop();\n      for(auto &e : graph[p])\
    \ {\n        if(e.cap >= base && min_cost[e.to] == -1) {\n          min_cost[e.to]\
    \ = min_cost[p] + 1;\n          que.push(e.to);\n        }\n      }\n    }\n \
    \   return min_cost[t] != -1;\n  }\n\n  flow_t find_augment_path(int idx, const\
    \ int t, flow_t base, flow_t flow) {\n    if(idx == t) return flow;\n    flow_t\
    \ sum = 0;\n    for(int &i = iter[idx]; i < (int)graph[idx].size(); i++) {\n \
    \     edge &e = graph[idx][i];\n      if(e.cap >= base && min_cost[idx] < min_cost[e.to])\
    \ {\n        flow_t d = find_augment_path(e.to, t, base, min(flow - sum, e.cap));\n\
    \        if(d > 0) {\n          e.cap -= d;\n          graph[e.to][e.rev].cap\
    \ += d;\n          sum += d;\n          if(flow - sum < base) break;\n       \
    \ }\n      }\n    }\n    return sum;\n  }\n\n  flow_t max_flow(int s, int t) {\n\
    \    if(max_cap == flow_t(0)) return flow_t(0);\n    flow_t flow = 0;\n    for(int\
    \ i = 63 - __builtin_clzll(max_cap); i >= 0; i--) {\n      flow_t now = flow_t(1)\
    \ << i;\n      while(build_augment_path(s, t, now)) {\n        iter.assign(graph.size(),\
    \ 0);\n        flow += find_augment_path(s, t, now, INF);\n      }\n    }\n  \
    \  return flow;\n  }\n\n  void output() {\n    for(int i = 0; i < graph.size();\
    \ i++) {\n      for(auto &e : graph[i]) {\n        if(e.isrev) continue;\n   \
    \     auto &rev_e = graph[e.to][e.rev];\n        cout << i << \"->\" << e.to <<\
    \ \" (flow: \" << rev_e.cap << \"/\" << e.cap + rev_e.cap << \")\" << endl;\n\
    \      }\n    }\n  }\n};\n#line 6 \"test/verify/aoj-grl-6-a-4.test.cpp\"\n\nint\
    \ main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  DinicCapacityScaling<\
    \ int > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"\
    %d %d %d\", &a, &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0,\
    \ V - 1));\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/dinic-capacity-scaling.hpp\"\
    \n\nint main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  DinicCapacityScaling<\
    \ int > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"\
    %d %d %d\", &a, &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0,\
    \ V - 1));\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/dinic-capacity-scaling.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-6-a-4.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-6-a-4.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-6-a-4.test.cpp
- /verify/test/verify/aoj-grl-6-a-4.test.cpp.html
title: test/verify/aoj-grl-6-a-4.test.cpp
---
