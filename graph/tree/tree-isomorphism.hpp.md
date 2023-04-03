---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid.hpp
    title: "Centroid(\u6728\u306E\u91CD\u5FC3)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2821.test.cpp
    title: test/verify/aoj-2821.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Tree-Isomorphism(\u6728\u306E\u540C\u578B\u6027\u5224\u5B9A)"
    links: []
  bundledCode: "#line 2 \"graph/tree/tree-isomorphism.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 2 \"graph/tree/centroid.hpp\"\
    \n\n#line 4 \"graph/tree/centroid.hpp\"\n\n/**\n * @brief Centroid(\u6728\u306E\
    \u91CD\u5FC3)\n * @docs docs/centroid.md\n */\ntemplate< typename T >\nvector<\
    \ int > centroid(const Graph< T > &g) {\n  const int N = (int) g.size();\n\n \
    \ stack< pair< int, int > > st;\n  st.emplace(0, -1);\n  vector< int > sz(N),\
    \ par(N);\n  while(!st.empty()) {\n    auto p = st.top();\n    if(sz[p.first]\
    \ == 0) {\n      sz[p.first] = 1;\n      for(auto &to : g[p.first]) if(to != p.second)\
    \ st.emplace(to, p.first);\n    } else {\n      for(auto &to : g[p.first]) if(to\
    \ != p.second) sz[p.first] += sz[to];\n      par[p.first] = p.second;\n      st.pop();\n\
    \    }\n  }\n\n  vector< int > ret;\n  int size = N;\n  for(int i = 0; i < N;\
    \ i++) {\n    int val = N - sz[i];\n    for(auto &to : g[i]) if(to != par[i])\
    \ val = max(val, sz[to]);\n    if(val < size) size = val, ret.clear();\n    if(val\
    \ == size) ret.emplace_back(i);\n  }\n\n  return ret;\n}\n#line 5 \"graph/tree/tree-isomorphism.hpp\"\
    \n\n/**\n * @brief Tree-Isomorphism(\u6728\u306E\u540C\u578B\u6027\u5224\u5B9A\
    )\n */\ntemplate< typename T >\nbool tree_isomorphism(const Graph< T > &a, const\
    \ Graph< T > &b) {\n  if(a.size() != b.size()) return false;\n\n  const int N\
    \ = (int) a.size();\n  using pvi = pair< vector< int >, vector< int > >;\n\n \
    \ auto get_uku = [&](const Graph< T > &t, int e) {\n    stack< pair< int, int\
    \ > > st;\n    st.emplace(e, -1);\n    vector< int > dep(N, -1), par(N);\n   \
    \ while(!st.empty()) {\n      auto p = st.top();\n      if(dep[p.first] == -1)\
    \ {\n        dep[p.first] = p.second == -1 ? 0 : dep[p.second] + 1;\n        for(auto\
    \ &to : t[p.first]) if(to != p.second) st.emplace(to, p.first);\n      } else\
    \ {\n        par[p.first] = p.second;\n        st.pop();\n      }\n    }\n   \
    \ return make_pair(dep, par);\n  };\n\n  auto solve = [&](const pvi &latte, const\
    \ pvi &malta) {\n\n    int d = *max_element(begin(latte.first), end(latte.first));\n\
    \    if(d != *max_element(begin(malta.first), end(malta.first))) return false;\n\
    \n    vector< vector< int > > latte_d(d + 1), malta_d(d + 1), latte_key(N), malta_key(N);\n\
    \n    for(int i = 0; i < N; i++) latte_d[latte.first[i]].emplace_back(i);\n  \
    \  for(int i = 0; i < N; i++) malta_d[malta.first[i]].emplace_back(i);\n\n   \
    \ for(int i = d; i >= 0; i--) {\n      map< vector< int >, int > ord;\n      for(auto\
    \ &idx : latte_d[i]) {\n        sort(begin(latte_key[idx]), end(latte_key[idx]));\n\
    \        ord[latte_key[idx]]++;\n      }\n      for(auto &idx : malta_d[i]) {\n\
    \        sort(begin(malta_key[idx]), end(malta_key[idx]));\n        if(--ord[malta_key[idx]]\
    \ < 0) return false;\n      }\n      if(i == 0) return ord.size() == 1;\n\n  \
    \    int ptr = 0;\n      for(auto &p : ord) {\n        if(p.second != 0) return\
    \ false;\n        p.second = ptr++;\n      }\n      for(auto &idx : latte_d[i])\
    \ {\n        latte_key[latte.second[idx]].emplace_back(ord[latte_key[idx]]);\n\
    \      }\n      for(auto &idx : malta_d[i]) {\n        malta_key[malta.second[idx]].emplace_back(ord[malta_key[idx]]);\n\
    \      }\n    }\n    assert(0);\n  };\n  auto p = centroid(a), q = centroid(b);\n\
    \  if(p.size() != q.size()) return false;\n  auto a1 = get_uku(a, p[0]);\n  auto\
    \ b1 = get_uku(b, q[0]);\n  if(solve(a1, b1)) return true;\n  if(p.size() == 1)\
    \ return false;\n  auto a2 = get_uku(a, p[1]);\n  return solve(a2, b1);\n}\n"
  code: "#pragma once\n\n#include \"../graph-template.hpp\"\n#include \"./centroid.hpp\"\
    \n\n/**\n * @brief Tree-Isomorphism(\u6728\u306E\u540C\u578B\u6027\u5224\u5B9A\
    )\n */\ntemplate< typename T >\nbool tree_isomorphism(const Graph< T > &a, const\
    \ Graph< T > &b) {\n  if(a.size() != b.size()) return false;\n\n  const int N\
    \ = (int) a.size();\n  using pvi = pair< vector< int >, vector< int > >;\n\n \
    \ auto get_uku = [&](const Graph< T > &t, int e) {\n    stack< pair< int, int\
    \ > > st;\n    st.emplace(e, -1);\n    vector< int > dep(N, -1), par(N);\n   \
    \ while(!st.empty()) {\n      auto p = st.top();\n      if(dep[p.first] == -1)\
    \ {\n        dep[p.first] = p.second == -1 ? 0 : dep[p.second] + 1;\n        for(auto\
    \ &to : t[p.first]) if(to != p.second) st.emplace(to, p.first);\n      } else\
    \ {\n        par[p.first] = p.second;\n        st.pop();\n      }\n    }\n   \
    \ return make_pair(dep, par);\n  };\n\n  auto solve = [&](const pvi &latte, const\
    \ pvi &malta) {\n\n    int d = *max_element(begin(latte.first), end(latte.first));\n\
    \    if(d != *max_element(begin(malta.first), end(malta.first))) return false;\n\
    \n    vector< vector< int > > latte_d(d + 1), malta_d(d + 1), latte_key(N), malta_key(N);\n\
    \n    for(int i = 0; i < N; i++) latte_d[latte.first[i]].emplace_back(i);\n  \
    \  for(int i = 0; i < N; i++) malta_d[malta.first[i]].emplace_back(i);\n\n   \
    \ for(int i = d; i >= 0; i--) {\n      map< vector< int >, int > ord;\n      for(auto\
    \ &idx : latte_d[i]) {\n        sort(begin(latte_key[idx]), end(latte_key[idx]));\n\
    \        ord[latte_key[idx]]++;\n      }\n      for(auto &idx : malta_d[i]) {\n\
    \        sort(begin(malta_key[idx]), end(malta_key[idx]));\n        if(--ord[malta_key[idx]]\
    \ < 0) return false;\n      }\n      if(i == 0) return ord.size() == 1;\n\n  \
    \    int ptr = 0;\n      for(auto &p : ord) {\n        if(p.second != 0) return\
    \ false;\n        p.second = ptr++;\n      }\n      for(auto &idx : latte_d[i])\
    \ {\n        latte_key[latte.second[idx]].emplace_back(ord[latte_key[idx]]);\n\
    \      }\n      for(auto &idx : malta_d[i]) {\n        malta_key[malta.second[idx]].emplace_back(ord[malta_key[idx]]);\n\
    \      }\n    }\n    assert(0);\n  };\n  auto p = centroid(a), q = centroid(b);\n\
    \  if(p.size() != q.size()) return false;\n  auto a1 = get_uku(a, p[0]);\n  auto\
    \ b1 = get_uku(b, q[0]);\n  if(solve(a1, b1)) return true;\n  if(p.size() == 1)\
    \ return false;\n  auto a2 = get_uku(a, p[1]);\n  return solve(a2, b1);\n}\n"
  dependsOn:
  - graph/graph-template.hpp
  - graph/tree/centroid.hpp
  isVerificationFile: false
  path: graph/tree/tree-isomorphism.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-2821.test.cpp
documentation_of: graph/tree/tree-isomorphism.hpp
layout: document
redirect_from:
- /library/graph/tree/tree-isomorphism.hpp
- /library/graph/tree/tree-isomorphism.hpp.html
title: "Tree-Isomorphism(\u6728\u306E\u540C\u578B\u6027\u5224\u5B9A)"
---
