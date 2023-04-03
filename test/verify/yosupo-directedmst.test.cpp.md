---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/mst/directed-mst.hpp
    title: "Directed MST(\u6700\u5C0F\u6709\u5411\u5168\u57DF\u6728)"
  - icon: ':heavy_check_mark:'
    path: structure/heap/skew-heap.hpp
    title: Skew-Heap
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
    PROBLEM: https://judge.yosupo.jp/problem/directedmst
    links:
    - https://judge.yosupo.jp/problem/directedmst
  bundledCode: "#line 1 \"test/verify/yosupo-directedmst.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/directedmst\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-directedmst.test.cpp\"\
    \n\n#line 2 \"graph/mst/directed-mst.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 1 \"structure/heap/skew-heap.hpp\"\
    \n/**\n * @brief Skew-Heap\n */\ntemplate< typename T, bool isMin = true >\nstruct\
    \ SkewHeap {\n  struct Node {\n    T key, lazy;\n    Node *l, *r;\n    int idx;\n\
    \n    explicit Node(const T &key, int idx) : key(key), idx(idx), lazy(0), l(nullptr),\
    \ r(nullptr) {}\n  };\n\n  SkewHeap() = default;\n\n  Node *alloc(const T &key,\
    \ int idx = -1) {\n    return new Node(key, idx);\n  }\n\n  Node *propagate(Node\
    \ *t) {\n    if(t && t->lazy != 0) {\n      if(t->l) t->l->lazy += t->lazy;\n\
    \      if(t->r) t->r->lazy += t->lazy;\n      t->key += t->lazy;\n      t->lazy\
    \ = 0;\n    }\n    return t;\n  }\n\n  Node *meld(Node *x, Node *y) {\n    propagate(x),\
    \ propagate(y);\n    if(!x || !y) return x ? x : y;\n    if((x->key < y->key)\
    \ ^ isMin) swap(x, y);\n    x->r = meld(y, x->r);\n    swap(x->l, x->r);\n   \
    \ return x;\n  }\n\n  Node *push(Node *t, const T &key, int idx = -1) {\n    return\
    \ meld(t, alloc(key, idx));\n  }\n\n  Node *pop(Node *t) {\n    assert(t != nullptr);\n\
    \    return meld(t->l, t->r);\n  }\n\n  Node *add(Node *t, const T &lazy) {\n\
    \    if(t) {\n      t->lazy += lazy;\n      propagate(t);\n    }\n    return t;\n\
    \  }\n\n  Node *make_root() {\n    return nullptr;\n  }\n};\n#line 5 \"graph/mst/directed-mst.hpp\"\
    \n\n/**\n * @brief Directed MST(\u6700\u5C0F\u6709\u5411\u5168\u57DF\u6728)\n\
    \ * @docs docs/directed-mst.md\n */\ntemplate< typename T >\nstruct MinimumSpanningTree\
    \ {\n  T cost;\n  Edges< T > edges;\n};\n\ntemplate< typename T >\nMinimumSpanningTree<\
    \ T > directed_mst(int V, int root, Edges< T > edges) {\n  for(int i = 0; i <\
    \ V; ++i) {\n    if(i != root) edges.emplace_back(i, root, 0);\n  }\n\n  int x\
    \ = 0;\n  vector< int > par(2 * V, -1), vis(par), link(par);\n\n  using Heap =\
    \ SkewHeap< T, true >;\n  using Node = typename Heap::Node;\n\n  Heap heap;\n\
    \  vector< Node * > ins(2 * V, heap.make_root());\n\n  for(int i = 0; i < (int)\
    \ edges.size(); i++) {\n    auto &e = edges[i];\n    ins[e.to] = heap.push(ins[e.to],\
    \ e.cost, i);\n  }\n  vector< int > st;\n  auto go = [&](int x) {\n    x = edges[ins[x]->idx].from;\n\
    \    while(link[x] != -1) {\n      st.emplace_back(x);\n      x = link[x];\n \
    \   }\n    for(auto &p : st) {\n      link[p] = x;\n    }\n    st.clear();\n \
    \   return x;\n  };\n  for(int i = V; ins[x]; i++) {\n    for(; vis[x] == -1;\
    \ x = go(x)) vis[x] = 0;\n    for(; x != i; x = go(x)) {\n      auto w = ins[x]->key;\n\
    \      auto v = heap.pop(ins[x]);\n      v = heap.add(v, -w);\n      ins[i] =\
    \ heap.meld(ins[i], v);\n      par[x] = i;\n      link[x] = i;\n    }\n    for(;\
    \ ins[x] && go(x) == x; ins[x] = heap.pop(ins[x]));\n  }\n  T cost = 0;\n  Edges<\
    \ T > ans;\n  for(int i = root; i != -1; i = par[i]) {\n    vis[i] = 1;\n  }\n\
    \  for(int i = x; i >= 0; i--) {\n    if(vis[i] == 1) continue;\n    cost += edges[ins[i]->idx].cost;\n\
    \    ans.emplace_back(edges[ins[i]->idx]);\n    for(int j = edges[ins[i]->idx].to;\
    \ j != -1 && vis[j] == 0; j = par[j]) {\n      vis[j] = 1;\n    }\n  }\n  return\
    \ {cost, ans};\n}\n#line 6 \"test/verify/yosupo-directedmst.test.cpp\"\n\nint\
    \ main() {\n  int n, m, r;\n  cin >> n >> m >> r;\n  Edges< int64_t > edges;\n\
    \  for(int i = 0; i < m; ++i) {\n    int a, b;\n    int64_t w;\n    cin >> a >>\
    \ b >> w;\n    edges.emplace_back(a, b, w);\n  }\n  auto res = directed_mst(n,\
    \ r, edges);\n  cout << res.cost << \"\\n\";\n  vector< int > ans(n);\n  ans[r]\
    \ = r;\n  for(auto &e : res.edges) {\n    ans[e.to] = e.from;\n  }\n  cout <<\
    \ ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/directedmst\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../graph/mst/directed-mst.hpp\"\
    \n\nint main() {\n  int n, m, r;\n  cin >> n >> m >> r;\n  Edges< int64_t > edges;\n\
    \  for(int i = 0; i < m; ++i) {\n    int a, b;\n    int64_t w;\n    cin >> a >>\
    \ b >> w;\n    edges.emplace_back(a, b, w);\n  }\n  auto res = directed_mst(n,\
    \ r, edges);\n  cout << res.cost << \"\\n\";\n  vector< int > ans(n);\n  ans[r]\
    \ = r;\n  for(auto &e : res.edges) {\n    ans[e.to] = e.from;\n  }\n  cout <<\
    \ ans << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/mst/directed-mst.hpp
  - graph/graph-template.hpp
  - structure/heap/skew-heap.hpp
  isVerificationFile: true
  path: test/verify/yosupo-directedmst.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-directedmst.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-directedmst.test.cpp
- /verify/test/verify/yosupo-directedmst.test.cpp.html
title: test/verify/yosupo-directedmst.test.cpp
---
