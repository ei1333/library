---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/others/maximum-clique.hpp
    title: "Maximum Clique(\u6700\u5927\u30AF\u30EA\u30FC\u30AF)"
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
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"test/verify/yosupo-maximum-independent-set-2.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n\n\
    #line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-maximum-independent-set-2.test.cpp\"\
    \n\n#line 2 \"graph/others/maximum-clique.hpp\"\n\n/**\n * @brief Maximum Clique(\u6700\
    \u5927\u30AF\u30EA\u30FC\u30AF)\n */\ntemplate< int V >\nstruct MaximumClique\
    \ {\n  using B = bitset< V >;\n  vector< B > g, col_buf;\n\n  struct P {\n   \
    \ int idx, col, deg;\n\n    P(int idx, int col, int deg) : idx(idx), col(col),\
    \ deg(deg) {}\n  };\n\n  MaximumClique() = default;\n\n  explicit MaximumClique(int\
    \ N) : g(N), col_buf(N) {}\n\n  void add_edge(int a, int b) {\n    g[a].set(b);\n\
    \    g[b].set(a);\n  }\n\n  vector< int > now, clique;\n\n  void dfs(vector< P\
    \ > &rem) {\n    if(clique.size() < now.size()) clique = now;\n    sort(begin(rem),\
    \ end(rem), [](const P &a, const P &b) {\n      return a.deg > b.deg;\n    });\n\
    \    int max_c = 1;\n    for(auto &p : rem) {\n      p.col = 0;\n      while((g[p.idx]\
    \ & col_buf[p.col]).any()) ++p.col;\n      max_c = max(max_c, p.idx + 1);\n  \
    \    col_buf[p.col].set(p.idx);\n    }\n    for(int i = 0; i < max_c; i++) col_buf[i].reset();\n\
    \    sort(begin(rem), end(rem), [&](const P &a, const P &b) {\n      return a.col\
    \ < b.col;\n    });\n    for(; !rem.empty(); rem.pop_back()) {\n      auto &p\
    \ = rem.back();\n      if(now.size() + p.col + 1 <= clique.size()) break;\n  \
    \    vector< P > nrem;\n      B bs;\n      for(auto &q : rem) {\n        if(g[p.idx][q.idx])\
    \ {\n          nrem.emplace_back(q.idx, -1, 0);\n          bs.set(q.idx);\n  \
    \      }\n      }\n      for(auto &q : nrem) {\n        q.deg = (bs & g[q.idx]).count();\n\
    \      }\n      now.emplace_back(p.idx);\n      dfs(nrem);\n      now.pop_back();\n\
    \    }\n  }\n\n  vector< int > solve() {\n    vector< P > remark;\n    for(size_t\
    \ i = 0; i < g.size(); i++) {\n      remark.emplace_back(i, -1, (int) g[i].size());\n\
    \    }\n    dfs(remark);\n    return clique;\n  }\n};\n#line 6 \"test/verify/yosupo-maximum-independent-set-2.test.cpp\"\
    \n\nint main() {\n  int V, E;\n  cin >> V >> E;\n  auto D = make_v< int >(V, V);\n\
    \  for(int i = 0; i < E; i++) {\n    int a, b;\n    cin >> a >> b;\n    D[a][b]\
    \ = D[b][a] = true;\n  }\n  MaximumClique< 40 > mc(V);\n  for(int i = 0; i < V;\
    \ i++) {\n    for(int j = 0; j < i; j++) {\n      if(!D[i][j]) mc.add_edge(i,\
    \ j);\n    }\n  }\n  auto ret = mc.solve();\n  cout << ret.size() << \"\\n\";\n\
    \  cout << ret << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/others/maximum-clique.hpp\"\
    \n\nint main() {\n  int V, E;\n  cin >> V >> E;\n  auto D = make_v< int >(V, V);\n\
    \  for(int i = 0; i < E; i++) {\n    int a, b;\n    cin >> a >> b;\n    D[a][b]\
    \ = D[b][a] = true;\n  }\n  MaximumClique< 40 > mc(V);\n  for(int i = 0; i < V;\
    \ i++) {\n    for(int j = 0; j < i; j++) {\n      if(!D[i][j]) mc.add_edge(i,\
    \ j);\n    }\n  }\n  auto ret = mc.solve();\n  cout << ret.size() << \"\\n\";\n\
    \  cout << ret << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/others/maximum-clique.hpp
  isVerificationFile: true
  path: test/verify/yosupo-maximum-independent-set-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-maximum-independent-set-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-maximum-independent-set-2.test.cpp
- /verify/test/verify/yosupo-maximum-independent-set-2.test.cpp.html
title: test/verify/yosupo-maximum-independent-set-2.test.cpp
---
