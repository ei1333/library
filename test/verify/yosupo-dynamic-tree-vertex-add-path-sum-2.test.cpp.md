---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/develop/link-cut-tree.hpp
    title: Link-Cut-Tree
  - icon: ':heavy_check_mark:'
    path: structure/develop/reversible-splay-tree.hpp
    title: "Reversible-Splay-Tree(\u53CD\u8EE2\u53EF\u80FDSplay\u6728)"
  - icon: ':heavy_check_mark:'
    path: structure/develop/splay-tree-base.hpp
    title: "Splay-Tree-Base(Splay\u6728)"
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
  bundledCode: "#line 1 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp\"\
    \n\n#line 1 \"structure/develop/splay-tree-base.hpp\"\n/**\n * @brief Splay-Tree-Base(Splay\u6728\
    )\n */\ntemplate< typename Node >\nstruct SplayTreeBase {\npublic:\n  using NP\
    \ = Node *;\n\n  bool is_root(const NP &t) const { return !t->p || (t->p->l !=\
    \ t && t->p->r != t); }\n\n  inline size_t count(const NP &t) const { return t\
    \ ? t->sz : 0; }\n\n  void splay(NP t) {\n    push(t);\n    while(!is_root(t))\
    \ {\n      auto *q = t->p;\n      if(!is_root(t)) {\n        push(q), push(t);\n\
    \        if(q->l == t) rotr(t);\n        else rotl(t);\n      } else {\n     \
    \   auto *r = q->p;\n        push(r), push(q), push(t);\n        if(r->l == q)\
    \ {\n          if(q->l == t) rotr(q), rotr(t);\n          else rotl(t), rotr(t);\n\
    \        } else {\n          if(q->r == t) rotl(q), rotl(t);\n          else rotr(t),\
    \ rotl(t);\n        }\n      }\n    }\n  }\n\n  NP erase(NP t) {\n    splay(t);\n\
    \    Node *x = t->l, *y = t->r;\n    delete t;\n    if(!x) {\n      t = y;\n \
    \     if(t) t->p = nullptr;\n    } else if(!y) {\n      t = x;\n      t->p = nullptr;\n\
    \    } else {\n      x->p = nullptr;\n      t = get_right(x);\n      splay(t);\n\
    \      t->r = y;\n      y->p = t;\n    }\n    return t;\n  }\n\n  NP splay_front(NP\
    \ t) {\n    splay(t);\n    while(t->l) t = t->l;\n    splay(t);\n    return t;\n\
    \  }\n\n  NP splay_back(NP t) {\n    splay(t);\n    while(t->r) t = t->r;\n  \
    \  splay(t);\n    return t;\n  }\n\n  pair< NP, NP > split(NP t, int k) {\n  \
    \  if(!t) return {nullptr, nullptr};\n    push(t);\n    if(k <= count(t->l)) {\n\
    \      auto x = split(t->l, k);\n      t->l = x.second;\n      t->p = nullptr;\n\
    \      if(x.second) x.second->p = t;\n      return {x.first, update(t)};\n   \
    \ } else {\n      auto x = split(t->r, k - count(t->l) - 1);\n      t->r = x.first;\n\
    \      t->p = nullptr;\n      if(x.first) x.first->p = t;\n      return {update(t),\
    \ x.second};\n    }\n  }\n\n  template< typename... Args >\n  NP merge(NP p, Args...\
    \ args) {\n    return merge(p, merge(args...));\n  }\n\n  NP merge(NP l, NP r)\
    \ {\n    if(!l && !r) return nullptr;\n    if(!l) return splay(r), r;\n    if(!r)\
    \ return splay(l), l;\n    splay(l), splay(r);\n    l = splay_back(l);\n    l->r\
    \ = r;\n    r->p = l;\n    update(l);\n    return l;\n  }\n\n  tuple< NP, NP,\
    \ NP > split3(NP t, int a, int b) {\n    splay(t);\n    auto x = split(t, a);\n\
    \    auto y = split(x.second, b - a);\n    return make_tuple(x.first, y.first,\
    \ y.second);\n  }\n\n  virtual void push(NP t) = 0;\n\n  virtual Node *update(NP\
    \ t) = 0;\n\nprivate:\n\n  void rotr(NP t) {\n    auto *x = t->p, *y = x->p;\n\
    \    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n      update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    auto *x = t->p,\
    \ *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n  \
    \  update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n\
    \      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  NP build(int\
    \ l, int r, const vector< NP > &v) {\n    if(l + 1 >= r) return v[l];\n    return\
    \ merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));\n  }\n\nprotected:\n\
    \n  NP build_node(const vector< NP > &v) {\n    return build(0, v.size(), v);\n\
    \  }\n\n  NP insert_node(NP t, int k, NP v) {\n    splay(t);\n    auto x = split(t,\
    \ k);\n    return merge(x.first, v, x.second);\n  }\n\n  NP erase_node(NP t, int\
    \ k) {\n    splay(t);\n    auto x = split(t, k);\n    auto y = split(x.second,\
    \ 1);\n    delete y.first;\n    return merge(x.first, y.second);\n  }\n};\n#line\
    \ 1 \"structure/develop/reversible-splay-tree.hpp\"\n/**\n * @brief Reversible-Splay-Tree(\u53CD\
    \u8EE2\u53EF\u80FDSplay\u6728)\n */\ntemplate< typename Tp >\nstruct ReversibleSplayTreeNode\
    \ {\n  using T = Tp;\n  ReversibleSplayTreeNode *l, *r, *p;\n  T key, sum;\n \
    \ bool rev;\n  size_t sz;\n\n  ReversibleSplayTreeNode() : ReversibleSplayTreeNode(Tp())\
    \ {}\n\n  ReversibleSplayTreeNode(const T &key) :\n      key(key), sum(key), rev(false),\
    \ l(nullptr), r(nullptr), p(nullptr), sz(1) {}\n};\n\ntemplate< typename Np >\n\
    struct ReversibleSplayTree : SplayTreeBase< Np > {\npublic:\n  using Node = Np;\n\
    \  using T = typename Node::T;\n  using F = function< T(T, T) >;\n  using S =\
    \ function< T(T) >;\n  using super = SplayTreeBase< Node >;\n  using NP = typename\
    \ super::NP;\n\n  explicit ReversibleSplayTree(const F &f, const S &s, const T\
    \ &M1) :\n      f(f), s(s), M1(M1) {}\n\n  using super::splay;\n  using super::split;\n\
    \  using super::count;\n  using super::merge;\n  using super::build_node;\n  using\
    \ super::insert_node;\n\n  inline const T &sum(const NP t) { return t ? t->sum\
    \ : M1; }\n\n  NP alloc(const T &x) { return new Node(x); }\n\n  T query(NP &t,\
    \ int a, int b) {\n    splay(t);\n    auto x = split(t, a);\n    auto y = split(x.second,\
    \ b - a);\n    auto ret = sum(y.first);\n    t = merge(x.first, y.first, y.second);\n\
    \    return ret;\n  }\n\n  NP build(const vector< T > &v) {\n    vector< NP >\
    \ vs(v.size());\n    for(int i = 0; i < v.size(); i++) vs[i] = alloc(v[i]);\n\
    \    return build_node(vs);\n  }\n\n  void toggle(NP t) {\n    swap(t->l, t->r);\n\
    \    t->sum = s(t->sum);\n    t->rev ^= true;\n  }\n\n  NP update(NP t) override\
    \ {\n    t->sz = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum\
    \ = f(t->l->sum, t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum,\
    \ t->r->sum);\n    return t;\n  }\n\n  void push(NP t) override {\n    if(t->rev)\
    \ {\n      if(t->l) toggle(t->l);\n      if(t->r) toggle(t->r);\n      t->rev\
    \ = false;\n    }\n  }\n\n  NP insert(NP t, int k, const T &x) {\n    return insert_node(t,\
    \ k, alloc(x));\n  }\n\n  NP set_element(NP t, int k, const T &x) {\n    splay(t);\n\
    \    return imp_set_element(t, k, x);\n  }\n\n  pair< NP , NP > split_lower_bound(NP\
    \ t, const T &key) {\n    if(!t) return {nullptr, nullptr};\n    push(t);\n  \
    \  if(key <= t->key) {\n      auto x = split_lower_bound(t->l, key);\n      t->l\
    \ = x.second;\n      t->p = nullptr;\n      if(x.second) x.second->p = t;\n  \
    \    return {x.first, update(t)};\n    } else {\n      auto x = split_lower_bound(t->r,\
    \ key);\n      t->r = x.first;\n      t->p = nullptr;\n      if(x.first) x.first->p\
    \ = t;\n      return {update(t), x.second};\n    }\n  }\n\nprivate:\n  const T\
    \ M1;\n  const F f;\n  const S s;\n\n  NP imp_set_element(NP t, int k, const T\
    \ &x) {\n    push(t);\n    if(k < count(t->l)) {\n      return imp_set_element(t->l,\
    \ k, x);\n    } else if(k == count(t->l)) {\n      t->key = x;\n      splay(t);\n\
    \      return t;\n    } else {\n      return imp_set_element(t->r, k - count(t->l)\
    \ - 1, x);\n    }\n  }\n};\n\ntemplate< typename T >\nusing RST = ReversibleSplayTree<\
    \ ReversibleSplayTreeNode< T > >;\n#line 1 \"structure/develop/link-cut-tree.hpp\"\
    \n/**\n * @brief Link-Cut-Tree\n */\ntemplate< typename STp >\nstruct LinkCutTree\
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
    \    return x;\n  }\n};\n#line 8 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  using LCT = LinkCutTree< RST<\
    \ int64 > >;\n\n  auto add = [](int64 a, int64 b) { return a + b; };\n  auto s\
    \ = [](int64 a) { return a; };\n  LCT lct(add, s, 0);\n\n  vector< int > A(N);\n\
    \  cin >> A;\n\n  vector< LCT::Node * > vs(N);\n  for(int i = 0; i < N; i++) {\n\
    \    vs[i] = lct.alloc(A[i]);\n  }\n  for(int i = 1; i < N; i++) {\n    int a,\
    \ b;\n    cin >> a >> b;\n    lct.evert(vs[a]);\n    lct.link(vs[a], vs[b]);\n\
    \  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n    if(T == 0) {\n      int\
    \ U, V, W, X;\n      cin >> U >> V >> W >> X;\n      lct.evert(vs[U]);\n     \
    \ lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W], vs[X]);\n  \
    \  } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n      lct.expose(vs[P]);\n\
    \      vs[P]->key += X;\n      lct.update(vs[P]);\n    } else {\n      int U,\
    \ V;\n      cin >> U >> V;\n      lct.evert(vs[U]);\n      lct.expose(vs[V]);\n\
    \      cout << vs[V]->sum << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/develop/splay-tree-base.hpp\"\
    \n#include \"../../structure/develop/reversible-splay-tree.hpp\"\n#include \"\
    ../../structure/develop/link-cut-tree.hpp\"\n\nint main() {\n  int N, Q;\n  cin\
    \ >> N >> Q;\n  using LCT = LinkCutTree< RST< int64 > >;\n\n  auto add = [](int64\
    \ a, int64 b) { return a + b; };\n  auto s = [](int64 a) { return a; };\n  LCT\
    \ lct(add, s, 0);\n\n  vector< int > A(N);\n  cin >> A;\n\n  vector< LCT::Node\
    \ * > vs(N);\n  for(int i = 0; i < N; i++) {\n    vs[i] = lct.alloc(A[i]);\n \
    \ }\n  for(int i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[a]);\n\
    \    lct.link(vs[a], vs[b]);\n  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n\
    \    if(T == 0) {\n      int U, V, W, X;\n      cin >> U >> V >> W >> X;\n   \
    \   lct.evert(vs[U]);\n      lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W],\
    \ vs[X]);\n    } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n  \
    \    lct.expose(vs[P]);\n      vs[P]->key += X;\n      lct.update(vs[P]);\n  \
    \  } else {\n      int U, V;\n      cin >> U >> V;\n      lct.evert(vs[U]);\n\
    \      lct.expose(vs[V]);\n      cout << vs[V]->sum << \"\\n\";\n    }\n  }\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - structure/develop/splay-tree-base.hpp
  - structure/develop/reversible-splay-tree.hpp
  - structure/develop/link-cut-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp.html
title: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-2.test.cpp
---
