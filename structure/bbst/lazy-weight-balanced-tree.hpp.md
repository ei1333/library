---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-range-affine-range-sum-3.test.cpp
    title: test/verify/yosupo-range-affine-range-sum-3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Lazy-Weight-Balanced-Tree(\u9045\u5EF6\u4F1D\u642C\u91CD\u307F\
      \u5E73\u8861\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/bbst/lazy-weight-balanced-tree.hpp\"\n/**\n *\
    \ @brief Lazy-Weight-Balanced-Tree(\u9045\u5EF6\u4F1D\u642C\u91CD\u307F\u5E73\u8861\
    \u6728)\n */\ntemplate< typename Monoid, typename OperatorMonoid, typename F,\
    \ typename G, typename H >\nstruct LazyWeightBalancedTree {\npublic:\n  struct\
    \ Node {\n    Node *l, *r;\n    int cnt;\n    Monoid key, sum;\n    OperatorMonoid\
    \ lazy;\n\n    Node() {}\n\n    Node(const Monoid &k, const OperatorMonoid &laz)\
    \ : key(k), sum(k), l(nullptr), r(nullptr), cnt(1), lazy(laz) {}\n\n    Node(Node\
    \ *l, Node *r, const Monoid &k, const OperatorMonoid &laz) : key(k), l(l), r(r),\
    \ lazy(laz) {}\n\n    bool is_leaf() { return !l || !r; }\n  };\n\nprivate:\n\
    \  Node *propagate(Node *t) {\n    t = clone(t);\n    if(t->lazy != OM0) {\n \
    \     if(t->is_leaf()) {\n        t->key = g(t->key, t->lazy);\n      } else {\n\
    \        if(t->l) {\n          t->l = clone(t->l);\n          t->l->lazy = h(t->l->lazy,\
    \ t->lazy);\n          t->l->sum = g(t->l->sum, t->lazy);\n        }\n       \
    \ if(t->r) {\n          t->r = clone(t->r);\n          t->r->lazy = h(t->r->lazy,\
    \ t->lazy);\n          t->r->sum = g(t->r->sum, t->lazy);\n        }\n      }\n\
    \      t->lazy = OM0;\n    }\n    return update(t);\n  }\n\n  Node *update(Node\
    \ *t) {\n    t->cnt = count(t->l) + count(t->r) + t->is_leaf();\n    t->sum =\
    \ f(f(sum(t->l), t->key), sum(t->r));\n    return t;\n  }\n\n  inline Node *alloc(Node\
    \ *l, Node *r) {\n    auto t = &(*pool.alloc() = Node(l, r, M1, OM0));\n    return\
    \ update(t);\n  }\n\n  Node *submerge(Node *l, Node *r) {\n    if(count(l) > count(r)\
    \ * 4) {\n      l = propagate(l);\n      auto nl = propagate(l->l);\n      auto\
    \ nr = submerge(l->r, r);\n      if(count(nl) * 4 >= count(nr)) {\n        l->r\
    \ = nr;\n        return update(l);\n      }\n      l->r = nr->l;\n      nr->l\
    \ = l;\n      update(l);\n      return update(nr);\n    }\n    if(count(l) * 4\
    \ < count(r)) {\n      r = propagate(r);\n      auto nl = submerge(l, r->l);\n\
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
    \    t = ret.first;\n    return ret.second->key;\n  }\n};\n"
  code: "/**\n * @brief Lazy-Weight-Balanced-Tree(\u9045\u5EF6\u4F1D\u642C\u91CD\u307F\
    \u5E73\u8861\u6728)\n */\ntemplate< typename Monoid, typename OperatorMonoid,\
    \ typename F, typename G, typename H >\nstruct LazyWeightBalancedTree {\npublic:\n\
    \  struct Node {\n    Node *l, *r;\n    int cnt;\n    Monoid key, sum;\n    OperatorMonoid\
    \ lazy;\n\n    Node() {}\n\n    Node(const Monoid &k, const OperatorMonoid &laz)\
    \ : key(k), sum(k), l(nullptr), r(nullptr), cnt(1), lazy(laz) {}\n\n    Node(Node\
    \ *l, Node *r, const Monoid &k, const OperatorMonoid &laz) : key(k), l(l), r(r),\
    \ lazy(laz) {}\n\n    bool is_leaf() { return !l || !r; }\n  };\n\nprivate:\n\
    \  Node *propagate(Node *t) {\n    t = clone(t);\n    if(t->lazy != OM0) {\n \
    \     if(t->is_leaf()) {\n        t->key = g(t->key, t->lazy);\n      } else {\n\
    \        if(t->l) {\n          t->l = clone(t->l);\n          t->l->lazy = h(t->l->lazy,\
    \ t->lazy);\n          t->l->sum = g(t->l->sum, t->lazy);\n        }\n       \
    \ if(t->r) {\n          t->r = clone(t->r);\n          t->r->lazy = h(t->r->lazy,\
    \ t->lazy);\n          t->r->sum = g(t->r->sum, t->lazy);\n        }\n      }\n\
    \      t->lazy = OM0;\n    }\n    return update(t);\n  }\n\n  Node *update(Node\
    \ *t) {\n    t->cnt = count(t->l) + count(t->r) + t->is_leaf();\n    t->sum =\
    \ f(f(sum(t->l), t->key), sum(t->r));\n    return t;\n  }\n\n  inline Node *alloc(Node\
    \ *l, Node *r) {\n    auto t = &(*pool.alloc() = Node(l, r, M1, OM0));\n    return\
    \ update(t);\n  }\n\n  Node *submerge(Node *l, Node *r) {\n    if(count(l) > count(r)\
    \ * 4) {\n      l = propagate(l);\n      auto nl = propagate(l->l);\n      auto\
    \ nr = submerge(l->r, r);\n      if(count(nl) * 4 >= count(nr)) {\n        l->r\
    \ = nr;\n        return update(l);\n      }\n      l->r = nr->l;\n      nr->l\
    \ = l;\n      update(l);\n      return update(nr);\n    }\n    if(count(l) * 4\
    \ < count(r)) {\n      r = propagate(r);\n      auto nl = submerge(l, r->l);\n\
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
    \    t = ret.first;\n    return ret.second->key;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/bbst/lazy-weight-balanced-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-range-affine-range-sum-3.test.cpp
documentation_of: structure/bbst/lazy-weight-balanced-tree.hpp
layout: document
redirect_from:
- /library/structure/bbst/lazy-weight-balanced-tree.hpp
- /library/structure/bbst/lazy-weight-balanced-tree.hpp.html
title: "Lazy-Weight-Balanced-Tree(\u9045\u5EF6\u4F1D\u642C\u91CD\u307F\u5E73\u8861\
  \u6728)"
---
