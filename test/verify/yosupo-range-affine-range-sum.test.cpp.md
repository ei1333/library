---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: structure/segment-tree/lazy-segment-tree.hpp
    title: "Lazy-Segment-Tree(\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\
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
  bundledCode: "#line 1 \"test/verify/yosupo-range-affine-range-sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#line\
    \ 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-range-affine-range-sum.test.cpp\"\
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
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/yosupo-range-affine-range-sum.test.cpp\"\
    \n\n#line 1 \"structure/segment-tree/lazy-segment-tree.hpp\"\n/**\n * @brief Lazy-Segment-Tree(\u9045\
    \u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs docs/lazy-segment-tree.md\n\
    \ */\ntemplate< typename T, typename E, typename F, typename G, typename H >\n\
    struct LazySegmentTree {\nprivate:\n  int n{}, sz{}, height{};\n  vector< T >\
    \ data;\n  vector< E > lazy;\n  const F f;\n  const G g;\n  const H h;\n  const\
    \ T ti;\n  const E ei;\n\n  inline void update(int k) {\n    data[k] = f(data[2\
    \ * k + 0], data[2 * k + 1]);\n  }\n\n  inline void all_apply(int k, const E &x)\
    \ {\n    data[k] = g(data[k], x);\n    if(k < sz) lazy[k] = h(lazy[k], x);\n \
    \ }\n\n  inline void propagate(int k) {\n    if(lazy[k] != ei) {\n      all_apply(2\
    \ * k + 0, lazy[k]);\n      all_apply(2 * k + 1, lazy[k]);\n      lazy[k] = ei;\n\
    \    }\n  }\n\npublic:\n  LazySegmentTree() = default;\n\n  explicit LazySegmentTree(int\
    \ n, const F f, const G g, const H h,\n                           const T &ti,\
    \ const E &ei)\n      : n(n), f(f), g(g), h(h), ti(ti), ei(ei) {\n    sz = 1;\n\
    \    height = 0;\n    while(sz < n) sz <<= 1, height++;\n    data.assign(2 * sz,\
    \ ti);\n    lazy.assign(2 * sz, ei);\n  }\n\n  explicit LazySegmentTree(const\
    \ vector< T > &v, const F f, const G g, const H h,\n                         \
    \  const T &ti, const E &ei)\n      : LazySegmentTree(v.size(), f, g, h, ti, ei)\
    \ {\n    build(v);\n  }\n\n  void build(const vector< T > &v) {\n    assert(n\
    \ == (int) v.size());\n    for(int k = 0; k < n; k++) data[k + sz] = v[k];\n \
    \   for(int k = sz - 1; k > 0; k--) update(k);\n  }\n\n  void set(int k, const\
    \ T &x) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k >> i);\n\
    \    data[k] = x;\n    for(int i = 1; i <= height; i++) update(k >> i);\n  }\n\
    \n  T get(int k) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k\
    \ >> i);\n    return data[k];\n  }\n\n  T operator[](int k) {\n    return get(k);\n\
    \  }\n\n  T prod(int l, int r) {\n    if(l >= r) return ti;\n    l += sz;\n  \
    \  r += sz;\n    for(int i = height; i > 0; i--) {\n      if(((l >> i) << i) !=\
    \ l) propagate(l >> i);\n      if(((r >> i) << i) != r) propagate((r - 1) >> i);\n\
    \    }\n    T L = ti, R = ti;\n    for(; l < r; l >>= 1, r >>= 1) {\n      if(l\
    \ & 1) L = f(L, data[l++]);\n      if(r & 1) R = f(data[--r], R);\n    }\n   \
    \ return f(L, R);\n  }\n\n  T all_prod() const {\n    return data[1];\n  }\n\n\
    \  void apply(int k, const E &x) {\n    k += sz;\n    for(int i = height; i >\
    \ 0; i--) propagate(k >> i);\n    data[k] = g(data[k], x);\n    for(int i = 1;\
    \ i <= height; i++) update(k >> i);\n  }\n\n  void apply(int l, int r, const E\
    \ &x) {\n    if(l >= r) return;\n    l += sz;\n    r += sz;\n    for(int i = height;\
    \ i > 0; i--) {\n      if(((l >> i) << i) != l) propagate(l >> i);\n      if(((r\
    \ >> i) << i) != r) propagate((r - 1) >> i);\n    }\n    {\n      int l2 = l,\
    \ r2 = r;\n      for(; l < r; l >>= 1, r >>= 1) {\n        if(l & 1) all_apply(l++,\
    \ x);\n        if(r & 1) all_apply(--r, x);\n      }\n      l = l2, r = r2;\n\
    \    }\n    for(int i = 1; i <= height; i++) {\n      if(((l >> i) << i) != l)\
    \ update(l >> i);\n      if(((r >> i) << i) != r) update((r - 1) >> i);\n    }\n\
    \  }\n\n  template< typename C >\n  int find_first(int l, const C &check) {\n\
    \    if(l >= n) return n;\n    l += sz;\n    for(int i = height; i > 0; i--) propagate(l\
    \ >> i);\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>= 1;\n    \
    \  if(check(f(sum, data[l]))) {\n        while(l < sz) {\n          propagate(l);\n\
    \          l <<= 1;\n          auto nxt = f(sum, data[l]);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            l++;\n          }\n        }\n      \
    \  return l + 1 - sz;\n      }\n      sum = f(sum, data[l++]);\n    } while((l\
    \ & -l) != l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int\
    \ r, const C &check) {\n    if(r <= 0) return -1;\n    r += sz;\n    for(int i\
    \ = height; i > 0; i--) propagate((r - 1) >> i);\n    T sum = ti;\n    do {\n\
    \      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n      if(check(f(data[r],\
    \ sum))) {\n        while(r < sz) {\n          propagate(r);\n          r = (r\
    \ << 1) + 1;\n          auto nxt = f(data[r], sum);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            r--;\n          }\n        }\n      \
    \  return r - sz;\n      }\n      sum = f(data[r], sum);\n    } while((r & -r)\
    \ != r);\n    return -1;\n  }\n};\n\ntemplate< typename T, typename E, typename\
    \ F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (int N, const F &f, const G &g, const H &h, const T &ti, const E &ei) {\n\
    \  return LazySegmentTree{N, f, g, h, ti, ei};\n}\n\ntemplate< typename T, typename\
    \ E, typename F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (const vector< T > &v, const F &f, const G &g, const H &h, const T &ti, const\
    \ E &ei) {\n  return LazySegmentTree{v, f, g, h, ti, ei};\n}\n#line 8 \"test/verify/yosupo-range-affine-range-sum.test.cpp\"\
    \n\nusing mint = ModInt< 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N\
    \ >> Q;\n  using pi = pair< mint, int >;\n  using qi = pair< mint, mint >;\n \
    \ auto f = [](const pi &a, const pi &b) -> pi {\n    return {a.first + b.first,\
    \ a.second + b.second};\n  };\n  auto g = [](const pi &a, const qi &b) -> pi {\n\
    \    return {a.first * b.first + mint(a.second) * b.second, a.second};\n  };\n\
    \  auto h = [](const qi &a, const qi &b) -> qi {\n    return {a.first * b.first,\
    \ a.second * b.first + b.second};\n  };\n  auto seg = get_lazy_segment_tree(N,\
    \ f, g, h, pi(0, 0), qi(1, 0));\n  for(int i = 0; i < N; i++) {\n    mint a;\n\
    \    cin >> a;\n    seg.set(i, pi(a, 1));\n  }\n  for(int i = 0; i < Q; i++) {\n\
    \    int t;\n    cin >> t;\n    if(t == 0) {\n      int l, r;\n      mint b, c;\n\
    \      cin >> l >> r >> b >> c;\n      seg.apply(l, r, qi(b, c));\n    } else\
    \ {\n      int l, r;\n      cin >> l >> r;\n      cout << seg.prod(l, r).first\
    \ << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../structure/segment-tree/lazy-segment-tree.hpp\"\n\nusing mint\
    \ = ModInt< 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  using\
    \ pi = pair< mint, int >;\n  using qi = pair< mint, mint >;\n  auto f = [](const\
    \ pi &a, const pi &b) -> pi {\n    return {a.first + b.first, a.second + b.second};\n\
    \  };\n  auto g = [](const pi &a, const qi &b) -> pi {\n    return {a.first *\
    \ b.first + mint(a.second) * b.second, a.second};\n  };\n  auto h = [](const qi\
    \ &a, const qi &b) -> qi {\n    return {a.first * b.first, a.second * b.first\
    \ + b.second};\n  };\n  auto seg = get_lazy_segment_tree(N, f, g, h, pi(0, 0),\
    \ qi(1, 0));\n  for(int i = 0; i < N; i++) {\n    mint a;\n    cin >> a;\n   \
    \ seg.set(i, pi(a, 1));\n  }\n  for(int i = 0; i < Q; i++) {\n    int t;\n   \
    \ cin >> t;\n    if(t == 0) {\n      int l, r;\n      mint b, c;\n      cin >>\
    \ l >> r >> b >> c;\n      seg.apply(l, r, qi(b, c));\n    } else {\n      int\
    \ l, r;\n      cin >> l >> r;\n      cout << seg.prod(l, r).first << \"\\n\";\n\
    \    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - structure/segment-tree/lazy-segment-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-range-affine-range-sum.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-range-affine-range-sum.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-range-affine-range-sum.test.cpp
- /verify/test/verify/yosupo-range-affine-range-sum.test.cpp.html
title: test/verify/yosupo-range-affine-range-sum.test.cpp
---
