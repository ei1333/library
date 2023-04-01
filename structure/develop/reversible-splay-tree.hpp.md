---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2450-3.test.cpp
    title: test/verify/aoj-2450-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
    title: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dynamic-tree-vertex-set-path-composite-2.test.cpp
    title: test/verify/yosupo-dynamic-tree-vertex-set-path-composite-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-set-range-composite-3.test.cpp
    title: test/verify/yosupo-point-set-range-composite-3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/develop/reversible-splay-tree.hpp\"\n/**\n * @brief\
    \ Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728)\n */\ntemplate< typename\
    \ Tp >\nstruct ReversibleSplayTreeNode {\n  using T = Tp;\n  ReversibleSplayTreeNode\
    \ *l, *r, *p;\n  T key, sum;\n  bool rev;\n  size_t sz;\n\n  ReversibleSplayTreeNode()\
    \ : ReversibleSplayTreeNode(Tp()) {}\n\n  ReversibleSplayTreeNode(const T &key)\
    \ :\n      key(key), sum(key), rev(false), l(nullptr), r(nullptr), p(nullptr),\
    \ sz(1) {}\n};\n\ntemplate< typename Np >\nstruct ReversibleSplayTree : SplayTreeBase<\
    \ Np > {\npublic:\n  using Node = Np;\n  using T = typename Node::T;\n  using\
    \ F = function< T(T, T) >;\n  using S = function< T(T) >;\n  using super = SplayTreeBase<\
    \ Node >;\n  using NP = typename super::NP;\n\n  explicit ReversibleSplayTree(const\
    \ F &f, const S &s, const T &M1) :\n      f(f), s(s), M1(M1) {}\n\n  using super::splay;\n\
    \  using super::split;\n  using super::count;\n  using super::merge;\n  using\
    \ super::build_node;\n  using super::insert_node;\n\n  inline const T &sum(const\
    \ NP t) { return t ? t->sum : M1; }\n\n  NP alloc(const T &x) { return new Node(x);\
    \ }\n\n  T query(NP &t, int a, int b) {\n    splay(t);\n    auto x = split(t,\
    \ a);\n    auto y = split(x.second, b - a);\n    auto ret = sum(y.first);\n  \
    \  t = merge(x.first, y.first, y.second);\n    return ret;\n  }\n\n  NP build(const\
    \ vector< T > &v) {\n    vector< NP > vs(v.size());\n    for(int i = 0; i < v.size();\
    \ i++) vs[i] = alloc(v[i]);\n    return build_node(vs);\n  }\n\n  void toggle(NP\
    \ t) {\n    swap(t->l, t->r);\n    t->sum = s(t->sum);\n    t->rev ^= true;\n\
    \  }\n\n  NP update(NP t) override {\n    t->sz = 1;\n    t->sum = t->key;\n \
    \   if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);\n    if(t->r) t->sz\
    \ += t->r->sz, t->sum = f(t->sum, t->r->sum);\n    return t;\n  }\n\n  void push(NP\
    \ t) override {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n      if(t->r)\
    \ toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  NP insert(NP t, int k,\
    \ const T &x) {\n    return insert_node(t, k, alloc(x));\n  }\n\n  NP set_element(NP\
    \ t, int k, const T &x) {\n    splay(t);\n    return imp_set_element(t, k, x);\n\
    \  }\n\n  pair< NP , NP > split_lower_bound(NP t, const T &key) {\n    if(!t)\
    \ return {nullptr, nullptr};\n    push(t);\n    if(key <= t->key) {\n      auto\
    \ x = split_lower_bound(t->l, key);\n      t->l = x.second;\n      t->p = nullptr;\n\
    \      if(x.second) x.second->p = t;\n      return {x.first, update(t)};\n   \
    \ } else {\n      auto x = split_lower_bound(t->r, key);\n      t->r = x.first;\n\
    \      t->p = nullptr;\n      if(x.first) x.first->p = t;\n      return {update(t),\
    \ x.second};\n    }\n  }\n\nprivate:\n  const T M1;\n  const F f;\n  const S s;\n\
    \n  NP imp_set_element(NP t, int k, const T &x) {\n    push(t);\n    if(k < count(t->l))\
    \ {\n      return imp_set_element(t->l, k, x);\n    } else if(k == count(t->l))\
    \ {\n      t->key = x;\n      splay(t);\n      return t;\n    } else {\n     \
    \ return imp_set_element(t->r, k - count(t->l) - 1, x);\n    }\n  }\n};\n\ntemplate<\
    \ typename T >\nusing RST = ReversibleSplayTree< ReversibleSplayTreeNode< T >\
    \ >;\n"
  code: "/**\n * @brief Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728\
    )\n */\ntemplate< typename Tp >\nstruct ReversibleSplayTreeNode {\n  using T =\
    \ Tp;\n  ReversibleSplayTreeNode *l, *r, *p;\n  T key, sum;\n  bool rev;\n  size_t\
    \ sz;\n\n  ReversibleSplayTreeNode() : ReversibleSplayTreeNode(Tp()) {}\n\n  ReversibleSplayTreeNode(const\
    \ T &key) :\n      key(key), sum(key), rev(false), l(nullptr), r(nullptr), p(nullptr),\
    \ sz(1) {}\n};\n\ntemplate< typename Np >\nstruct ReversibleSplayTree : SplayTreeBase<\
    \ Np > {\npublic:\n  using Node = Np;\n  using T = typename Node::T;\n  using\
    \ F = function< T(T, T) >;\n  using S = function< T(T) >;\n  using super = SplayTreeBase<\
    \ Node >;\n  using NP = typename super::NP;\n\n  explicit ReversibleSplayTree(const\
    \ F &f, const S &s, const T &M1) :\n      f(f), s(s), M1(M1) {}\n\n  using super::splay;\n\
    \  using super::split;\n  using super::count;\n  using super::merge;\n  using\
    \ super::build_node;\n  using super::insert_node;\n\n  inline const T &sum(const\
    \ NP t) { return t ? t->sum : M1; }\n\n  NP alloc(const T &x) { return new Node(x);\
    \ }\n\n  T query(NP &t, int a, int b) {\n    splay(t);\n    auto x = split(t,\
    \ a);\n    auto y = split(x.second, b - a);\n    auto ret = sum(y.first);\n  \
    \  t = merge(x.first, y.first, y.second);\n    return ret;\n  }\n\n  NP build(const\
    \ vector< T > &v) {\n    vector< NP > vs(v.size());\n    for(int i = 0; i < v.size();\
    \ i++) vs[i] = alloc(v[i]);\n    return build_node(vs);\n  }\n\n  void toggle(NP\
    \ t) {\n    swap(t->l, t->r);\n    t->sum = s(t->sum);\n    t->rev ^= true;\n\
    \  }\n\n  NP update(NP t) override {\n    t->sz = 1;\n    t->sum = t->key;\n \
    \   if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);\n    if(t->r) t->sz\
    \ += t->r->sz, t->sum = f(t->sum, t->r->sum);\n    return t;\n  }\n\n  void push(NP\
    \ t) override {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n      if(t->r)\
    \ toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  NP insert(NP t, int k,\
    \ const T &x) {\n    return insert_node(t, k, alloc(x));\n  }\n\n  NP set_element(NP\
    \ t, int k, const T &x) {\n    splay(t);\n    return imp_set_element(t, k, x);\n\
    \  }\n\n  pair< NP , NP > split_lower_bound(NP t, const T &key) {\n    if(!t)\
    \ return {nullptr, nullptr};\n    push(t);\n    if(key <= t->key) {\n      auto\
    \ x = split_lower_bound(t->l, key);\n      t->l = x.second;\n      t->p = nullptr;\n\
    \      if(x.second) x.second->p = t;\n      return {x.first, update(t)};\n   \
    \ } else {\n      auto x = split_lower_bound(t->r, key);\n      t->r = x.first;\n\
    \      t->p = nullptr;\n      if(x.first) x.first->p = t;\n      return {update(t),\
    \ x.second};\n    }\n  }\n\nprivate:\n  const T M1;\n  const F f;\n  const S s;\n\
    \n  NP imp_set_element(NP t, int k, const T &x) {\n    push(t);\n    if(k < count(t->l))\
    \ {\n      return imp_set_element(t->l, k, x);\n    } else if(k == count(t->l))\
    \ {\n      t->key = x;\n      splay(t);\n      return t;\n    } else {\n     \
    \ return imp_set_element(t->r, k - count(t->l) - 1, x);\n    }\n  }\n};\n\ntemplate<\
    \ typename T >\nusing RST = ReversibleSplayTree< ReversibleSplayTreeNode< T >\
    \ >;\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/develop/reversible-splay-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-dynamic-tree-vertex-set-path-composite-2.test.cpp
  - test/verify/aoj-2450-3.test.cpp
  - test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
  - test/verify/yosupo-point-set-range-composite-3.test.cpp
documentation_of: structure/develop/reversible-splay-tree.hpp
layout: document
redirect_from:
- /library/structure/develop/reversible-splay-tree.hpp
- /library/structure/develop/reversible-splay-tree.hpp.html
title: "Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728)"
---
