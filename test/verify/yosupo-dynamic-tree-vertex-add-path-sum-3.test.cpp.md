---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/develop/super-link-cut-tree.hpp
    title: "\u4F55\u3067\u3082\u3067\u304D\u308BLCT"
  - icon: ':heavy_check_mark:'
    path: structure/develop/vertex-set-path-sum.hpp
    title: Vertex Set Path Sum
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
  bundledCode: "#line 1 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp\"\
    \n\n#line 1 \"structure/develop/super-link-cut-tree.hpp\"\n/**\n * @brief \u4F55\
    \u3067\u3082\u3067\u304D\u308BLCT\n */\ntemplate< typename LInfo, typename Lazy\
    \ >\nstruct SplayTree {\n  struct Node {\n    Node *l, *r, *p;\n    LInfo info;\n\
    \    Lazy lazy, lbuf;\n\n    explicit Node(const LInfo &info) : info(info), l(nullptr),\
    \ r(nullptr),\n                                       p(nullptr), lazy(Lazy()),\
    \ lbuf(Lazy()) {}\n  };\n\n  const LInfo e;\n\n  SplayTree() : e(LInfo()) {}\n\
    \n  using NP = Node *;\n\n  void rotr(NP t) {\n    NP x = t->p, y = x->p;\n  \
    \  push(x), push(t);\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p =\
    \ t;\n    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l\
    \ = t;\n      if(y->r == x) y->r = t;\n    }\n  }\n\n  void rotl(NP t) {\n   \
    \ NP x = t->p, y = x->p;\n    push(x), push(t);\n    if((x->r = t->l)) t->l->p\
    \ = x;\n    t->l = x, x->p = t;\n    update(x), update(t);\n    if((t->p = y))\
    \ {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n    }\n  }\n\
    \n  const LInfo &get_info(NP t) {\n    return t ? t->info : e;\n  }\n\n  void\
    \ update(NP t) {\n    t->info.update(get_info(t->l), get_info(t->r));\n  }\n\n\
    \  NP get_right(NP t) {\n    while(t->r) t = t->r;\n    return t;\n  }\n\n  NP\
    \ alloc(const LInfo &v) {\n    auto t = new Node(v);\n    update(t);\n    return\
    \ t;\n  }\n\n  void propagate(NP t, const Lazy &lazy) {\n    t->info.propagate(lazy);\n\
    \    t->lbuf.propagate(lazy);\n    t->lazy.propagate(lazy);\n  }\n\n  void push(NP\
    \ t) {\n    if(t->l) propagate(t->l, t->lazy);\n    if(t->r) propagate(t->r, t->lazy);\n\
    \    t->lazy = Lazy();\n  }\n\n  void splay(NP t) {\n    push(t);\n    while(t->p)\
    \ {\n      NP q = t->p;\n      if(!q->p) {\n        if(q->l == t) rotr(t);\n \
    \       else rotl(t);\n      } else {\n        NP r = q->p;\n        if(r->l ==\
    \ q) {\n          if(q->l == t) rotr(q), rotr(t);\n          else rotl(t), rotr(t);\n\
    \        } else {\n          if(q->r == t) rotl(q), rotl(t);\n          else rotr(t),\
    \ rotl(t);\n        }\n      }\n    }\n  }\n\n  NP insert(NP t, const LInfo &v)\
    \ {\n    if(not t) {\n      t = alloc(v);\n      return t;\n    } else {\n   \
    \   NP cur = get_right(t), z = alloc(v);\n      splay(cur);\n      z->p = cur;\n\
    \      cur->r = z;\n      update(cur);\n      splay(z);\n      return z;\n   \
    \ }\n  }\n\n  NP erase(NP t) {\n    splay(t);\n    NP x = t->l, y = t->r;\n  \
    \  delete t;\n    if(not x) {\n      t = y;\n      if(t) t->p = nullptr;\n   \
    \ } else if(not y) {\n      t = x;\n      t->p = nullptr;\n    } else {\n    \
    \  x->p = nullptr;\n      t = get_right(x);\n      splay(t);\n      t->r = y;\n\
    \      y->p = t;\n      update(t);\n    }\n    return t;\n  }\n};\n\ntemplate<\
    \ template< typename, typename > typename _Info,\n    template< typename > typename\
    \ _LInfo, typename Lazy >\nstruct SuperLinkCutTree {\n  using LInfo = _LInfo<\
    \ Lazy >;\n  using Info = _Info< LInfo, Lazy >;\n\nprivate:\n  struct Node {\n\
    \    Node *l, *r, *p;\n    Info info;\n    typename SplayTree< LInfo, Lazy >::Node\
    \ *light, *belong;\n    bool rev;\n    Lazy hlazy, llazy;\n\n    bool is_root()\
    \ const {\n      return not p or (p->l != this and p->r != this);\n    }\n\n \
    \   explicit Node(const Info &info)\n        : info(info), l(nullptr), r(nullptr),\
    \ p(nullptr), rev(false),\n          light(nullptr), belong(nullptr), hlazy(Lazy()),\
    \ llazy(Lazy()) {}\n  };\n\npublic:\n  using NP = Node *;\n  SplayTree< LInfo,\
    \ Lazy > splay_tree;\n\nprivate:\n  const Info e;\n\nprivate:\n  void toggle(NP\
    \ t) {\n    swap(t->l, t->r);\n    t->info.toggle();\n    t->rev ^= true;\n  }\n\
    \n  void rotr(NP t) {\n    NP x = t->p, y = x->p;\n    push(x), push(t);\n   \
    \ if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n    }\n  }\n\n  void rotl(NP t) {\n    NP x = t->p, y = x->p;\n    push(x),\
    \ push(t);\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n    update(x),\
    \ update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r\
    \ == x) y->r = t;\n    }\n  }\n\n  void propagate_heavy(NP t, const Lazy &hlazy)\
    \ {\n    t->hlazy.propagate(hlazy);\n    t->info.propagate(hlazy);\n  }\n\n  void\
    \ propagate_light(NP t, const Lazy &llazy) {\n    t->llazy.propagate(llazy);\n\
    \    t->info.propagate_light(llazy);\n  }\n\n  void propagate_all(NP t, const\
    \ Lazy &lazy) {\n    propagate_heavy(t, lazy);\n    propagate_light(t, lazy);\n\
    \  }\n\npublic:\n  SuperLinkCutTree() : e{Info()}, splay_tree{} {}\n\n  void push(NP\
    \ t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n      if(t->r) toggle(t->r);\n\
    \      t->rev = false;\n    }\n    {\n      if(t->l) {\n        propagate_heavy(t->l,\
    \ t->hlazy);\n        propagate_light(t->l, t->llazy);\n      }\n      if(t->r)\
    \ {\n        propagate_heavy(t->r, t->hlazy);\n        propagate_light(t->r, t->llazy);\n\
    \      }\n      if(t->light) {\n        splay_tree.propagate(t->light, t->llazy);\n\
    \      }\n      t->hlazy = Lazy();\n      t->llazy = Lazy();\n    }\n  }\n\n \
    \ void push_rev(NP t) {\n    if(t->rev) {\n      if(t->l) toggle(t->l);\n    \
    \  if(t->r) toggle(t->r);\n      t->rev = false;\n    }\n  }\n\n  const Info &get_info(NP\
    \ t) {\n    return t ? t->info : e;\n  }\n\n  void update(NP t) {\n    t->info.update(get_info(t->l),\
    \ get_info(t->r), splay_tree.get_info(t->light));\n  }\n\n  void splay(NP t) {\n\
    \    push(t);\n    {\n      NP rot = t;\n      while(not rot->is_root()) rot =\
    \ rot->p;\n      t->belong = rot->belong;\n      if(t != rot) rot->belong = nullptr;\n\
    \    }\n    while(not t->is_root()) {\n      NP q = t->p;\n      if(q->is_root())\
    \ {\n        push_rev(q), push_rev(t);\n        if(q->l == t) rotr(t);\n     \
    \   else rotl(t);\n      } else {\n        NP r = q->p;\n        push_rev(r),\
    \ push_rev(q), push_rev(t);\n        if(r->l == q) {\n          if(q->l == t)\
    \ rotr(q), rotr(t);\n          else rotl(t), rotr(t);\n        } else {\n    \
    \      if(q->r == t) rotl(q), rotl(t);\n          else rotr(t), rotl(t);\n   \
    \     }\n      }\n    }\n  }\n\n  NP expose(NP t) {\n    NP rp = nullptr;\n  \
    \  for(NP cur = t; cur; cur = cur->p) {\n      splay(cur);\n      if(cur->r) {\n\
    \        cur->light = splay_tree.insert(cur->light, cur->r->info.link());\n  \
    \      cur->r->belong = cur->light;\n      }\n      cur->r = rp;\n      if(cur->r)\
    \ {\n        splay_tree.splay(cur->r->belong);\n        propagate_all(cur->r,\
    \ cur->r->belong->lbuf);\n        push(cur->r);\n        cur->light = splay_tree.erase(cur->r->belong);\n\
    \      }\n      update(cur);\n      rp = cur;\n    }\n    splay(t);\n    return\
    \ rp;\n  }\n\n  void link(NP child, NP parent) {\n    expose(parent);\n    expose(child);\n\
    \    child->p = parent;\n    parent->r = child;\n    update(parent);\n  }\n\n\
    \  void cut(NP child) {\n    expose(child);\n    NP parent = child->l;\n    child->l\
    \ = nullptr;\n    parent->p = nullptr;\n    update(child);\n  }\n\n  void evert(NP\
    \ t) {\n    expose(t);\n    toggle(t);\n    push(t);\n  }\n\n  NP alloc(const\
    \ Info &info) {\n    NP t = new Node(info);\n    update(t);\n    return t;\n \
    \ }\n\n  bool is_connected(NP u, NP v) {\n    expose(u), expose(v);\n    return\
    \ u == v or u->p;\n  }\n\n  vector< NP > build(vector< Info > &vs) {\n    vector<\
    \ NP > nodes(vs.size());\n    for(int i = 0; i < (int) vs.size(); i++) {\n   \
    \   nodes[i] = alloc(vs[i]);\n    }\n    return nodes;\n  }\n\n  NP lca(NP u,\
    \ NP v) {\n    if(not is_connected(u, v)) return nullptr;\n    expose(u);\n  \
    \  return expose(v);\n  }\n\n  void set_key(NP t, const Info &v) {\n    expose(t);\n\
    \    t->info = move(v);\n    update(t);\n  }\n\n  void set_propagate_path(NP t,\
    \ const Lazy &lazy) {\n    expose(t);\n    propagate_heavy(t, lazy);\n    push(t);\n\
    \    update(t);\n  }\n\n  void set_propagate_path(NP u, NP v, const Lazy &lazy)\
    \ {\n    evert(u);\n    set_propagate_path(v, lazy);\n  }\n\n  void set_propagate_all(NP\
    \ t, const Lazy &lazy) {\n    expose(t);\n    propagate_all(t, lazy);\n    push(t);\n\
    \    update(t);\n  }\n\n  void set_propagate_subtree(NP t, const Lazy &lazy) {\n\
    \    expose(t);\n    NP l = t->l;\n    t->l = nullptr;\n    propagate_all(t, lazy);\n\
    \    push(t);\n    t->l = l;\n    update(t);\n  }\n\n  const Info &query(NP u)\
    \ {\n    expose(u);\n    return get_info(u);\n  }\n\n  const Info &query_path(NP\
    \ u, NP v) {\n    evert(u);\n    expose(v);\n    return get_info(v);\n  }\n\n\
    \  Info query_subtree(NP u) {\n    expose(u);\n    NP l = u->l;\n    u->l = nullptr;\n\
    \    update(u);\n    auto ret = u->info;\n    u->l = l;\n    update(u);\n    return\
    \ ret;\n  }\n};\n\n/*\nusing T = int64_t;\n// \u9045\u5EF6\u4F1D\u642C\u3092\u3059\
    \u308B\u305F\u3081\u306E\u4F5C\u7528\u7D20\nstruct Lazy {\n\n  // \u5358\u4F4D\
    \u5143\n  Lazy() {}\n\n  // \u521D\u671F\u5316\n  Lazy(T v) {}\n\n  // \u9045\u5EF6\
    \u4F1D\u642C\n  void propagate(const Lazy &p) {}\n};\n\n// Light-edge \u306E\u60C5\
    \u5831\ntemplate< typename Lazy >\nstruct LInfo {\n\n  // \u5358\u4F4D\u5143(\u30AD\
    \u30FC\u306E\u5024\u306F\u30A2\u30AF\u30BB\u30B9\u3057\u306A\u3044\u306E\u3067\
    \u672A\u521D\u671F\u5316\u3067\u3082\u3088\u3044\n  LInfo() {}\n\n  // \u521D\u671F\
    \u5316\n  LInfo(T v) {}\n\n  // l, r \u306F Splay-tree \u306E\u5B50 (\u539F\u7406\
    \u4E0A\u3001\u5404\u30CE\u30FC\u30C9\u533A\u5225\u306F\u306A\u3044)\n  void update(const\
    \ LInfo &l, const LInfo &r) {}\n\n  // \u90E8\u5206\u6728\u3078\u306E\u9045\u5EF6\
    \u4F1D\u642C\n  void propagate(const Lazy &p) {}\n};\n\n// Heavy-edge \u306E\u60C5\
    \u5831\ntemplate< typename LInfo, typename Lazy >\nstruct Info {\n\n  // \u5358\
    \u4F4D\u5143(\u30AD\u30FC\u306E\u5024\u306F\u30A2\u30AF\u30BB\u30B9\u3057\u306A\
    \u3044\u306E\u3067\u672A\u521D\u671F\u5316\u3067\u3082\u3088\u3044\n  Info() {}\n\
    \n  // \u521D\u671F\u5316\n  Info(T v) {}\n\n  // \u53CD\u8EE2\n  void toggle()\
    \ {}\n\n  // p\u304C\u89AA, c\u304Cheavy-edge\u3067\u7D50\u3070\u308C\u305F\u5B50\
    , l\u304C\u305D\u308C\u4EE5\u5916\u306E\u5B50\n  void update(const Info &p, const\
    \ Info &c, const LInfo &l) {}\n\n  // \u89AA\u3068 light-edge \u3067\u7E4B\u3052\
    \u308B\n  LInfo link() const { return LInfo(); }\n\n  // \u9045\u5EF6\u4F1D\u642C\
    \n  void propagate(const Lazy &p) {}\n\n  // light-edge\u306B\u5BFE\u3059\u308B\
    \u9045\u5EF6\u4F1D\u642C\n  // path\u3068subtree\u306E\u9045\u5EF6\u4F1D\u642C\
    \u304C\u4E21\u65B9\u3042\u308B\u5834\u5408\u306B\u5B9F\u88C5\u3059\u308B\n  void\
    \ propagate_light(const Lazy &p) {}\n};\n\nusing LCT = SuperLinkCutTree< Info,\
    \ LInfo, Lazy >;\n*/\n#line 2 \"structure/develop/vertex-set-path-sum.hpp\"\n\n\
    /**\n * @brief Vertex Set Path Sum\n */\nusing T = int64_t;\n\n// \u9045\u5EF6\
    \u4F1D\u642C\u3092\u3059\u308B\u305F\u3081\u306E\u4F5C\u7528\u7D20\nstruct Lazy\
    \ {\n\n  // \u5358\u4F4D\u5143\n  Lazy() {}\n\n  // \u521D\u671F\u5316\n  Lazy(T\
    \ v) {}\n\n  // \u9045\u5EF6\u4F1D\u642C\n  void propagate(const Lazy &p) {}\n\
    };\n\n// Light-edge \u306E\u60C5\u5831\ntemplate< typename Lazy >\nstruct LInfo\
    \ {\n\n  // \u5358\u4F4D\u5143(\u30AD\u30FC\u306E\u5024\u306F\u30A2\u30AF\u30BB\
    \u30B9\u3057\u306A\u3044\u306E\u3067\u672A\u521D\u671F\u5316\u3067\u3082\u3088\
    \u3044\n  LInfo() {}\n\n  // \u521D\u671F\u5316\n  LInfo(T v) {}\n\n  // l, r\
    \ \u306F Splay-tree \u306E\u5B50 (\u539F\u7406\u4E0A\u3001\u5404\u30CE\u30FC\u30C9\
    \u533A\u5225\u306F\u306A\u3044)\n  void update(const LInfo &l, const LInfo &r)\
    \ {}\n\n  // \u90E8\u5206\u6728\u3078\u306E\u9045\u5EF6\u4F1D\u642C\n  void propagate(const\
    \ Lazy &p) {}\n};\n\n// Heavy-edge \u306E\u60C5\u5831\ntemplate< typename LInfo,\
    \ typename Lazy >\nstruct Info {\n  T v;\n\n  T sum;\n\n  // \u5358\u4F4D\u5143\
    (\u30AD\u30FC\u306E\u5024\u306F\u30A2\u30AF\u30BB\u30B9\u3057\u306A\u3044\u306E\
    \u3067\u672A\u521D\u671F\u5316\u3067\u3082\u3088\u3044\n  Info() : sum{0} {}\n\
    \n  // \u521D\u671F\u5316\n  Info(T v) : v{v} {}\n\n  // \u53CD\u8EE2\n  void\
    \ toggle() {}\n\n  // p\u304C\u89AA, c\u304Cheavy-edge\u3067\u7D50\u3070\u308C\
    \u305F\u5B50, l\u304C\u305D\u308C\u4EE5\u5916\u306E\u5B50\n  void update(const\
    \ Info &p, const Info &c, const LInfo &l) {\n    sum = p.sum + v + c.sum;\n  }\n\
    \n  // \u89AA\u3068 light-edge \u3067\u7E4B\u3052\u308B\n  LInfo link() const\
    \ { return LInfo(); }\n\n  // \u9045\u5EF6\u4F1D\u642C\n  void propagate(const\
    \ Lazy &p) {}\n\n  // light-edge\u306B\u5BFE\u3059\u308B\u9045\u5EF6\u4F1D\u642C\
    \n  // path\u3068subtree\u306E\u9045\u5EF6\u4F1D\u642C\u304C\u4E21\u65B9\u3042\
    \u308B\u5834\u5408\u306B\u5B9F\u88C5\u3059\u308B\n  void propagate_light(const\
    \ Lazy &p) {}\n};\n\nusing LCT = SuperLinkCutTree< Info, LInfo, Lazy >;\n#line\
    \ 6 \"test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp\"\n\nint\
    \ main() {\n  int N, Q;\n  cin >> N >> Q;\n  LCT lct;\n  vector< LCT::NP > vs(N);\n\
    \  for(int i = 0; i < N; i++) {\n    T a;\n    cin >> a;\n    vs[i] = lct.alloc(a);\n\
    \  }\n  for(int i = 1; i < N; i++) {\n    int a, b;\n    cin >> a >> b;\n    lct.evert(vs[a]);\n\
    \    lct.link(vs[a], vs[b]);\n  }\n  while(Q--) {\n    int t;\n    cin >> t;\n\
    \    if(t == 0) {\n      int u, v, w, x;\n      cin >> u >> v >> w >> x;\n   \
    \   lct.evert(vs[u]);\n      lct.cut(vs[v]);\n      lct.evert(vs[w]);\n      lct.link(vs[w],\
    \ vs[x]);\n    } else if(t == 1) {\n      int p;\n      T x;\n      cin >> p >>\
    \ x;\n      lct.set_key(vs[p], lct.get_info(vs[p]).v + x);\n    } else {\n   \
    \   int u, v;\n      cin >> u >> v;\n      cout << lct.query_path(vs[u], vs[v]).sum\
    \ << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/develop/vertex-set-path-sum.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  LCT lct;\n  vector< LCT::NP\
    \ > vs(N);\n  for(int i = 0; i < N; i++) {\n    T a;\n    cin >> a;\n    vs[i]\
    \ = lct.alloc(a);\n  }\n  for(int i = 1; i < N; i++) {\n    int a, b;\n    cin\
    \ >> a >> b;\n    lct.evert(vs[a]);\n    lct.link(vs[a], vs[b]);\n  }\n  while(Q--)\
    \ {\n    int t;\n    cin >> t;\n    if(t == 0) {\n      int u, v, w, x;\n    \
    \  cin >> u >> v >> w >> x;\n      lct.evert(vs[u]);\n      lct.cut(vs[v]);\n\
    \      lct.evert(vs[w]);\n      lct.link(vs[w], vs[x]);\n    } else if(t == 1)\
    \ {\n      int p;\n      T x;\n      cin >> p >> x;\n      lct.set_key(vs[p],\
    \ lct.get_info(vs[p]).v + x);\n    } else {\n      int u, v;\n      cin >> u >>\
    \ v;\n      cout << lct.query_path(vs[u], vs[v]).sum << \"\\n\";\n    }\n  }\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - structure/develop/vertex-set-path-sum.hpp
  - structure/develop/super-link-cut-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp
- /verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp.html
title: test/verify/yosupo-dynamic-tree-vertex-add-path-sum-3.test.cpp
---
