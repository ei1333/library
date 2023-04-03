---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/others/namori-graph.hpp
    title: Namori Graph
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
    PROBLEM: https://yukicoder.me/problems/no/1254
    links:
    - https://yukicoder.me/problems/no/1254
  bundledCode: "#line 1 \"test/verify/yukicoder-1254.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1254\"\n\n#line 1 \"template/template.hpp\"\n\
    #include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-1254.test.cpp\"\
    \n\n#line 2 \"graph/others/namori-graph.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/others/namori-graph.hpp\"\
    \n\n/**\n * @brief Namori Graph\n * @docs docs/namori-graph.md\n */\ntemplate<\
    \ typename T = int >\nstruct NamoriGraph : Graph< T > {\npublic:\n  using Graph<\
    \ T >::Graph;\n  using Graph< T >::g;\n\n  vector< Graph< T > > forest;\n  Edges<\
    \ T > loop_edges;\n\n  struct Info {\n    int tree_id, id;\n  };\n\n  Info operator[](const\
    \ int &k) const {\n    return (Info) {mark_id[k], id[k]};\n  }\n\n  int inv(int\
    \ tree_id, int k) {\n    return iv[tree_id][k];\n  }\n\n  void build() {\n   \
    \ int n = (int) g.size();\n    vector< int > deg(n), used(n);\n    queue< int\
    \ > que;\n    for(int i = 0; i < n; i++) {\n      deg[i] = (int) g[i].size();\n\
    \      if(deg[i] == 1) {\n        que.emplace(i);\n        used[i] = true;\n \
    \     }\n    }\n    while(not que.empty()) {\n      int idx = que.front();\n \
    \     que.pop();\n      for(auto &e : g[idx]) {\n        if(used[e.to]) {\n  \
    \        continue;\n        }\n        --deg[e.to];\n        if(deg[e.to] == 1)\
    \ {\n          que.emplace(e.to);\n          used[e.to] = true;\n        }\n \
    \     }\n    }\n    int mx = 0;\n    for(auto &edges : g) {\n      for(auto &e\
    \ : edges) mx = max(mx, e.idx);\n    }\n    vector< int > edge_used(mx + 1);\n\
    \    vector< int > loop;\n    for(int v = 0; v < n; v++) {\n      if(!used[v])\
    \ {\n        for(bool update = true; update;) {\n          update = false;\n \
    \         loop.emplace_back(v);\n          for(auto &e : g[v]) {\n           \
    \ if(used[e.to] or edge_used[e.idx]) {\n              continue;\n            }\n\
    \            edge_used[e.idx] = true;\n            loop_edges.emplace_back(v,\
    \ e.to, e.cost, e.idx);\n            v = e.to;\n            update = true;\n \
    \           break;\n          }\n        }\n        break;\n      }\n    }\n \
    \   loop.pop_back();\n    mark_id.resize(n);\n    id.resize(n);\n    for(int i\
    \ = 0; i < (int) loop.size(); i++) {\n      int pre = loop[(i + loop.size() -\
    \ 1) % loop.size()];\n      int nxt = loop[(i + 1) % loop.size()];\n      int\
    \ sz = 0;\n      mark_id[loop[i]] = i;\n      iv.emplace_back();\n      id[loop[i]]\
    \ = sz++;\n      iv.back().emplace_back(loop[i]);\n      for(auto &e : g[loop[i]])\
    \ {\n        if(e.to != pre and e.to != nxt) {\n          mark_dfs(e.to, loop[i],\
    \ i, sz);\n        }\n      }\n      Graph< T > tree(sz);\n      for(auto &e :\
    \ g[loop[i]]) {\n        if(e.to != pre and e.to != nxt) {\n          tree.g[id[loop[i]]].emplace_back(id[loop[i]],\
    \ id[e.to], e.cost, e.idx);\n          tree.g[id[e.to]].emplace_back(id[e.to],\
    \ id[loop[i]], e.cost, e.idx);\n          build_dfs(e.to, loop[i], tree);\n  \
    \      }\n      }\n      forest.emplace_back(tree);\n    }\n  }\n\nprivate:\n\
    \  vector< vector< int > > iv;\n  vector< int > mark_id, id;\n\n  void mark_dfs(int\
    \ idx, int par, int k, int &l) {\n    mark_id[idx] = k;\n    id[idx] = l++;\n\
    \    iv.back().emplace_back(idx);\n    for(auto &e : g[idx]) {\n      if(e.to\
    \ != par) {\n        mark_dfs(e.to, idx, k, l);\n      }\n    }\n  }\n\n  void\
    \ build_dfs(int idx, int par, Graph< T > &tree) {\n    for(auto &e : g[idx]) {\n\
    \      if(e.to != par) {\n        tree.g[id[idx]].emplace_back(id[idx], id[e.to],\
    \ e.cost, e.idx);\n        tree.g[id[e.to]].emplace_back(id[e.to], id[idx], e.cost,\
    \ e.idx);\n        build_dfs(e.to, idx, tree);\n      }\n    }\n  }\n};\n#line\
    \ 6 \"test/verify/yukicoder-1254.test.cpp\"\n\nint main() {\n  int N;\n  cin >>\
    \ N;\n  NamoriGraph< int > g(N);\n  g.read(N);\n  g.build();\n  vector< int >\
    \ ans;\n  for(auto &e : g.loop_edges) {\n    ans.emplace_back(e.idx + 1);\n  }\n\
    \  sort(begin(ans), end(ans));\n  cout << ans.size() << \"\\n\";\n  cout << ans\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1254\"\n\n#include \"\
    ../../template/template.hpp\"\n\n#include \"../../graph/others/namori-graph.hpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  NamoriGraph< int > g(N);\n  g.read(N);\n\
    \  g.build();\n  vector< int > ans;\n  for(auto &e : g.loop_edges) {\n    ans.emplace_back(e.idx\
    \ + 1);\n  }\n  sort(begin(ans), end(ans));\n  cout << ans.size() << \"\\n\";\n\
    \  cout << ans << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/others/namori-graph.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-1254.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-1254.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-1254.test.cpp
- /verify/test/verify/yukicoder-1254.test.cpp.html
title: test/verify/yukicoder-1254.test.cpp
---
