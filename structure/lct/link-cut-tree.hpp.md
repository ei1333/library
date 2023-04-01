---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
    title: test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp
    title: test/verify/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/link-cut-tree.md
    document_title: Link Cut Tree
    links: []
  bundledCode: "#line 1 \"structure/lct/link-cut-tree.hpp\"\n/**\n * @brief Link Cut\
    \ Tree\n * @docs docs/link-cut-tree.md\n */\ntemplate< typename T, typename F,\
    \ typename S >\nstruct LinkCutTree {\n\nprivate:\n  F f;\n  S s;\n\n  struct Node\
    \ {\n    Node *l, *r, *p;\n    T key, sum;\n    bool rev;\n    size_t sz;\n\n\
    \    explicit Node(const T &v) : key(v), sum(v), sz(1), rev(false),\n        \
    \                        l(nullptr), r(nullptr), p(nullptr) {}\n\n    bool is_root()\
    \ const {\n      return not p or (p->l != this and p->r != this);\n    }\n  };\n\
    \npublic:\n  using NP = Node *;\n\nprivate:\n  NP update(NP t) {\n    t->sz =\
    \ 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum,\
    \ t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);\n \
    \   return t;\n  }\n\n  void rotr(NP t) {\n    NP x = t->p, y = x->p;\n    if((x->l\
    \ = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n      update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    NP x = t->p,\
    \ y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n   \
    \ update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n\
    \      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void toggle(NP\
    \ t) {\n    swap(t->l, t->r);\n    t->sum = s(t->sum);\n    t->rev ^= true;\n\
    \  }\n\n  void push(NP t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n\
    \      if(t->r) toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  void splay(NP\
    \ t) {\n    push(t);\n    while(not t->is_root()) {\n      NP q = t->p;\n    \
    \  if(q->is_root()) {\n        push(q), push(t);\n        if(q->l == t) rotr(t);\n\
    \        else rotl(t);\n      } else {\n        NP r = q->p;\n        push(r),\
    \ push(q), push(t);\n        if(r->l == q) {\n          if(q->l == t) rotr(q),\
    \ rotr(t);\n          else rotl(t), rotr(t);\n        } else {\n          if(q->r\
    \ == t) rotl(q), rotl(t);\n          else rotr(t), rotl(t);\n        }\n     \
    \ }\n    }\n  }\n\npublic:\n  LinkCutTree(const F &f, const S &s) : f(f), s(s)\
    \ {}\n\n  NP alloc(const T &v = T()) {\n    return new Node(v);\n  }\n\n  vector<\
    \ NP > build(vector< T > &vs) {\n    vector< NP > nodes(vs.size());\n    for(int\
    \ i = 0; i < (int) vs.size(); i++) {\n      nodes[i] = alloc(vs[i]);\n    }\n\
    \    return nodes;\n  }\n\n  NP expose(NP t) {\n    NP rp = nullptr;\n    for(NP\
    \ cur = t; cur; cur = cur->p) {\n      splay(cur);\n      cur->r = rp;\n     \
    \ update(cur);\n      rp = cur;\n    }\n    splay(t);\n    return rp;\n  }\n\n\
    \  void evert(NP t) {\n    expose(t);\n    toggle(t);\n    push(t);\n  }\n\n \
    \ void link(NP child, NP parent) {\n    if(is_connected(child, parent)) {\n  \
    \    throw runtime_error(\"child and parent must be different connected components\"\
    );\n    }\n    if(child->l) {\n      throw runtime_error(\"child must be root\"\
    );\n    }\n    child->p = parent;\n    parent->r = child;\n    update(parent);\n\
    \  }\n\n  void cut(NP child) {\n    expose(child);\n    NP parent = child->l;\n\
    \    if(not parent) {\n      throw runtime_error(\"child must not be root\");\n\
    \    }\n    child->l = nullptr;\n    parent->p = nullptr;\n    update(child);\n\
    \  }\n\n  bool is_connected(NP u, NP v) {\n    expose(u), expose(v);\n    return\
    \ u == v or u->p;\n  }\n\n  NP lca(NP u, NP v) {\n    if(not is_connected(u, v))\
    \ return nullptr;\n    expose(u);\n    return expose(v);\n  }\n\n  NP get_kth(NP\
    \ x, int k) {\n    expose(x);\n    while(x) {\n      push(x);\n      if(x->r &&\
    \ x->r->sz > k) {\n        x = x->r;\n      } else {\n        if(x->r) k -= x->r->sz;\n\
    \        if(k == 0) {\n          splay(x);\n          return x;\n        }\n \
    \       k -= 1;\n        x = x->l;\n      }\n    }\n    return nullptr;\n  }\n\
    \n  const T &query(NP u) {\n    expose(u);\n    return u->sum;\n  }\n\n  const\
    \ T &query(NP u, NP v) {\n    evert(u);\n    return query(v);\n  }\n\n  void set_key(NP\
    \ t, T v) {\n    expose(t);\n    t->key = v;\n    update(t);\n  }\n};\n\ntemplate<\
    \ typename T, typename F, typename S >\nLinkCutTree< T, F, S > get_link_cut_tree(const\
    \ F &f, const S &s) {\n  return {f, s};\n}\n"
  code: "/**\n * @brief Link Cut Tree\n * @docs docs/link-cut-tree.md\n */\ntemplate<\
    \ typename T, typename F, typename S >\nstruct LinkCutTree {\n\nprivate:\n  F\
    \ f;\n  S s;\n\n  struct Node {\n    Node *l, *r, *p;\n    T key, sum;\n    bool\
    \ rev;\n    size_t sz;\n\n    explicit Node(const T &v) : key(v), sum(v), sz(1),\
    \ rev(false),\n                                l(nullptr), r(nullptr), p(nullptr)\
    \ {}\n\n    bool is_root() const {\n      return not p or (p->l != this and p->r\
    \ != this);\n    }\n  };\n\npublic:\n  using NP = Node *;\n\nprivate:\n  NP update(NP\
    \ t) {\n    t->sz = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz,\
    \ t->sum = f(t->l->sum, t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum,\
    \ t->r->sum);\n    return t;\n  }\n\n  void rotr(NP t) {\n    NP x = t->p, y =\
    \ x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x),\
    \ update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r\
    \ == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    NP\
    \ x = t->p, y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p\
    \ = t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void\
    \ toggle(NP t) {\n    swap(t->l, t->r);\n    t->sum = s(t->sum);\n    t->rev ^=\
    \ true;\n  }\n\n  void push(NP t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n\
    \      if(t->r) toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  void splay(NP\
    \ t) {\n    push(t);\n    while(not t->is_root()) {\n      NP q = t->p;\n    \
    \  if(q->is_root()) {\n        push(q), push(t);\n        if(q->l == t) rotr(t);\n\
    \        else rotl(t);\n      } else {\n        NP r = q->p;\n        push(r),\
    \ push(q), push(t);\n        if(r->l == q) {\n          if(q->l == t) rotr(q),\
    \ rotr(t);\n          else rotl(t), rotr(t);\n        } else {\n          if(q->r\
    \ == t) rotl(q), rotl(t);\n          else rotr(t), rotl(t);\n        }\n     \
    \ }\n    }\n  }\n\npublic:\n  LinkCutTree(const F &f, const S &s) : f(f), s(s)\
    \ {}\n\n  NP alloc(const T &v = T()) {\n    return new Node(v);\n  }\n\n  vector<\
    \ NP > build(vector< T > &vs) {\n    vector< NP > nodes(vs.size());\n    for(int\
    \ i = 0; i < (int) vs.size(); i++) {\n      nodes[i] = alloc(vs[i]);\n    }\n\
    \    return nodes;\n  }\n\n  NP expose(NP t) {\n    NP rp = nullptr;\n    for(NP\
    \ cur = t; cur; cur = cur->p) {\n      splay(cur);\n      cur->r = rp;\n     \
    \ update(cur);\n      rp = cur;\n    }\n    splay(t);\n    return rp;\n  }\n\n\
    \  void evert(NP t) {\n    expose(t);\n    toggle(t);\n    push(t);\n  }\n\n \
    \ void link(NP child, NP parent) {\n    if(is_connected(child, parent)) {\n  \
    \    throw runtime_error(\"child and parent must be different connected components\"\
    );\n    }\n    if(child->l) {\n      throw runtime_error(\"child must be root\"\
    );\n    }\n    child->p = parent;\n    parent->r = child;\n    update(parent);\n\
    \  }\n\n  void cut(NP child) {\n    expose(child);\n    NP parent = child->l;\n\
    \    if(not parent) {\n      throw runtime_error(\"child must not be root\");\n\
    \    }\n    child->l = nullptr;\n    parent->p = nullptr;\n    update(child);\n\
    \  }\n\n  bool is_connected(NP u, NP v) {\n    expose(u), expose(v);\n    return\
    \ u == v or u->p;\n  }\n\n  NP lca(NP u, NP v) {\n    if(not is_connected(u, v))\
    \ return nullptr;\n    expose(u);\n    return expose(v);\n  }\n\n  NP get_kth(NP\
    \ x, int k) {\n    expose(x);\n    while(x) {\n      push(x);\n      if(x->r &&\
    \ x->r->sz > k) {\n        x = x->r;\n      } else {\n        if(x->r) k -= x->r->sz;\n\
    \        if(k == 0) {\n          splay(x);\n          return x;\n        }\n \
    \       k -= 1;\n        x = x->l;\n      }\n    }\n    return nullptr;\n  }\n\
    \n  const T &query(NP u) {\n    expose(u);\n    return u->sum;\n  }\n\n  const\
    \ T &query(NP u, NP v) {\n    evert(u);\n    return query(v);\n  }\n\n  void set_key(NP\
    \ t, T v) {\n    expose(t);\n    t->key = v;\n    update(t);\n  }\n};\n\ntemplate<\
    \ typename T, typename F, typename S >\nLinkCutTree< T, F, S > get_link_cut_tree(const\
    \ F &f, const S &s) {\n  return {f, s};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/lct/link-cut-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp
  - test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
documentation_of: structure/lct/link-cut-tree.hpp
layout: document
redirect_from:
- /library/structure/lct/link-cut-tree.hpp
- /library/structure/lct/link-cut-tree.hpp.html
title: Link Cut Tree
---
## 概要

Link Cut Tree とは動的木の一つで, 辺の追加や削除などの木構造の動的な変化がある場合でも効率的にクエリを処理できる.


## 使い方

* `LinkCutTree(f, s)`: コンストラクタ. `f` は 2 つの要素の値をマージする二項演算, `s` は要素を反転する演算を指す.
* `alloc(v)`: 要素の値を `v` としたノードを生成する.
* `build(vs)`: 各要素の値を `vs[i]` としたノードを生成し, その配列を返す.
* `expose(t)`: `t` と根をつなげて, `t` を splay Tree の根にする.
* `evert(t)`: `t` を根に変更する.
* `link(child, parent)`: `child` の親を `parent` にする. `child` と `parent` は別の連結成分で, `child` が根であることを要求する.
* `cut(child)`: `child` の親と `child` を切り離す.
* `is_connected(u, v)`: `u` と `v` が同じ連結成分に属する場合は `true`, そうでなければ `false` を返す.
* `lca(u, v)`: `u` と `v` の lca を返す. `u` と `v` が異なる連結成分なら `nullptr` を返す.
* `get_kth(x, k)`: `x` から根までのパスに出現するノードを並べたとき, 0-indexed で `k` 番目のノードを返す.
* `query(u)`: `u` から根までのパス上の頂点の値を二項演算でまとめた結果を返す.
* `query(u, v)`: `u` から `v` までのパス上の頂点の値を二項演算でまとめた結果を返す.
* `set_key(t, v)`: `t` の値を `v` に変更する.

## 計算量

* 各クエリ ならし $O(\log n)$
