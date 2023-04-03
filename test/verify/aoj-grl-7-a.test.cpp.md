---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/bipartite-matching.hpp
    title: "Bipartite-Matching(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\
      \u30C3\u30C1\u30F3\u30B0)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
  bundledCode: "#line 1 \"test/verify/aoj-grl-7-a.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-7-a.test.cpp\"\
    \n\n#line 1 \"graph/flow/bipartite-matching.hpp\"\n/**\n * @brief Bipartite-Matching(\u4E8C\
    \u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0)\n *\
    \ @docs docs/bipartite-matching.md\n */\nstruct BipartiteMatching {\n  vector<\
    \ vector< int > > graph;\n  vector< int > alive, used, match;\n  int timestamp;\n\
    \n  explicit BipartiteMatching(int n) : graph(n), alive(n, 1), used(n, 0), match(n,\
    \ -1), timestamp(0) {}\n\n  void add_edge(int u, int v) {\n    graph[u].push_back(v);\n\
    \    graph[v].push_back(u);\n  }\n\n  bool augment(int idx) {\n    used[idx] =\
    \ timestamp;\n    for(auto &to : graph[idx]) {\n      int to_match = match[to];\n\
    \      if(alive[to] == 0) continue;\n      if(to_match == -1 || (used[to_match]\
    \ != timestamp && augment(to_match))) {\n        match[idx] = to;\n        match[to]\
    \ = idx;\n        return true;\n      }\n    }\n    return false;\n  }\n\n  int\
    \ bipartite_matching() {\n    int ret = 0;\n    for(int i = 0; i < (int) graph.size();\
    \ i++) {\n      if(alive[i] == 0) continue;\n      if(match[i] == -1) {\n    \
    \    ++timestamp;\n        ret += augment(i);\n      }\n    }\n    return ret;\n\
    \  }\n\n  int add_vertex(int idx) {\n    alive[idx] = 1;\n    ++timestamp;\n \
    \   return augment(idx);\n  }\n\n  int erase_vertex(int idx) {\n    alive[idx]\
    \ = 0;\n    if(match[idx] == -1) {\n      return 0;\n    }\n    match[match[idx]]\
    \ = -1;\n    ++timestamp;\n    int ret = augment(match[idx]);\n    match[idx]\
    \ = -1;\n    return ret - 1;\n  }\n\n  void output() const {\n    for(int i =\
    \ 0; i < (int) graph.size(); i++) {\n      if(i < match[i]) {\n        cout <<\
    \ i << \"-\" << match[i] << endl;\n      }\n    }\n  }\n};\n#line 6 \"test/verify/aoj-grl-7-a.test.cpp\"\
    \n\nint main() {\n  int X, Y, E;\n  scanf(\"%d %d %d\", &X, &Y, &E);\n  BipartiteMatching\
    \ bm(X + Y);\n  for(int i = 0; i < E; i++) {\n    int a, b;\n    scanf(\"%d %d\"\
    , &a, &b);\n    bm.add_edge(a, X + b);\n  }\n  printf(\"%d\\n\", bm.bipartite_matching());\n\
    }\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/bipartite-matching.hpp\"\
    \n\nint main() {\n  int X, Y, E;\n  scanf(\"%d %d %d\", &X, &Y, &E);\n  BipartiteMatching\
    \ bm(X + Y);\n  for(int i = 0; i < E; i++) {\n    int a, b;\n    scanf(\"%d %d\"\
    , &a, &b);\n    bm.add_edge(a, X + b);\n  }\n  printf(\"%d\\n\", bm.bipartite_matching());\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/bipartite-matching.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-7-a.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-7-a.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-7-a.test.cpp
- /verify/test/verify/aoj-grl-7-a.test.cpp.html
title: test/verify/aoj-grl-7-a.test.cpp
---
