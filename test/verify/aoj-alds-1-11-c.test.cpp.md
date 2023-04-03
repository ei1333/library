---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/bfs.hpp
    title: "BFS(\u5E45\u512A\u5148\u63A2\u7D22)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C
  bundledCode: "#line 1 \"test/verify/aoj-alds-1-11-c.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C\"\n\n\
    #line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-alds-1-11-c.test.cpp\"\
    \n\n#line 2 \"graph/shortest-path/bfs.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
    \n\n/**\n * @brief Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\
    \u30C8)\n */\ntemplate< typename T = int >\nstruct Edge {\n  int from, to;\n \
    \ T cost;\n  int idx;\n\n  Edge() = default;\n\n  Edge(int from, int to, T cost\
    \ = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}\n\n  operator\
    \ int() const { return to; }\n};\n\ntemplate< typename T = int >\nstruct Graph\
    \ {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n  Graph() = default;\n\n\
    \  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t size() const {\n    return\
    \ g.size();\n  }\n\n  void add_directed_edge(int from, int to, T cost = 1) {\n\
    \    g[from].emplace_back(from, to, cost, es++);\n  }\n\n  void add_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es);\n    g[to].emplace_back(to,\
    \ from, cost, es++);\n  }\n\n  void read(int M, int padding = -1, bool weighted\
    \ = false, bool directed = false) {\n    for(int i = 0; i < M; i++) {\n      int\
    \ a, b;\n      cin >> a >> b;\n      a += padding;\n      b += padding;\n    \
    \  T c = T(1);\n      if(weighted) cin >> c;\n      if(directed) add_directed_edge(a,\
    \ b, c);\n      else add_edge(a, b, c);\n    }\n  }\n\n  inline vector< Edge<\
    \ T > > &operator[](const int &k) {\n    return g[k];\n  }\n\n  inline const vector<\
    \ Edge< T > > &operator[](const int &k) const {\n    return g[k];\n  }\n};\n\n\
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/bfs.hpp\"\
    \n\n/**\n * @brief BFS(\u5E45\u512A\u5148\u63A2\u7D22)\n */\ntemplate< typename\
    \ T >\nvector< T > bfs(const Graph< T > &g, int s) {\n  T max_cost = 0, beet =\
    \ 0;\n  for(auto &es : g.g) {\n    for(auto &e : es) max_cost = max(max_cost,\
    \ e.cost);\n  }\n  ++max_cost;\n  const auto INF = numeric_limits< T >::max();\n\
    \  vector< T > dist(g.size(), INF);\n  vector< queue< int > > ques(max_cost +\
    \ 1);\n  dist[s] = 0;\n  ques[0].emplace(s);\n  for(T cost = 0; cost <= beet;\
    \ cost++) {\n    auto &que = ques[cost % max_cost];\n    while(!que.empty()) {\n\
    \      int idx = que.front();\n      que.pop();\n      if(dist[idx] < cost) continue;\n\
    \      for(auto &e : g[idx]) {\n        auto next_cost = cost + e.cost;\n    \
    \    if(dist[e.to] <= next_cost) continue;;\n        dist[e.to] = next_cost;\n\
    \        beet = max(beet, dist[e.to]);\n        ques[dist[e.to] % max_cost].emplace(e.to);\n\
    \      }\n    }\n  }\n  return dist;\n}\n#line 6 \"test/verify/aoj-alds-1-11-c.test.cpp\"\
    \n\n\nint main() {\n  int N;\n  cin >> N;\n  Graph<> g(N);\n  for(int i = 0; i\
    \ < N; i++) {\n    int U, K;\n    cin >> U >> K;\n    --U;\n    for(int j = 0;\
    \ j < K; j++) {\n      int x;\n      cin >> x;\n      --x;\n      g.add_directed_edge(U,\
    \ x);\n    }\n  }\n  auto d = bfs(g, 0);\n  for(int i = 0; i < N; i++) {\n   \
    \ cout << i + 1 << \" \";\n    if(d[i] == numeric_limits< int >::max()) cout <<\
    \ -1 << \"\\n\";\n    else cout << d[i] << \"\\n\";\n  }\n}\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/shortest-path/bfs.hpp\"\
    \n\n\nint main() {\n  int N;\n  cin >> N;\n  Graph<> g(N);\n  for(int i = 0; i\
    \ < N; i++) {\n    int U, K;\n    cin >> U >> K;\n    --U;\n    for(int j = 0;\
    \ j < K; j++) {\n      int x;\n      cin >> x;\n      --x;\n      g.add_directed_edge(U,\
    \ x);\n    }\n  }\n  auto d = bfs(g, 0);\n  for(int i = 0; i < N; i++) {\n   \
    \ cout << i + 1 << \" \";\n    if(d[i] == numeric_limits< int >::max()) cout <<\
    \ -1 << \"\\n\";\n    else cout << d[i] << \"\\n\";\n  }\n}\n\n"
  dependsOn:
  - template/template.hpp
  - graph/shortest-path/bfs.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/aoj-alds-1-11-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-alds-1-11-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-alds-1-11-c.test.cpp
- /verify/test/verify/aoj-alds-1-11-c.test.cpp.html
title: test/verify/aoj-alds-1-11-c.test.cpp
---
