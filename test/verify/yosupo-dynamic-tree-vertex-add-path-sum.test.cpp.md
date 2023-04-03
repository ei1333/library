---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/lct/link-cut-tree.hpp
    title: Link Cut Tree
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
  bundledCode: "#line 1 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp\"\
    \n\n#line 1 \"structure/lct/link-cut-tree.hpp\"\n/**\n * @brief Link Cut Tree\n\
    \ * @docs docs/link-cut-tree.md\n */\ntemplate< typename T, typename F, typename\
    \ S >\nstruct LinkCutTree {\n\nprivate:\n  F f;\n  S s;\n\n  struct Node {\n \
    \   Node *l, *r, *p;\n    T key, sum;\n    bool rev;\n    size_t sz;\n\n    explicit\
    \ Node(const T &v) : key(v), sum(v), sz(1), rev(false),\n                    \
    \            l(nullptr), r(nullptr), p(nullptr) {}\n\n    bool is_root() const\
    \ {\n      return not p or (p->l != this and p->r != this);\n    }\n  };\n\npublic:\n\
    \  using NP = Node *;\n\nprivate:\n  NP update(NP t) {\n    t->sz = 1;\n    t->sum\
    \ = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);\n\
    \    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);\n    return t;\n\
    \  }\n\n  void rotr(NP t) {\n    NP x = t->p, y = x->p;\n    if((x->l = t->r))\
    \ t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n    if((t->p\
    \ = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n    \
    \  update(y);\n    }\n  }\n\n  void rotl(NP t) {\n    NP x = t->p, y = x->p;\n\
    \    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n      update(y);\n    }\n  }\n\n  void toggle(NP t) {\n    swap(t->l,\
    \ t->r);\n    t->sum = s(t->sum);\n    t->rev ^= true;\n  }\n\n  void push(NP\
    \ t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n      if(t->r) toggle(t->r);\n\
    \      t->rev = false;\n    }\n  }\n\n  void splay(NP t) {\n    push(t);\n   \
    \ while(not t->is_root()) {\n      NP q = t->p;\n      if(q->is_root()) {\n  \
    \      push(q), push(t);\n        if(q->l == t) rotr(t);\n        else rotl(t);\n\
    \      } else {\n        NP r = q->p;\n        push(r), push(q), push(t);\n  \
    \      if(r->l == q) {\n          if(q->l == t) rotr(q), rotr(t);\n          else\
    \ rotl(t), rotr(t);\n        } else {\n          if(q->r == t) rotl(q), rotl(t);\n\
    \          else rotr(t), rotl(t);\n        }\n      }\n    }\n  }\n\npublic:\n\
    \  LinkCutTree(const F &f, const S &s) : f(f), s(s) {}\n\n  NP alloc(const T &v\
    \ = T()) {\n    return new Node(v);\n  }\n\n  vector< NP > build(vector< T > &vs)\
    \ {\n    vector< NP > nodes(vs.size());\n    for(int i = 0; i < (int) vs.size();\
    \ i++) {\n      nodes[i] = alloc(vs[i]);\n    }\n    return nodes;\n  }\n\n  NP\
    \ expose(NP t) {\n    NP rp = nullptr;\n    for(NP cur = t; cur; cur = cur->p)\
    \ {\n      splay(cur);\n      cur->r = rp;\n      update(cur);\n      rp = cur;\n\
    \    }\n    splay(t);\n    return rp;\n  }\n\n  void evert(NP t) {\n    expose(t);\n\
    \    toggle(t);\n    push(t);\n  }\n\n  void link(NP child, NP parent) {\n   \
    \ if(is_connected(child, parent)) {\n      throw runtime_error(\"child and parent\
    \ must be different connected components\");\n    }\n    if(child->l) {\n    \
    \  throw runtime_error(\"child must be root\");\n    }\n    child->p = parent;\n\
    \    parent->r = child;\n    update(parent);\n  }\n\n  void cut(NP child) {\n\
    \    expose(child);\n    NP parent = child->l;\n    if(not parent) {\n      throw\
    \ runtime_error(\"child must not be root\");\n    }\n    child->l = nullptr;\n\
    \    parent->p = nullptr;\n    update(child);\n  }\n\n  bool is_connected(NP u,\
    \ NP v) {\n    expose(u), expose(v);\n    return u == v or u->p;\n  }\n\n  NP\
    \ lca(NP u, NP v) {\n    if(not is_connected(u, v)) return nullptr;\n    expose(u);\n\
    \    return expose(v);\n  }\n\n  NP get_kth(NP x, int k) {\n    expose(x);\n \
    \   while(x) {\n      push(x);\n      if(x->r && x->r->sz > k) {\n        x =\
    \ x->r;\n      } else {\n        if(x->r) k -= x->r->sz;\n        if(k == 0) {\n\
    \          splay(x);\n          return x;\n        }\n        k -= 1;\n      \
    \  x = x->l;\n      }\n    }\n    return nullptr;\n  }\n\n  const T &query(NP\
    \ u) {\n    expose(u);\n    return u->sum;\n  }\n\n  const T &query(NP u, NP v)\
    \ {\n    evert(u);\n    return query(v);\n  }\n\n  void set_key(NP t, T v) {\n\
    \    expose(t);\n    t->key = v;\n    update(t);\n  }\n};\n\ntemplate< typename\
    \ T, typename F, typename S >\nLinkCutTree< T, F, S > get_link_cut_tree(const\
    \ F &f, const S &s) {\n  return {f, s};\n}\n#line 6 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  auto add = [](int64 a, int64\
    \ b) { return a + b; };\n  auto s = [](int64 a) { return a; };\n  auto lct = get_link_cut_tree<\
    \ int64 >(add, s);\n\n  vector< int64 > A(N);\n  cin >> A;\n\n  auto vs = lct.build(A);\n\
    \  for(int i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[a]);\n\
    \    lct.link(vs[a], vs[b]);\n  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n\
    \    if(T == 0) {\n      int U, V, W, X;\n      cin >> U >> V >> W >> X;\n   \
    \   lct.evert(vs[U]);\n      lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W],\
    \ vs[X]);\n    } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n  \
    \    lct.set_key(vs[P], vs[P]->key + X);\n    } else {\n      int U, V;\n    \
    \  cin >> U >> V;\n      cout << lct.query(vs[U], vs[V]) << \"\\n\";\n    }\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/lct/link-cut-tree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  auto add = [](int64 a, int64\
    \ b) { return a + b; };\n  auto s = [](int64 a) { return a; };\n  auto lct = get_link_cut_tree<\
    \ int64 >(add, s);\n\n  vector< int64 > A(N);\n  cin >> A;\n\n  auto vs = lct.build(A);\n\
    \  for(int i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[a]);\n\
    \    lct.link(vs[a], vs[b]);\n  }\n\n  while(Q--) {\n    int T;\n    cin >> T;\n\
    \    if(T == 0) {\n      int U, V, W, X;\n      cin >> U >> V >> W >> X;\n   \
    \   lct.evert(vs[U]);\n      lct.cut(vs[V]);\n      lct.evert(vs[W]);\n      lct.link(vs[W],\
    \ vs[X]);\n    } else if(T == 1) {\n      int P, X;\n      cin >> P >> X;\n  \
    \    lct.set_key(vs[P], vs[P]->key + X);\n    } else {\n      int U, V;\n    \
    \  cin >> U >> V;\n      cout << lct.query(vs[U], vs[V]) << \"\\n\";\n    }\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/lct/link-cut-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp.html
title: test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp
---
