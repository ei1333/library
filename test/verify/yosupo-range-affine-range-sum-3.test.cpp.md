---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: other/vector-pool.hpp
    title: other/vector-pool.hpp
  - icon: ':heavy_check_mark:'
    path: structure/bbst/lazy-weight-balanced-tree.hpp
    title: "Lazy-Weight-Balanced-Tree(\u9045\u5EF6\u4F1D\u642C\u91CD\u307F\u5E73\u8861\
      \u6728)"
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/verify/yosupo-range-affine-range-sum-3.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-range-affine-range-sum-3.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-int.hpp\"\ntemplate< int mod >\nstruct ModInt\
    \ {\n  int x;\n\n  ModInt() : x(0) {}\n\n  ModInt(int64_t y) : x(y >= 0 ? y %\
    \ mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt &operator+=(const ModInt &p)\
    \ {\n    if((x += p.x) >= mod) x -= mod;\n    return *this;\n  }\n\n  ModInt &operator-=(const\
    \ ModInt &p) {\n    if((x += mod - p.x) >= mod) x -= mod;\n    return *this;\n\
    \  }\n\n  ModInt &operator*=(const ModInt &p) {\n    x = (int) (1LL * x * p.x\
    \ % mod);\n    return *this;\n  }\n\n  ModInt &operator/=(const ModInt &p) {\n\
    \    *this *= p.inverse();\n    return *this;\n  }\n\n  ModInt operator-() const\
    \ { return ModInt(-x); }\n\n  ModInt operator+(const ModInt &p) const { return\
    \ ModInt(*this) += p; }\n\n  ModInt operator-(const ModInt &p) const { return\
    \ ModInt(*this) -= p; }\n\n  ModInt operator*(const ModInt &p) const { return\
    \ ModInt(*this) *= p; }\n\n  ModInt operator/(const ModInt &p) const { return\
    \ ModInt(*this) /= p; }\n\n  bool operator==(const ModInt &p) const { return x\
    \ == p.x; }\n\n  bool operator!=(const ModInt &p) const { return x != p.x; }\n\
    \n  ModInt inverse() const {\n    int a = x, b = mod, u = 1, v = 0, t;\n    while(b\
    \ > 0) {\n      t = a / b;\n      swap(a -= t * b, b);\n      swap(u -= t * v,\
    \ v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt pow(int64_t n) const {\n\
    \    ModInt ret(1), mul(x);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream\
    \ &operator<<(ostream &os, const ModInt &p) {\n    return os << p.x;\n  }\n\n\
    \  friend istream &operator>>(istream &is, ModInt &a) {\n    int64_t t;\n    is\
    \ >> t;\n    a = ModInt< mod >(t);\n    return (is);\n  }\n\n  static int get_mod()\
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/yosupo-range-affine-range-sum-3.test.cpp\"\
    \n\n#line 1 \"other/vector-pool.hpp\"\ntemplate< class T >\nstruct VectorPool\
    \ {\n  vector< T > pool;\n  vector< T * > stock;\n  int ptr;\n\n  VectorPool()\
    \ = default;\n\n  VectorPool(int sz) : pool(sz), stock(sz) {}\n\n  inline T *alloc()\
    \ { return stock[--ptr]; }\n\n  inline void free(T *t) { stock[ptr++] = t; }\n\
    \n  void clear() {\n    ptr = (int) pool.size();\n    for(int i = 0; i < pool.size();\
    \ i++) stock[i] = &pool[i];\n  }\n};\n#line 8 \"test/verify/yosupo-range-affine-range-sum-3.test.cpp\"\
    \n\n#line 1 \"structure/bbst/lazy-weight-balanced-tree.hpp\"\n/**\n * @brief Lazy-Weight-Balanced-Tree(\u9045\
    \u5EF6\u4F1D\u642C\u91CD\u307F\u5E73\u8861\u6728)\n */\ntemplate< typename Monoid,\
    \ typename OperatorMonoid, typename F, typename G, typename H >\nstruct LazyWeightBalancedTree\
    \ {\npublic:\n  struct Node {\n    Node *l, *r;\n    int cnt;\n    Monoid key,\
    \ sum;\n    OperatorMonoid lazy;\n\n    Node() {}\n\n    Node(const Monoid &k,\
    \ const OperatorMonoid &laz) : key(k), sum(k), l(nullptr), r(nullptr), cnt(1),\
    \ lazy(laz) {}\n\n    Node(Node *l, Node *r, const Monoid &k, const OperatorMonoid\
    \ &laz) : key(k), l(l), r(r), lazy(laz) {}\n\n    bool is_leaf() { return !l ||\
    \ !r; }\n  };\n\nprivate:\n  Node *propagate(Node *t) {\n    t = clone(t);\n \
    \   if(t->lazy != OM0) {\n      if(t->is_leaf()) {\n        t->key = g(t->key,\
    \ t->lazy);\n      } else {\n        if(t->l) {\n          t->l = clone(t->l);\n\
    \          t->l->lazy = h(t->l->lazy, t->lazy);\n          t->l->sum = g(t->l->sum,\
    \ t->lazy);\n        }\n        if(t->r) {\n          t->r = clone(t->r);\n  \
    \        t->r->lazy = h(t->r->lazy, t->lazy);\n          t->r->sum = g(t->r->sum,\
    \ t->lazy);\n        }\n      }\n      t->lazy = OM0;\n    }\n    return update(t);\n\
    \  }\n\n  Node *update(Node *t) {\n    t->cnt = count(t->l) + count(t->r) + t->is_leaf();\n\
    \    t->sum = f(f(sum(t->l), t->key), sum(t->r));\n    return t;\n  }\n\n  inline\
    \ Node *alloc(Node *l, Node *r) {\n    auto t = &(*pool.alloc() = Node(l, r, M1,\
    \ OM0));\n    return update(t);\n  }\n\n  Node *submerge(Node *l, Node *r) {\n\
    \    if(count(l) > count(r) * 4) {\n      l = propagate(l);\n      auto nl = propagate(l->l);\n\
    \      auto nr = submerge(l->r, r);\n      if(count(nl) * 4 >= count(nr)) {\n\
    \        l->r = nr;\n        return update(l);\n      }\n      l->r = nr->l;\n\
    \      nr->l = l;\n      update(l);\n      return update(nr);\n    }\n    if(count(l)\
    \ * 4 < count(r)) {\n      r = propagate(r);\n      auto nl = submerge(l, r->l);\n\
    \      auto nr = propagate(r->r);\n      if(count(nl) <= count(nr) * 4) {\n  \
    \      r->l = nl;\n        return update(r);\n      }\n      r->l = nl->r;\n \
    \     nl->r = r;\n      update(r);\n      return update(nl);\n    }\n    return\
    \ alloc(l, r);\n  }\n\n  Node *build(int l, int r, const vector< Monoid > &v)\
    \ {\n    if(l + 1 >= r) return alloc(v[l]);\n    return merge(build(l, (l + r)\
    \ >> 1, v), build((l + r) >> 1, r, v));\n  }\n\n  void dump(Node *r, typename\
    \ vector< Monoid >::iterator &it, OperatorMonoid lazy) {\n    if(r->lazy != OM0)\
    \ lazy = h(lazy, r->lazy);\n    if(r->is_leaf()) {\n      *it++ = g(r->key, lazy);\n\
    \      return;\n    }\n    dump(r->l, it, lazy);\n    dump(r->r, it, lazy);\n\
    \  }\n\n  virtual Node *clone(Node *t) {\n    return t;\n  }\n\n  Node *merge(Node\
    \ *l) {\n    return l;\n  }\n\n\npublic:\n  VectorPool< Node > pool;\n  const\
    \ F f;\n  const G g;\n  const H h;\n  const Monoid M1;\n  const OperatorMonoid\
    \ OM0;\n\n  LazyWeightBalancedTree(int sz, const F &f, const G &g, const H &h,\
    \ const Monoid &M1, const OperatorMonoid &OM0)\n      : pool(sz), M1(M1), f(f),\
    \ g(g), h(h), OM0(OM0) {\n    pool.clear();\n  }\n\n  inline Node *alloc(const\
    \ Monoid &key) {\n    return &(*pool.alloc() = Node(key, OM0));\n  }\n\n  static\
    \ inline int count(const Node *t) { return t ? t->cnt : 0; }\n\n  inline const\
    \ Monoid &sum(const Node *t) { return t ? t->sum : M1; }\n\n  pair< Node *, Node\
    \ * > split(Node *t, int k) {\n    if(!t) return {nullptr, nullptr};\n    t =\
    \ propagate(t);\n    if(k == 0) return {nullptr, t};\n    if(k >= count(t)) return\
    \ {t, nullptr};\n    Node *l = t->l, *r = t->r;\n    pool.free(t);\n    if(k <\
    \ count(l)) {\n      auto pp = split(l, k);\n      return {pp.first, merge(pp.second,\
    \ r)};\n    }\n    if(k > count(l)) {\n      auto pp = split(r, k - count(l));\n\
    \      return {merge(l, pp.first), pp.second};\n    }\n    return {l, r};\n  }\n\
    \n  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {\n    auto\
    \ x = split(t, a);\n    auto y = split(x.second, b - a);\n    return make_tuple(x.first,\
    \ y.first, y.second);\n  }\n\n  template< typename ... Args >\n  Node *merge(Node\
    \ *l, Args ...rest) {\n    Node *r = merge(rest...);\n    if(!l || !r) return\
    \ l ? l : r;\n    return submerge(l, r);\n  }\n\n  Node *build(const vector< Monoid\
    \ > &v) {\n    return build(0, (int) v.size(), v);\n  }\n\n  vector< Monoid >\
    \ dump(Node *r) {\n    vector< Monoid > v((size_t) count(r));\n    auto it = begin(v);\n\
    \    dump(r, it, OM0);\n    return v;\n  }\n\n  string to_string(Node *r) {\n\
    \    auto s = dump(r);\n    string ret;\n    for(int i = 0; i < s.size(); i++)\
    \ {\n      ret += std::to_string(s[i]);\n      ret += \", \";\n    }\n    return\
    \ ret;\n  }\n\n  void insert(Node *&t, int k, const Monoid &v) {\n    auto x =\
    \ split(t, k);\n    t = merge(merge(x.first, alloc(v)), x.second);\n  }\n\n  Monoid\
    \ erase(Node *&t, int k) {\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    auto v = y.first->c;\n    pool.free(y.first);\n    t = merge(x.first,\
    \ y.second);\n    return v;\n  }\n\n  Monoid query(Node *&t, int a, int b) {\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    Monoid ret\
    \ = sum(y.first);\n    t = merge(x.first, y.first, y.second);\n    return ret;\n\
    \  }\n\n  void set_propagate(Node *&t, int a, int b, const OperatorMonoid &pp)\
    \ {\n    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    y.first->lazy\
    \ = h(y.first->lazy, pp);\n    t = merge(x.first, propagate(y.first), y.second);\n\
    \  }\n\n  void set_element(Node *&t, int k, const Monoid &x) {\n    t = propagate(t);\n\
    \    if(t->is_leaf()) {\n      t->key = t->sum = x;\n      return;\n    }\n  \
    \  if(k < count(t->l)) set_element(t->l, k, x);\n    else set_element(t->r, k\
    \ - count(t->l), x);\n    t = update(t);\n  }\n\n  void push_front(Node *&t, const\
    \ Monoid &v) {\n    t = merge(alloc(v), t);\n  }\n\n  void push_back(Node *&t,\
    \ const Monoid &v) {\n    t = merge(t, alloc(v));\n  }\n\n  Monoid pop_front(Node\
    \ *&t) {\n    auto ret = split(t, 1);\n    t = ret.second;\n    return ret.first->key;\n\
    \  }\n\n  Monoid pop_back(Node *&t) {\n    auto ret = split(t, count(t) - 1);\n\
    \    t = ret.first;\n    return ret.second->key;\n  }\n};\n#line 10 \"test/verify/yosupo-range-affine-range-sum-3.test.cpp\"\
    \n\nusing mint = ModInt< 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N\
    \ >> Q;\n  using pi = pair< mint, int >;\n  using qi = pair< mint, mint >;\n \
    \ auto f = [](const pi &a, const pi &b) -> pi {\n    return {a.first + b.first,\
    \ a.second + b.second};\n  };\n  auto g = [](const pi &a, const qi &b) -> pi {\n\
    \    return {a.first * b.first + mint(a.second) * b.second, a.second};\n  };\n\
    \  auto h = [](const qi &a, const qi &b) -> qi {\n    return {a.first * b.first,\
    \ a.second * b.first + b.second};\n  };\n  LazyWeightBalancedTree< pi, qi, decltype(f),\
    \ decltype(g), decltype(h) > rbt(2 * N, f, g, h, pi(0, 0), pi(1, 0));\n  vector<\
    \ pi > A(N);\n  for(int i = 0; i < N; i++) {\n    mint a;\n    cin >> a;\n   \
    \ A[i] = {a, 1};\n  }\n  auto root = rbt.build(A);\n  for(int i = 0; i < Q; i++)\
    \ {\n    int t;\n    cin >> t;\n    if(t == 0) {\n      int l, r;\n      mint\
    \ b, c;\n      cin >> l >> r >> b >> c;\n      rbt.set_propagate(root, l, r, qi(b,\
    \ c));\n    } else {\n      int l, r;\n      cin >> l >> r;\n      cout << rbt.query(root,\
    \ l, r).first << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../other/vector-pool.hpp\"\n\n#include \"../../structure/bbst/lazy-weight-balanced-tree.hpp\"\
    \n\nusing mint = ModInt< 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N\
    \ >> Q;\n  using pi = pair< mint, int >;\n  using qi = pair< mint, mint >;\n \
    \ auto f = [](const pi &a, const pi &b) -> pi {\n    return {a.first + b.first,\
    \ a.second + b.second};\n  };\n  auto g = [](const pi &a, const qi &b) -> pi {\n\
    \    return {a.first * b.first + mint(a.second) * b.second, a.second};\n  };\n\
    \  auto h = [](const qi &a, const qi &b) -> qi {\n    return {a.first * b.first,\
    \ a.second * b.first + b.second};\n  };\n  LazyWeightBalancedTree< pi, qi, decltype(f),\
    \ decltype(g), decltype(h) > rbt(2 * N, f, g, h, pi(0, 0), pi(1, 0));\n  vector<\
    \ pi > A(N);\n  for(int i = 0; i < N; i++) {\n    mint a;\n    cin >> a;\n   \
    \ A[i] = {a, 1};\n  }\n  auto root = rbt.build(A);\n  for(int i = 0; i < Q; i++)\
    \ {\n    int t;\n    cin >> t;\n    if(t == 0) {\n      int l, r;\n      mint\
    \ b, c;\n      cin >> l >> r >> b >> c;\n      rbt.set_propagate(root, l, r, qi(b,\
    \ c));\n    } else {\n      int l, r;\n      cin >> l >> r;\n      cout << rbt.query(root,\
    \ l, r).first << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - other/vector-pool.hpp
  - structure/bbst/lazy-weight-balanced-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-range-affine-range-sum-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-range-affine-range-sum-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-range-affine-range-sum-3.test.cpp
- /verify/test/verify/yosupo-range-affine-range-sum-3.test.cpp.html
title: test/verify/yosupo-range-affine-range-sum-3.test.cpp
---
