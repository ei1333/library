---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/heavy-light-decomposition.hpp
    title: "Heavy-Light-Decomposition(HL\u5206\u89E3)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
  bundledCode: "#line 1 \"test/verify/aoj-grl-5-c-2.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C\"\n\n#line 1\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-5-c-2.test.cpp\"\
    \n\n#line 2 \"graph/tree/heavy-light-decomposition.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/heavy-light-decomposition.hpp\"\
    \n\n/**\n * @brief Heavy-Light-Decomposition(HL\u5206\u89E3)\n * @see https://smijake3.hatenablog.com/entry/2019/09/15/200200\n\
    \ */\ntemplate< typename T = int >\nstruct HeavyLightDecomposition : Graph< T\
    \ > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > sz, in, out, head, rev, par, dep;\n\n  void build() {\n    sz.assign(g.size(),\
    \ 0);\n    in.assign(g.size(), 0);\n    out.assign(g.size(), 0);\n    head.assign(g.size(),\
    \ 0);\n    rev.assign(g.size(), 0);\n    par.assign(g.size(), 0);\n    dep.assign(g.size(),\
    \ 0);\n    dfs_sz(0, -1, 0);\n    int t = 0;\n    dfs_hld(0, -1, t);\n  }\n\n\
    \  /* k: 0-indexed */\n  int la(int v, int k) {\n    while(1) {\n      int u =\
    \ head[v];\n      if(in[v] - k >= in[u]) return rev[in[v] - k];\n      k -= in[v]\
    \ - in[u] + 1;\n      v = par[u];\n    }\n  }\n\n  int lca(int u, int v) const\
    \ {\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v);\n   \
    \   if(head[u] == head[v]) return u;\n    }\n  }\n\n  int dist(int u, int v) const\
    \ {\n    return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n  }\n\n  template< typename\
    \ E, typename Q, typename F, typename S >\n  E query(int u, int v, const E &ti,\
    \ const Q &q, const F &f, const S &s, bool edge = false) {\n    E l = ti, r =\
    \ ti;\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v), swap(l,\
    \ r);\n      if(head[u] == head[v]) break;\n      l = f(q(in[head[v]], in[v] +\
    \ 1), l);\n    }\n    return s(f(q(in[u] + edge, in[v] + 1), l), r);\n  }\n\n\
    \  template< typename E, typename Q, typename F >\n  E query(int u, int v, const\
    \ E &ti, const Q &q, const F &f, bool edge = false) {\n    return query(u, v,\
    \ ti, q, f, f, edge);\n  }\n\n  template< typename Q >\n  void add(int u, int\
    \ v, const Q &q, bool edge = false) {\n    for(;; v = par[head[v]]) {\n      if(in[u]\
    \ > in[v]) swap(u, v);\n      if(head[u] == head[v]) break;\n      q(in[head[v]],\
    \ in[v] + 1);\n    }\n    q(in[u] + edge, in[v] + 1);\n  }\n\n  /* {parent, child}\
    \ */\n  vector< pair< int, int > > compress(vector< int > &remark) {\n    auto\
    \ cmp = [&](int a, int b) { return in[a] < in[b]; };\n    sort(begin(remark),\
    \ end(remark), cmp);\n    remark.erase(unique(begin(remark), end(remark)), end(remark));\n\
    \    int K = (int) remark.size();\n    for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k\
    \ - 1], remark[k]));\n    sort(begin(remark), end(remark), cmp);\n    remark.erase(unique(begin(remark),\
    \ end(remark)), end(remark));\n    vector< pair< int, int > > es;\n    stack<\
    \ int > st;\n    for(auto &k : remark) {\n      while(!st.empty() && out[st.top()]\
    \ <= in[k]) st.pop();\n      if(!st.empty()) es.emplace_back(st.top(), k);\n \
    \     st.emplace(k);\n    }\n    return es;\n  }\n\n  explicit HeavyLightDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  void dfs_sz(int idx, int p,\
    \ int d) {\n    dep[idx] = d;\n    par[idx] = p;\n    sz[idx] = 1;\n    if(g[idx].size()\
    \ && g[idx][0] == p) swap(g[idx][0], g[idx].back());\n    for(auto &to : g[idx])\
    \ {\n      if(to == p) continue;\n      dfs_sz(to, idx, d + 1);\n      sz[idx]\
    \ += sz[to];\n      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);\n    }\n \
    \ }\n\n  void dfs_hld(int idx, int p, int &times) {\n    in[idx] = times++;\n\
    \    rev[in[idx]] = idx;\n    for(auto &to : g[idx]) {\n      if(to == p) continue;\n\
    \      head[to] = (g[idx][0] == to ? head[idx] : to);\n      dfs_hld(to, idx,\
    \ times);\n    }\n    out[idx] = times;\n  }\n};\n#line 6 \"test/verify/aoj-grl-5-c-2.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N;\n  HeavyLightDecomposition< int > hld(N);\n\
    \  for(int i = 0; i < N; i++) {\n    int k;\n    cin >> k;\n    for(int j = 0;\
    \ j < k; j++) {\n      int c;\n      cin >> c;\n      hld.add_edge(i, c);\n  \
    \  }\n  }\n  hld.build();\n  cin >> Q;\n  for(int i = 0; i < Q; i++) {\n    int\
    \ u, v;\n    cin >> u >> v;\n    cout << hld.lca(u, v) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/tree/heavy-light-decomposition.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N;\n  HeavyLightDecomposition< int > hld(N);\n\
    \  for(int i = 0; i < N; i++) {\n    int k;\n    cin >> k;\n    for(int j = 0;\
    \ j < k; j++) {\n      int c;\n      cin >> c;\n      hld.add_edge(i, c);\n  \
    \  }\n  }\n  hld.build();\n  cin >> Q;\n  for(int i = 0; i < Q; i++) {\n    int\
    \ u, v;\n    cin >> u >> v;\n    cout << hld.lca(u, v) << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/heavy-light-decomposition.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-5-c-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-5-c-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-5-c-2.test.cpp
- /verify/test/verify/aoj-grl-5-c-2.test.cpp.html
title: test/verify/aoj-grl-5-c-2.test.cpp
---
