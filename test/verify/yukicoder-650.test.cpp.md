---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/heavy-light-decomposition.hpp
    title: "Heavy-Light-Decomposition(HL\u5206\u89E3)"
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: math/matrix/square-matrix.hpp
    title: "Square-Matrix(\u6B63\u65B9\u884C\u5217)"
  - icon: ':heavy_check_mark:'
    path: structure/segment-tree/segment-tree.hpp
    title: "Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
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
    PROBLEM: https://yukicoder.me/problems/no/650
    links:
    - https://yukicoder.me/problems/no/650
  bundledCode: "#line 1 \"test/verify/yukicoder-650.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/650\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-650.test.cpp\"\
    \n\n#line 2 \"graph/tree/heavy-light-decomposition.hpp\"\n\n#line 2 \"graph/graph-template.hpp\"\
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
    template< typename T = int >\nusing Edges = vector< Edge< T > >;\n#line 4 \"graph/tree/heavy-light-decomposition.hpp\"\
    \n\n/**\n * @brief Heavy-Light-Decomposition(HL\u5206\u89E3)\n * @see https://smijake3.hatenablog.com/entry/2019/09/15/200200\n\
    \ */\ntemplate< typename T = int >\nstruct HeavyLightDecomposition : Graph< T\
    \ > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > sz, in, out, head, rev, par, dep;\n\n  void build() {\n    sz.assign(g.size(),\
    \ 0);\n    in.assign(g.size(), 0);\n    out.assign(g.size(), 0);\n    head.assign(g.size(),\
    \ 0);\n    rev.assign(g.size(), 0);\n    par.assign(g.size(), 0);\n    dep.assign(g.size(),\
    \ 0);\n    dfs_sz(0, -1, 0);\n    int t = 0;\n    dfs_hld(0, -1, t);\n  }\n\n\
    \  /* k: 0-indexed */\n  int la(int v, int k) {\n    while(1) {\n      int u =\
    \ head[v];\n      if(in[v] - k >= in[u]) return rev[in[v] - k];\n      k -= in[v]\
    \ - in[u] + 1;\n      v = par[u];\n    }\n  }\n\n  int lca(int u, int v) const\
    \ {\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v);\n   \
    \   if(head[u] == head[v]) return u;\n    }\n  }\n\n  int dist(int u, int v) const\
    \ {\n    return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n  }\n\n  template< typename\
    \ E, typename Q, typename F, typename S >\n  E query(int u, int v, const E &ti,\
    \ const Q &q, const F &f, const S &s, bool edge = false) {\n    E l = ti, r =\
    \ ti;\n    for(;; v = par[head[v]]) {\n      if(in[u] > in[v]) swap(u, v), swap(l,\
    \ r);\n      if(head[u] == head[v]) break;\n      l = f(q(in[head[v]], in[v] +\
    \ 1), l);\n    }\n    return s(f(q(in[u] + edge, in[v] + 1), l), r);\n  }\n\n\
    \  template< typename E, typename Q, typename F >\n  E query(int u, int v, const\
    \ E &ti, const Q &q, const F &f, bool edge = false) {\n    return query(u, v,\
    \ ti, q, f, f, edge);\n  }\n\n  template< typename Q >\n  void add(int u, int\
    \ v, const Q &q, bool edge = false) {\n    for(;; v = par[head[v]]) {\n      if(in[u]\
    \ > in[v]) swap(u, v);\n      if(head[u] == head[v]) break;\n      q(in[head[v]],\
    \ in[v] + 1);\n    }\n    q(in[u] + edge, in[v] + 1);\n  }\n\n  /* {parent, child}\
    \ */\n  vector< pair< int, int > > compress(vector< int > &remark) {\n    auto\
    \ cmp = [&](int a, int b) { return in[a] < in[b]; };\n    sort(begin(remark),\
    \ end(remark), cmp);\n    remark.erase(unique(begin(remark), end(remark)), end(remark));\n\
    \    int K = (int) remark.size();\n    for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k\
    \ - 1], remark[k]));\n    sort(begin(remark), end(remark), cmp);\n    remark.erase(unique(begin(remark),\
    \ end(remark)), end(remark));\n    vector< pair< int, int > > es;\n    stack<\
    \ int > st;\n    for(auto &k : remark) {\n      while(!st.empty() && out[st.top()]\
    \ <= in[k]) st.pop();\n      if(!st.empty()) es.emplace_back(st.top(), k);\n \
    \     st.emplace(k);\n    }\n    return es;\n  }\n\n  explicit HeavyLightDecomposition(const\
    \ Graph< T > &g) : Graph< T >(g) {}\n\nprivate:\n  void dfs_sz(int idx, int p,\
    \ int d) {\n    dep[idx] = d;\n    par[idx] = p;\n    sz[idx] = 1;\n    if(g[idx].size()\
    \ && g[idx][0] == p) swap(g[idx][0], g[idx].back());\n    for(auto &to : g[idx])\
    \ {\n      if(to == p) continue;\n      dfs_sz(to, idx, d + 1);\n      sz[idx]\
    \ += sz[to];\n      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);\n    }\n \
    \ }\n\n  void dfs_hld(int idx, int p, int &times) {\n    in[idx] = times++;\n\
    \    rev[in[idx]] = idx;\n    for(auto &to : g[idx]) {\n      if(to == p) continue;\n\
    \      head[to] = (g[idx][0] == to ? head[idx] : to);\n      dfs_hld(to, idx,\
    \ times);\n    }\n    out[idx] = times;\n  }\n};\n#line 6 \"test/verify/yukicoder-650.test.cpp\"\
    \n\n#line 1 \"structure/segment-tree/segment-tree.hpp\"\n/**\n * @brief Segment\
    \ Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs docs/segment-tree.md\n\
    \ */\ntemplate< typename T, typename F >\nstruct SegmentTree {\n  int n, sz;\n\
    \  vector< T > seg;\n\n  const F f;\n  const T ti;\n\n  SegmentTree() = default;\n\
    \n  explicit SegmentTree(int n, const F f, const T &ti) : n(n), f(f), ti(ti) {\n\
    \    sz = 1;\n    while(sz < n) sz <<= 1;\n    seg.assign(2 * sz, ti);\n  }\n\n\
    \  explicit SegmentTree(const vector< T > &v, const F f, const T &ti) :\n    \
    \  SegmentTree((int) v.size(), f, ti) {\n    build(v);\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int k = 0; k <\
    \ n; k++) seg[k + sz] = v[k];\n    for(int k = sz - 1; k > 0; k--) {\n      seg[k]\
    \ = f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  void set(int k, const\
    \ T &x) {\n    k += sz;\n    seg[k] = x;\n    while(k >>= 1) {\n      seg[k] =\
    \ f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  T get(int k) const {\n \
    \   return seg[k + sz];\n  }\n\n  T operator[](const int &k) const {\n    return\
    \ get(k);\n  }\n\n  void apply(int k, const T &x) {\n    k += sz;\n    seg[k]\
    \ = f(seg[k], x);\n    while(k >>= 1) {\n      seg[k] = f(seg[2 * k + 0], seg[2\
    \ * k + 1]);\n    }\n  }\n\n  T prod(int l, int r) const {\n    T L = ti, R =\
    \ ti;\n    for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n      if(l & 1) L\
    \ = f(L, seg[l++]);\n      if(r & 1) R = f(seg[--r], R);\n    }\n    return f(L,\
    \ R);\n  }\n\n  T all_prod() const {\n    return seg[1];\n  }\n\n  template< typename\
    \ C >\n  int find_first(int l, const C &check) const {\n    if(l >= n) return\
    \ n;\n    l += sz;\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>=\
    \ 1;\n      if(check(f(sum, seg[l]))) {\n        while(l < sz) {\n          l\
    \ <<= 1;\n          auto nxt = f(sum, seg[l]);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            l++;\n          }\n        }\n        return\
    \ l + 1 - sz;\n      }\n      sum = f(sum, seg[l++]);\n    } while((l & -l) !=\
    \ l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int r,\
    \ const C &check) const {\n    if(r <= 0) return -1;\n    r += sz;\n    T sum\
    \ = ti;\n    do {\n      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n     \
    \ if(check(f(seg[r], sum))) {\n        while(r < sz) {\n          r = (r << 1)\
    \ + 1;\n          auto nxt = f(seg[r], sum);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            r--;\n          }\n        }\n        return\
    \ r - sz;\n      }\n      sum = f(seg[r], sum);\n    } while((r & -r) != r);\n\
    \    return -1;\n  }\n};\n\ntemplate< typename T, typename F >\nSegmentTree< T,\
    \ F > get_segment_tree(int N, const F &f, const T &ti) {\n  return SegmentTree{N,\
    \ f, ti};\n}\n\ntemplate< typename T, typename F >\nSegmentTree< T, F > get_segment_tree(const\
    \ vector< T > &v, const F &f, const T &ti) {\n  return SegmentTree{v, f, ti};\n\
    }\n#line 8 \"test/verify/yukicoder-650.test.cpp\"\n\n#line 1 \"math/combinatorics/mod-int.hpp\"\
    \ntemplate< int mod >\nstruct ModInt {\n  int x;\n\n  ModInt() : x(0) {}\n\n \
    \ ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt\
    \ &operator+=(const ModInt &p) {\n    if((x += p.x) >= mod) x -= mod;\n    return\
    \ *this;\n  }\n\n  ModInt &operator-=(const ModInt &p) {\n    if((x += mod - p.x)\
    \ >= mod) x -= mod;\n    return *this;\n  }\n\n  ModInt &operator*=(const ModInt\
    \ &p) {\n    x = (int) (1LL * x * p.x % mod);\n    return *this;\n  }\n\n  ModInt\
    \ &operator/=(const ModInt &p) {\n    *this *= p.inverse();\n    return *this;\n\
    \  }\n\n  ModInt operator-() const { return ModInt(-x); }\n\n  ModInt operator+(const\
    \ ModInt &p) const { return ModInt(*this) += p; }\n\n  ModInt operator-(const\
    \ ModInt &p) const { return ModInt(*this) -= p; }\n\n  ModInt operator*(const\
    \ ModInt &p) const { return ModInt(*this) *= p; }\n\n  ModInt operator/(const\
    \ ModInt &p) const { return ModInt(*this) /= p; }\n\n  bool operator==(const ModInt\
    \ &p) const { return x == p.x; }\n\n  bool operator!=(const ModInt &p) const {\
    \ return x != p.x; }\n\n  ModInt inverse() const {\n    int a = x, b = mod, u\
    \ = 1, v = 0, t;\n    while(b > 0) {\n      t = a / b;\n      swap(a -= t * b,\
    \ b);\n      swap(u -= t * v, v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt\
    \ pow(int64_t n) const {\n    ModInt ret(1), mul(x);\n    while(n > 0) {\n   \
    \   if(n & 1) ret *= mul;\n      mul *= mul;\n      n >>= 1;\n    }\n    return\
    \ ret;\n  }\n\n  friend ostream &operator<<(ostream &os, const ModInt &p) {\n\
    \    return os << p.x;\n  }\n\n  friend istream &operator>>(istream &is, ModInt\
    \ &a) {\n    int64_t t;\n    is >> t;\n    a = ModInt< mod >(t);\n    return (is);\n\
    \  }\n\n  static int get_mod() { return mod; }\n};\n\nusing modint = ModInt< mod\
    \ >;\n#line 1 \"math/matrix/square-matrix.hpp\"\n/**\n * @brief Square-Matrix(\u6B63\
    \u65B9\u884C\u5217)\n */\ntemplate< class T, size_t N >\nstruct SquareMatrix {\n\
    \  array< array< T, N >, N > A;\n\n  SquareMatrix() : A{{}} {}\n\n  size_t size()\
    \ const { return N; }\n\n  inline const array< T, N > &operator[](int k) const\
    \ {\n    return (A.at(k));\n  }\n\n  inline array< T, N > &operator[](int k) {\n\
    \    return (A.at(k));\n  }\n\n  static SquareMatrix add_identity() {\n    return\
    \ SquareMatrix();\n  }\n\n  static SquareMatrix mul_identity() {\n    SquareMatrix\
    \ mat;\n    for(size_t i = 0; i < N; i++) mat[i][i] = 1;\n    return mat;\n  }\n\
    \n  SquareMatrix &operator+=(const SquareMatrix &B) {\n    for(size_t i = 0; i\
    \ < N; i++) {\n      for(size_t j = 0; j < N; j++) {\n        (*this)[i][j] +=\
    \ B[i][j];\n      }\n    }\n    return *this;\n  }\n\n  SquareMatrix &operator-=(const\
    \ SquareMatrix &B) {\n    for(size_t i = 0; i < N; i++) {\n      for(size_t j\
    \ = 0; j < N; j++) {\n        (*this)[i][j] -= B[i][j];\n      }\n    }\n    return\
    \ *this;\n  }\n\n  SquareMatrix &operator*=(const SquareMatrix &B) {\n    array<\
    \ array< T, N >, N > C;\n    for(size_t i = 0; i < N; i++) {\n      for(size_t\
    \ j = 0; j < N; j++) {\n        for(size_t k = 0; k < N; k++) {\n          C[i][j]\
    \ = (C[i][j] + (*this)[i][k] * B[k][j]);\n        }\n      }\n    }\n    A.swap(C);\n\
    \    return (*this);\n  }\n\n  SquareMatrix &operator^=(uint64_t k) {\n    SquareMatrix\
    \ B = SquareMatrix::mul_identity();\n    while(k > 0) {\n      if(k & 1) B *=\
    \ *this;\n      *this *= *this;\n      k >>= 1LL;\n    }\n    A.swap(B.A);\n \
    \   return *this;\n  }\n\n  SquareMatrix operator+(const SquareMatrix &B) const\
    \ {\n    return SquareMatrix(*this) += B;\n  }\n\n  SquareMatrix operator-(const\
    \ SquareMatrix &B) const {\n    return SquareMatrix(*this) -= B;\n  }\n\n  SquareMatrix\
    \ operator*(const SquareMatrix &B) const {\n    return SquareMatrix(*this) *=\
    \ B;\n  }\n\n  SquareMatrix operator^(uint64_t k) const {\n    return SquareMatrix(*this)\
    \ ^= k;\n  }\n\n  friend ostream &operator<<(ostream &os, SquareMatrix &p) {\n\
    \    for(int i = 0; i < N; i++) {\n      os << \"[\";\n      for(int j = 0; j\
    \ < N; j++) {\n        os << p[i][j] << (j + 1 == N ? \"]\\n\" : \",\");\n   \
    \   }\n    }\n    return os;\n  }\n};\n#line 11 \"test/verify/yukicoder-650.test.cpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  vector< int > X(N), Y(N);\n  HeavyLightDecomposition<>\
    \ g(N);\n  for(int i = 1; i < N; i++) {\n    cin >> X[i] >> Y[i];\n    g.add_edge(X[i],\
    \ Y[i]);\n  }\n  g.build();\n  for(int i = 1; i < N; i++) {\n    if(g.in[X[i]]\
    \ > g.in[Y[i]]) swap(X[i], Y[i]);\n  }\n  using Mat = SquareMatrix< modint, 2\
    \ >;\n  auto f = [](const Mat &a, const Mat &b) { return a * b; };\n  auto seg\
    \ = get_segment_tree(N, f, Mat::mul_identity());\n  int Q;\n  cin >> Q;\n  while(Q--)\
    \ {\n    char x;\n    cin >> x;\n    if(x == 'x') {\n      int v;\n      cin >>\
    \ v;\n      Mat m;\n      cin >> m[0][0] >> m[0][1] >> m[1][0] >> m[1][1];\n \
    \     seg.set(g.in[Y[v + 1]], m);\n    } else {\n      int y, z;\n      cin >>\
    \ y >> z;\n      auto mat = g.query(y, z, Mat::mul_identity(), [&](int a, int\
    \ b) { return seg.prod(a, b); }, f, true);\n      cout << mat[0][0] << \" \" <<\
    \ mat[0][1] << \" \" << mat[1][0] << \" \" << mat[1][1] << \"\\n\";\n    }\n \
    \ }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/650\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../graph/tree/heavy-light-decomposition.hpp\"\n\n#include \"\
    ../../structure/segment-tree/segment-tree.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n#include \"../../math/matrix/square-matrix.hpp\"\n\nint main() {\n  int N;\n\
    \  cin >> N;\n  vector< int > X(N), Y(N);\n  HeavyLightDecomposition<> g(N);\n\
    \  for(int i = 1; i < N; i++) {\n    cin >> X[i] >> Y[i];\n    g.add_edge(X[i],\
    \ Y[i]);\n  }\n  g.build();\n  for(int i = 1; i < N; i++) {\n    if(g.in[X[i]]\
    \ > g.in[Y[i]]) swap(X[i], Y[i]);\n  }\n  using Mat = SquareMatrix< modint, 2\
    \ >;\n  auto f = [](const Mat &a, const Mat &b) { return a * b; };\n  auto seg\
    \ = get_segment_tree(N, f, Mat::mul_identity());\n  int Q;\n  cin >> Q;\n  while(Q--)\
    \ {\n    char x;\n    cin >> x;\n    if(x == 'x') {\n      int v;\n      cin >>\
    \ v;\n      Mat m;\n      cin >> m[0][0] >> m[0][1] >> m[1][0] >> m[1][1];\n \
    \     seg.set(g.in[Y[v + 1]], m);\n    } else {\n      int y, z;\n      cin >>\
    \ y >> z;\n      auto mat = g.query(y, z, Mat::mul_identity(), [&](int a, int\
    \ b) { return seg.prod(a, b); }, f, true);\n      cout << mat[0][0] << \" \" <<\
    \ mat[0][1] << \" \" << mat[1][0] << \" \" << mat[1][1] << \"\\n\";\n    }\n \
    \ }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/heavy-light-decomposition.hpp
  - graph/graph-template.hpp
  - structure/segment-tree/segment-tree.hpp
  - math/combinatorics/mod-int.hpp
  - math/matrix/square-matrix.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-650.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-650.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-650.test.cpp
- /verify/test/verify/yukicoder-650.test.cpp.html
title: test/verify/yukicoder-650.test.cpp
---
