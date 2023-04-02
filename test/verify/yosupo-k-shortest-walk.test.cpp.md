---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/dijkstra.hpp
    title: "Dijkstra(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/k-shortest-walk.hpp
    title: K-Shortest-Walk
  - icon: ':heavy_check_mark:'
    path: structure/heap/leftist-heap.hpp
    title: Leftist-Heap
  - icon: ':heavy_check_mark:'
    path: structure/heap/persistent-leftist-heap.hpp
    title: Persistent-Leftist-Heap
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/k_shortest_walk
    links:
    - https://judge.yosupo.jp/problem/k_shortest_walk
  bundledCode: "#line 1 \"test/verify/yosupo-k-shortest-walk.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-k-shortest-walk.test.cpp\"\
    \n\n#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
    \u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T =\
    \ int >\nstruct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"graph/shortest-path/dijkstra.hpp\"\
    \n\n#line 4 \"graph/shortest-path/dijkstra.hpp\"\n\n/**\n * @brief Dijkstra(\u5358\
    \u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)\n * @docs docs/dijkstra.md\n */\ntemplate<\
    \ typename T >\nstruct ShortestPath {\n  vector< T > dist;\n  vector< int > from,\
    \ id;\n};\n\ntemplate< typename T >\nShortestPath< T > dijkstra(const Graph< T\
    \ > &g, int s) {\n  const auto INF = numeric_limits< T >::max();\n  vector< T\
    \ > dist(g.size(), INF);\n  vector< int > from(g.size(), -1), id(g.size(), -1);\n\
    \  using Pi = pair< T, int >;\n  priority_queue< Pi, vector< Pi >, greater<> >\
    \ que;\n  dist[s] = 0;\n  que.emplace(dist[s], s);\n  while(!que.empty()) {\n\
    \    T cost;\n    int idx;\n    tie(cost, idx) = que.top();\n    que.pop();\n\
    \    if(dist[idx] < cost) continue;\n    for(auto &e : g[idx]) {\n      auto next_cost\
    \ = cost + e.cost;\n      if(dist[e.to] <= next_cost) continue;\n      dist[e.to]\
    \ = next_cost;\n      from[e.to] = idx;\n      id[e.to] = e.idx;\n      que.emplace(dist[e.to],\
    \ e.to);\n    }\n  }\n  return {dist, from, id};\n}\n#line 7 \"test/verify/yosupo-k-shortest-walk.test.cpp\"\
    \n\n#line 1 \"structure/heap/leftist-heap.hpp\"\n/**\n * @brief Leftist-Heap\n\
    \ */\ntemplate< typename T, bool isMin = true >\nstruct LeftistHeap {\n  struct\
    \ Node {\n    Node *l, *r;\n    int s;\n    T key;\n    int idx;\n\n    explicit\
    \ Node(const T &key, int idx) : key(key), s(1), l(nullptr), r(nullptr), idx(idx)\
    \ {}\n  };\n\n  LeftistHeap() = default;\n\n  virtual Node *clone(Node *t) {\n\
    \    return t;\n  }\n\n  Node *alloc(const T &key, int idx = -1) {\n    return\
    \ new Node(key, idx);\n  }\n\n  Node *meld(Node *a, Node *b) {\n    if(!a || !b)\
    \ return a ? a : b;\n    if((a->key < b->key) ^ isMin) swap(a, b);\n    a = clone(a);\n\
    \    a->r = meld(a->r, b);\n    if(!a->l || a->l->s < a->r->s) swap(a->l, a->r);\n\
    \    a->s = (a->r ? a->r->s : 0) + 1;\n    return a;\n  }\n\n  Node *push(Node\
    \ *t, const T &key, int idx = -1) {\n    return meld(t, alloc(key, idx));\n  }\n\
    \n  Node *pop(Node *t) {\n    assert(t != nullptr);\n    return meld(t->l, t->r);\n\
    \  }\n\n  Node *make_root() {\n    return nullptr;\n  }\n};\n#line 1 \"structure/heap/persistent-leftist-heap.hpp\"\
    \n/**\n * @brief Persistent-Leftist-Heap\n */\ntemplate< typename T, bool isMin\
    \ = true >\nstruct PersistentLeftistHeap : LeftistHeap< T, isMin > {\n  using\
    \ Node = typename LeftistHeap< T, isMin >::Node;\n\n  Node *clone(Node *t) override\
    \ {\n    return new Node(*t);\n  }\n};\n#line 2 \"graph/shortest-path/k-shortest-walk.hpp\"\
    \n\n#line 4 \"graph/shortest-path/k-shortest-walk.hpp\"\n\n/**\n * @brief K-Shortest-Walk\n\
    \ * @docs docs/k-shortest-walk.md\n * @see https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e\n\
    \ */\ntemplate< typename T >\nvector< T > k_shortest_walk(const Graph< T > &g,\
    \ int s, int t, int k) {\n  int N = (int) g.size();\n  Graph< T > rg(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    for(auto &e : g[i]) rg.add_directed_edge(e.to, i,\
    \ e.cost);\n  }\n  auto dist = dijkstra(rg, t);\n  if(dist.from[s] == -1) return\
    \ {};\n  auto &p = dist.dist;\n  vector< vector< int > > ch(N);\n  for(int i =\
    \ 0; i < N; i++) {\n    if(dist.from[i] >= 0) ch[dist.from[i]].emplace_back(i);\n\
    \  }\n  using PHeap = PersistentLeftistHeap< T >;\n  using Node = typename PHeap::Node;\n\
    \  PHeap heap;\n  vector< Node * > h(N, heap.make_root());\n  {\n    queue< int\
    \ > que;\n    que.emplace(t);\n    while(!que.empty()) {\n      int idx = que.front();\n\
    \      que.pop();\n      if(dist.from[idx] >= 0) {\n        h[idx] = heap.meld(h[idx],\
    \ h[dist.from[idx]]);\n      }\n      bool used = true;\n      for(auto &e : g[idx])\
    \ {\n        if(e.to != t && dist.from[e.to] == -1) continue;\n        if(used\
    \ && dist.from[idx] == e.to && p[e.to] + e.cost == p[idx]) {\n          used =\
    \ false;\n          continue;\n        }\n        h[idx] = heap.push(h[idx], e.cost\
    \ - p[idx] + p[e.to], e.to);\n      }\n      for(auto &to : ch[idx]) que.emplace(to);\n\
    \    }\n  }\n  using pi = pair< T, Node * >;\n  auto comp = [](const pi &x, const\
    \ pi &y) { return x.first > y.first; };\n  priority_queue< pi, vector< pi >, decltype(comp)\
    \ > que(comp);\n  Node *root = heap.make_root();\n  root = heap.push(root, p[s],\
    \ s);\n  que.emplace(p[s], root);\n  vector< T > ans;\n  while(!que.empty()) {\n\
    \    T cost;\n    Node *cur;\n    tie(cost, cur) = que.top();\n    que.pop();\n\
    \    ans.emplace_back(cost);\n    if((int)ans.size() == k) break;\n    if(cur->l)\
    \ que.emplace(cost + cur->l->key - cur->key, cur->l);\n    if(cur->r) que.emplace(cost\
    \ + cur->r->key - cur->key, cur->r);\n    if(h[cur->idx]) que.emplace(cost + h[cur->idx]->key,\
    \ h[cur->idx]);\n  }\n  return ans;\n}\n#line 11 \"test/verify/yosupo-k-shortest-walk.test.cpp\"\
    \n\nint main() {\n  int N, M, S, T, K;\n  cin >> N >> M >> S >> T >> K;\n  Graph<\
    \ int64 > g(N);\n  g.read(M, 0, true, true);\n  auto ret = k_shortest_walk(g,\
    \ S, T, K);\n  for(int i = 0; i < K; i++) {\n    if(i >= (int)ret.size()) cout\
    \ << -1 << \"\\n\";\n    else cout << ret[i] << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../graph/graph-template.hpp\"\
    \n#include \"../../graph/shortest-path/dijkstra.hpp\"\n\n#include \"../../structure/heap/leftist-heap.hpp\"\
    \n#include \"../../structure/heap/persistent-leftist-heap.hpp\"\n#include \"../../graph/shortest-path/k-shortest-walk.hpp\"\
    \n\nint main() {\n  int N, M, S, T, K;\n  cin >> N >> M >> S >> T >> K;\n  Graph<\
    \ int64 > g(N);\n  g.read(M, 0, true, true);\n  auto ret = k_shortest_walk(g,\
    \ S, T, K);\n  for(int i = 0; i < K; i++) {\n    if(i >= (int)ret.size()) cout\
    \ << -1 << \"\\n\";\n    else cout << ret[i] << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/graph-template.hpp
  - graph/shortest-path/dijkstra.hpp
  - structure/heap/leftist-heap.hpp
  - structure/heap/persistent-leftist-heap.hpp
  - graph/shortest-path/k-shortest-walk.hpp
  isVerificationFile: true
  path: test/verify/yosupo-k-shortest-walk.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-k-shortest-walk.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-k-shortest-walk.test.cpp
- /verify/test/verify/yosupo-k-shortest-walk.test.cpp.html
title: test/verify/yosupo-k-shortest-walk.test.cpp
---
