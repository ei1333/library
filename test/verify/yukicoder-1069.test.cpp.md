---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/k-shortest-path.hpp
    title: K-Shortest-Path
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
    ERROR: 1e-4
    PROBLEM: https://yukicoder.me/problems/no/1069
    links:
    - https://yukicoder.me/problems/no/1069
  bundledCode: "#line 1 \"test/verify/yukicoder-1069.test.cpp\"\n#define ERROR \"\
    1e-4\"\n#define PROBLEM \"https://yukicoder.me/problems/no/1069\"\n\n#line 1 \"\
    template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing\
    \ int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL <<\
    \ 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n\
    \    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed <<\
    \ setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 5 \"test/verify/yukicoder-1069.test.cpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"graph/shortest-path/k-shortest-path.hpp\"\
    \n\n#line 4 \"graph/shortest-path/k-shortest-path.hpp\"\n\n/**\n * @brief K-Shortest-Path\n\
    \ * @docs docs/k-shortest-path.md\n * @see https://qiita.com/nariaki3551/items/821dc6ffdc552d3d5f22\n\
    \ */\ntemplate< typename T >\nvector< pair< T, vector< int > > > k_shortest_path(const\
    \ Graph< T > &g, int s, int t, int k) {\n  assert(s != t);\n  int N = (int) g.size();\n\
    \  int M = 0;\n  for(int i = 0; i < N; i++) M += (int) g[i].size();\n  vector<\
    \ int > latte(M), malta(M);\n  vector< T > cost(M);\n  for(int i = 0; i < N; i++)\
    \ {\n    for(auto &e : g[i]) {\n      latte[e.idx] = i;\n      malta[e.idx] =\
    \ e.to;\n      cost[e.idx] = e.cost;\n    }\n  }\n  const auto INF = numeric_limits<\
    \ T >::max();\n  vector< int > dame(M, -1);\n  int timestamp = 0;\n  auto shortest_path\
    \ = [&](vector< T > &dist, vector< int > &from, vector< int > &id, int st) {\n\
    \    using Pi = pair< T, int >;\n    priority_queue< Pi, vector< Pi >, greater<>\
    \ > que;\n    que.emplace(dist[st], st);\n    while(!que.empty()) {\n      T cost;\n\
    \      int idx;\n      tie(cost, idx) = que.top();\n      que.pop();\n      if(dist[idx]\
    \ < cost) continue;\n      if(idx == t) return;\n      for(auto &e : g[idx]) {\n\
    \        auto next_cost = cost + e.cost;\n        if(dist[e.to] <= next_cost)\
    \ continue;\n        if(dame[e.idx] == timestamp) continue;\n        dist[e.to]\
    \ = next_cost;\n        from[e.to] = idx;\n        id[e.to] = e.idx;\n       \
    \ que.emplace(dist[e.to], e.to);\n      }\n    }\n  };\n  auto restore = [](const\
    \ vector< int > &es, const vector< int > &vs, int from, int to) {\n    vector<\
    \ int > tap;\n    while(to != from) {\n      tap.emplace_back(es[to]);\n     \
    \ to = vs[to];\n    }\n    reverse(begin(tap), end(tap));\n    return tap;\n \
    \ };\n\n  vector< T > dist(g.size(), INF);\n  vector< int > from(g.size(), -1),\
    \ id(g.size(), -1);\n  dist[s] = 0;\n  shortest_path(dist, from, id, s);\n  if(dist[t]\
    \ == INF) return {};\n\n  vector< pair< T, vector< int > > > A;\n  set< pair<\
    \ T, vector< int > > > B;\n  A.emplace_back(dist[t], restore(id, from, s, t));\n\
    \n  for(int i = 1; i < k; i++) {\n    dist.assign(g.size(), INF);\n    from.assign(g.size(),\
    \ -1);\n    id.assign(g.size(), -1);\n    dist[s] = 0;\n    vector< int > candidate(A.size());\n\
    \    iota(begin(candidate), end(candidate), 0);\n    auto &last_path = A.back().second;\n\
    \    int cur = s;\n    for(int j = 0; j < last_path.size(); j++) {\n      for(auto\
    \ &k : candidate) {\n        if(j < A[k].second.size()) dame[A[k].second[j]] =\
    \ timestamp;\n      }\n      vector< T > dist2{dist};\n      vector< int > from2{from},\
    \ id2{id};\n      shortest_path(dist2, from2, id2, cur);\n      ++timestamp;\n\
    \      if(dist2[t] != INF) {\n        auto path = restore(id2, from2, s, t);\n\
    \        bool ok = true;\n        for(auto &p : candidate) {\n          if(path\
    \ == A[p].second) {\n            ok = false;\n            break;\n          }\n\
    \        }\n        if(ok) B.emplace(dist2[t], path);\n      }\n      vector<\
    \ int > accept;\n      for(auto &k : candidate) {\n        if(j < A[k].second.size()\
    \ && A[k].second[j] == last_path[j]) {\n          accept.emplace_back(k);\n  \
    \      }\n      }\n      dist[malta[last_path[j]]] = dist[latte[last_path[j]]]\
    \ + cost[last_path[j]];\n      from[malta[last_path[j]]] = latte[last_path[j]];\n\
    \      id[malta[last_path[j]]] = last_path[j];\n      cur = malta[last_path[j]];\n\
    \      candidate = move(accept);\n    }\n    if(B.size()) {\n      A.emplace_back(*B.begin());\n\
    \      B.erase(B.begin());\n    }\n  }\n  return A;\n}\n#line 8 \"test/verify/yukicoder-1069.test.cpp\"\
    \n\nint main() {\n  int N, M, K;\n  cin >> N >> M >> K;\n  int X, Y;\n  cin >>\
    \ X >> Y;\n  --X, --Y;\n  vector< int > P(N), Q(N);\n  for(int i = 0; i < N; i++)\
    \ {\n    cin >> P[i] >> Q[i];\n  }\n  Graph< double > g(N);\n  vector< int > x(M\
    \ * 2), y(M * 2);\n  for(int i = 0; i < M; i++) {\n    int a, b;\n    cin >> a\
    \ >> b;\n    --a, --b;\n    g.add_directed_edge(a, b, hypot(P[a] - P[b], Q[a]\
    \ - Q[b]));\n    x[i] = a, y[i] = b;\n  }\n  for(int i = 0; i < M; i++) {\n  \
    \  int a = x[i], b = y[i];\n    x[i + M] = b, y[i + M] = a;\n    g.add_directed_edge(b,\
    \ a, hypot(P[a] - P[b], Q[a] - Q[b]));\n  }\n  auto ans = k_shortest_path(g, X,\
    \ Y, K);\n  for(int i = 0; i < K; i++) {\n    if(i < ans.size()) cout << ans[i].first\
    \ << \"\\n\";\n    else cout << -1 << \"\\n\";\n  }\n}\n"
  code: "#define ERROR \"1e-4\"\n#define PROBLEM \"https://yukicoder.me/problems/no/1069\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/graph-template.hpp\"\
    \n#include \"../../graph/shortest-path/k-shortest-path.hpp\"\n\nint main() {\n\
    \  int N, M, K;\n  cin >> N >> M >> K;\n  int X, Y;\n  cin >> X >> Y;\n  --X,\
    \ --Y;\n  vector< int > P(N), Q(N);\n  for(int i = 0; i < N; i++) {\n    cin >>\
    \ P[i] >> Q[i];\n  }\n  Graph< double > g(N);\n  vector< int > x(M * 2), y(M *\
    \ 2);\n  for(int i = 0; i < M; i++) {\n    int a, b;\n    cin >> a >> b;\n   \
    \ --a, --b;\n    g.add_directed_edge(a, b, hypot(P[a] - P[b], Q[a] - Q[b]));\n\
    \    x[i] = a, y[i] = b;\n  }\n  for(int i = 0; i < M; i++) {\n    int a = x[i],\
    \ b = y[i];\n    x[i + M] = b, y[i + M] = a;\n    g.add_directed_edge(b, a, hypot(P[a]\
    \ - P[b], Q[a] - Q[b]));\n  }\n  auto ans = k_shortest_path(g, X, Y, K);\n  for(int\
    \ i = 0; i < K; i++) {\n    if(i < ans.size()) cout << ans[i].first << \"\\n\"\
    ;\n    else cout << -1 << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/graph-template.hpp
  - graph/shortest-path/k-shortest-path.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-1069.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-1069.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-1069.test.cpp
- /verify/test/verify/yukicoder-1069.test.cpp.html
title: test/verify/yukicoder-1069.test.cpp
---
