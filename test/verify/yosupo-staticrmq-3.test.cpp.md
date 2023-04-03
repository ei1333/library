---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/vector-pool.hpp
    title: other/vector-pool.hpp
  - icon: ':heavy_check_mark:'
    path: structure/bbst/red-black-tree.hpp
    title: "Red-Black-Tree(\u8D64\u9ED2\u6728)"
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/verify/yosupo-staticrmq-3.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-staticrmq-3.test.cpp\"\
    \n\n#line 1 \"other/vector-pool.hpp\"\ntemplate< class T >\nstruct VectorPool\
    \ {\n  vector< T > pool;\n  vector< T * > stock;\n  int ptr;\n\n  VectorPool()\
    \ = default;\n\n  VectorPool(int sz) : pool(sz), stock(sz) {}\n\n  inline T *alloc()\
    \ { return stock[--ptr]; }\n\n  inline void free(T *t) { stock[ptr++] = t; }\n\
    \n  void clear() {\n    ptr = (int) pool.size();\n    for(int i = 0; i < pool.size();\
    \ i++) stock[i] = &pool[i];\n  }\n};\n#line 6 \"test/verify/yosupo-staticrmq-3.test.cpp\"\
    \n\n#line 1 \"structure/bbst/red-black-tree.hpp\"\n/**\n * @brief Red-Black-Tree(\u8D64\
    \u9ED2\u6728)\n * @docs docs/red-black-tree.md\n */\ntemplate< typename Monoid,\
    \ typename F >\nstruct RedBlackTree {\npublic:\n  enum COLOR {\n    BLACK, RED\n\
    \  };\n\n  struct Node {\n    Node *l, *r;\n    COLOR color;\n    int level, cnt;\n\
    \    Monoid key, sum;\n\n    Node() {}\n\n    Node(const Monoid &k) :\n      \
    \  key(k), sum(k), l(nullptr), r(nullptr), color(BLACK), level(0), cnt(1) {}\n\
    \n    Node(Node *l, Node *r, const Monoid &k) :\n        key(k), color(RED), l(l),\
    \ r(r) {}\n\n    bool is_leaf() const {\n      return l == nullptr;\n    }\n \
    \ };\n\nprivate:\n  inline Node *alloc(Node *l, Node *r) {\n    auto t = &(*pool.alloc()\
    \ = Node(l, r, M1));\n    return update(t);\n  }\n\n  virtual Node *clone(Node\
    \ *t) {\n    return t;\n  }\n\n  Node *rotate(Node *t, bool b) {\n    t = clone(t);\n\
    \    Node *s;\n    if(b) {\n      s = clone(t->l);\n      t->l = s->r;\n     \
    \ s->r = t;\n    } else {\n      s = clone(t->r);\n      t->r = s->l;\n      s->l\
    \ = t;\n    }\n    update(t);\n    return update(s);\n  }\n\n  Node *submerge(Node\
    \ *l, Node *r) {\n    if(l->level < r->level) {\n      r = clone(r);\n      Node\
    \ *c = (r->l = submerge(l, r->l));\n      if(r->color == BLACK && c->color ==\
    \ RED && c->l && c->l->color == RED) {\n        r->color = RED;\n        c->color\
    \ = BLACK;\n        if(r->r->color == BLACK) return rotate(r, true);\n       \
    \ r->r->color = BLACK;\n      }\n      return update(r);\n    }\n    if(l->level\
    \ > r->level) {\n      l = clone(l);\n      Node *c = (l->r = submerge(l->r, r));\n\
    \      if(l->color == BLACK && c->color == RED && c->r && c->r->color == RED)\
    \ {\n        l->color = RED;\n        c->color = BLACK;\n        if(l->l->color\
    \ == BLACK) return rotate(l, false);\n        l->l->color = BLACK;\n      }\n\
    \      return update(l);\n    }\n    return alloc(l, r);\n  }\n\n  Node *build(int\
    \ l, int r, const vector< Monoid > &v) {\n    if(l + 1 >= r) return alloc(v[l]);\n\
    \    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\
    \n  Node *update(Node *t) {\n    t->cnt = count(t->l) + count(t->r) + (!t->l ||\
    \ !t->r);\n    t->level = t->l ? t->l->level + (t->l->color == BLACK) : 0;\n \
    \   t->sum = f(f(sum(t->l), t->key), sum(t->r));\n    return t;\n  }\n\n  void\
    \ dump(Node *r, typename vector< Monoid >::iterator &it) {\n    if(r->is_leaf())\
    \ {\n      *it++ = r->key;\n      return;\n    }\n    dump(r->l, it);\n    dump(r->r,\
    \ it);\n  }\n\n  Node *merge(Node *l) {\n    return l;\n  }\n\n  Monoid query(Node\
    \ *t, int a, int b, int l, int r) {\n    if(r <= a || b <= l) return M1;\n   \
    \ if(a <= l && r <= b) return t->sum;\n    return f(query(t->l, a, b, l, l + count(t->l)),\
    \ query(t->r, a, b, r - count(t->r), r));\n  }\n\npublic:\n\n  VectorPool< Node\
    \ > pool;\n  const F f;\n  const Monoid M1;\n\n  RedBlackTree(int sz, const F\
    \ &f, const Monoid &M1) :\n      pool(sz), M1(M1), f(f) { pool.clear(); }\n\n\n\
    \  inline Node *alloc(const Monoid &key) {\n    return &(*pool.alloc() = Node(key));\n\
    \  }\n\n  inline int count(const Node *t) { return t ? t->cnt : 0; }\n\n  inline\
    \ const Monoid &sum(const Node *t) { return t ? t->sum : M1; }\n\n  pair< Node\
    \ *, Node * > split(Node *t, int k) {\n    if(!t) return {nullptr, nullptr};\n\
    \    if(k == 0) return {nullptr, t};\n    if(k >= count(t)) return {t, nullptr};\n\
    \    t = clone(t);\n    Node *l = t->l, *r = t->r;\n    pool.free(t);\n    if(k\
    \ < count(l)) {\n      auto pp = split(l, k);\n      return {pp.first, merge(pp.second,\
    \ r)};\n    }\n    if(k > count(l)) {\n      auto pp = split(r, k - count(l));\n\
    \      return {merge(l, pp.first), pp.second};\n    }\n    return {l, r};\n  }\n\
    \n  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {\n    auto\
    \ x = split(t, a);\n    auto y = split(x.second, b - a);\n    return make_tuple(x.first,\
    \ y.first, y.second);\n  }\n\n  template< typename ... Args >\n  Node *merge(Node\
    \ *l, Args ...rest) {\n    Node *r = merge(rest...);\n    if(!l || !r) return\
    \ l ? l : r;\n    Node *c = submerge(l, r);\n    c->color = BLACK;\n    return\
    \ c;\n  }\n\n  Node *build(const vector< Monoid > &v) {\n    return build(0, (int)\
    \ v.size(), v);\n  }\n\n  vector< Monoid > dump(Node *r) {\n    vector< Monoid\
    \ > v((size_t) count(r));\n    auto it = begin(v);\n    dump(r, it);\n    return\
    \ v;\n  }\n\n  string to_string(Node *r) {\n    auto s = dump(r);\n    string\
    \ ret;\n    for(int i = 0; i < s.size(); i++) {\n      ret += std::to_string(s[i]);\n\
    \      ret += \", \";\n    }\n    return ret;\n  }\n\n  void insert(Node *&t,\
    \ int k, const Monoid &v) {\n    auto x = split(t, k);\n    t = merge(merge(x.first,\
    \ alloc(v)), x.second);\n  }\n\n  Monoid erase(Node *&t, int k) {\n    auto x\
    \ = split(t, k);\n    auto y = split(x.second, 1);\n    auto v = y.first->key;\n\
    \    pool.free(y.first);\n    t = merge(x.first, y.second);\n    return v;\n \
    \ }\n\n  Monoid query(Node *t, int a, int b) {\n    return query(t, a, b, 0, count(t));\n\
    \  }\n\n  void set_element(Node *&t, int k, const Monoid &x) {\n    t = clone(t);\n\
    \    if(t->is_leaf()) {\n      t->key = t->sum = x;\n      return;\n    }\n  \
    \  if(k < count(t->l)) set_element(t->l, k, x);\n    else set_element(t->r, k\
    \ - count(t->l), x);\n    t = update(t);\n  }\n\n  void push_front(Node *&t, const\
    \ Monoid &v) {\n    t = merge(alloc(v), t);\n  }\n\n  void push_back(Node *&t,\
    \ const Monoid &v) {\n    t = merge(t, alloc(v));\n  }\n\n  Monoid pop_front(Node\
    \ *&t) {\n    auto ret = split(t, 1);\n    t = ret.second;\n    return ret.first->key;\n\
    \  }\n\n  Monoid pop_back(Node *&t) {\n    auto ret = split(t, count(t) - 1);\n\
    \    t = ret.first;\n    return ret.second->key;\n  }\n};\n#line 8 \"test/verify/yosupo-staticrmq-3.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  cin\
    \ >> A;\n  auto f = [](int a, int b) { return min(a, b); };\n  RedBlackTree< int,\
    \ decltype(f) > rbt(2 * N, f, inf);\n  auto root = rbt.build(A);\n  while(Q--)\
    \ {\n    int l, r;\n    cin >> l >> r;\n    cout << rbt.query(root, l, r) << \"\
    \\n\";\n  }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../other/vector-pool.hpp\"\n\
    \n#include \"../../structure/bbst/red-black-tree.hpp\"\n\nint main() {\n  int\
    \ N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  cin >> A;\n  auto f = [](int\
    \ a, int b) { return min(a, b); };\n  RedBlackTree< int, decltype(f) > rbt(2 *\
    \ N, f, inf);\n  auto root = rbt.build(A);\n  while(Q--) {\n    int l, r;\n  \
    \  cin >> l >> r;\n    cout << rbt.query(root, l, r) << \"\\n\";\n  }\n}\n\n"
  dependsOn:
  - template/template.hpp
  - other/vector-pool.hpp
  - structure/bbst/red-black-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-staticrmq-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-staticrmq-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-staticrmq-3.test.cpp
- /verify/test/verify/yosupo-staticrmq-3.test.cpp.html
title: test/verify/yosupo-staticrmq-3.test.cpp
---
