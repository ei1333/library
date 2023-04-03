---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':warning:'
    path: structure/develop/dynamic-tree-test.hpp
    title: Dynamic Tree Test
  - icon: ':heavy_check_mark:'
    path: structure/develop/super-link-cut-tree.hpp
    title: "\u4F55\u3067\u3082\u3067\u304D\u308BLCT"
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://dmoj.ca/problem/ds5
  bundledCode: "#line 1 \"test/verify/dmoj-ds5.hpp\"\n#define PROBLEM \"https://dmoj.ca/problem/ds5\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/dmoj-ds5.hpp\"\
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
    \ LInfo, Lazy >;\n*/\n#line 2 \"structure/develop/dynamic-tree-test.hpp\"\n\n\
    /**\n * @brief Dynamic Tree Test\n * @see https://dmoj.ca/problem/ds5\n */\nusing\
    \ T = int;\nconst T inf_max = numeric_limits< T >::max();\nconst T inf_min = numeric_limits<\
    \ T >::min();\n\n// \u9045\u5EF6\u4F1D\u642C\u3092\u3059\u308B\u4F5C\u7528\u7D20\
    \nstruct Lazy {\n  int type; // 0: none, 1: change, 2:inc\n  T v;\n\n  // \u5358\
    \u4F4D\u5143\n  Lazy() : type(0) {}\n\n  // \u521D\u671F\u5316\n  constexpr Lazy(int\
    \ type, T v) : type(type), v(v) {}\n\n  inline constexpr void propagate(const\
    \ Lazy &p) {\n    if(p.type == 0) {\n      return;\n    }\n    if(type == 0 or\
    \ p.type == 1) {\n      type = p.type;\n      v = p.v;\n    } else {\n      v\
    \ += p.v;\n    }\n  }\n};\n\n// Light-edge \u306E\u60C5\u5831\ntemplate< typename\
    \ Lazy >\nstruct LInfo {\n  T min, max, sum, sz;\n\n  T all_min, all_max, all_sum,\
    \ all_sz;\n\n  // \u5358\u4F4D\u5143(\u30AD\u30FC\u306E\u5024\u306F\u30A2\u30AF\
    \u30BB\u30B9\u3057\u306A\u3044\u306E\u3067\u672A\u521D\u671F\u5316\u3067\u3082\
    \u3088\u3044\n  LInfo() : all_min(inf_max), all_max(inf_min), all_sum(0), all_sz(0)\
    \ {}\n\n  // \u521D\u671F\u5316\n  LInfo(T min, T max, T sum, T sz) : min(min),\
    \ max(max), sum(sum), sz(sz) {}\n\n  // l, r \u306F Splay-tree \u306E\u5B50 (\u539F\
    \u7406\u4E0A\u3001\u5404\u30CE\u30FC\u30C9\u533A\u5225\u306F\u306A\u3044)\n  void\
    \ update(const LInfo &l, const LInfo &r) {\n    all_min = std::min({l.all_min,\
    \ min, r.all_min});\n    all_max = std::max({l.all_max, max, r.all_max});\n  \
    \  all_sum = l.all_sum + sum + r.all_sum;\n    all_sz = l.all_sz + sz + r.all_sz;\n\
    \  }\n\n  // light-edge\u306B\u5BFE\u3059\u308B\u9045\u5EF6\u4F1D\u642C\n  void\
    \ propagate(const Lazy &p) {\n    if(p.type == 0) {\n      return;\n    } else\
    \ if(p.type == 1) { // change\n      min = p.v;\n      max = p.v;\n      sum =\
    \ p.v * sz;\n      all_min = p.v;\n      all_max = p.v;\n      all_sum = p.v *\
    \ all_sz;\n    } else { // inc\n      min += p.v;\n      max += p.v;\n      sum\
    \ += p.v * sz;\n      all_min += p.v;\n      all_max += p.v;\n      all_sum +=\
    \ p.v * all_sz;\n    }\n  }\n};\n\n// Heavy-edge \u306E\u60C5\u5831\ntemplate<\
    \ typename LInfo, typename Lazy >\nstruct Info {\n  T v;\n\n  T path_min, path_max,\
    \ path_sum, path_sz;\n  T light_min, light_max, light_sum, light_sz;\n\n  // \u5358\
    \u4F4D\u5143(\u30AD\u30FC\u306E\u5024\u306F\u30A2\u30AF\u30BB\u30B9\u3057\u306A\
    \u3044\u306E\u3067\u672A\u521D\u671F\u5316\u3067\u3082\u3088\u3044\n  Info() :\
    \ light_min(inf_max), light_max(inf_min), light_sum(0), light_sz(0),\n       \
    \    path_min(inf_max), path_max(inf_min), path_sum(0), path_sz(0) {}\n\n  //\
    \ \u521D\u671F\u5316\n  Info(T v) : v(v) {}\n\n  // \u53CD\u8EE2\n  void toggle()\
    \ {}\n\n  // p\u304C\u89AA, c\u304Cheavy-edge\u3067\u7D50\u3070\u308C\u305F\u5B50\
    , l\u304C\u305D\u308C\u4EE5\u5916\u306E\u5B50\n  void update(const Info &p, const\
    \ Info &c, const LInfo &l) {\n    light_min = min({p.light_min, c.light_min, l.all_min});\n\
    \    light_max = max({p.light_max, c.light_max, l.all_max});\n    light_sum =\
    \ p.light_sum + c.light_sum + l.all_sum;\n    light_sz = p.light_sz + c.light_sz\
    \ + l.all_sz;\n\n    path_min = min({p.path_min, v, c.path_min});\n    path_max\
    \ = max({p.path_max, v, c.path_max});\n    path_sum = p.path_sum + v + c.path_sum;\n\
    \    path_sz = p.path_sz + 1 + c.path_sz;\n  }\n\n  // \u89AA\u3068 light-edge\
    \ \u3067\u7E4B\u3052\u308B\n  LInfo link() const {\n    return LInfo(min(light_min,\
    \ path_min), max(light_max, path_max), path_sum + light_sum, light_sz + path_sz);\n\
    \  }\n\n  // \u9045\u5EF6\u4F1D\u642C\n  void propagate(const Lazy &p) {\n   \
    \ if(p.type == 0) {\n      return;\n    } else if(p.type == 1) { // change\n \
    \     v = p.v;\n      path_min = p.v;\n      path_max = p.v;\n      path_sum =\
    \ p.v * path_sz;\n    } else { // inc\n      v += p.v;\n      path_min += p.v;\n\
    \      path_max += p.v;\n      path_sum += p.v * path_sz;\n    }\n  }\n\n  //\
    \ light-edge\u306B\u5BFE\u3059\u308B\u9045\u5EF6\u4F1D\u642C\n  // path\u3068\
    subtree\u306E\u9045\u5EF6\u4F1D\u642C\u304C\u4E21\u65B9\u3042\u308B\u5834\u5408\
    \u306B\u5B9F\u88C5\u3059\u308B\n  void propagate_light(const Lazy &p) {\n    if(p.type\
    \ == 0 or light_min == inf_max) {\n      return;\n    } else if(p.type == 1) {\
    \ // change\n      light_min = p.v;\n      light_max = p.v;\n      light_sum =\
    \ p.v * light_sz;\n    } else { // inc\n      light_min += p.v;\n      light_max\
    \ += p.v;\n      light_sum += p.v * light_sz;\n    }\n  }\n};\n\nusing LCT = SuperLinkCutTree<\
    \ Info, LInfo, Lazy >;\n#line 6 \"test/verify/dmoj-ds5.hpp\"\n\n#line 1 \"other/scanner.hpp\"\
    \n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n */\nstruct Scanner {\npublic:\n\
    \n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n  template< typename T, typename...\
    \ E >\n  void read(T &t, E &... e) {\n    read_single(t);\n    read(e...);\n \
    \ }\n\nprivate:\n  static constexpr size_t line_size = 1 << 16;\n  static constexpr\
    \ size_t int_digits = 20;\n  char line[line_size + 1] = {};\n  FILE *fp = nullptr;\n\
    \  char *st = line;\n  char *ed = line;\n\n  void read() {}\n\n  static inline\
    \ bool is_space(char c) {\n    return c <= ' ';\n  }\n\n  void reread() {\n  \
    \  ptrdiff_t len = ed - st;\n    memmove(line, st, len);\n    char *tmp = line\
    \ + len;\n    ed = tmp + fread(tmp, 1, line_size - len, fp);\n    *ed = 0;\n \
    \   st = line;\n  }\n\n  void skip_space() {\n    while(true) {\n      if(st ==\
    \ ed) reread();\n      while(*st && is_space(*st)) ++st;\n      if(st != ed) return;\n\
    \    }\n  }\n\n  template< typename T, enable_if_t< is_integral< T >::value, int\
    \ > = 0 >\n  void read_single(T &s) {\n    skip_space();\n    if(st + int_digits\
    \ >= ed) reread();\n    bool neg = false;\n    if(is_signed< T >::value && *st\
    \ == '-') {\n      neg = true;\n      ++st;\n    }\n    typename make_unsigned<\
    \ T >::type y = *st++ - '0';\n    while(*st >= '0') {\n      y = 10 * y + *st++\
    \ - '0';\n    }\n    s = (neg ? -y : y);\n  }\n\n  template< typename T, enable_if_t<\
    \ is_same< T, string >::value, int > = 0 >\n  void read_single(T &s) {\n    s\
    \ = \"\";\n    skip_space();\n    while(true) {\n      char *base = st;\n    \
    \  while(*st && !is_space(*st)) ++st;\n      s += string(base, st);\n      if(st\
    \ != ed) return;\n      reread();\n    }\n  }\n\n  template< typename T >\n  void\
    \ read_single(vector< T > &s) {\n    for(auto &d : s) read(d);\n  }\n};\n#line\
    \ 1 \"other/printer.hpp\"\n/**\n * @brief Printer(\u9AD8\u901F\u51FA\u529B)\n\
    \ */\nstruct Printer {\npublic:\n  explicit Printer(FILE *fp) : fp(fp) {}\n\n\
    \  ~Printer() { flush(); }\n\n  template< bool f = false, typename T, typename...\
    \ E >\n  void write(const T &t, const E &... e) {\n    if(f) write_single(' ');\n\
    \    write_single(t);\n    write< true >(e...);\n  }\n\n  template< typename...\
    \ T >\n  void writeln(const T &...t) {\n    write(t...);\n    write_single('\\\
    n');\n  }\n\n  void flush() {\n    fwrite(line, 1, st - line, fp);\n    st = line;\n\
    \  }\n\nprivate:\n  FILE *fp = nullptr;\n  static constexpr size_t line_size =\
    \ 1 << 16;\n  static constexpr size_t int_digits = 20;\n  char line[line_size\
    \ + 1] = {};\n  char *st = line;\n\n  template< bool f = false >\n  void write()\
    \ {}\n\n  void write_single(const char &t) {\n    if(st + 1 >= line + line_size)\
    \ flush();\n    *st++ = t;\n  }\n\n  template< typename T, enable_if_t< is_integral<\
    \ T >::value, int > = 0 >\n  void write_single(T s) {\n    if(st + int_digits\
    \ >= line + line_size) flush();\n    st += to_chars(st, st + int_digits, s).ptr\
    \ - st;\n  }\n\n  void write_single(const string &s) {\n    for(auto &c: s) write_single(c);\n\
    \  }\n\n  void write_single(const char *s) {\n    while(*s != 0) write_single(*s++);\n\
    \  }\n\n  template< typename T >\n  void write_single(const vector< T > &s) {\n\
    \    for(size_t i = 0; i < s.size(); i++) {\n      if(i) write_single(' ');\n\
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/dmoj-ds5.hpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n\n  int N, M;\n\
    \  in.read(N, M);\n  vector< vector< int > > g(N);\n  for(int i = 0; i + 1 < N;\
    \ i++) {\n    int x, y;\n    in.read(x, y);\n    --x, --y;\n    g[x].emplace_back(y);\n\
    \    g[y].emplace_back(x);\n  }\n  LCT lct;\n  vector< LCT::NP > vs(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    T x;\n    in.read(x);\n    vs[i] = lct.alloc(x);\n\
    \  }\n  int R;\n  in.read(R);\n  --R;\n  MFP([&](auto dfs, int idx, int par) ->\
    \ void {\n    for(auto &to: g[idx]) {\n      if(to != par) {\n        lct.link(vs[to],\
    \ vs[idx]);\n        dfs(to, idx);\n      }\n    }\n  })(R, -1);\n\n  for(int\
    \ i = 0; i < M; i++) {\n    int k;\n    in.read(k);\n    if(k == 0) {\n      int\
    \ x, y;\n      in.read(x, y);\n      --x;\n      lct.evert(vs[R]);\n      lct.set_propagate_subtree(vs[x],\
    \ {1, y});\n    } else if(k == 1) {\n      in.read(R);\n      --R;\n    } else\
    \ if(k == 2) {\n      int x, y;\n      T z;\n      in.read(x, y, z);\n      --x,\
    \ --y;\n      lct.set_propagate_path(vs[x], vs[y], {1, z});\n    } else if(k ==\
    \ 3) {\n      int x;\n      in.read(x);\n      --x;\n      lct.evert(vs[R]);\n\
    \      auto ret = lct.query_subtree(vs[x]);\n      out.writeln(min(ret.light_min,\
    \ ret.path_min));\n    } else if(k == 4) {\n      int x;\n      in.read(x);\n\
    \      --x;\n      lct.evert(vs[R]);\n      auto ret = lct.query_subtree(vs[x]);\n\
    \      out.writeln(max(ret.light_max, ret.path_max));\n    } else if(k == 5) {\n\
    \      int x, y;\n      in.read(x, y);\n      --x;\n      lct.evert(vs[R]);\n\
    \      lct.set_propagate_subtree(vs[x], {2, y});\n    } else if(k == 6) {\n  \
    \    int x, y;\n      T z;\n      in.read(x, y, z);\n      --x, --y;\n      lct.set_propagate_path(vs[x],\
    \ vs[y], {2, z});\n    } else if(k == 7) {\n      int x, y;\n      in.read(x,\
    \ y);\n      --x, --y;\n      out.writeln(lct.query_path(vs[x], vs[y]).path_min);\n\
    \    } else if(k == 8) {\n      int x, y;\n      in.read(x, y);\n      --x, --y;\n\
    \      out.writeln(lct.query_path(vs[x], vs[y]).path_max);\n    } else if(k ==\
    \ 9) {\n      int x, y;\n      in.read(x, y);\n      --x, --y;\n      lct.evert(vs[R]);\n\
    \      if(lct.lca(vs[x], vs[y]) == vs[x]) {\n        continue;\n      }\n    \
    \  lct.cut(vs[x]);\n      lct.link(vs[x], vs[y]);\n    } else if(k == 10) {\n\
    \      int x, y;\n      in.read(x, y);\n      --x, --y;\n      out.writeln(lct.query_path(vs[x],\
    \ vs[y]).path_sum);\n    } else {\n      int x;\n      in.read(x);\n      --x;\n\
    \      lct.evert(vs[R]);\n      auto ret = lct.query_subtree(vs[x]);\n      out.writeln(ret.path_sum\
    \ + ret.light_sum);\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://dmoj.ca/problem/ds5\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../structure/develop/dynamic-tree-test.hpp\"\n\n#include \"\
    ../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\n\nint main()\
    \ {\n  Scanner in(stdin);\n  Printer out(stdout);\n\n  int N, M;\n  in.read(N,\
    \ M);\n  vector< vector< int > > g(N);\n  for(int i = 0; i + 1 < N; i++) {\n \
    \   int x, y;\n    in.read(x, y);\n    --x, --y;\n    g[x].emplace_back(y);\n\
    \    g[y].emplace_back(x);\n  }\n  LCT lct;\n  vector< LCT::NP > vs(N);\n  for(int\
    \ i = 0; i < N; i++) {\n    T x;\n    in.read(x);\n    vs[i] = lct.alloc(x);\n\
    \  }\n  int R;\n  in.read(R);\n  --R;\n  MFP([&](auto dfs, int idx, int par) ->\
    \ void {\n    for(auto &to: g[idx]) {\n      if(to != par) {\n        lct.link(vs[to],\
    \ vs[idx]);\n        dfs(to, idx);\n      }\n    }\n  })(R, -1);\n\n  for(int\
    \ i = 0; i < M; i++) {\n    int k;\n    in.read(k);\n    if(k == 0) {\n      int\
    \ x, y;\n      in.read(x, y);\n      --x;\n      lct.evert(vs[R]);\n      lct.set_propagate_subtree(vs[x],\
    \ {1, y});\n    } else if(k == 1) {\n      in.read(R);\n      --R;\n    } else\
    \ if(k == 2) {\n      int x, y;\n      T z;\n      in.read(x, y, z);\n      --x,\
    \ --y;\n      lct.set_propagate_path(vs[x], vs[y], {1, z});\n    } else if(k ==\
    \ 3) {\n      int x;\n      in.read(x);\n      --x;\n      lct.evert(vs[R]);\n\
    \      auto ret = lct.query_subtree(vs[x]);\n      out.writeln(min(ret.light_min,\
    \ ret.path_min));\n    } else if(k == 4) {\n      int x;\n      in.read(x);\n\
    \      --x;\n      lct.evert(vs[R]);\n      auto ret = lct.query_subtree(vs[x]);\n\
    \      out.writeln(max(ret.light_max, ret.path_max));\n    } else if(k == 5) {\n\
    \      int x, y;\n      in.read(x, y);\n      --x;\n      lct.evert(vs[R]);\n\
    \      lct.set_propagate_subtree(vs[x], {2, y});\n    } else if(k == 6) {\n  \
    \    int x, y;\n      T z;\n      in.read(x, y, z);\n      --x, --y;\n      lct.set_propagate_path(vs[x],\
    \ vs[y], {2, z});\n    } else if(k == 7) {\n      int x, y;\n      in.read(x,\
    \ y);\n      --x, --y;\n      out.writeln(lct.query_path(vs[x], vs[y]).path_min);\n\
    \    } else if(k == 8) {\n      int x, y;\n      in.read(x, y);\n      --x, --y;\n\
    \      out.writeln(lct.query_path(vs[x], vs[y]).path_max);\n    } else if(k ==\
    \ 9) {\n      int x, y;\n      in.read(x, y);\n      --x, --y;\n      lct.evert(vs[R]);\n\
    \      if(lct.lca(vs[x], vs[y]) == vs[x]) {\n        continue;\n      }\n    \
    \  lct.cut(vs[x]);\n      lct.link(vs[x], vs[y]);\n    } else if(k == 10) {\n\
    \      int x, y;\n      in.read(x, y);\n      --x, --y;\n      out.writeln(lct.query_path(vs[x],\
    \ vs[y]).path_sum);\n    } else {\n      int x;\n      in.read(x);\n      --x;\n\
    \      lct.evert(vs[R]);\n      auto ret = lct.query_subtree(vs[x]);\n      out.writeln(ret.path_sum\
    \ + ret.light_sum);\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/develop/dynamic-tree-test.hpp
  - structure/develop/super-link-cut-tree.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: false
  path: test/verify/dmoj-ds5.hpp
  requiredBy: []
  timestamp: '2023-04-03 20:40:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/verify/dmoj-ds5.hpp
layout: document
redirect_from:
- /library/test/verify/dmoj-ds5.hpp
- /library/test/verify/dmoj-ds5.hpp.html
title: test/verify/dmoj-ds5.hpp
---
