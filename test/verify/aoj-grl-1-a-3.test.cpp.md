---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/dijkstra-radix-heap.hpp
    title: "Dijkstra-Radix-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: structure/heap/radix-heap.hpp
    title: structure/heap/radix-heap.hpp
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
  bundledCode: "#line 1 \"test/verify/aoj-grl-1-a-3.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\n\n#line 1\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-1-a-3.test.cpp\"\
    \n\n#line 1 \"structure/heap/radix-heap.hpp\"\ntemplate< typename key_t, typename\
    \ val_t >\nstruct RadixHeap {\n  static constexpr int bit = sizeof(key_t) * 8;\n\
    \  array< vector< pair< key_t, val_t > >, bit > vs;\n\n  size_t sz;\n  key_t last;\n\
    \n  RadixHeap() : sz(0), last(0) {}\n\n  bool empty() const { return sz == 0;\
    \ }\n\n  size_t size() const { return sz; }\n\n  inline int getbit(int a) const\
    \ {\n    return a ? bit - __builtin_clz(a) : 0;\n  }\n\n  inline int getbit(int64_t\
    \ a) const {\n    return a ? bit - __builtin_clzll(a) : 0;\n  }\n\n  void push(const\
    \ key_t &key, const val_t &val) {\n    sz++;\n    vs[getbit(key ^ last)].emplace_back(key,\
    \ val);\n  }\n\n  pair< key_t, val_t > pop() {\n    if(vs[0].empty()) {\n    \
    \  int idx = 1;\n      while(vs[idx].empty()) idx++;\n      last = min_element(vs[idx].begin(),\
    \ vs[idx].end())->first;\n      for(auto &p:vs[idx]) vs[getbit(p.first ^ last)].emplace_back(p);\n\
    \      vs[idx].clear();\n    }\n    --sz;\n    auto res = vs[0].back();\n    vs[0].pop_back();\n\
    \    return res;\n  }\n};\n#line 6 \"test/verify/aoj-grl-1-a-3.test.cpp\"\n\n\
    #line 2 \"graph/shortest-path/dijkstra-radix-heap.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/shortest-path/dijkstra-radix-heap.hpp\"\
    \n\n/**\n * @brief Dijkstra-Radix-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\
    )\n */\ntemplate< typename T >\nvector< T > dijkstra_radix_heap(Graph< T > &g,\
    \ int s) {\n  const auto INF = numeric_limits< T >::max();\n  vector< T > dist(g.size(),\
    \ INF);\n\n  RadixHeap< T, int > heap;\n  dist[s] = 0;\n  heap.push(dist[s], s);\n\
    \  while(!heap.empty()) {\n    T cost;\n    int idx;\n    tie(cost, idx) = heap.pop();\n\
    \    if(dist[idx] < cost) continue;\n    for(auto &e : g.g[idx]) {\n      auto\
    \ next_cost = cost + e.cost;\n      if(dist[e.to] <= next_cost) continue;\n  \
    \    dist[e.to] = next_cost;\n      heap.push(dist[e.to], e.to);\n    }\n  }\n\
    \  return dist;\n}\n#line 8 \"test/verify/aoj-grl-1-a-3.test.cpp\"\n\nint main()\
    \ {\n  int V, E, R;\n  cin >> V >> E >> R;\n  Graph< int > g(V);\n  g.read(E,\
    \ 0, true, true);\n  for(auto &dist : dijkstra_radix_heap(g, R)) {\n    if(dist\
    \ == numeric_limits< int >::max()) cout << \"INF\\n\";\n    else cout << dist\
    \ << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/heap/radix-heap.hpp\"\
    \n\n#include \"../../graph/shortest-path/dijkstra-radix-heap.hpp\"\n\nint main()\
    \ {\n  int V, E, R;\n  cin >> V >> E >> R;\n  Graph< int > g(V);\n  g.read(E,\
    \ 0, true, true);\n  for(auto &dist : dijkstra_radix_heap(g, R)) {\n    if(dist\
    \ == numeric_limits< int >::max()) cout << \"INF\\n\";\n    else cout << dist\
    \ << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/heap/radix-heap.hpp
  - graph/shortest-path/dijkstra-radix-heap.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-1-a-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-1-a-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-1-a-3.test.cpp
- /verify/test/verify/aoj-grl-1-a-3.test.cpp.html
title: test/verify/aoj-grl-1-a-3.test.cpp
---
