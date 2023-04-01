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
    document_title: "Splay-Tree-Base(Splay\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/develop/splay-tree-base.hpp\"\n/**\n * @brief\
    \ Splay-Tree-Base(Splay\u6728)\n */\ntemplate< typename Node >\nstruct SplayTreeBase\
    \ {\npublic:\n  using NP = Node *;\n\n  bool is_root(const NP &t) const { return\
    \ !t->p || (t->p->l != t && t->p->r != t); }\n\n  inline size_t count(const NP\
    \ &t) const { return t ? t->sz : 0; }\n\n  void splay(NP t) {\n    push(t);\n\
    \    while(!is_root(t)) {\n      auto *q = t->p;\n      if(!is_root(t)) {\n  \
    \      push(q), push(t);\n        if(q->l == t) rotr(t);\n        else rotl(t);\n\
    \      } else {\n        auto *r = q->p;\n        push(r), push(q), push(t);\n\
    \        if(r->l == q) {\n          if(q->l == t) rotr(q), rotr(t);\n        \
    \  else rotl(t), rotr(t);\n        } else {\n          if(q->r == t) rotl(q),\
    \ rotl(t);\n          else rotr(t), rotl(t);\n        }\n      }\n    }\n  }\n\
    \n  NP erase(NP t) {\n    splay(t);\n    Node *x = t->l, *y = t->r;\n    delete\
    \ t;\n    if(!x) {\n      t = y;\n      if(t) t->p = nullptr;\n    } else if(!y)\
    \ {\n      t = x;\n      t->p = nullptr;\n    } else {\n      x->p = nullptr;\n\
    \      t = get_right(x);\n      splay(t);\n      t->r = y;\n      y->p = t;\n\
    \    }\n    return t;\n  }\n\n  NP splay_front(NP t) {\n    splay(t);\n    while(t->l)\
    \ t = t->l;\n    splay(t);\n    return t;\n  }\n\n  NP splay_back(NP t) {\n  \
    \  splay(t);\n    while(t->r) t = t->r;\n    splay(t);\n    return t;\n  }\n\n\
    \  pair< NP, NP > split(NP t, int k) {\n    if(!t) return {nullptr, nullptr};\n\
    \    push(t);\n    if(k <= count(t->l)) {\n      auto x = split(t->l, k);\n  \
    \    t->l = x.second;\n      t->p = nullptr;\n      if(x.second) x.second->p =\
    \ t;\n      return {x.first, update(t)};\n    } else {\n      auto x = split(t->r,\
    \ k - count(t->l) - 1);\n      t->r = x.first;\n      t->p = nullptr;\n      if(x.first)\
    \ x.first->p = t;\n      return {update(t), x.second};\n    }\n  }\n\n  template<\
    \ typename... Args >\n  NP merge(NP p, Args... args) {\n    return merge(p, merge(args...));\n\
    \  }\n\n  NP merge(NP l, NP r) {\n    if(!l && !r) return nullptr;\n    if(!l)\
    \ return splay(r), r;\n    if(!r) return splay(l), l;\n    splay(l), splay(r);\n\
    \    l = splay_back(l);\n    l->r = r;\n    r->p = l;\n    update(l);\n    return\
    \ l;\n  }\n\n  tuple< NP, NP, NP > split3(NP t, int a, int b) {\n    splay(t);\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    return make_tuple(x.first,\
    \ y.first, y.second);\n  }\n\n  virtual void push(NP t) = 0;\n\n  virtual Node\
    \ *update(NP t) = 0;\n\nprivate:\n\n  void rotr(NP t) {\n    auto *x = t->p, *y\
    \ = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x),\
    \ update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r\
    \ == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    auto\
    \ *x = t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p\
    \ = t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  NP build(int\
    \ l, int r, const vector< NP > &v) {\n    if(l + 1 >= r) return v[l];\n    return\
    \ merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\nprotected:\n\
    \n  NP build_node(const vector< NP > &v) {\n    return build(0, v.size(), v);\n\
    \  }\n\n  NP insert_node(NP t, int k, NP v) {\n    splay(t);\n    auto x = split(t,\
    \ k);\n    return merge(x.first, v, x.second);\n  }\n\n  NP erase_node(NP t, int\
    \ k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    delete y.first;\n    return merge(x.first, y.second);\n  }\n};\n"
  code: "/**\n * @brief Splay-Tree-Base(Splay\u6728)\n */\ntemplate< typename Node\
    \ >\nstruct SplayTreeBase {\npublic:\n  using NP = Node *;\n\n  bool is_root(const\
    \ NP &t) const { return !t->p || (t->p->l != t && t->p->r != t); }\n\n  inline\
    \ size_t count(const NP &t) const { return t ? t->sz : 0; }\n\n  void splay(NP\
    \ t) {\n    push(t);\n    while(!is_root(t)) {\n      auto *q = t->p;\n      if(!is_root(t))\
    \ {\n        push(q), push(t);\n        if(q->l == t) rotr(t);\n        else rotl(t);\n\
    \      } else {\n        auto *r = q->p;\n        push(r), push(q), push(t);\n\
    \        if(r->l == q) {\n          if(q->l == t) rotr(q), rotr(t);\n        \
    \  else rotl(t), rotr(t);\n        } else {\n          if(q->r == t) rotl(q),\
    \ rotl(t);\n          else rotr(t), rotl(t);\n        }\n      }\n    }\n  }\n\
    \n  NP erase(NP t) {\n    splay(t);\n    Node *x = t->l, *y = t->r;\n    delete\
    \ t;\n    if(!x) {\n      t = y;\n      if(t) t->p = nullptr;\n    } else if(!y)\
    \ {\n      t = x;\n      t->p = nullptr;\n    } else {\n      x->p = nullptr;\n\
    \      t = get_right(x);\n      splay(t);\n      t->r = y;\n      y->p = t;\n\
    \    }\n    return t;\n  }\n\n  NP splay_front(NP t) {\n    splay(t);\n    while(t->l)\
    \ t = t->l;\n    splay(t);\n    return t;\n  }\n\n  NP splay_back(NP t) {\n  \
    \  splay(t);\n    while(t->r) t = t->r;\n    splay(t);\n    return t;\n  }\n\n\
    \  pair< NP, NP > split(NP t, int k) {\n    if(!t) return {nullptr, nullptr};\n\
    \    push(t);\n    if(k <= count(t->l)) {\n      auto x = split(t->l, k);\n  \
    \    t->l = x.second;\n      t->p = nullptr;\n      if(x.second) x.second->p =\
    \ t;\n      return {x.first, update(t)};\n    } else {\n      auto x = split(t->r,\
    \ k - count(t->l) - 1);\n      t->r = x.first;\n      t->p = nullptr;\n      if(x.first)\
    \ x.first->p = t;\n      return {update(t), x.second};\n    }\n  }\n\n  template<\
    \ typename... Args >\n  NP merge(NP p, Args... args) {\n    return merge(p, merge(args...));\n\
    \  }\n\n  NP merge(NP l, NP r) {\n    if(!l && !r) return nullptr;\n    if(!l)\
    \ return splay(r), r;\n    if(!r) return splay(l), l;\n    splay(l), splay(r);\n\
    \    l = splay_back(l);\n    l->r = r;\n    r->p = l;\n    update(l);\n    return\
    \ l;\n  }\n\n  tuple< NP, NP, NP > split3(NP t, int a, int b) {\n    splay(t);\n\
    \    auto x = split(t, a);\n    auto y = split(x.second, b - a);\n    return make_tuple(x.first,\
    \ y.first, y.second);\n  }\n\n  virtual void push(NP t) = 0;\n\n  virtual Node\
    \ *update(NP t) = 0;\n\nprivate:\n\n  void rotr(NP t) {\n    auto *x = t->p, *y\
    \ = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x),\
    \ update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r\
    \ == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    auto\
    \ *x = t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p\
    \ = t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  NP build(int\
    \ l, int r, const vector< NP > &v) {\n    if(l + 1 >= r) return v[l];\n    return\
    \ merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\nprotected:\n\
    \n  NP build_node(const vector< NP > &v) {\n    return build(0, v.size(), v);\n\
    \  }\n\n  NP insert_node(NP t, int k, NP v) {\n    splay(t);\n    auto x = split(t,\
    \ k);\n    return merge(x.first, v, x.second);\n  }\n\n  NP erase_node(NP t, int\
    \ k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    delete y.first;\n    return merge(x.first, y.second);\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/develop/splay-tree-base.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-dynamic-tree-vertex-set-path-composite-2.test.cpp
  - test/verify/aoj-2450-3.test.cpp
  - test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
  - test/verify/yosupo-point-set-range-composite-3.test.cpp
documentation_of: structure/develop/splay-tree-base.hpp
layout: document
redirect_from:
- /library/structure/develop/splay-tree-base.hpp
- /library/structure/develop/splay-tree-base.hpp.html
title: "Splay-Tree-Base(Splay\u6728)"
---
