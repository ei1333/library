---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/others/cycle-detection.hpp
    title: "Cycle Detection(\u9589\u8DEF\u691C\u51FA)"
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
    PROBLEM: https://judge.yosupo.jp/problem/cycle_detection
    links:
    - https://judge.yosupo.jp/problem/cycle_detection
  bundledCode: "#line 1 \"test/verify/yosupo-cycle-detection.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-cycle-detection.test.cpp\"\
    \n\n#line 2 \"graph/others/cycle-detection.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/others/cycle-detection.hpp\"\
    \n\n/**\n * @brief Cycle Detection(\u9589\u8DEF\u691C\u51FA)\n * @docs docs/cycle-detection.md\n\
    \ */\ntemplate< typename T = int >\nstruct CycleDetection : Graph< T > {\n  using\
    \ Graph< T >::Graph;\n  using Graph< T >::g;\n\n  vector< int > used;\n  Edges<\
    \ T > pre, cycle;\n\n  bool dfs(int idx) {\n    used[idx] = 1;\n    for(auto &e\
    \ : g[idx]) {\n      if(used[e] == 0) {\n        pre[e] = e;\n        if(dfs(e))\
    \ return true;\n      } else if(used[e] == 1) {\n        int cur = idx;\n    \
    \    while(cur != e) {\n          cycle.emplace_back(pre[cur]);\n          cur\
    \ = pre[cur].from;\n        }\n        cycle.emplace_back(e);\n        return\
    \ true;\n      }\n    }\n\n    used[idx] = 2;\n    return false;\n  }\n\n  Edges<\
    \ T > build() {\n    used.assign(g.size(), 0);\n    pre.resize(g.size());\n  \
    \  for(int i = 0; i < (int) g.size(); i++) {\n      if(used[i] == 0 && dfs(i))\
    \ {\n        reverse(begin(cycle), end(cycle));\n        return cycle;\n     \
    \ }\n    }\n    return {};\n  }\n};\n#line 6 \"test/verify/yosupo-cycle-detection.test.cpp\"\
    \n\nint main() {\n    int N, M;\n    cin >> N >> M;\n    CycleDetection<> g(N);\n\
    \    g.read(M, 0, false, true);\n    auto ret = g.build();\n    if(ret.empty())\
    \ {\n        cout << -1 << \"\\n\";\n    } else {\n        cout << ret.size()\
    \ << \"\\n\";\n        for(auto& e : ret) cout << e.idx << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../graph/others/cycle-detection.hpp\"\
    \n\nint main() {\n    int N, M;\n    cin >> N >> M;\n    CycleDetection<> g(N);\n\
    \    g.read(M, 0, false, true);\n    auto ret = g.build();\n    if(ret.empty())\
    \ {\n        cout << -1 << \"\\n\";\n    } else {\n        cout << ret.size()\
    \ << \"\\n\";\n        for(auto& e : ret) cout << e.idx << \"\\n\";\n    }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/others/cycle-detection.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/yosupo-cycle-detection.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-cycle-detection.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-cycle-detection.test.cpp
- /verify/test/verify/yosupo-cycle-detection.test.cpp.html
title: test/verify/yosupo-cycle-detection.test.cpp
---
