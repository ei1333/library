---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/lct/link-cut-tree-subtree.hpp
    title: structure/lct/link-cut-tree-subtree.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
  bundledCode: "#line 1 \"test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp\"\
    \n\n#line 1 \"structure/lct/link-cut-tree-subtree.hpp\"\ntemplate< typename SUM,\
    \ typename KEY >\nstruct LinkCutTreeSubtree {\n \n  struct Node {\n    Node *l,\
    \ *r, *p;\n \n    KEY key;\n    SUM sum;\n \n    bool rev;\n    int sz;\n \n \
    \   bool is_root() const {\n      return !p || (p->l != this && p->r != this);\n\
    \    }\n \n    Node(const KEY &key, const SUM &sum) :\n        key(key), sum(sum),\
    \ rev(false), sz(1),\n        l(nullptr), r(nullptr), p(nullptr) {}\n  };\n \n\
    \  const SUM ident;\n \n  LinkCutTreeSubtree(const SUM &ident) : ident(ident)\
    \ {}\n \n  Node *make_node(const KEY &key) {\n    auto ret = new Node(key, ident);\n\
    \    update(ret);\n    return ret;\n  }\n \n  Node *set_key(Node *t, const KEY\
    \ &key) {\n    expose(t);\n    t->key = key;\n    update(t);\n    return t;\n\
    \  }\n \n  void toggle(Node *t) {\n    swap(t->l, t->r);\n    t->sum.toggle();\n\
    \    t->rev ^= true;\n  }\n \n  void push(Node *t) {\n    if(t->rev) {\n     \
    \ if(t->l) toggle(t->l);\n      if(t->r) toggle(t->r);\n      t->rev = false;\n\
    \    }\n  }\n \n \n  void update(Node *t) {\n    t->sz = 1;\n    if(t->l) t->sz\
    \ += t->l->sz;\n    if(t->r) t->sz += t->r->sz;\n    t->sum.merge(t->key, t->l\
    \ ? t->l->sum : ident, t->r ? t->r->sum : ident);\n  }\n \n  void rotr(Node *t)\
    \ {\n    auto *x = t->p, *y = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r\
    \ = x, x->p = t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l\
    \ == x) y->l = t;\n      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\
    \ \n  void rotl(Node *t) {\n    auto *x = t->p, *y = x->p;\n    if((x->r = t->l))\
    \ t->l->p = x;\n    t->l = x, x->p = t;\n    update(x), update(t);\n    if((t->p\
    \ = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n    \
    \  update(y);\n    }\n  }\n \n \n  void splay(Node *t) {\n    push(t);\n    while(!t->is_root())\
    \ {\n      auto *q = t->p;\n      if(q->is_root()) {\n        push(q), push(t);\n\
    \        if(q->l == t) rotr(t);\n        else rotl(t);\n      } else {\n     \
    \   auto *r = q->p;\n        push(r), push(q), push(t);\n        if(r->l == q)\
    \ {\n          if(q->l == t) rotr(q), rotr(t);\n          else rotl(t), rotr(t);\n\
    \        } else {\n          if(q->r == t) rotl(q), rotl(t);\n          else rotr(t),\
    \ rotl(t);\n        }\n      }\n    }\n  }\n \n \n  Node *expose(Node *t) {\n\
    \    Node *rp = nullptr;\n    for(auto *cur = t; cur; cur = cur->p) {\n      splay(cur);\n\
    \      if(cur->r) cur->sum.add(cur->r->sum);\n      cur->r = rp;\n      if(cur->r)\
    \ cur->sum.erase(cur->r->sum);\n      update(cur);\n      rp = cur;\n    }\n \
    \   splay(t);\n    return rp;\n  }\n \n  void link(Node *child, Node *parent)\
    \ {\n    expose(child);\n    expose(parent);\n    child->p = parent;\n    parent->r\
    \ = child;\n    update(parent);\n  }\n \n  void cut(Node *child) {\n    expose(child);\n\
    \    auto *parent = child->l;\n    child->l = nullptr;\n    parent->p = nullptr;\n\
    \    update(child);\n  }\n \n  void evert(Node *t) {\n    expose(t);\n    toggle(t);\n\
    \    push(t);\n  }\n \n  Node *lca(Node *u, Node *v) {\n    if(get_root(u) !=\
    \ get_root(v)) return nullptr;\n    expose(u);\n    return expose(v);\n  }\n \n\
    \ \n  Node *get_kth(Node *x, int k) {\n    expose(x);\n    while(x) {\n      push(x);\n\
    \      if(x->r && x->r->sz > k) {\n        x = x->r;\n      } else {\n       \
    \ if(x->r) k -= x->r->sz;\n        if(k == 0) return x;\n        k -= 1;\n   \
    \     x = x->l;\n      }\n    }\n    return nullptr;\n  }\n \n  Node *get_root(Node\
    \ *x) {\n    expose(x);\n    while(x->l) {\n      push(x);\n      x = x->l;\n\
    \    }\n    return x;\n  }\n \n  SUM &query(Node *t) {\n    expose(t);\n    return\
    \ t->sum;\n  }\n};\n#line 6 \"test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n\n\n  struct Node {\n    int64\
    \ sum, psum, csum, lsum;\n\n    Node() : sum(0), lsum(0), psum(0), csum(0) {}\n\
    \n    void toggle() {\n      swap(psum, csum);\n    }\n\n    void merge(int64\
    \ cost, const Node &parent, const Node &child) {\n      sum = cost + parent.sum\
    \ + child.sum + lsum;\n      psum = parent.psum + cost + lsum;\n      csum = child.csum\
    \ + cost + lsum;\n    }\n\n    void add(const Node &chsum) {\n      lsum += chsum.sum;\n\
    \    }\n\n    void erase(const Node &chsum) {\n      lsum -= chsum.sum;\n    }\n\
    \  } e;\n\n  using LCT = LinkCutTreeSubtree< Node, int64 >;\n  LCT lct(e);\n\n\
    \  vector< int > A(N);\n  cin >> A;\n\n  vector< LCT::Node * > vs(N), es(N);\n\
    \  for(int i = 0; i < N; i++) {\n    vs[i] = lct.make_node(A[i]);\n  }\n  for(int\
    \ i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[b]);\n\
    \    lct.link(vs[b], vs[a]);\n  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n\
    \    if(T == 0) {\n      int U, V, W, X;\n      cin >> U >> V >> W >> X;\n   \
    \   lct.evert(vs[U]);\n      lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W],\
    \ vs[X]);\n    } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n  \
    \    lct.set_key(vs[P], vs[P]->key + X);\n    } else {\n      int V, P;\n    \
    \  cin >> V >> P;\n      lct.evert(vs[P]);\n      cout << lct.query(vs[V]).csum\
    \ << \"\\n\";\n    }\n  }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/lct/link-cut-tree-subtree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n\n\n  struct Node {\n    int64\
    \ sum, psum, csum, lsum;\n\n    Node() : sum(0), lsum(0), psum(0), csum(0) {}\n\
    \n    void toggle() {\n      swap(psum, csum);\n    }\n\n    void merge(int64\
    \ cost, const Node &parent, const Node &child) {\n      sum = cost + parent.sum\
    \ + child.sum + lsum;\n      psum = parent.psum + cost + lsum;\n      csum = child.csum\
    \ + cost + lsum;\n    }\n\n    void add(const Node &chsum) {\n      lsum += chsum.sum;\n\
    \    }\n\n    void erase(const Node &chsum) {\n      lsum -= chsum.sum;\n    }\n\
    \  } e;\n\n  using LCT = LinkCutTreeSubtree< Node, int64 >;\n  LCT lct(e);\n\n\
    \  vector< int > A(N);\n  cin >> A;\n\n  vector< LCT::Node * > vs(N), es(N);\n\
    \  for(int i = 0; i < N; i++) {\n    vs[i] = lct.make_node(A[i]);\n  }\n  for(int\
    \ i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[b]);\n\
    \    lct.link(vs[b], vs[a]);\n  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n\
    \    if(T == 0) {\n      int U, V, W, X;\n      cin >> U >> V >> W >> X;\n   \
    \   lct.evert(vs[U]);\n      lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W],\
    \ vs[X]);\n    } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n  \
    \    lct.set_key(vs[P], vs[P]->key + X);\n    } else {\n      int V, P;\n    \
    \  cin >> V >> P;\n      lct.evert(vs[P]);\n      cout << lct.query(vs[V]).csum\
    \ << \"\\n\";\n    }\n  }\n}\n\n"
  dependsOn:
  - template/template.hpp
  - structure/lct/link-cut-tree-subtree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp.html
title: test/verify/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp
---
