---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/incremental-bridge-connectivity.hpp
    title: Incremental Bridge Connectivity
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/three-edge-connected-components.hpp
    title: graph/connected-components/three-edge-connected-components.hpp
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
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
    PROBLEM: https://judge.yosupo.jp/problem/three_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/three_edge_connected_components
  bundledCode: "#line 1 \"test/verify/yosupo-three-edge-connected-components.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/three_edge_connected_components\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-three-edge-connected-components.test.cpp\"\
    \n\n#line 2 \"graph/connected-components/three-edge-connected-components.hpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"graph/connected-components/incremental-bridge-connectivity.hpp\"\
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
    \ 4 \"graph/connected-components/incremental-bridge-connectivity.hpp\"\n\nstruct\
    \ IncrementalBridgeConnectivity {\nprivate:\n  UnionFind cc, bcc;\n  vector< int\
    \ > bbf;\n  size_t bridge;\n\n  int size() {\n    return bbf.size();\n  }\n\n\
    \  int par(int x) {\n    return bbf[x] == size() ? size() : bcc.find(bbf[x]);\n\
    \  }\n\n  int lca(int x, int y) {\n    unordered_set< int > used;\n    for(;;)\
    \ {\n      if(x != size()) {\n        if(!used.insert(x).second) return x;\n \
    \       x = par(x);\n      }\n      swap(x, y);\n    }\n  }\n\n  void compress(int\
    \ x, int y) {\n    while(bcc.find(x) != bcc.find(y)) {\n      int nxt = par(x);\n\
    \      bbf[x] = bbf[y];\n      bcc.unite(x, y);\n      x = nxt;\n      --bridge;\n\
    \    }\n  }\n\n  void link(int x, int y) {\n    int v = x, pre = y;\n    while(v\
    \ != size()) {\n      int nxt = par(v);\n      bbf[v] = pre;\n      pre = v;\n\
    \      v = nxt;\n    }\n  }\n\npublic:\n  IncrementalBridgeConnectivity() = default;\n\
    \n  explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), bbf(sz,\
    \ sz), bridge(0) {}\n\n  int find(int k) {\n    return bcc.find(k);\n  }\n\n \
    \ size_t bridge_size() const {\n    return bridge;\n  }\n\n  void add_edge(int\
    \ x, int y) {\n    x = bcc.find(x);\n    y = bcc.find(y);\n    if(cc.find(x) ==\
    \ cc.find(y)) {\n      int w = lca(x, y);\n      compress(x, w);\n      compress(y,\
    \ w);\n    } else {\n      if(cc.size(x) > cc.size(y)) swap(x, y);\n      link(x,\
    \ y);\n      cc.unite(x, y);\n      ++bridge;\n    }\n  }\n};\n#line 5 \"graph/connected-components/three-edge-connected-components.hpp\"\
    \n\ntemplate< typename T = int >\nstruct ThreeEdgeConnectedComponents : Graph<\
    \ T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ vector< int > > group;\n\n  void build() {\n    uf = UnionFind(g.size());\n\
    \    bcc = IncrementalBridgeConnectivity(g.size());\n    used.assign(g.size(),\
    \ 0);\n    in.assign(g.size(), 0);\n    out.assign(g.size(), 0);\n    deg.assign(g.size(),\
    \ 0);\n    low.assign(g.size(), g.size());\n    for(size_t from = 0; from < g.size();\
    \ from++) {\n      for(auto &to : g[from]) {\n        if((T)from < to) bcc.add_edge(from,\
    \ to);\n      }\n    }\n    int cnt = 0;\n    for(size_t i = 0; i < g.size();\
    \ i++) {\n      if(used[i]) continue;\n      vector< int > tmp;\n      dfs(i,\
    \ -1, tmp, cnt);\n      cnt++;\n    }\n    vector< int > id(g.size(), -1);\n \
    \   cnt = 0;\n    for(size_t i = 0; i < g.size(); i++) {\n      if(id[uf.find(i)]\
    \ == -1) id[uf.find(i)] = cnt++;\n    }\n    group.resize(cnt);\n    for(size_t\
    \ i = 0; i < g.size(); i++) {\n      group[id[uf.find(i)]].emplace_back(i);\n\
    \    }\n  }\n\n  int operator[](const int &k) {\n    return uf.find(k);\n  }\n\
    \nprivate:\n  vector< int > used;\n  vector< int > in, out, low, deg;\n  IncrementalBridgeConnectivity\
    \ bcc;\n  UnionFind uf;\n\n  void absorb(vector< int > &path, int v, int w = -1)\
    \ {\n    while(!path.empty()) {\n      int x = path.back();\n      if(w != -1\
    \ && (in[x] > in[w] or in[w] >= out[x])) break;\n      path.pop_back();\n    \
    \  uf.unite(v, x);\n      deg[v] += deg[x] - 2;\n    }\n  }\n\n  void dfs(int\
    \ idx, int p, vector< int > &path, int &k) {\n    used[idx] = 1;\n    in[idx]\
    \ = low[idx] = k++;\n    for(auto &to : g[idx]) {\n      if(idx == to || bcc.find(idx)\
    \ != bcc.find(to)) continue;\n      deg[idx]++;\n      if(to == p) {\n       \
    \ p = -1;\n        continue;\n      }\n      if(used[to]) {\n        if(in[idx]\
    \ > in[to]) {\n          if(in[to] < low[idx]) {\n            low[idx] = in[to];\n\
    \            absorb(path, idx);\n          }\n        } else {\n          deg[idx]\
    \ -= 2;\n          absorb(path, idx, to);\n        }\n      } else {\n       \
    \ vector< int > ps;\n        dfs(to, idx, ps, k);\n        if(deg[to] == 2) ps.pop_back();\n\
    \        if(low[to] < low[idx]) {\n          low[idx] = low[to];\n          absorb(path,\
    \ idx);\n          path = ps;\n        } else {\n          absorb(ps, idx);\n\
    \        }\n      }\n    }\n    out[idx] = k;\n    path.push_back(idx);\n  }\n\
    };\n\n#line 6 \"test/verify/yosupo-three-edge-connected-components.test.cpp\"\n\
    \nint main() {\n  int N, M;\n  cin >> N >> M;\n  ThreeEdgeConnectedComponents<>\
    \ g(N);\n  g.read(M, 0);\n  g.build();\n  cout << g.group.size() << \"\\n\";\n\
    \  for(auto &p : g.group) {\n    cout << p.size() << \" \" << p << \"\\n\";\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/three_edge_connected_components\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/connected-components/three-edge-connected-components.hpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  ThreeEdgeConnectedComponents<>\
    \ g(N);\n  g.read(M, 0);\n  g.build();\n  cout << g.group.size() << \"\\n\";\n\
    \  for(auto &p : g.group) {\n    cout << p.size() << \" \" << p << \"\\n\";\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/connected-components/three-edge-connected-components.hpp
  - graph/graph-template.hpp
  - graph/connected-components/incremental-bridge-connectivity.hpp
  - structure/union-find/union-find.hpp
  isVerificationFile: true
  path: test/verify/yosupo-three-edge-connected-components.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-three-edge-connected-components.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-three-edge-connected-components.test.cpp
- /verify/test/verify/yosupo-three-edge-connected-components.test.cpp.html
title: test/verify/yosupo-three-edge-connected-components.test.cpp
---
