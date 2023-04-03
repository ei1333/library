---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/connected-components/incremental-bridge-connectivity.hpp
    title: Incremental Bridge Connectivity
  - icon: ':question:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/two_edge_connected_components
  bundledCode: "#line 1 \"test/verify/yosupo-two-edge-connected-components-2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-two-edge-connected-components-2.test.cpp\"\
    \n\n#line 2 \"graph/connected-components/incremental-bridge-connectivity.hpp\"\
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
    \ y);\n      cc.unite(x, y);\n      ++bridge;\n    }\n  }\n};\n#line 6 \"test/verify/yosupo-two-edge-connected-components-2.test.cpp\"\
    \n\nint main() {\n  int n, m;\n  cin >> n >> m;\n  IncrementalBridgeConnectivity\
    \ ibc(n);\n  for(int i = 0; i < m; i++) {\n    int a, b;\n    cin >> a >> b;\n\
    \    ibc.add_edge(a, b);\n  }\n  vector< int > id(n, -1);\n  int k = 0;\n  vector<\
    \ vector< int > > ans(n);\n  for(int i = 0; i < n; i++) {\n    int r = ibc.find(i);\n\
    \    if(id[r] == -1) {\n      id[r] = k;\n      k += 1;\n    }\n    ans[id[r]].push_back(i);\n\
    \  }\n  cout << k << \"\\n\";\n  for(int i = 0; i < k; i++) {\n    cout << ans[i].size()\
    \ << \" \" << ans[i] << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/connected-components/incremental-bridge-connectivity.hpp\"\
    \n\nint main() {\n  int n, m;\n  cin >> n >> m;\n  IncrementalBridgeConnectivity\
    \ ibc(n);\n  for(int i = 0; i < m; i++) {\n    int a, b;\n    cin >> a >> b;\n\
    \    ibc.add_edge(a, b);\n  }\n  vector< int > id(n, -1);\n  int k = 0;\n  vector<\
    \ vector< int > > ans(n);\n  for(int i = 0; i < n; i++) {\n    int r = ibc.find(i);\n\
    \    if(id[r] == -1) {\n      id[r] = k;\n      k += 1;\n    }\n    ans[id[r]].push_back(i);\n\
    \  }\n  cout << k << \"\\n\";\n  for(int i = 0; i < k; i++) {\n    cout << ans[i].size()\
    \ << \" \" << ans[i] << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/connected-components/incremental-bridge-connectivity.hpp
  - structure/union-find/union-find.hpp
  isVerificationFile: true
  path: test/verify/yosupo-two-edge-connected-components-2.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/verify/yosupo-two-edge-connected-components-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-two-edge-connected-components-2.test.cpp
- /verify/test/verify/yosupo-two-edge-connected-components-2.test.cpp.html
title: test/verify/yosupo-two-edge-connected-components-2.test.cpp
---
