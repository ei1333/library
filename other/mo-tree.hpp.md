---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/offline-lca.hpp
    title: "Offline LCA(\u30AA\u30D5\u30E9\u30A4\u30F3\u6700\u5C0F\u5171\u901A\u7956\
      \u5148)"
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2270.test.cpp
    title: test/verify/aoj-2270.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Mo Tree(\u6728\u4E0A\u306EMo)"
    links: []
  bundledCode: "#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"structure/union-find/union-find.hpp\"\
    \n\nstruct UnionFind {\n  vector< int > data;\n\n  UnionFind() = default;\n\n\
    \  explicit UnionFind(size_t sz) : data(sz, -1) {}\n\n  bool unite(int x, int\
    \ y) {\n    x = find(x), y = find(y);\n    if(x == y) return false;\n    if(data[x]\
    \ > data[y]) swap(x, y);\n    data[x] += data[y];\n    data[y] = x;\n    return\
    \ true;\n  }\n\n  int find(int k) {\n    if(data[k] < 0) return (k);\n    return\
    \ data[k] = find(data[k]);\n  }\n\n  int size(int k) {\n    return -data[find(k)];\n\
    \  }\n\n  bool same(int x, int y) {\n    return find(x) == find(y);\n  }\n\n \
    \ vector< vector< int > > groups() {\n    int n = (int) data.size();\n    vector<\
    \ vector< int > > ret(n);\n    for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n\
    \    }\n    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int >\
    \ &v) {\n      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n\
    #line 3 \"graph/tree/offline-lca.hpp\"\n\n/**\n * @brief Offline LCA(\u30AA\u30D5\
    \u30E9\u30A4\u30F3\u6700\u5C0F\u5171\u901A\u7956\u5148)\n **/\ntemplate< typename\
    \ T >\nvector< int > offline_lca(const Graph< T > &g, vector< pair< int, int >\
    \ > &qs, int root = 0) {\n  int n = (int) g.size();\n  UnionFind uf(n);\n  vector<\
    \ int > st(n), mark(n), ptr(n), ans(qs.size(), -1);\n  int top = 0;\n  st[top]\
    \ = root;\n  for(auto&[l, r]: qs) mark[l]++, mark[r]++;\n  vector< vector< pair<\
    \ int, int > > > q(n);\n  for(int i = 0; i < n; i++) {\n    q[i].reserve(mark[i]);\n\
    \    mark[i] = -1;\n    ptr[i] = (int) g[i].size();\n  }\n  for(int i = 0; i <\
    \ qs.size(); i++) {\n    q[qs[i].first].emplace_back(qs[i].second, i);\n    q[qs[i].second].emplace_back(qs[i].first,\
    \ i);\n  }\n  auto run = [&](int u) -> bool {\n    while(ptr[u]) {\n      int\
    \ v = g[u][--ptr[u]];\n      if(mark[v] == -1) {\n        st[++top] = v;\n   \
    \     return true;\n      }\n    }\n    return false;\n  };\n  while(~top) {\n\
    \    int u = st[top];\n    if(mark[u] == -1) {\n      mark[u] = u;\n    } else\
    \ {\n      uf.unite(u, g[u][ptr[u]]);\n      mark[uf.find(u)] = u;\n    }\n  \
    \  if(not run(u)) {\n      for(auto&[v, i]: q[u]) {\n        if(~mark[v] and ans[i]\
    \ == -1) {\n          ans[i] = mark[uf.find(v)];\n        }\n      }\n      --top;\n\
    \    }\n  }\n  return ans;\n}\n#line 3 \"other/mo-tree.hpp\"\n\n/**\n * @brief\
    \ Mo Tree(\u6728\u4E0A\u306EMo)\n **/\ntemplate< typename T = int >\nstruct MoTree\
    \ : Graph< T > {\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > in, vs;\n  vector< pair< int, int > > qs;\n\npublic:\n\n  void add(int\
    \ l, int r) { /* [l, r) */\n    qs.emplace_back(l, r);\n  }\n\nprivate:\n  void\
    \ dfs(int u, int p) {\n    in[u] = (int) vs.size();\n    vs.emplace_back(u);\n\
    \    for(auto &v: g[u]) {\n      if(v != p) {\n        dfs(v, u);\n        vs.emplace_back(v);\n\
    \      }\n    }\n  }\n\npublic:\n  template< typename A, typename E, typename\
    \ O >\n  void build(const A &add, const E &erase, const O &out) {\n    int n =\
    \ (int) g.size() * 2 - 1;\n    vs.reserve(n);\n    in.resize(g.size());\n    dfs(0,\
    \ -1);\n    vector< pair< int, int > > lr;\n    lr.reserve(qs.size());\n    auto\
    \ lca = offline_lca(*this, qs);\n    for(auto&[l, r]: qs) {\n      lr.emplace_back(minmax(in[l]\
    \ + 1, in[r] + 1));\n    }\n    int q = (int) lr.size();\n    int bs = n / min<\
    \ int >(n, sqrt(q));\n    vector< int > ord(q);\n    iota(begin(ord), end(ord),\
    \ 0);\n    sort(begin(ord), end(ord), [&](int a, int b) {\n      int ablock =\
    \ lr[a].first / bs, bblock = lr[b].first / bs;\n      if(ablock != bblock) return\
    \ ablock < bblock;\n      return (ablock & 1) ? lr[a].second > lr[b].second :\
    \ lr[a].second < lr[b].second;\n    });\n    int l = 0, r = 0;\n    vector< int\
    \ > flip(g.size());\n    auto f = [&](int u) {\n      flip[u] ^= 1;\n      if(flip[u])\
    \ add(u);\n      else erase(u);\n    };\n    for(auto &idx: ord) {\n      while(l\
    \ > lr[idx].first) f(vs[--l]);\n      while(r < lr[idx].second) f(vs[r++]);\n\
    \      while(l < lr[idx].first) f(vs[l++]);\n      while(r > lr[idx].second) f(vs[--r]);\n\
    \      f(lca[idx]);\n      out(idx);\n      f(lca[idx]);\n    }\n  }\n};\n"
  code: "#include \"../graph/graph-template.hpp\"\n#include \"../graph/tree/offline-lca.hpp\"\
    \n\n/**\n * @brief Mo Tree(\u6728\u4E0A\u306EMo)\n **/\ntemplate< typename T =\
    \ int >\nstruct MoTree : Graph< T > {\n  using Graph< T >::Graph;\n  using Graph<\
    \ T >::g;\n  vector< int > in, vs;\n  vector< pair< int, int > > qs;\n\npublic:\n\
    \n  void add(int l, int r) { /* [l, r) */\n    qs.emplace_back(l, r);\n  }\n\n\
    private:\n  void dfs(int u, int p) {\n    in[u] = (int) vs.size();\n    vs.emplace_back(u);\n\
    \    for(auto &v: g[u]) {\n      if(v != p) {\n        dfs(v, u);\n        vs.emplace_back(v);\n\
    \      }\n    }\n  }\n\npublic:\n  template< typename A, typename E, typename\
    \ O >\n  void build(const A &add, const E &erase, const O &out) {\n    int n =\
    \ (int) g.size() * 2 - 1;\n    vs.reserve(n);\n    in.resize(g.size());\n    dfs(0,\
    \ -1);\n    vector< pair< int, int > > lr;\n    lr.reserve(qs.size());\n    auto\
    \ lca = offline_lca(*this, qs);\n    for(auto&[l, r]: qs) {\n      lr.emplace_back(minmax(in[l]\
    \ + 1, in[r] + 1));\n    }\n    int q = (int) lr.size();\n    int bs = n / min<\
    \ int >(n, sqrt(q));\n    vector< int > ord(q);\n    iota(begin(ord), end(ord),\
    \ 0);\n    sort(begin(ord), end(ord), [&](int a, int b) {\n      int ablock =\
    \ lr[a].first / bs, bblock = lr[b].first / bs;\n      if(ablock != bblock) return\
    \ ablock < bblock;\n      return (ablock & 1) ? lr[a].second > lr[b].second :\
    \ lr[a].second < lr[b].second;\n    });\n    int l = 0, r = 0;\n    vector< int\
    \ > flip(g.size());\n    auto f = [&](int u) {\n      flip[u] ^= 1;\n      if(flip[u])\
    \ add(u);\n      else erase(u);\n    };\n    for(auto &idx: ord) {\n      while(l\
    \ > lr[idx].first) f(vs[--l]);\n      while(r < lr[idx].second) f(vs[r++]);\n\
    \      while(l < lr[idx].first) f(vs[l++]);\n      while(r > lr[idx].second) f(vs[--r]);\n\
    \      f(lca[idx]);\n      out(idx);\n      f(lca[idx]);\n    }\n  }\n};\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/tree/offline-lca.hpp
  - structure/union-find/union-find.hpp
  isVerificationFile: false
  path: other/mo-tree.hpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-2270.test.cpp
documentation_of: other/mo-tree.hpp
layout: document
redirect_from:
- /library/other/mo-tree.hpp
- /library/other/mo-tree.hpp.html
title: "Mo Tree(\u6728\u4E0A\u306EMo)"
---
