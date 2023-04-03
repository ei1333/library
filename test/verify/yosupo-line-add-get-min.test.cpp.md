---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/convex-hull-trick/dynamic-li-chao-tree.hpp
    title: Dynamic-Li-Chao-Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"test/verify/yosupo-line-add-get-min.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-line-add-get-min.test.cpp\"\
    \n\n#line 1 \"structure/convex-hull-trick/dynamic-li-chao-tree.hpp\"\n/**\n *\
    \ @brief Dynamic-Li-Chao-Tree\n * @docs docs/dynamic-li-chao-tree.md\n*/\ntemplate<\
    \ typename T, T x_low, T x_high, T id >\nstruct DynamicLiChaoTree {\n\n  struct\
    \ Line {\n    T a, b;\n\n    Line(T a, T b) : a(a), b(b) {}\n\n    inline T get(T\
    \ x) const { return a * x + b; }\n  };\n\n  struct Node {\n    Line x;\n    Node\
    \ *l, *r;\n\n    Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}\n  };\n\
    \n  Node *root;\n\n  DynamicLiChaoTree() : root{nullptr} {}\n\n  Node *add_line(Node\
    \ *t, Line &x, const T &l, const T &r, const T &x_l, const T &x_r) {\n    if(!t)\
    \ return new Node(x);\n\n    T t_l = t->x.get(l), t_r = t->x.get(r);\n\n    if(t_l\
    \ <= x_l && t_r <= x_r) {\n      return t;\n    } else if(t_l >= x_l && t_r >=\
    \ x_r) {\n      t->x = x;\n      return t;\n    } else {\n      T m = (l + r)\
    \ / 2;\n      if(m == r) --m;\n      T t_m = t->x.get(m), x_m = x.get(m);\n  \
    \    if(t_m > x_m) {\n        swap(t->x, x);\n        if(x_l >= t_l) t->l = add_line(t->l,\
    \ x, l, m, t_l, t_m);\n        else t->r = add_line(t->r, x, m + 1, r, t_m + x.a,\
    \ t_r);\n      } else {\n        if(t_l >= x_l) t->l = add_line(t->l, x, l, m,\
    \ x_l, x_m);\n        else t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);\n\
    \      }\n      return t;\n    }\n  }\n\n  void add_line(const T &a, const T &b)\
    \ {\n    Line x(a, b);\n    root = add_line(root, x, x_low, x_high, x.get(x_low),\
    \ x.get(x_high));\n  }\n\n  Node *add_segment(Node *t, Line &x, const T &a, const\
    \ T &b, const T &l, const T &r, const T &x_l, const T &x_r) {\n    if(r < a ||\
    \ b < l) return t;\n    if(a <= l && r <= b) {\n      Line y{x};\n      return\
    \ add_line(t, y, l, r, x_l, x_r);\n    }\n    if(t) {\n      T t_l = t->x.get(l),\
    \ t_r = t->x.get(r);\n      if(t_l <= x_l && t_r <= x_r) return t;\n    } else\
    \ {\n      t = new Node(Line(0, id));\n    }\n    T m = (l + r) / 2;\n    if(m\
    \ == r) --m;\n    T x_m = x.get(m);\n    t->l = add_segment(t->l, x, a, b, l,\
    \ m, x_l, x_m);\n    t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);\n\
    \    return t;\n  }\n\n  void add_segment(const T &l, const T &r, const T &a,\
    \ const T &b) {\n    Line x(a, b);\n    root = add_segment(root, x, l, r - 1,\
    \ x_low, x_high, x.get(x_low), x.get(x_high));\n  }\n\n  T query(const Node *t,\
    \ const T &l, const T &r, const T &x) const {\n    if(!t) return id;\n    if(l\
    \ == r) return t->x.get(x);\n    T m = (l + r) / 2;\n    if(m == r) --m;\n   \
    \ if(x <= m) return min(t->x.get(x), query(t->l, l, m, x));\n    else return min(t->x.get(x),\
    \ query(t->r, m + 1, r, x));\n  }\n\n  T query(const T &x) const {\n    return\
    \ query(root, x_low, x_high, x);\n  }\n};\n#line 6 \"test/verify/yosupo-line-add-get-min.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  const int64 MAX_P = 1000000000;\n\
    \  DynamicLiChaoTree< int64, -MAX_P, MAX_P, infll > cht;\n  for(int i = 0; i <\
    \ N; i++) {\n    int64 a, b;\n    cin >> a >> b;\n    cht.add_line(a, b);\n  }\n\
    \  while(Q--) {\n    int T;\n    cin >> T;\n    if(T == 0) {\n      int64 A, B;\n\
    \      cin >> A >> B;\n      cht.add_line(A, B);\n    } else {\n      int64 P;\n\
    \      cin >> P;\n      cout << cht.query(P) << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  const int64 MAX_P = 1000000000;\n\
    \  DynamicLiChaoTree< int64, -MAX_P, MAX_P, infll > cht;\n  for(int i = 0; i <\
    \ N; i++) {\n    int64 a, b;\n    cin >> a >> b;\n    cht.add_line(a, b);\n  }\n\
    \  while(Q--) {\n    int T;\n    cin >> T;\n    if(T == 0) {\n      int64 A, B;\n\
    \      cin >> A >> B;\n      cht.add_line(A, B);\n    } else {\n      int64 P;\n\
    \      cin >> P;\n      cout << cht.query(P) << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/convex-hull-trick/dynamic-li-chao-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-line-add-get-min.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-line-add-get-min.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-line-add-get-min.test.cpp
- /verify/test/verify/yosupo-line-add-get-min.test.cpp.html
title: test/verify/yosupo-line-add-get-min.test.cpp
---
