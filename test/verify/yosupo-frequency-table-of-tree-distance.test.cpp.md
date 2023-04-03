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
    path: math/fft/fast-fourier-transform.hpp
    title: math/fft/fast-fourier-transform.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 1 \"test/verify/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-frequency-table-of-tree-distance.test.cpp\"\
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
    };\n#line 6 \"test/verify/yosupo-frequency-table-of-tree-distance.test.cpp\"\n\
    \n#line 1 \"math/fft/fast-fourier-transform.hpp\"\nnamespace FastFourierTransform\
    \ {\n  using real = double;\n\n  struct C {\n    real x, y;\n\n    C() : x(0),\
    \ y(0) {}\n\n    C(real x, real y) : x(x), y(y) {}\n\n    inline C operator+(const\
    \ C &c) const { return C(x + c.x, y + c.y); }\n\n    inline C operator-(const\
    \ C &c) const { return C(x - c.x, y - c.y); }\n\n    inline C operator*(const\
    \ C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }\n\n    inline\
    \ C conj() const { return C(x, -y); }\n  };\n\n  const real PI = acosl(-1);\n\
    \  int base = 1;\n  vector< C > rts = { {0, 0},\n                     {1, 0} };\n\
    \  vector< int > rev = {0, 1};\n\n\n  void ensure_base(int nbase) {\n    if(nbase\
    \ <= base) return;\n    rev.resize(1 << nbase);\n    rts.resize(1 << nbase);\n\
    \    for(int i = 0; i < (1 << nbase); i++) {\n      rev[i] = (rev[i >> 1] >> 1)\
    \ + ((i & 1) << (nbase - 1));\n    }\n    while(base < nbase) {\n      real angle\
    \ = PI * 2.0 / (1 << (base + 1));\n      for(int i = 1 << (base - 1); i < (1 <<\
    \ base); i++) {\n        rts[i << 1] = rts[i];\n        real angle_i = angle *\
    \ (2 * i + 1 - (1 << base));\n        rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));\n\
    \      }\n      ++base;\n    }\n  }\n\n  void fft(vector< C > &a, int n) {\n \
    \   assert((n & (n - 1)) == 0);\n    int zeros = __builtin_ctz(n);\n    ensure_base(zeros);\n\
    \    int shift = base - zeros;\n    for(int i = 0; i < n; i++) {\n      if(i <\
    \ (rev[i] >> shift)) {\n        swap(a[i], a[rev[i] >> shift]);\n      }\n   \
    \ }\n    for(int k = 1; k < n; k <<= 1) {\n      for(int i = 0; i < n; i += 2\
    \ * k) {\n        for(int j = 0; j < k; j++) {\n          C z = a[i + j + k] *\
    \ rts[j + k];\n          a[i + j + k] = a[i + j] - z;\n          a[i + j] = a[i\
    \ + j] + z;\n        }\n      }\n    }\n  }\n\n  vector< int64_t > multiply(const\
    \ vector< int > &a, const vector< int > &b) {\n    int need = (int) a.size() +\
    \ (int) b.size() - 1;\n    int nbase = 1;\n    while((1 << nbase) < need) nbase++;\n\
    \    ensure_base(nbase);\n    int sz = 1 << nbase;\n    vector< C > fa(sz);\n\
    \    for(int i = 0; i < sz; i++) {\n      int x = (i < (int) a.size() ? a[i] :\
    \ 0);\n      int y = (i < (int) b.size() ? b[i] : 0);\n      fa[i] = C(x, y);\n\
    \    }\n    fft(fa, sz);\n    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);\n\
    \    for(int i = 0; i <= (sz >> 1); i++) {\n      int j = (sz - i) & (sz - 1);\n\
    \      C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;\n      fa[j] = (fa[i]\
    \ * fa[i] - (fa[j] * fa[j]).conj()) * r;\n      fa[i] = z;\n    }\n    for(int\
    \ i = 0; i < (sz >> 1); i++) {\n      C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;\n\
    \      C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];\n      fa[i]\
    \ = A0 + A1 * s;\n    }\n    fft(fa, sz >> 1);\n    vector< int64_t > ret(need);\n\
    \    for(int i = 0; i < need; i++) {\n      ret[i] = llround(i & 1 ? fa[i >> 1].y\
    \ : fa[i >> 1].x);\n    }\n    return ret;\n  }\n};\n#line 8 \"test/verify/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  CentroidDecomposition< int > g(N);\n\
    \  g.read(N - 1, 0);\n  int root = g.build();\n  vector< int > used(N);\n  vector<\
    \ int64 > dist(N);\n  MFP([&](auto rec, int centroid) -> void {\n    used[centroid]\
    \ = true;\n    vector< int > cnt{1};\n    for(auto &ch : g.g[centroid]) {\n  \
    \    if(used[ch]) continue;\n      vector< int > num;\n      queue< tuple< int,\
    \ int, int > > que;\n      que.emplace(ch, centroid, 1);\n      while(!que.empty())\
    \ {\n        int idx, par, dep;\n        tie(idx, par, dep) = que.front();\n \
    \       que.pop();\n        if(cnt.size() <= dep) cnt.resize(dep + 1, 0);\n  \
    \      if(num.size() <= dep) num.resize(dep + 1, 0);\n        cnt[dep]++;\n  \
    \      num[dep]++;\n        for(auto &to : g.g[idx]) {\n          if(to == par\
    \ || used[to]) continue;\n          que.emplace(to.to, idx, dep + 1);\n      \
    \  }\n      }\n      auto ret = FastFourierTransform::multiply(num, num);\n  \
    \    for(int i = 0; i < ret.size(); i++) dist[i] -= ret[i];\n    }\n    auto ret\
    \ = FastFourierTransform::multiply(cnt, cnt);\n    for(int i = 0; i < ret.size();\
    \ i++) dist[i] += ret[i];\n    for(auto &to : g.tree.g[centroid]) rec(to);\n \
    \ })(root);\n  dist.erase(begin(dist));\n  for(auto &p : dist) p /= 2;\n  cout\
    \ << dist << \"\\n\";\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/tree/centroid-decomposition.hpp\"\
    \n\n#include \"../../math/fft/fast-fourier-transform.hpp\"\n\nint main() {\n \
    \ int N;\n  cin >> N;\n  CentroidDecomposition< int > g(N);\n  g.read(N - 1, 0);\n\
    \  int root = g.build();\n  vector< int > used(N);\n  vector< int64 > dist(N);\n\
    \  MFP([&](auto rec, int centroid) -> void {\n    used[centroid] = true;\n   \
    \ vector< int > cnt{1};\n    for(auto &ch : g.g[centroid]) {\n      if(used[ch])\
    \ continue;\n      vector< int > num;\n      queue< tuple< int, int, int > > que;\n\
    \      que.emplace(ch, centroid, 1);\n      while(!que.empty()) {\n        int\
    \ idx, par, dep;\n        tie(idx, par, dep) = que.front();\n        que.pop();\n\
    \        if(cnt.size() <= dep) cnt.resize(dep + 1, 0);\n        if(num.size()\
    \ <= dep) num.resize(dep + 1, 0);\n        cnt[dep]++;\n        num[dep]++;\n\
    \        for(auto &to : g.g[idx]) {\n          if(to == par || used[to]) continue;\n\
    \          que.emplace(to.to, idx, dep + 1);\n        }\n      }\n      auto ret\
    \ = FastFourierTransform::multiply(num, num);\n      for(int i = 0; i < ret.size();\
    \ i++) dist[i] -= ret[i];\n    }\n    auto ret = FastFourierTransform::multiply(cnt,\
    \ cnt);\n    for(int i = 0; i < ret.size(); i++) dist[i] += ret[i];\n    for(auto\
    \ &to : g.tree.g[centroid]) rec(to);\n  })(root);\n  dist.erase(begin(dist));\n\
    \  for(auto &p : dist) p /= 2;\n  cout << dist << \"\\n\";\n}\n\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/centroid-decomposition.hpp
  - graph/graph-template.hpp
  - math/fft/fast-fourier-transform.hpp
  isVerificationFile: true
  path: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
- /verify/test/verify/yosupo-frequency-table-of-tree-distance.test.cpp.html
title: test/verify/yosupo-frequency-table-of-tree-distance.test.cpp
---
