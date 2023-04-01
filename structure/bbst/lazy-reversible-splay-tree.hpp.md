---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-set-range-composite-2.test.cpp
    title: test/verify/yosupo-point-set-range-composite-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Lazy-Reversible-Splay-Tree(\u9045\u5EF6\u4F1D\u642C\u53CD\u8EE2\
      \u53EF\u80FDSplay\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/bbst/lazy-reversible-splay-tree.hpp\"\n/**\n *\
    \ @brief Lazy-Reversible-Splay-Tree(\u9045\u5EF6\u4F1D\u642C\u53CD\u8EE2\u53EF\
    \u80FDSplay\u6728)\n */\ntemplate< typename Monoid = int, typename OperatorMonoid\
    \ = Monoid >\nstruct LazyReversibleSplayTree {\npublic:\n  using F = function<\
    \ Monoid(Monoid, Monoid) >;\n  using G = function< Monoid(Monoid, OperatorMonoid)\
    \ >;\n  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;\n\
    \  using S = function< Monoid(Monoid) >;\n\n  struct Node {\n    Node *l, *r,\
    \ *p;\n    Monoid key, sum;\n    OperatorMonoid lazy;\n    bool rev;\n    size_t\
    \ sz;\n\n    bool is_root() const {\n      return !p || (p->l != this && p->r\
    \ != this);\n    }\n\n    Node(const Monoid &key, const OperatorMonoid &om) :\n\
    \        key(key), sum(key), lazy(om), sz(1), rev(false),\n        l(nullptr),\
    \ r(nullptr), p(nullptr) {}\n  };\n\n  LazyReversibleSplayTree(const F &f, const\
    \ Monoid &M1) :\n      LazyReversibleSplayTree(f, [](const Monoid &a) { return\
    \ a; }, M1) {}\n\n  LazyReversibleSplayTree(const F &f, const S &s, const Monoid\
    \ &M1) :\n      LazyReversibleSplayTree(f, G(), H(), s, M1, OperatorMonoid())\
    \ {}\n\n  LazyReversibleSplayTree(const F &f, const G &g, const H &h, const S\
    \ &s,\n                          const Monoid &M1, const OperatorMonoid &OM0)\
    \ :\n      f(f), g(g), h(h), s(s), M1(M1), OM0(OM0) {}\n\n\n  inline size_t count(const\
    \ Node *t) { return t ? t->sz : 0; }\n\n  inline const Monoid &sum(const Node\
    \ *t) { return t ? t->sum : M1; }\n\n  Node *alloc(const Monoid &v = Monoid())\
    \ {\n    return new Node(v, OM0);\n  }\n\n  void splay(Node *t) {\n    push(t);\n\
    \    while(!t->is_root()) {\n      auto *q = t->p;\n      if(q->is_root()) {\n\
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
    \ *t) const {\n    while(t->r) t = t->r;\n    return t;\n  }\n\n  void set_propagate(Node\
    \ *&t, int a, int b, const OperatorMonoid &pp) {\n    splay(t);\n    auto x =\
    \ split(t, a);\n    auto y = split(x.second, b - a);\n    set_propagate(y.first,\
    \ pp);\n    t = merge(x.first, y.first, y.second);\n  }\n\n  virtual void set_propagate(Node\
    \ *&t, const OperatorMonoid &pp) {\n    splay(t);\n    propagate(t, pp);\n   \
    \ push(t);\n  }\n\n  pair< Node *, Node * > split(Node *t, int k) {\n    if(!t)\
    \ return {nullptr, nullptr};\n    push(t);\n    if(k <= count(t->l)) {\n     \
    \ auto x = split(t->l, k);\n      t->l = x.second;\n      t->p = nullptr;\n  \
    \    if(x.second) x.second->p = t;\n      return {x.first, update(t)};\n    }\
    \ else {\n      auto x = split(t->r, k - count(t->l) - 1);\n      t->r = x.first;\n\
    \      t->p = nullptr;\n      if(x.first) x.first->p = t;\n      return {update(t),\
    \ x.second};\n    }\n  }\n\n  tuple< Node *, Node *, Node * > split3(Node *t,\
    \ int a, int b) {\n    splay(t);\n    auto x = split(t, a);\n    auto y = split(x.second,\
    \ b - a);\n    return make_tuple(x.first, y.first, y.second);\n  }\n\n  template<\
    \ typename ... Args >\n  Node *merge(Node *l, Args ...rest) {\n    Node *r = merge(rest...);\n\
    \    if(!l && !r) return nullptr;\n    if(!l) return splay(r), r;\n    if(!r)\
    \ return splay(l), l;\n    splay(l), splay(r);\n    l = get_right(l);\n    splay(l);\n\
    \    l->r = r;\n    r->p = l;\n    update(l);\n    return l;\n  }\n\n  void insert(Node\
    \ *&t, int k, const Monoid &v) {\n    splay(t);\n    auto x = split(t, k);\n \
    \   t = merge(x.first, alloc(v), x.second);\n  }\n\n  Monoid erase(Node *&t, int\
    \ k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    auto v = y.first->c;\n    delete y.first;\n    t = merge(x.first, y.second);\n\
    \    return v;\n  }\n\n  Monoid query(Node *&t, int a, int b) {\n    splay(t);\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    auto ret\
    \ = sum(y.first);\n    t = merge(x.first, y.first, y.second);\n    return ret;\n\
    \  }\n\n  Node *build(const vector< Monoid > &v) {\n    return build(0, (int)\
    \ v.size(), v);\n  }\n\n  void toggle(Node *t) {\n    swap(t->l, t->r);\n    t->sum\
    \ = s(t->sum);\n    t->rev ^= true;\n  }\n\n  Node *update(Node *t) {\n    t->sz\
    \ = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum,\
    \ t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);\n \
    \   return t;\n  }\n\n  void push(Node *t) {\n    if(t->lazy != OM0) {\n     \
    \ if(t->l) propagate(t->l, t->lazy);\n      if(t->r) propagate(t->r, t->lazy);\n\
    \      t->lazy = OM0;\n    }\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n\
    \      if(t->r) toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  void set_element(Node\
    \ *&t, int k, const Monoid &x) {\n    splay(t);\n    sub_set_element(t, k, x);\n\
    \  }\n\nprivate:\n  const Monoid M1;\n  const OperatorMonoid OM0;\n  const F f;\n\
    \  const G g;\n  const H h;\n  const S s;\n\n  Node *build(int l, int r, const\
    \ vector< Monoid > &v) {\n    if(l + 1 >= r) return alloc(v[l]);\n    return merge(build(l,\
    \ (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\n  void propagate(Node\
    \ *t, const OperatorMonoid &x) {\n    t->lazy = h(t->lazy, x);\n    t->key = g(t->key,\
    \ x);\n    t->sum = g(t->sum, x);\n  }\n\n  void rotr(Node *t) {\n    auto *x\
    \ = t->p, *y = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p =\
    \ t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void\
    \ rotl(Node *t) {\n    auto *x = t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p\
    \ = x;\n    t->l = x, x->p = t;\n    update(x), update(t);\n    if((t->p = y))\
    \ {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n      update(y);\n\
    \    }\n  }\n\n  Node *merge(Node *l) {\n    return l;\n  }\n\n  Node *sub_set_element(Node\
    \ *&t, int k, const Monoid &x) {\n    push(t);\n    if(k < count(t->l)) {\n  \
    \    return sub_set_element(t->l, k, x);\n    } else if(k == count(t->l)) {\n\
    \      t->key = x;\n      splay(t);\n      return t;\n    } else {\n      return\
    \ sub_set_element(t->r, k - count(t->l) - 1, x);\n    }\n  }\n};\n"
  code: "/**\n * @brief Lazy-Reversible-Splay-Tree(\u9045\u5EF6\u4F1D\u642C\u53CD\u8EE2\
    \u53EF\u80FDSplay\u6728)\n */\ntemplate< typename Monoid = int, typename OperatorMonoid\
    \ = Monoid >\nstruct LazyReversibleSplayTree {\npublic:\n  using F = function<\
    \ Monoid(Monoid, Monoid) >;\n  using G = function< Monoid(Monoid, OperatorMonoid)\
    \ >;\n  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;\n\
    \  using S = function< Monoid(Monoid) >;\n\n  struct Node {\n    Node *l, *r,\
    \ *p;\n    Monoid key, sum;\n    OperatorMonoid lazy;\n    bool rev;\n    size_t\
    \ sz;\n\n    bool is_root() const {\n      return !p || (p->l != this && p->r\
    \ != this);\n    }\n\n    Node(const Monoid &key, const OperatorMonoid &om) :\n\
    \        key(key), sum(key), lazy(om), sz(1), rev(false),\n        l(nullptr),\
    \ r(nullptr), p(nullptr) {}\n  };\n\n  LazyReversibleSplayTree(const F &f, const\
    \ Monoid &M1) :\n      LazyReversibleSplayTree(f, [](const Monoid &a) { return\
    \ a; }, M1) {}\n\n  LazyReversibleSplayTree(const F &f, const S &s, const Monoid\
    \ &M1) :\n      LazyReversibleSplayTree(f, G(), H(), s, M1, OperatorMonoid())\
    \ {}\n\n  LazyReversibleSplayTree(const F &f, const G &g, const H &h, const S\
    \ &s,\n                          const Monoid &M1, const OperatorMonoid &OM0)\
    \ :\n      f(f), g(g), h(h), s(s), M1(M1), OM0(OM0) {}\n\n\n  inline size_t count(const\
    \ Node *t) { return t ? t->sz : 0; }\n\n  inline const Monoid &sum(const Node\
    \ *t) { return t ? t->sum : M1; }\n\n  Node *alloc(const Monoid &v = Monoid())\
    \ {\n    return new Node(v, OM0);\n  }\n\n  void splay(Node *t) {\n    push(t);\n\
    \    while(!t->is_root()) {\n      auto *q = t->p;\n      if(q->is_root()) {\n\
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
    \ *t) const {\n    while(t->r) t = t->r;\n    return t;\n  }\n\n  void set_propagate(Node\
    \ *&t, int a, int b, const OperatorMonoid &pp) {\n    splay(t);\n    auto x =\
    \ split(t, a);\n    auto y = split(x.second, b - a);\n    set_propagate(y.first,\
    \ pp);\n    t = merge(x.first, y.first, y.second);\n  }\n\n  virtual void set_propagate(Node\
    \ *&t, const OperatorMonoid &pp) {\n    splay(t);\n    propagate(t, pp);\n   \
    \ push(t);\n  }\n\n  pair< Node *, Node * > split(Node *t, int k) {\n    if(!t)\
    \ return {nullptr, nullptr};\n    push(t);\n    if(k <= count(t->l)) {\n     \
    \ auto x = split(t->l, k);\n      t->l = x.second;\n      t->p = nullptr;\n  \
    \    if(x.second) x.second->p = t;\n      return {x.first, update(t)};\n    }\
    \ else {\n      auto x = split(t->r, k - count(t->l) - 1);\n      t->r = x.first;\n\
    \      t->p = nullptr;\n      if(x.first) x.first->p = t;\n      return {update(t),\
    \ x.second};\n    }\n  }\n\n  tuple< Node *, Node *, Node * > split3(Node *t,\
    \ int a, int b) {\n    splay(t);\n    auto x = split(t, a);\n    auto y = split(x.second,\
    \ b - a);\n    return make_tuple(x.first, y.first, y.second);\n  }\n\n  template<\
    \ typename ... Args >\n  Node *merge(Node *l, Args ...rest) {\n    Node *r = merge(rest...);\n\
    \    if(!l && !r) return nullptr;\n    if(!l) return splay(r), r;\n    if(!r)\
    \ return splay(l), l;\n    splay(l), splay(r);\n    l = get_right(l);\n    splay(l);\n\
    \    l->r = r;\n    r->p = l;\n    update(l);\n    return l;\n  }\n\n  void insert(Node\
    \ *&t, int k, const Monoid &v) {\n    splay(t);\n    auto x = split(t, k);\n \
    \   t = merge(x.first, alloc(v), x.second);\n  }\n\n  Monoid erase(Node *&t, int\
    \ k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    auto v = y.first->c;\n    delete y.first;\n    t = merge(x.first, y.second);\n\
    \    return v;\n  }\n\n  Monoid query(Node *&t, int a, int b) {\n    splay(t);\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    auto ret\
    \ = sum(y.first);\n    t = merge(x.first, y.first, y.second);\n    return ret;\n\
    \  }\n\n  Node *build(const vector< Monoid > &v) {\n    return build(0, (int)\
    \ v.size(), v);\n  }\n\n  void toggle(Node *t) {\n    swap(t->l, t->r);\n    t->sum\
    \ = s(t->sum);\n    t->rev ^= true;\n  }\n\n  Node *update(Node *t) {\n    t->sz\
    \ = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum,\
    \ t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);\n \
    \   return t;\n  }\n\n  void push(Node *t) {\n    if(t->lazy != OM0) {\n     \
    \ if(t->l) propagate(t->l, t->lazy);\n      if(t->r) propagate(t->r, t->lazy);\n\
    \      t->lazy = OM0;\n    }\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n\
    \      if(t->r) toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  void set_element(Node\
    \ *&t, int k, const Monoid &x) {\n    splay(t);\n    sub_set_element(t, k, x);\n\
    \  }\n\nprivate:\n  const Monoid M1;\n  const OperatorMonoid OM0;\n  const F f;\n\
    \  const G g;\n  const H h;\n  const S s;\n\n  Node *build(int l, int r, const\
    \ vector< Monoid > &v) {\n    if(l + 1 >= r) return alloc(v[l]);\n    return merge(build(l,\
    \ (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\n  void propagate(Node\
    \ *t, const OperatorMonoid &x) {\n    t->lazy = h(t->lazy, x);\n    t->key = g(t->key,\
    \ x);\n    t->sum = g(t->sum, x);\n  }\n\n  void rotr(Node *t) {\n    auto *x\
    \ = t->p, *y = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p =\
    \ t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void\
    \ rotl(Node *t) {\n    auto *x = t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p\
    \ = x;\n    t->l = x, x->p = t;\n    update(x), update(t);\n    if((t->p = y))\
    \ {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n      update(y);\n\
    \    }\n  }\n\n  Node *merge(Node *l) {\n    return l;\n  }\n\n  Node *sub_set_element(Node\
    \ *&t, int k, const Monoid &x) {\n    push(t);\n    if(k < count(t->l)) {\n  \
    \    return sub_set_element(t->l, k, x);\n    } else if(k == count(t->l)) {\n\
    \      t->key = x;\n      splay(t);\n      return t;\n    } else {\n      return\
    \ sub_set_element(t->r, k - count(t->l) - 1, x);\n    }\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/bbst/lazy-reversible-splay-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-point-set-range-composite-2.test.cpp
documentation_of: structure/bbst/lazy-reversible-splay-tree.hpp
layout: document
redirect_from:
- /library/structure/bbst/lazy-reversible-splay-tree.hpp
- /library/structure/bbst/lazy-reversible-splay-tree.hpp.html
title: "Lazy-Reversible-Splay-Tree(\u9045\u5EF6\u4F1D\u642C\u53CD\u8EE2\u53EF\u80FD\
  Splay\u6728)"
---
