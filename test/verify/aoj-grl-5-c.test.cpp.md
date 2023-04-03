---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/doubling-lowest-common-ancestor.hpp
    title: "Doubling-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
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
  bundledCode: "#line 1 \"test/verify/aoj-grl-5-c.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-5-c.test.cpp\"\
    \n\n#line 2 \"graph/tree/doubling-lowest-common-ancestor.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/doubling-lowest-common-ancestor.hpp\"\
    \n\n/**\n * @brief Doubling-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\
    \u5148)\n * @docs docs/doubling-lowest-common-ancestor.md\n */\ntemplate< typename\
    \ T >\nstruct DoublingLowestCommonAncestor : Graph< T > {\npublic:\n  using Graph<\
    \ T >::g;\n  vector< int > dep;\n  vector< T > sum;\n  vector< vector< int > >\
    \ table;\n  const int LOG;\n\n  explicit DoublingLowestCommonAncestor(int n)\n\
    \      : Graph< T >(n), LOG(32 - __builtin_clz(g.size())) {}\n\n  explicit DoublingLowestCommonAncestor(const\
    \ Graph< T > &g)\n      : LOG(32 - __builtin_clz(g.size())), Graph< T >(g) {}\n\
    \n  void build(int root = 0) {\n    dep.assign(g.size(), 0);\n    sum.assign(g.size(),\
    \ 0);\n    table.assign(LOG, vector< int >(g.size(), -1));\n    dfs(root, -1,\
    \ 0);\n    for(int k = 0; k + 1 < LOG; k++) {\n      for(int i = 0; i < (int)table[k].size();\
    \ i++) {\n        if(table[k][i] == -1) table[k + 1][i] = -1;\n        else table[k\
    \ + 1][i] = table[k][table[k][i]];\n      }\n    }\n  }\n\n  int lca(int u, int\
    \ v) {\n    if(dep[u] > dep[v]) swap(u, v);\n    v = climb(v, dep[v] - dep[u]);\n\
    \    if(u == v) return u;\n    for(int i = LOG - 1; i >= 0; i--) {\n      if(table[i][u]\
    \ != table[i][v]) {\n        u = table[i][u];\n        v = table[i][v];\n    \
    \  }\n    }\n    return table[0][u];\n  }\n\n  int climb(int u, int k) {\n   \
    \ if(dep[u] < k) return -1;\n    for(int i = LOG - 1; i >= 0; i--) {\n      if((k\
    \ >> i) & 1) u = table[i][u];\n    }\n    return u;\n  }\n\n  T dist(int u, int\
    \ v) {\n    return sum[u] + sum[v] - 2 * sum[lca(u, v)];\n  }\n\nprivate:\n  void\
    \ dfs(int idx, int par, int d) {\n    table[0][idx] = par;\n    dep[idx] = d;\n\
    \    for(auto &to : g[idx]) {\n      if(to != par) {\n        sum[to] = sum[idx]\
    \ + to.cost;\n        dfs(to, idx, d + 1);\n      }\n    }\n  }\n};\n#line 6 \"\
    test/verify/aoj-grl-5-c.test.cpp\"\n\nint main() {\n  int N, Q;\n  cin >> N;\n\
    \  DoublingLowestCommonAncestor< int > dlca(N);\n  for(int i = 0; i < N; i++)\
    \ {\n    int k;\n    cin >> k;\n    for(int j = 0; j < k; j++) {\n      int c;\n\
    \      cin >> c;\n      dlca.add_edge(i, c);\n    }\n  }\n  dlca.build();\n  cin\
    \ >> Q;\n  for(int i = 0; i < Q; i++) {\n    int u, v;\n    cin >> u >> v;\n \
    \   cout << dlca.lca(u, v) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/tree/doubling-lowest-common-ancestor.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N;\n  DoublingLowestCommonAncestor< int\
    \ > dlca(N);\n  for(int i = 0; i < N; i++) {\n    int k;\n    cin >> k;\n    for(int\
    \ j = 0; j < k; j++) {\n      int c;\n      cin >> c;\n      dlca.add_edge(i,\
    \ c);\n    }\n  }\n  dlca.build();\n  cin >> Q;\n  for(int i = 0; i < Q; i++)\
    \ {\n    int u, v;\n    cin >> u >> v;\n    cout << dlca.lca(u, v) << \"\\n\"\
    ;\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/doubling-lowest-common-ancestor.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-5-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-5-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-5-c.test.cpp
- /verify/test/verify/aoj-grl-5-c.test.cpp.html
title: test/verify/aoj-grl-5-c.test.cpp
---
