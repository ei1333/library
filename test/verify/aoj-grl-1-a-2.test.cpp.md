---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/dijkstra-fibonacchi-heap.hpp
    title: "Dijkstra-Fibonacchi-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: structure/heap/fibonacchi-heap.hpp
    title: "Fibonacchi-Heap(\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7\
      )"
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
  bundledCode: "#line 1 \"test/verify/aoj-grl-1-a-2.test.cpp\"\n#define PROBLEM \"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-1-a-2.test.cpp\"\
    \n\n#line 2 \"graph/shortest-path/dijkstra-fibonacchi-heap.hpp\"\n\n#line 2 \"\
    graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\u30E9\u30D5\
    \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T = int >\nstruct\
    \ Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\n  Edge(int\
    \ from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx)\
    \ {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename T = int\
    \ >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n  Graph()\
    \ = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t size() const\
    \ {\n    return g.size();\n  }\n\n  void add_directed_edge(int from, int to, T\
    \ cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\n  void\
    \ add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from, to,\
    \ cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void read(int\
    \ M, int padding = -1, bool weighted = false, bool directed = false) {\n    for(int\
    \ i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n      a += padding;\n\
    \      b += padding;\n      T c = T(1);\n      if(weighted) cin >> c;\n      if(directed)\
    \ add_directed_edge(a, b, c);\n      else add_edge(a, b, c);\n    }\n  }\n\n \
    \ inline vector< Edge< T > > &operator[](const int &k) {\n    return g[k];\n \
    \ }\n\n  inline const vector< Edge< T > > &operator[](const int &k) const {\n\
    \    return g[k];\n  }\n};\n\ntemplate< typename T = int >\nusing Edges = vector<\
    \ Edge< T > >;\n#line 1 \"structure/heap/fibonacchi-heap.hpp\"\n/**\n * @brief\
    \ Fibonacchi-Heap(\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7)\n *\
    \ @see https://www.cs.princeton.edu/~wayne/teaching/fibonacci-heap.pdf\n */\n\
    template< typename key_t, typename val_t >\nstruct FibonacchiHeap {\n  struct\
    \ Node {\n    key_t key;\n    val_t val;\n    Node *left, *right, *child, *par;\n\
    \    int sz;\n    bool mark;\n\n    Node(const key_t &key, const val_t &val)\n\
    \        : key(key), val(val), left(this), right(this), par(nullptr), child(nullptr),\
    \ sz(0), mark(false) {}\n  };\n\n  Node *root;\n  size_t sz;\n  vector< Node *\
    \ > rank;\n\n  FibonacchiHeap() : root(nullptr), sz(0) {}\n\n  size_t size() const\
    \ {\n    return sz;\n  }\n\n  bool empty() const {\n    return sz == 0;\n  }\n\
    \n  void update_min(Node *t) {\n    if(!root || t->key < root->key) {\n      root\
    \ = t;\n    }\n  }\n\n  void concat(Node *&r, Node *t) {\n    if(!r) {\n     \
    \ r = t;\n    } else {\n      t->left->right = r->right;\n      r->right->left\
    \ = t->left;\n      t->left = r;\n      r->right = t;\n    }\n  }\n\n  void delete_node(Node\
    \ *t) {\n    t->left->right = t->right;\n    t->right->left = t->left;\n    t->left\
    \ = t;\n    t->right = t;\n  }\n\n  Node *push(const key_t &key, const val_t &val)\
    \ {\n    ++sz;\n    auto node = new Node(key, val);\n    concat(root, node);\n\
    \    update_min(node);\n    return node;\n  }\n\n\n  Node *consolidate(Node *s,\
    \ Node *t) {\n    if(root == s || s->key < t->key) {\n      delete_node(t);\n\
    \      ++s->sz;\n      t->par = s;\n      concat(s->child, t);\n      return s;\n\
    \    } else {\n      delete_node(s);\n      ++t->sz;\n      s->par = t;\n    \
    \  concat(t->child, s);\n      return t;\n    }\n  }\n\n\n  pair< key_t, val_t\
    \ > pop() {\n    --sz;\n\n    Node *rem = root;\n\n\n    auto ret = make_pair(rem->key,\
    \ rem->val);\n\n    {\n      root = root->left == root ? nullptr : root->left;\n\
    \      delete_node(rem);\n    }\n\n\n    if(rem->child) {\n      concat(root,\
    \ rem->child);\n    }\n\n\n    if(root) {\n\n      {\n        Node *base = root,\
    \ *cur = base;\n        do {\n          cur->par = nullptr;\n          update_min(cur);\n\
    \          cur = cur->right;\n        } while(cur != base);\n      }\n\n\n   \
    \   {\n        Node *base = root;\n        int last = -1;\n        do {\n    \
    \      Node *nxt = base->right;\n          while(base->sz < rank.size() && rank[base->sz])\
    \ {\n            Node *u = rank[base->sz];\n            rank[base->sz] = nullptr;\n\
    \            base = consolidate(u, base);\n          }\n          if(base->sz\
    \ >= rank.size()) rank.resize(base->sz + 1);\n          last = max(last, base->sz);\n\
    \          rank[base->sz] = base;\n          base = nxt;\n        } while(base\
    \ != root);\n\n        for(int i = last; i >= 0; i--) rank[i] = nullptr;\n   \
    \   }\n    }\n\n    return ret;\n  }\n\n  inline void mark_dfs(Node *t) {\n  \
    \  if(!t->par) {\n      t->mark = false;\n    } else if(t->mark) {\n      mark_dfs(t->par);\n\
    \      t->par->child = t->left == t ? nullptr : t->left;\n      delete_node(t);\n\
    \      t->sz--;\n      t->mark = false;\n      t->par = nullptr;\n      concat(root,\
    \ t);\n    } else {\n      t->mark = true;\n      t->sz--;\n    }\n  }\n\n\n \
    \ void decrease_key(Node *t, const key_t &d) {\n    t->key -= d;\n\n    if(!t->par)\
    \ {\n      update_min(t);\n      return;\n    }\n\n    if(t->par->key <= t->key)\
    \ {\n      return;\n    }\n\n    t->sz++;\n    t->mark = true;\n    mark_dfs(t);\n\
    \    update_min(t);\n  }\n};\n#line 5 \"graph/shortest-path/dijkstra-fibonacchi-heap.hpp\"\
    \n\n/**\n * @brief Dijkstra-Fibonacchi-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\
    \u8DEF)\n * @docs docs/dijkstra-fibonacchi-heap.md\n */\ntemplate< typename T\
    \ >\nvector< T > dijkstra_fibonacchi_heap(Graph< T > &g, int s) {\n  const auto\
    \ INF = numeric_limits< T >::max();\n  using Heap = FibonacchiHeap< T, int >;\n\
    \  using Node = typename Heap::Node;\n\n  Heap heap;\n  vector< Node * > keep(g.size(),\
    \ nullptr);\n  vector< T > dist;\n  dist.assign(g.size(), INF);\n  dist[s] = 0;\n\
    \  keep[s] = heap.push(dist[s], s);\n\n  while(!heap.empty()) {\n    T cost;\n\
    \    int idx;\n    tie(cost, idx) = heap.pop();\n    if(dist[idx] < cost) continue;\n\
    \    for(auto &e : g[idx]) {\n      auto next_cost = cost + e.cost;\n      if(dist[e.to]\
    \ <= next_cost) continue;\n      if(keep[e.to] == nullptr) {\n        dist[e.to]\
    \ = next_cost;\n        keep[e.to] = heap.push(dist[e.to], e.to);\n      } else\
    \ {\n        T d = dist[e.to] - next_cost;\n        heap.decrease_key(keep[e.to],\
    \ d);\n        dist[e.to] -= d;\n      }\n    }\n  }\n  return dist;\n}\n#line\
    \ 6 \"test/verify/aoj-grl-1-a-2.test.cpp\"\n\nint main() {\n  int V, E, R;\n \
    \ cin >> V >> E >> R;\n  Graph< int > g(V);\n  g.read(E, 0, true, true);\n  for(auto\
    \ &dist : dijkstra_fibonacchi_heap(g, R)) {\n    if(dist == numeric_limits< int\
    \ >::max()) cout << \"INF\\n\";\n    else cout << dist << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/shortest-path/dijkstra-fibonacchi-heap.hpp\"\
    \n\nint main() {\n  int V, E, R;\n  cin >> V >> E >> R;\n  Graph< int > g(V);\n\
    \  g.read(E, 0, true, true);\n  for(auto &dist : dijkstra_fibonacchi_heap(g, R))\
    \ {\n    if(dist == numeric_limits< int >::max()) cout << \"INF\\n\";\n    else\
    \ cout << dist << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/shortest-path/dijkstra-fibonacchi-heap.hpp
  - graph/graph-template.hpp
  - structure/heap/fibonacchi-heap.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-1-a-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-1-a-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-1-a-2.test.cpp
- /verify/test/verify/aoj-grl-1-a-2.test.cpp.html
title: test/verify/aoj-grl-1-a-2.test.cpp
---
