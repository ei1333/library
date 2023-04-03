---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/mst/boruvka.hpp
    title: "Boruvka(\u6700\u5C0F\u5168\u57DF\u6728)"
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A
  bundledCode: "#line 1 \"test/verify/aoj-grl-2-a-3.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A\"\n\n#line 1\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-2-a-3.test.cpp\"\
    \n\n#line 2 \"structure/union-find/union-find.hpp\"\n\nstruct UnionFind {\n  vector<\
    \ int > data;\n\n  UnionFind() = default;\n\n  explicit UnionFind(size_t sz) :\
    \ data(sz, -1) {}\n\n  bool unite(int x, int y) {\n    x = find(x), y = find(y);\n\
    \    if(x == y) return false;\n    if(data[x] > data[y]) swap(x, y);\n    data[x]\
    \ += data[y];\n    data[y] = x;\n    return true;\n  }\n\n  int find(int k) {\n\
    \    if(data[k] < 0) return (k);\n    return data[k] = find(data[k]);\n  }\n\n\
    \  int size(int k) {\n    return -data[find(k)];\n  }\n\n  bool same(int x, int\
    \ y) {\n    return find(x) == find(y);\n  }\n\n  vector< vector< int > > groups()\
    \ {\n    int n = (int) data.size();\n    vector< vector< int > > ret(n);\n   \
    \ for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n    }\n \
    \   ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int > &v) {\n\
    \      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n#line\
    \ 2 \"graph/mst/boruvka.hpp\"\n\n/**\n * @brief Boruvka(\u6700\u5C0F\u5168\u57DF\
    \u6728)\n * @docs docs/boruvka.md\n */\ntemplate< typename T >\nstruct Boruvka\
    \ {\nprivate:\n  size_t V;\n  UnionFind uf;\n  const T INF;\n\npublic:\n  explicit\
    \ Boruvka(size_t V, T INF = numeric_limits< T >::max()) : V(V), uf(V), INF(INF)\
    \ {}\n\n  inline int find(int k) {\n    return uf.find(k);\n  }\n\n  template<\
    \ typename F >\n  T build(const F &update) {\n    T ret = T();\n    while(uf.size(0)\
    \ < (int)V) {\n      vector< pair< T, int > > v(V, make_pair(INF, -1));\n    \
    \  update(v);\n      bool con = false;\n      for(int i = 0; i < (int)V; i++)\
    \ {\n        if(v[i].second >= 0 && uf.unite(i, v[i].second)) {\n          ret\
    \ += v[i].first;\n          con = true;\n        }\n      }\n      if(!con) return\
    \ INF;\n    }\n    return ret;\n  }\n};\n#line 6 \"test/verify/aoj-grl-2-a-3.test.cpp\"\
    \n\nint main() {\n  int V, E;\n  cin >> V >> E;\n  vector< int > X(E), Y(E), Z(E);\n\
    \  for(int i = 0; i < E; i++) {\n    cin >> X[i] >> Y[i] >> Z[i];\n  }\n  Boruvka<\
    \ int > mst(V);\n  auto f = [&](vector< pair< int, int > > &ret) {\n    for(int\
    \ i = 0; i < E; i++) {\n      X[i] = mst.find(X[i]);\n      Y[i] = mst.find(Y[i]);\n\
    \      if(X[i] == Y[i]) continue;\n      ret[X[i]] = min(ret[X[i]], make_pair(Z[i],\
    \ Y[i]));\n      ret[Y[i]] = min(ret[Y[i]], make_pair(Z[i], X[i]));\n    }\n \
    \   return ret;\n  };\n  cout << mst.build(f) << endl;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/mst/boruvka.hpp\"\
    \n\nint main() {\n  int V, E;\n  cin >> V >> E;\n  vector< int > X(E), Y(E), Z(E);\n\
    \  for(int i = 0; i < E; i++) {\n    cin >> X[i] >> Y[i] >> Z[i];\n  }\n  Boruvka<\
    \ int > mst(V);\n  auto f = [&](vector< pair< int, int > > &ret) {\n    for(int\
    \ i = 0; i < E; i++) {\n      X[i] = mst.find(X[i]);\n      Y[i] = mst.find(Y[i]);\n\
    \      if(X[i] == Y[i]) continue;\n      ret[X[i]] = min(ret[X[i]], make_pair(Z[i],\
    \ Y[i]));\n      ret[Y[i]] = min(ret[Y[i]], make_pair(Z[i], X[i]));\n    }\n \
    \   return ret;\n  };\n  cout << mst.build(f) << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/mst/boruvka.hpp
  - structure/union-find/union-find.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-2-a-3.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-2-a-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-2-a-3.test.cpp
- /verify/test/verify/aoj-grl-2-a-3.test.cpp.html
title: test/verify/aoj-grl-2-a-3.test.cpp
---
