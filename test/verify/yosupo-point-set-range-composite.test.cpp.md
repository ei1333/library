---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: structure/bbst/reversible-splay-tree.hpp
    title: "Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728)"
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/verify/yosupo-point-set-range-composite.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\
    \n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-point-set-range-composite.test.cpp\"\
    \n\n#line 1 \"structure/bbst/reversible-splay-tree.hpp\"\n/**\n * @brief Reversible-Splay-Tree(\u53CD\
    \u8EE2\u53EF\u80FDSplay\u6728)\n */\ntemplate< typename Monoid = int, typename\
    \ OperatorMonoid = void >\nstruct ReversibleSplayTree {\npublic:\n  using F =\
    \ function< Monoid(Monoid, Monoid) >;\n  using S = function< Monoid(Monoid) >;\n\
    \n  struct Node {\n    Node *l, *r, *p;\n    Monoid key, sum;\n    bool rev;\n\
    \    size_t sz;\n\n    bool is_root() const {\n      return !p || (p->l != this\
    \ && p->r != this);\n    }\n\n    Node(const Monoid &key) :\n        key(key),\
    \ sum(key), sz(1), rev(false),\n        l(nullptr), r(nullptr), p(nullptr) {}\n\
    \  };\n\n  ReversibleSplayTree(const F &f, const Monoid &M1) :\n      ReversibleSplayTree(f,\
    \ [](const Monoid &a) { return a; }, M1) {}\n\n  ReversibleSplayTree(const F &f,\
    \ const S &s, const Monoid &M1) :\n      f(f), s(s), M1(M1) {}\n\n\n  inline size_t\
    \ count(const Node *t) { return t ? t->sz : 0; }\n\n  inline const Monoid &sum(const\
    \ Node *t) { return t ? t->sum : M1; }\n\n  Node *alloc(const Monoid &v = Monoid())\
    \ {\n    return new Node(v);\n  }\n\n  void splay(Node *t) {\n    push(t);\n \
    \   while(!t->is_root()) {\n      auto *q = t->p;\n      if(q->is_root()) {\n\
    \        push(q), push(t);\n        if(q->l == t) rotr(t);\n        else rotl(t);\n\
    \      } else {\n        auto *r = q->p;\n        push(r), push(q), push(t);\n\
    \        if(r->l == q) {\n          if(q->l == t) rotr(q), rotr(t);\n        \
    \  else rotl(t), rotr(t);\n        } else {\n          if(q->r == t) rotl(q),\
    \ rotl(t);\n          else rotr(t), rotl(t);\n        }\n      }\n    }\n  }\n\
    \n  Node *push_front(Node *t, const Monoid &v = Monoid()) {\n    if(!t) {\n  \
    \    t = alloc(v);\n      return t;\n    } else {\n      splay(t);\n      Node\
    \ *cur = get_left(t), *z = alloc(v);\n      splay(cur);\n      z->p = cur;\n \
    \     cur->l = z;\n      splay(z);\n      return z;\n    }\n  }\n\n  Node *push_back(Node\
    \ *t, const Monoid &v = Monoid()) {\n    if(!t) {\n      t = alloc(v);\n     \
    \ return t;\n    } else {\n      splay(t);\n      Node *cur = get_right(t), *z\
    \ = alloc(v);\n      splay(cur);\n      z->p = cur;\n      cur->r = z;\n     \
    \ splay(z);\n      return z;\n    }\n  }\n\n  Node *erase(Node *t) {\n    splay(t);\n\
    \    Node *x = t->l, *y = t->r;\n    delete t;\n    if(!x) {\n      t = y;\n \
    \     if(t) t->p = nullptr;\n    } else if(!y) {\n      t = x;\n      t->p = nullptr;\n\
    \    } else {\n      x->p = nullptr;\n      t = get_right(x);\n      splay(t);\n\
    \      t->r = y;\n      y->p = t;\n    }\n    return t;\n  }\n\n  Node *get_left(Node\
    \ *t) const {\n    while(t->l) t = t->l;\n    return t;\n  }\n\n  Node *get_right(Node\
    \ *t) const {\n    while(t->r) t = t->r;\n    return t;\n  }\n\n  pair< Node *,\
    \ Node * > split(Node *t, int k) {\n    if(!t) return {nullptr, nullptr};\n  \
    \  push(t);\n    if(k <= count(t->l)) {\n      auto x = split(t->l, k);\n    \
    \  t->l = x.second;\n      t->p = nullptr;\n      if(x.second) x.second->p = t;\n\
    \      return {x.first, update(t)};\n    } else {\n      auto x = split(t->r,\
    \ k - count(t->l) - 1);\n      t->r = x.first;\n      t->p = nullptr;\n      if(x.first)\
    \ x.first->p = t;\n      return {update(t), x.second};\n    }\n  }\n\n  template<\
    \ typename ... Args >\n  Node *merge(Node *l, Args ...rest) {\n    Node *r = merge(rest...);\n\
    \    if(!l && !r) return nullptr;\n    if(!l) return splay(r), r;\n    if(!r)\
    \ return splay(l), l;\n    splay(l), splay(r);\n    l = get_right(l);\n    splay(l);\n\
    \    l->r = r;\n    r->p = l;\n    update(l);\n    return l;\n  }\n\n  void insert(Node\
    \ *&t, int k, const Monoid &v) {\n    splay(t);\n    auto x = split(t, k);\n \
    \   t = merge(merge(x.first, alloc(v)), x.second);\n  }\n\n  Monoid erase(Node\
    \ *&t, int k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    auto v = y.first->c;\n    delete y.first;\n    t = merge(x.first, y.second);\n\
    \    return v;\n  }\n\n  Monoid query(Node *&t, int a, int b) {\n    splay(t);\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    auto ret\
    \ = sum(y.first);\n    t = merge(x.first, y.first, y.second);\n    return ret;\n\
    \  }\n\n  Node *build(const vector< Monoid > &v) {\n    return build(0, (int)\
    \ v.size(), v);\n  }\n\n  void toggle(Node *t) {\n    swap(t->l, t->r);\n    t->sum\
    \ = s(t->sum);\n    t->rev ^= true;\n  }\n\n  Node *update(Node *t) {\n    t->sz\
    \ = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum,\
    \ t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);\n \
    \   return t;\n  }\n\n  tuple< Node *, Node *, Node * > split3(Node *t, int a,\
    \ int b) {\n    splay(t);\n    auto x = split(t, a);\n    auto y = split(x.second,\
    \ b - a);\n    return make_tuple(x.first, y.first, y.second);\n  }\n\n  void push(Node\
    \ *t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n      if(t->r) toggle(t->r);\n\
    \      t->rev = false;\n    }\n  }\n\n  void set_element(Node *&t, int k, const\
    \ Monoid &x) {\n    splay(t);\n    sub_set_element(t, k, x);\n  }\n\nprivate:\n\
    \  const Monoid M1;\n  const F f;\n  const S s;\n\n  Node *build(int l, int r,\
    \ const vector< Monoid > &v) {\n    if(l + 1 >= r) return alloc(v[l]);\n    return\
    \ merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\n  Node\
    \ *sub_set_element(Node *&t, int k, const Monoid &x) {\n    push(t);\n    if(k\
    \ < count(t->l)) {\n      return sub_set_element(t->l, k, x);\n    } else if(k\
    \ == count(t->l)) {\n      t->key = x;\n      splay(t);\n      return t;\n   \
    \ } else {\n      return sub_set_element(t->r, k - count(t->l) - 1, x);\n    }\n\
    \  }\n\n\n  void rotr(Node *t) {\n    auto *x = t->p, *y = x->p;\n    if((x->l\
    \ = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n      update(y);\n    }\n  }\n\n  void rotl(Node *t) {\n    auto *x =\
    \ t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n\
    \    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n\
    \      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  Node *merge(Node\
    \ *l) {\n    return l;\n  }\n};\n#line 6 \"test/verify/yosupo-point-set-range-composite.test.cpp\"\
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
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 8 \"test/verify/yosupo-point-set-range-composite.test.cpp\"\
    \n\nusing mint = ModInt< 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N\
    \ >> Q;\n  using pi = pair< mint, mint >;\n  auto f = [](const pi &a, const pi\
    \ &b) -> pi {\n    return {a.first * b.first, a.second * b.first + b.second};\n\
    \  };\n  ReversibleSplayTree< pi > seg(f, pi(1, 0));\n  vector< pi > V(N);\n \
    \ for(int i = 0; i < N; i++) {\n    cin >> V[i].first >> V[i].second;\n  }\n \
    \ auto root = seg.build(V);\n  for(int i = 0; i < Q; i++) {\n    int t;\n    cin\
    \ >> t;\n    if(t == 0) {\n      int p;\n      mint a, b;\n      cin >> p >> a\
    \ >> b;\n      seg.set_element(root, p, pi(a, b));\n    } else {\n      int l,\
    \ r;\n      mint x;\n      cin >> l >> r >> x;\n      auto ret = seg.query(root,\
    \ l, r);\n      cout << ret.first * x + ret.second << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/bbst/reversible-splay-tree.hpp\"\
    \n\n#include \"../../math/combinatorics/mod-int.hpp\"\n\nusing mint = ModInt<\
    \ 998244353 >;\n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  using pi = pair<\
    \ mint, mint >;\n  auto f = [](const pi &a, const pi &b) -> pi {\n    return {a.first\
    \ * b.first, a.second * b.first + b.second};\n  };\n  ReversibleSplayTree< pi\
    \ > seg(f, pi(1, 0));\n  vector< pi > V(N);\n  for(int i = 0; i < N; i++) {\n\
    \    cin >> V[i].first >> V[i].second;\n  }\n  auto root = seg.build(V);\n  for(int\
    \ i = 0; i < Q; i++) {\n    int t;\n    cin >> t;\n    if(t == 0) {\n      int\
    \ p;\n      mint a, b;\n      cin >> p >> a >> b;\n      seg.set_element(root,\
    \ p, pi(a, b));\n    } else {\n      int l, r;\n      mint x;\n      cin >> l\
    \ >> r >> x;\n      auto ret = seg.query(root, l, r);\n      cout << ret.first\
    \ * x + ret.second << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/bbst/reversible-splay-tree.hpp
  - math/combinatorics/mod-int.hpp
  isVerificationFile: true
  path: test/verify/yosupo-point-set-range-composite.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-point-set-range-composite.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-point-set-range-composite.test.cpp
- /verify/test/verify/yosupo-point-set-range-composite.test.cpp.html
title: test/verify/yosupo-point-set-range-composite.test.cpp
---
