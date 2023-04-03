---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: structure/heap/fibonacchi-heap.hpp
    title: "Fibonacchi-Heap(\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7\
      )"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-1-a-2.test.cpp
    title: test/verify/aoj-grl-1-a-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/dijkstra-fibonacchi-heap.md
    document_title: "Dijkstra-Fibonacchi-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\
      \u8DEF)"
    links: []
  bundledCode: "#line 2 \"graph/shortest-path/dijkstra-fibonacchi-heap.hpp\"\n\n#line\
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
    using Edges = vector< Edge< T > >;\n#line 1 \"structure/heap/fibonacchi-heap.hpp\"\
    \n/**\n * @brief Fibonacchi-Heap(\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\
    \u30D7)\n * @see https://www.cs.princeton.edu/~wayne/teaching/fibonacci-heap.pdf\n\
    \ */\ntemplate< typename key_t, typename val_t >\nstruct FibonacchiHeap {\n  struct\
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
    \ d);\n        dist[e.to] -= d;\n      }\n    }\n  }\n  return dist;\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"../../structure/heap/fibonacchi-heap.hpp\"\
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
    \ d);\n        dist[e.to] -= d;\n      }\n    }\n  }\n  return dist;\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  - structure/heap/fibonacchi-heap.hpp
  isVerificationFile: false
  path: graph/shortest-path/dijkstra-fibonacchi-heap.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-1-a-2.test.cpp
documentation_of: graph/shortest-path/dijkstra-fibonacchi-heap.hpp
layout: document
redirect_from:
- /library/graph/shortest-path/dijkstra-fibonacchi-heap.hpp
- /library/graph/shortest-path/dijkstra-fibonacchi-heap.hpp.html
title: "Dijkstra-Fibonacchi-Heap(\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF)"
---
## 概要

負辺のないグラフで単一始点全点間最短路を求めるアルゴリズム.

通常の dijkstra 法では `std::priority_queue` を使用していたが, これをフィボナッチヒープにすることで計算量を落とせる(実用上早くなるかは知らない).

* `dijkstra_fibonacchi_heap(g, s)`: 重み付きグラフ `g` で, 頂点 `s` から全点間の最短距離を求める. 到達できない頂点には, 型の最大値が格納される.

## 計算量

* $O(V \log V + E)$
~

