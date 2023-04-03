---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/bipartite-flow.hpp
    title: "Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC)"
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
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"test/verify/yosupo-bipartitematching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n#line 1 \"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-bipartitematching.test.cpp\"\
    \n\n#line 1 \"graph/flow/bipartite-flow.hpp\"\n/**\n * @brief Bipartite Flow(\u4E8C\
    \u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC)\n * @docs docs/bipartite-flow.md\n\
    \ */\nstruct BipartiteFlow {\n  size_t n, m, time_stamp;\n  vector< vector< int\
    \ > > g, rg;\n  vector< int > match_l, match_r, dist, used, alive;\n  bool matched;\n\
    \npublic:\n  explicit BipartiteFlow(size_t n, size_t m) :\n      n(n), m(m), time_stamp(0),\
    \ g(n), rg(m), match_l(n, -1), match_r(m, -1), used(n), alive(n, 1), matched(false)\
    \ {}\n\n  void add_edge(int u, int v) {\n    g[u].push_back(v);\n    rg[v].emplace_back(u);\n\
    \  }\n\n  vector< pair< int, int > > max_matching() {\n    matched = true;\n \
    \   for(;;) {\n      build_augment_path();\n      ++time_stamp;\n      int flow\
    \ = 0;\n      for(int i = 0; i < (int)n; i++) {\n        if(match_l[i] == -1)\
    \ flow += find_min_dist_augment_path(i);\n      }\n      if(flow == 0) break;\n\
    \    }\n    vector< pair< int, int > > ret;\n    for(int i = 0; i < (int)n; i++)\
    \ {\n      if(match_l[i] >= 0) ret.emplace_back(i, match_l[i]);\n    }\n    return\
    \ ret;\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198\
    \ */\n  void erase_edge(int a, int b) {\n    if(match_l[a] == b) {\n      match_l[a]\
    \ = -1;\n      match_r[b] = -1;\n    }\n    g[a].erase(find(begin(g[a]), end(g[a]),\
    \ b));\n    rg[b].erase(find(begin(rg[b]), end(rg[b]), a));\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334\
    \ */\n  vector< pair< int, int > > lex_max_matching() {\n    if(!matched) max_matching();\n\
    \    for(auto &vs : g) sort(begin(vs), end(vs));\n    vector< pair< int, int >\
    \ > es;\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1 || alive[i]\
    \ == 0) {\n        continue;\n      }\n      match_r[match_l[i]] = -1;\n     \
    \ match_l[i] = -1;\n      ++time_stamp;\n      find_augment_path(i);\n      alive[i]\
    \ = 0;\n      es.emplace_back(i, match_l[i]);\n    }\n    return es;\n  }\n\n\
    \  vector< int > min_vertex_cover() {\n    auto visited = find_residual_path();\n\
    \    vector< int > ret;\n    for(int i = 0; i < (int)(n + m); i++) {\n      if(visited[i]\
    \ ^ (i < (int)n)) {\n        ret.emplace_back(i);\n      }\n    }\n    return\
    \ ret;\n  }\n\n  /* https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11 */\n\
    \  vector< int > lex_min_vertex_cover(const vector< int > &ord) {\n    assert(ord.size()\
    \ == n + m);\n    auto res = build_risidual_graph();\n    vector< vector< int\
    \ > > r_res(n + m + 2);\n    for(int i = 0; i < (int)(n + m + 2); i++) {\n   \
    \   for(auto &j : res[i]) r_res[j].emplace_back(i);\n    }\n    queue< int > que;\n\
    \    vector< int > visited(n + m + 2, -1);\n    auto expand_left = [&](int t)\
    \ {\n      if(visited[t] != -1) return;\n      que.emplace(t);\n      visited[t]\
    \ = 1;\n      while(!que.empty()) {\n        int idx = que.front();\n        que.pop();\n\
    \        for(auto &to : r_res[idx]) {\n          if(visited[to] != -1) continue;\n\
    \          visited[to] = 1;\n          que.emplace(to);\n        }\n      }\n\
    \    };\n    auto expand_right = [&](int t) {\n      if(visited[t] != -1) return;\n\
    \      que.emplace(t);\n      visited[t] = 0;\n      while(!que.empty()) {\n \
    \       int idx = que.front();\n        que.pop();\n        for(auto &to : res[idx])\
    \ {\n          if(visited[to] != -1) continue;\n          visited[to] = 0;\n \
    \         que.emplace(to);\n        }\n      }\n    };\n    expand_right(n + m);\n\
    \    expand_left(n + m + 1);\n    vector< int > ret;\n    for(auto &t : ord) {\n\
    \      if(t < (int)n) {\n        expand_left(t);\n        if(visited[t] & 1) ret.emplace_back(t);\n\
    \      } else {\n        expand_right(t);\n        if(~visited[t] & 1) ret.emplace_back(t);\n\
    \      }\n    }\n    return ret;\n  }\n\n\n  vector< int > max_independent_set()\
    \ {\n    auto visited = find_residual_path();\n    vector< int > ret;\n    for(int\
    \ i = 0; i < (int)(n + m); i++) {\n      if(visited[i] ^ (i >= (int)n)) {\n  \
    \      ret.emplace_back(i);\n      }\n    }\n    return ret;\n  }\n\n  vector<\
    \ pair< int, int > > min_edge_cover() {\n    auto es = max_matching();\n    for(int\
    \ i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) {\n        continue;\n\
    \      }\n      if(g[i].empty()) {\n        return {};\n      }\n      es.emplace_back(i,\
    \ g[i][0]);\n    }\n    for(int i = 0; i < (int)m; i++) {\n      if(match_r[i]\
    \ >= 0) {\n        continue;\n      }\n      if(rg[i].empty()) {\n        return\
    \ {};\n      }\n      es.emplace_back(rg[i][0], i);\n    }\n    return es;\n \
    \ }\n\n  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1\n  vector< vector< int\
    \ > > build_risidual_graph() {\n    if(!matched) max_matching();\n    const size_t\
    \ S = n + m;\n    const size_t T = n + m + 1;\n    vector< vector< int > > ris(n\
    \ + m + 2);\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1)\
    \ ris[S].emplace_back(i);\n      else ris[i].emplace_back(S);\n    }\n    for(int\
    \ i = 0; i < (int)m; i++) {\n      if(match_r[i] == -1) ris[i + n].emplace_back(T);\n\
    \      else ris[T].emplace_back(i + n);\n    }\n    for(int i = 0; i < (int)n;\
    \ i++) {\n      for(auto &j : g[i]) {\n        if(match_l[i] == j) ris[j + n].emplace_back(i);\n\
    \        else ris[i].emplace_back(j + n);\n      }\n    }\n    return ris;\n \
    \ }\n\nprivate:\n  vector< int > find_residual_path() {\n    auto res = build_risidual_graph();\n\
    \    queue< int > que;\n    vector< int > visited(n + m + 2);\n    que.emplace(n\
    \ + m);\n    visited[n + m] = true;\n    while(!que.empty()) {\n      int idx\
    \ = que.front();\n      que.pop();\n      for(auto &to : res[idx]) {\n       \
    \ if(visited[to]) continue;\n        visited[to] = true;\n        que.emplace(to);\n\
    \      }\n    }\n    return visited;\n  }\n\n  void build_augment_path() {\n \
    \   queue< int > que;\n    dist.assign(g.size(), -1);\n    for(int i = 0; i <\
    \ (int)n; i++) {\n      if(match_l[i] == -1) {\n        que.emplace(i);\n    \
    \    dist[i] = 0;\n      }\n    }\n    while(!que.empty()) {\n      int a = que.front();\n\
    \      que.pop();\n      for(auto &b : g[a]) {\n        int c = match_r[b];\n\
    \        if(c >= 0 && dist[c] == -1) {\n          dist[c] = dist[a] + 1;\n   \
    \       que.emplace(c);\n        }\n      }\n    }\n  }\n\n  bool find_min_dist_augment_path(int\
    \ a) {\n    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 && find_min_dist_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n\n  bool find_augment_path(int a) {\n\
    \    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp && find_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n};\n#line 6 \"test/verify/yosupo-bipartitematching.test.cpp\"\
    \n\nint main() {\n  int L, R, M;\n  cin >> L >> R >> M;\n  BipartiteFlow flow(L,\
    \ R);\n  for(int i = 0; i < M; i++) {\n    int a, b;\n    cin >> a >> b;\n   \
    \ flow.add_edge(a, b);\n  }\n  auto es = flow.max_matching();\n  cout << es.size()\
    \ << \"\\n\";\n  for(auto &p : es) cout << p.first << \" \" << p.second << \"\\\
    n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/bipartite-flow.hpp\"\
    \n\nint main() {\n  int L, R, M;\n  cin >> L >> R >> M;\n  BipartiteFlow flow(L,\
    \ R);\n  for(int i = 0; i < M; i++) {\n    int a, b;\n    cin >> a >> b;\n   \
    \ flow.add_edge(a, b);\n  }\n  auto es = flow.max_matching();\n  cout << es.size()\
    \ << \"\\n\";\n  for(auto &p : es) cout << p.first << \" \" << p.second << \"\\\
    n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/bipartite-flow.hpp
  isVerificationFile: true
  path: test/verify/yosupo-bipartitematching.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-bipartitematching.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-bipartitematching.test.cpp
- /verify/test/verify/yosupo-bipartitematching.test.cpp.html
title: test/verify/yosupo-bipartitematching.test.cpp
---
