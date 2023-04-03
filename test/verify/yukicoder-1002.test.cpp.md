---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid-decomposition.hpp
    title: "Centroid-Decomosition(\u91CD\u5FC3\u5206\u89E3)"
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
    PROBLEM: https://yukicoder.me/problems/no/1002
    links:
    - https://yukicoder.me/problems/no/1002
  bundledCode: "#line 1 \"test/verify/yukicoder-1002.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1002\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-1002.test.cpp\"\
    \n\n#line 2 \"graph/tree/centroid-decomposition.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/centroid-decomposition.hpp\"\
    \n\n/**\n * @brief Centroid-Decomosition(\u91CD\u5FC3\u5206\u89E3)\n */\ntemplate<\
    \ typename T >\nstruct CentroidDecomposition : Graph< T > {\npublic:\n  using\
    \ Graph< T >::Graph;\n  using Graph< T >::g;\n  Graph< int > tree;\n\n  int build(int\
    \ t = 0) {\n    sub.assign(g.size(), 0);\n    v.assign(g.size(), 0);\n    tree\
    \ = Graph< int >(g.size());\n    return build_dfs(0);\n  }\n\n  explicit CentroidDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  vector< int > sub;\n  vector<\
    \ int > v;\n\n  inline int build_dfs(int idx, int par) {\n    sub[idx] = 1;\n\
    \    for(auto &to : g[idx]) {\n      if(to == par || v[to]) continue;\n      sub[idx]\
    \ += build_dfs(to, idx);\n    }\n    return sub[idx];\n  }\n\n  inline int search_centroid(int\
    \ idx, int par, const int mid) {\n    for(auto &to : g[idx]) {\n      if(to ==\
    \ par || v[to]) continue;\n      if(sub[to] > mid) return search_centroid(to,\
    \ idx, mid);\n    }\n    return idx;\n  }\n\n  inline int build_dfs(int idx) {\n\
    \    int centroid = search_centroid(idx, -1, build_dfs(idx, -1) / 2);\n    v[centroid]\
    \ = true;\n    for(auto &to : g[centroid]) {\n      if(!v[to]) tree.add_directed_edge(centroid,\
    \ build_dfs(to));\n    }\n    v[centroid] = false;\n    return centroid;\n  }\n\
    };\n#line 6 \"test/verify/yukicoder-1002.test.cpp\"\n\nint main() {\n  int N,\
    \ K;\n  cin >> N >> K;\n  CentroidDecomposition< int > g(N);\n  g.read(N - 1,\
    \ -1, true);\n  int root = g.build();\n  int64 ret = 0;\n  vector< int > used(N);\n\
    \n  map< pair< int, int >, int > mp;\n  int all;\n  map< int, int > mp2;\n  map<\
    \ int, int > mp3;\n\n\n  auto get_vec = MFP([&](auto get_vec, int idx, int par,\
    \ int a, int b) -> void {\n    if(b == -1) {\n      ret += all - mp2[a];\n   \
    \   ret += mp3[a];\n    } else {\n      ret++;\n      ret += mp2[a] + mp2[b];\n\
    \      ret += mp[minmax(a, b)];\n    }\n    for(auto &e : g.g[idx]) {\n      if(e.to\
    \ == par) continue;\n      if(used[e.to]) continue;\n      if(a == e.cost) {\n\
    \        get_vec(e.to, idx, e.cost, b);\n      } else if(b == -1 || b == e.cost)\
    \ {\n        get_vec(e.to, idx, a, e.cost);\n      }\n    }\n  });\n\n  auto add_vec\
    \ = MFP([&](auto add_vec, int idx, int par, int a, int b) -> void {\n    if(b\
    \ == -1) {\n      mp2[a]++;\n      all++;\n    } else {\n      mp[minmax(a, b)]++;\n\
    \      mp3[a]++;\n      mp3[b]++;\n    }\n    for(auto &e : g.g[idx]) {\n    \
    \  if(e.to == par) continue;\n      if(used[e.to]) continue;\n      if(a == e.cost)\
    \ {\n        add_vec(e.to, idx, e.cost, b);\n      } else if(b == -1 || b == e.cost)\
    \ {\n        add_vec(e.to, idx, a, e.cost);\n      }\n    }\n  });\n\n  auto rec\
    \ = MFP([&](auto rec, int idx) -> void {\n    used[idx] = true;\n    mp.clear();\n\
    \    mp2.clear();\n    mp3.clear();\n    all = 0;\n    for(auto &e : g.g[idx])\
    \ {\n      if(used[e.to]) continue;\n      get_vec(e.to, idx, e.cost, -1);\n \
    \     add_vec(e.to, idx, e.cost, -1);\n    }\n    for(auto &to : g.tree.g[idx])\
    \ {\n      rec(to);\n    }\n    used[idx] = false;\n  });\n  rec(root);\n  cout\
    \ << ret << endl;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1002\"\n\n#include \"\
    ../../template/template.hpp\"\n\n#include \"../../graph/tree/centroid-decomposition.hpp\"\
    \n\nint main() {\n  int N, K;\n  cin >> N >> K;\n  CentroidDecomposition< int\
    \ > g(N);\n  g.read(N - 1, -1, true);\n  int root = g.build();\n  int64 ret =\
    \ 0;\n  vector< int > used(N);\n\n  map< pair< int, int >, int > mp;\n  int all;\n\
    \  map< int, int > mp2;\n  map< int, int > mp3;\n\n\n  auto get_vec = MFP([&](auto\
    \ get_vec, int idx, int par, int a, int b) -> void {\n    if(b == -1) {\n    \
    \  ret += all - mp2[a];\n      ret += mp3[a];\n    } else {\n      ret++;\n  \
    \    ret += mp2[a] + mp2[b];\n      ret += mp[minmax(a, b)];\n    }\n    for(auto\
    \ &e : g.g[idx]) {\n      if(e.to == par) continue;\n      if(used[e.to]) continue;\n\
    \      if(a == e.cost) {\n        get_vec(e.to, idx, e.cost, b);\n      } else\
    \ if(b == -1 || b == e.cost) {\n        get_vec(e.to, idx, a, e.cost);\n     \
    \ }\n    }\n  });\n\n  auto add_vec = MFP([&](auto add_vec, int idx, int par,\
    \ int a, int b) -> void {\n    if(b == -1) {\n      mp2[a]++;\n      all++;\n\
    \    } else {\n      mp[minmax(a, b)]++;\n      mp3[a]++;\n      mp3[b]++;\n \
    \   }\n    for(auto &e : g.g[idx]) {\n      if(e.to == par) continue;\n      if(used[e.to])\
    \ continue;\n      if(a == e.cost) {\n        add_vec(e.to, idx, e.cost, b);\n\
    \      } else if(b == -1 || b == e.cost) {\n        add_vec(e.to, idx, a, e.cost);\n\
    \      }\n    }\n  });\n\n  auto rec = MFP([&](auto rec, int idx) -> void {\n\
    \    used[idx] = true;\n    mp.clear();\n    mp2.clear();\n    mp3.clear();\n\
    \    all = 0;\n    for(auto &e : g.g[idx]) {\n      if(used[e.to]) continue;\n\
    \      get_vec(e.to, idx, e.cost, -1);\n      add_vec(e.to, idx, e.cost, -1);\n\
    \    }\n    for(auto &to : g.tree.g[idx]) {\n      rec(to);\n    }\n    used[idx]\
    \ = false;\n  });\n  rec(root);\n  cout << ret << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/centroid-decomposition.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-1002.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-1002.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-1002.test.cpp
- /verify/test/verify/yukicoder-1002.test.cpp.html
title: test/verify/yukicoder-1002.test.cpp
---
