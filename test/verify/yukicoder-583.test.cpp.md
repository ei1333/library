---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/others/eulerian-trail.hpp
    title: "Eulerian Trail(\u30AA\u30A4\u30E9\u30FC\u8DEF)"
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
    PROBLEM: https://yukicoder.me/problems/no/583
    links:
    - https://yukicoder.me/problems/no/583
  bundledCode: "#line 1 \"test/verify/yukicoder-583.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/583\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-583.test.cpp\"\
    \n\n#line 2 \"graph/others/eulerian-trail.hpp\"\n\n#line 2 \"structure/union-find/union-find.hpp\"\
    \n\nstruct UnionFind {\n  vector< int > data;\n\n  UnionFind() = default;\n\n\
    \  explicit UnionFind(size_t sz) : data(sz, -1) {}\n\n  bool unite(int x, int\
    \ y) {\n    x = find(x), y = find(y);\n    if(x == y) return false;\n    if(data[x]\
    \ > data[y]) swap(x, y);\n    data[x] += data[y];\n    data[y] = x;\n    return\
    \ true;\n  }\n\n  int find(int k) {\n    if(data[k] < 0) return (k);\n    return\
    \ data[k] = find(data[k]);\n  }\n\n  int size(int k) {\n    return -data[find(k)];\n\
    \  }\n\n  bool same(int x, int y) {\n    return find(x) == find(y);\n  }\n\n \
    \ vector< vector< int > > groups() {\n    int n = (int) data.size();\n    vector<\
    \ vector< int > > ret(n);\n    for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n\
    \    }\n    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int >\
    \ &v) {\n      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n\
    #line 4 \"graph/others/eulerian-trail.hpp\"\n\n/**\n * @brief Eulerian Trail(\u30AA\
    \u30A4\u30E9\u30FC\u8DEF)\n * @docs docs/eulerian-trail.md\n */\ntemplate< bool\
    \ directed >\nstruct EulerianTrail {\n  vector< vector< pair< int, int > > > g;\n\
    \  vector< pair< int, int > > es;\n  int M;\n  vector< int > used_vertex, used_edge,\
    \ deg;\n\n  explicit EulerianTrail(int V) : g(V), M(0), used_vertex(V), deg(V)\
    \ {}\n\n  void add_edge(int a, int b) {\n    es.emplace_back(a, b);\n    g[a].emplace_back(b,\
    \ M);\n    if(directed) {\n      deg[a]++;\n      deg[b]--;\n    } else {\n  \
    \    g[b].emplace_back(a, M);\n      deg[a]++;\n      deg[b]++;\n    }\n    M++;\n\
    \  }\n\n  pair< int, int > get_edge(int idx) const {\n    return es[idx];\n  }\n\
    \n  vector< vector< int > > enumerate_eulerian_trail() {\n    if(directed) {\n\
    \      for(auto &p : deg) if(p != 0) return {};\n    } else {\n      for(auto\
    \ &p : deg) if(p & 1) return {};\n    }\n    used_edge.assign(M, 0);\n    vector<\
    \ vector< int > > ret;\n    for(int i = 0; i < (int) g.size(); i++) {\n      if(g[i].empty()\
    \ || used_vertex[i]) continue;\n      ret.emplace_back(go(i));\n    }\n    return\
    \ ret;\n  }\n\n  vector< vector< int > > enumerate_semi_eulerian_trail() {\n \
    \   UnionFind uf(g.size());\n    for(auto &p : es) uf.unite(p.first, p.second);\n\
    \    vector< vector< int > > group(g.size());\n    for(int i = 0; i < (int) g.size();\
    \ i++) group[uf.find(i)].emplace_back(i);\n    vector< vector< int > > ret;\n\
    \    used_edge.assign(M, 0);\n    for(auto &vs : group) {\n      if(vs.empty())\
    \ continue;\n      int latte = -1, malta = -1;\n      if(directed) {\n       \
    \ for(auto &p : vs) {\n          if(abs(deg[p]) > 1) {\n            return {};\n\
    \          } else if(deg[p] == 1) {\n            if(latte >= 0) return {};\n \
    \           latte = p;\n          }\n        }\n      } else {\n        for(auto\
    \ &p : vs) {\n          if(deg[p] & 1) {\n            if(latte == -1) latte =\
    \ p;\n            else if(malta == -1) malta = p;\n            else return {};\n\
    \          }\n        }\n      }\n      ret.emplace_back(go(latte == -1 ? vs.front()\
    \ : latte));\n      if(ret.back().empty()) ret.pop_back();\n    }\n    return\
    \ ret;\n  }\n\n  vector< int > go(int s) {\n    stack< pair< int, int > > st;\n\
    \    vector< int > ord;\n    st.emplace(s, -1);\n    while(!st.empty()) {\n  \
    \    int idx = st.top().first;\n      used_vertex[idx] = true;\n      if(g[idx].empty())\
    \ {\n        ord.emplace_back(st.top().second);\n        st.pop();\n      } else\
    \ {\n        auto e = g[idx].back();\n        g[idx].pop_back();\n        if(used_edge[e.second])\
    \ continue;\n        used_edge[e.second] = true;\n        st.emplace(e);\n   \
    \   }\n    }\n    ord.pop_back();\n    reverse(ord.begin(), ord.end());\n    return\
    \ ord;\n  }\n};\n#line 6 \"test/verify/yukicoder-583.test.cpp\"\n\nint main()\
    \ {\n  int N, M;\n  cin >> N >> M;\n  vector< int > A(M), B(M);\n  EulerianTrail<\
    \ false > et(N);\n  for(int i = 0; i < M; i++) {\n    cin >> A[i] >> B[i];\n \
    \   et.add_edge(A[i], B[i]);\n  }\n  if(et.enumerate_semi_eulerian_trail().size()\
    \ == 1) cout << \"YES\\n\";\n  else cout << \"NO\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/583\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../graph/others/eulerian-trail.hpp\"\n\nint main() {\n  int\
    \ N, M;\n  cin >> N >> M;\n  vector< int > A(M), B(M);\n  EulerianTrail< false\
    \ > et(N);\n  for(int i = 0; i < M; i++) {\n    cin >> A[i] >> B[i];\n    et.add_edge(A[i],\
    \ B[i]);\n  }\n  if(et.enumerate_semi_eulerian_trail().size() == 1) cout << \"\
    YES\\n\";\n  else cout << \"NO\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/others/eulerian-trail.hpp
  - structure/union-find/union-find.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-583.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-583.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-583.test.cpp
- /verify/test/verify/yukicoder-583.test.cpp.html
title: test/verify/yukicoder-583.test.cpp
---
