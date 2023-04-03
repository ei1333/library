---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/montgomery-mod-int.hpp
    title: Montgomery ModInt
  - icon: ':heavy_check_mark:'
    path: structure/others/permutation-tree.hpp
    title: "Permutation Tree(\u9806\u5217\u6728)"
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
    PROBLEM: https://yukicoder.me/problems/no/1720
    links:
    - https://yukicoder.me/problems/no/1720
  bundledCode: "#line 1 \"test/verify/yukicoder-1720.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1720\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-1720.test.cpp\"\
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
    \ E &ei) {\n  return LazySegmentTree{v, f, g, h, ti, ei};\n}\n#line 2 \"structure/others/permutation-tree.hpp\"\
    \n\n/**\n * @brief Permutation Tree(\u9806\u5217\u6728)\n * @docs docs/permutation-tree.md\n\
    \ * @see https://codeforces.com/blog/entry/78898\n */\nstruct PermutationTree\
    \ {\npublic:\n  enum NodeType {\n    JOIN_ASC,\n    JOIN_DESC,\n    LEAF,\n  \
    \  CUT\n  };\n\n  struct Node {\n    NodeType type;\n    int l, r; // [l, r)\n\
    \    int min_v, max_v; // [min_v, max_v)\n    vector< Node * > ch;\n\n    size_t\
    \ size() const { return r - l; }\n\n    bool is_join() const { return type ==\
    \ JOIN_ASC or type == JOIN_DESC; };\n\n    bool is_leaf() const { return type\
    \ == LEAF; }\n\n    bool is_cut() const { return type == CUT; }\n  };\n\n  using\
    \ NP = Node *;\n\n  PermutationTree() = default;\n\nprivate:\n  static void add_child(NP\
    \ t, NP c) {\n    t->ch.emplace_back(c);\n    t->l = min(t->l, c->l);\n    t->r\
    \ = max(t->r, c->r);\n    t->min_v = min(t->min_v, c->min_v);\n    t->max_v =\
    \ max(t->max_v, c->max_v);\n  }\n\npublic:\n  static NP build(vector< int > &A)\
    \ {\n    int n = (int) A.size();\n\n    vector< int > desc{-1};\n    vector< int\
    \ > asc{-1};\n    vector< NP > st;\n\n    auto f = [](int a, int b) { return min(a,\
    \ b); };\n    auto g = [](int a, int b) { return a + b; };\n    constexpr int\
    \ lim = (1 << 30) - 1;\n    auto seg = get_lazy_segment_tree(vector< int >(n),\
    \ f, g, g, lim, 0);\n\n    for(int i = 0; i < n; i++) {\n      while(~desc.back()\
    \ and A[i] > A[desc.back()]) {\n        seg.apply(desc[desc.size() - 2] + 1, desc.back()\
    \ + 1, A[i] - A[desc.back()]);\n        desc.pop_back();\n      }\n      while(~asc.back()\
    \ and A[i] < A[asc.back()]) {\n        seg.apply(asc[asc.size() - 2] + 1, asc.back()\
    \ + 1, A[asc.back()] - A[i]);\n        asc.pop_back();\n      }\n      desc.emplace_back(i);\n\
    \      asc.emplace_back(i);\n\n      NP t = new Node{LEAF, i, i + 1, A[i], A[i]\
    \ + 1, {}};\n      for(;;) {\n        NodeType type = CUT;\n        if(not st.empty())\
    \ {\n          if(st.back()->max_v == t->min_v) {\n            type = JOIN_ASC;\n\
    \          } else if(t->max_v == st.back()->min_v) {\n            type = JOIN_DESC;\n\
    \          }\n        }\n        if(type != CUT) {\n          NP r = st.back();\n\
    \          if(type != r->type) {\n            r = new Node{type, r->l, r->r, r->min_v,\
    \ r->max_v, {r}};\n          }\n          add_child(r, t);\n          st.pop_back();\n\
    \          t = r;\n        } else if(seg.prod(0, i + 1 - (int) t->size()) == 0)\
    \ {\n          t = new Node{CUT, t->l, t->r, t->min_v, t->max_v, {t}};\n     \
    \     do {\n            add_child(t, st.back());\n            st.pop_back();\n\
    \          } while(t->max_v - t->min_v != t->size());\n          reverse(begin(t->ch),\
    \ end(t->ch));\n        } else {\n          break;\n        }\n      }\n     \
    \ st.emplace_back(t);\n      seg.apply(0, i + 1, -1);\n    }\n    return st[0];\n\
    \  }\n};\n#line 6 \"test/verify/yukicoder-1720.test.cpp\"\n\n#line 1 \"math/combinatorics/montgomery-mod-int.hpp\"\
    \n/**\n * @brief Montgomery ModInt\n */\ntemplate< uint32_t mod, bool fast = false\
    \ >\nstruct MontgomeryModInt {\n  using mint = MontgomeryModInt;\n  using i32\
    \ = int32_t;\n  using i64 = int64_t;\n  using u32 = uint32_t;\n  using u64 = uint64_t;\n\
    \n  static constexpr u32 get_r() {\n    u32 ret = mod;\n    for(i32 i = 0; i <\
    \ 4; i++) ret *= 2 - mod * ret;\n    return ret;\n  }\n\n  static constexpr u32\
    \ r = get_r();\n  static constexpr u32 n2 = -u64(mod) % mod;\n\n  static_assert(r\
    \ * mod == 1, \"invalid, r * mod != 1\");\n  static_assert(mod < (1 << 30), \"\
    invalid, mod >= 2 ^ 30\");\n  static_assert((mod & 1) == 1, \"invalid, mod % 2\
    \ == 0\");\n\n  u32 x;\n\n  MontgomeryModInt() : x{} {}\n\n  MontgomeryModInt(const\
    \ i64 &a)\n      : x(reduce(u64(fast ? a : (a % mod + mod)) * n2)) {}\n\n  static\
    \ constexpr u32 reduce(const u64 &b) {\n    return u32(b >> 32) + mod - u32((u64(u32(b)\
    \ * r) * mod) >> 32);\n  }\n\n  mint &operator+=(const mint &p) {\n    if(i32(x\
    \ += p.x - 2 * mod) < 0) x += 2 * mod;\n    return *this;\n  }\n\n  mint &operator-=(const\
    \ mint &p) {\n    if(i32(x -= p.x) < 0) x += 2 * mod;\n    return *this;\n  }\n\
    \n  mint &operator*=(const mint &p) {\n    x = reduce(u64(x) * p.x);\n    return\
    \ *this;\n  }\n\n  mint &operator/=(const mint &p) {\n    *this *= p.inverse();\n\
    \    return *this;\n  }\n\n  mint operator-() const { return mint() - *this; }\n\
    \n  mint operator+(const mint &p) const { return mint(*this) += p; }\n\n  mint\
    \ operator-(const mint &p) const { return mint(*this) -= p; }\n\n  mint operator*(const\
    \ mint &p) const { return mint(*this) *= p; }\n\n  mint operator/(const mint &p)\
    \ const { return mint(*this) /= p; }\n\n  bool operator==(const mint &p) const\
    \ { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }\n\n \
    \ bool operator!=(const mint &p) const { return (x >= mod ? x - mod : x) != (p.x\
    \ >= mod ? p.x - mod : p.x); }\n\n  u32 get() const {\n    u32 ret = reduce(x);\n\
    \    return ret >= mod ? ret - mod : ret;\n  }\n\n  mint pow(u64 n) const {\n\
    \    mint ret(1), mul(*this);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  mint inverse()\
    \ const {\n    return pow(mod - 2);\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, const mint &p) {\n    return os << p.get();\n  }\n\n  friend istream &operator>>(istream\
    \ &is, mint &a) {\n    i64 t;\n    is >> t;\n    a = mint(t);\n    return is;\n\
    \  }\n\n  static u32 get_mod() { return mod; }\n};\n\nusing modint = MontgomeryModInt<\
    \ mod >;\n#line 8 \"test/verify/yukicoder-1720.test.cpp\"\n\nconst int MOD = 998244353;\n\
    using mint = MontgomeryModInt< MOD >;\n\nint main() {\n  int N, K;\n  cin >> N\
    \ >> K;\n  vector< int > A(N);\n  cin >> A;\n  for(auto &a: A) --a;\n  using NP\
    \ = PermutationTree::Node *;\n  auto dp = make_v< mint >(K + 1, N + 1);\n  dp[0][0]\
    \ = 1;\n  MFP([&](auto rec, NP r) -> void {\n    if(r->is_cut() or r->is_leaf())\
    \ {\n      for(int k = 0; k < K; k++) {\n        dp[k + 1][r->r] += dp[k][r->l];\n\
    \      }\n    }\n    vector< mint > sum(K);\n    for(auto &c: r->ch) {\n     \
    \ rec(c);\n      if(r->is_join()) {\n        for(int k = 0; k < K; k++) {\n  \
    \        dp[k + 1][c->r] += sum[k];\n          sum[k] += dp[k][c->l];\n      \
    \  }\n      }\n    }\n  })(PermutationTree::build(A));\n  for(int i = 1; i <=\
    \ K; i++) {\n    cout << dp[i][N] << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1720\"\n\n#include \"\
    ../../template/template.hpp\"\n\n#include \"../../structure/others/permutation-tree.hpp\"\
    \n\n#include \"../../math/combinatorics/montgomery-mod-int.hpp\"\n\nconst int\
    \ MOD = 998244353;\nusing mint = MontgomeryModInt< MOD >;\n\nint main() {\n  int\
    \ N, K;\n  cin >> N >> K;\n  vector< int > A(N);\n  cin >> A;\n  for(auto &a:\
    \ A) --a;\n  using NP = PermutationTree::Node *;\n  auto dp = make_v< mint >(K\
    \ + 1, N + 1);\n  dp[0][0] = 1;\n  MFP([&](auto rec, NP r) -> void {\n    if(r->is_cut()\
    \ or r->is_leaf()) {\n      for(int k = 0; k < K; k++) {\n        dp[k + 1][r->r]\
    \ += dp[k][r->l];\n      }\n    }\n    vector< mint > sum(K);\n    for(auto &c:\
    \ r->ch) {\n      rec(c);\n      if(r->is_join()) {\n        for(int k = 0; k\
    \ < K; k++) {\n          dp[k + 1][c->r] += sum[k];\n          sum[k] += dp[k][c->l];\n\
    \        }\n      }\n    }\n  })(PermutationTree::build(A));\n  for(int i = 1;\
    \ i <= K; i++) {\n    cout << dp[i][N] << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/permutation-tree.hpp
  - structure/segment-tree/lazy-segment-tree.hpp
  - math/combinatorics/montgomery-mod-int.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-1720.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-1720.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-1720.test.cpp
- /verify/test/verify/yukicoder-1720.test.cpp.html
title: test/verify/yukicoder-1720.test.cpp
---
