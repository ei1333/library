---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/ford-fulkerson.hpp
    title: "Ford Fulkerson(\u6700\u5927\u6D41)"
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
  bundledCode: "#line 1 \"test/verify/aoj-grl-6-a-2.test.cpp\"\n#define PROBLEM \"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-6-a-2.test.cpp\"\
    \n\n#line 1 \"graph/flow/ford-fulkerson.hpp\"\n/**\n * @brief Ford Fulkerson(\u6700\
    \u5927\u6D41)\n * @docs docs/ford-fulkerson.md\n */\ntemplate< typename flow_t\
    \ >\nstruct FordFulkerson {\n  struct edge {\n    int to;\n    flow_t cap;\n \
    \   int rev;\n    bool isrev;\n    int idx;\n  };\n\n  const flow_t INF;\n  vector<\
    \ vector< edge > > graph;\n  vector< int > used;\n  int timestamp;\n\n  explicit\
    \ FordFulkerson(int V) : INF(numeric_limits< flow_t >::max()), graph(V), used(V,\
    \ -1), timestamp(0) {}\n\n  void add_edge(int from, int to, flow_t cap, int idx\
    \ = -1) {\n    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(),\
    \ false, idx});\n    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size()\
    \ - 1, true, idx});\n  }\n\n  flow_t find_augment_path(int idx, const int t, flow_t\
    \ flow) {\n    if(idx == t) return flow;\n    used[idx] = timestamp;\n    for(auto\
    \ &e : graph[idx]) {\n      if(e.cap > 0 && used[e.to] != timestamp) {\n     \
    \   flow_t d = find_augment_path(e.to, t, min(flow, e.cap));\n        if(d > 0)\
    \ {\n          e.cap -= d;\n          graph[e.to][e.rev].cap += d;\n         \
    \ return d;\n        }\n      }\n    }\n    return 0;\n  }\n\n  flow_t max_flow(int\
    \ s, int t) {\n    flow_t flow = 0;\n    for(flow_t f; (f = find_augment_path(s,\
    \ t, INF)) > 0; timestamp++) {\n      flow += f;\n    }\n    timestamp++;\n  \
    \  return flow;\n  }\n\n  void output() {\n    for(int i = 0; i < graph.size();\
    \ i++) {\n      for(auto &e : graph[i]) {\n        if(e.isrev) continue;\n   \
    \     auto &rev_e = graph[e.to][e.rev];\n        cout << i << \"->\" << e.to <<\
    \ \" (flow: \" << rev_e.cap << \"/\" << e.cap + rev_e.cap << \")\" << endl;\n\
    \      }\n    }\n  }\n};\n#line 6 \"test/verify/aoj-grl-6-a-2.test.cpp\"\n\nint\
    \ main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  FordFulkerson< int > g(V);\n\
    \  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"%d %d %d\", &a,\
    \ &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0, V\
    \ - 1));\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/ford-fulkerson.hpp\"\
    \n\nint main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  FordFulkerson< int\
    \ > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"%d %d\
    \ %d\", &a, &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0,\
    \ V - 1));\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/ford-fulkerson.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-6-a-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-6-a-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-6-a-2.test.cpp
- /verify/test/verify/aoj-grl-6-a-2.test.cpp.html
title: test/verify/aoj-grl-6-a-2.test.cpp
---
