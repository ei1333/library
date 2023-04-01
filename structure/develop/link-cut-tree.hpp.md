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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Link-Cut-Tree
    links: []
  bundledCode: "#line 1 \"structure/develop/link-cut-tree.hpp\"\n/**\n * @brief Link-Cut-Tree\n\
    \ */\ntemplate< typename STp >\nstruct LinkCutTree : STp {\n  using ST = STp;\n\
    \  using ST::ST;\n  using Node = typename ST::Node;\n\n  Node *expose(Node *t)\
    \ {\n    Node *rp = nullptr;\n    for(Node *cur = t; cur; cur = cur->p) {\n  \
    \    this->splay(cur);\n      cur->r = rp;\n      this->update(cur);\n      rp\
    \ = cur;\n    }\n    this->splay(t);\n    return rp;\n  }\n\n  void link(Node\
    \ *child, Node *parent) {\n    expose(child);\n    expose(parent);\n    child->p\
    \ = parent;\n    parent->r = child;\n    this->update(parent);\n  }\n\n  void\
    \ cut(Node *child) {\n    expose(child);\n    auto *parent = child->l;\n    child->l\
    \ = nullptr;\n    parent->p = nullptr;\n    this->update(child);\n  }\n\n  void\
    \ evert(Node *t) {\n    expose(t);\n    this->toggle(t);\n    this->push(t);\n\
    \  }\n\n  Node *lca(Node *u, Node *v) {\n    if(get_root(u) != get_root(v)) return\
    \ nullptr;\n    expose(u);\n    return expose(v);\n  }\n\n  Node *get_kth(Node\
    \ *x, int k) {\n    expose(x);\n    while(x) {\n      this->push(x);\n      if(x->r\
    \ && x->r->sz > k) {\n        x = x->r;\n      } else {\n        if(x->r) k -=\
    \ x->r->sz;\n        if(k == 0) return x;\n        k -= 1;\n        x = x->l;\n\
    \      }\n    }\n    return nullptr;\n  }\n\n  Node *get_root(Node *x) {\n   \
    \ expose(x);\n    while(x->l) {\n      this->push(x);\n      x = x->l;\n    }\n\
    \    return x;\n  }\n};\n"
  code: "/**\n * @brief Link-Cut-Tree\n */\ntemplate< typename STp >\nstruct LinkCutTree\
    \ : STp {\n  using ST = STp;\n  using ST::ST;\n  using Node = typename ST::Node;\n\
    \n  Node *expose(Node *t) {\n    Node *rp = nullptr;\n    for(Node *cur = t; cur;\
    \ cur = cur->p) {\n      this->splay(cur);\n      cur->r = rp;\n      this->update(cur);\n\
    \      rp = cur;\n    }\n    this->splay(t);\n    return rp;\n  }\n\n  void link(Node\
    \ *child, Node *parent) {\n    expose(child);\n    expose(parent);\n    child->p\
    \ = parent;\n    parent->r = child;\n    this->update(parent);\n  }\n\n  void\
    \ cut(Node *child) {\n    expose(child);\n    auto *parent = child->l;\n    child->l\
    \ = nullptr;\n    parent->p = nullptr;\n    this->update(child);\n  }\n\n  void\
    \ evert(Node *t) {\n    expose(t);\n    this->toggle(t);\n    this->push(t);\n\
    \  }\n\n  Node *lca(Node *u, Node *v) {\n    if(get_root(u) != get_root(v)) return\
    \ nullptr;\n    expose(u);\n    return expose(v);\n  }\n\n  Node *get_kth(Node\
    \ *x, int k) {\n    expose(x);\n    while(x) {\n      this->push(x);\n      if(x->r\
    \ && x->r->sz > k) {\n        x = x->r;\n      } else {\n        if(x->r) k -=\
    \ x->r->sz;\n        if(k == 0) return x;\n        k -= 1;\n        x = x->l;\n\
    \      }\n    }\n    return nullptr;\n  }\n\n  Node *get_root(Node *x) {\n   \
    \ expose(x);\n    while(x->l) {\n      this->push(x);\n      x = x->l;\n    }\n\
    \    return x;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/develop/link-cut-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-dynamic-tree-vertex-set-path-composite-2.test.cpp
  - test/verify/aoj-2450-3.test.cpp
  - test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
documentation_of: structure/develop/link-cut-tree.hpp
layout: document
redirect_from:
- /library/structure/develop/link-cut-tree.hpp
- /library/structure/develop/link-cut-tree.hpp.html
title: Link-Cut-Tree
---
