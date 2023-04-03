---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/segment-tree/dual-segment-tree.hpp
    title: "Dual-Segment-Tree(\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
  bundledCode: "#line 1 \"test/verify/aoj-dsl-2-d.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dsl-2-d.test.cpp\"\
    \n\n#line 1 \"structure/segment-tree/dual-segment-tree.hpp\"\n/**\n * @brief Dual-Segment-Tree(\u53CC\
    \u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs docs/dual-segment-tree.md\n\
    \ */\ntemplate< typename E, typename H >\nstruct DualSegmentTree {\n  int sz,\
    \ height;\n  vector< E > lazy;\n  const H h;\n  const E ei;\n\n  DualSegmentTree(int\
    \ n, const H h, const E &ei) : h(h), ei(ei) {\n    sz = 1;\n    height = 0;\n\
    \    while(sz < n) sz <<= 1, height++;\n    lazy.assign(2 * sz, ei);\n  }\n\n\
    \  inline void propagate(int k) {\n    if(lazy[k] != ei) {\n      lazy[2 * k +\
    \ 0] = h(lazy[2 * k + 0], lazy[k]);\n      lazy[2 * k + 1] = h(lazy[2 * k + 1],\
    \ lazy[k]);\n      lazy[k] = ei;\n    }\n  }\n\n  inline void thrust(int k) {\n\
    \    for(int i = height; i > 0; i--) propagate(k >> i);\n  }\n\n  void update(int\
    \ a, int b, const E &x) {\n    thrust(a += sz);\n    thrust(b += sz - 1);\n  \
    \  for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {\n      if(l & 1) lazy[l]\
    \ = h(lazy[l], x), ++l;\n      if(r & 1) --r, lazy[r] = h(lazy[r], x);\n    }\n\
    \  }\n\n  E operator[](int k) {\n    thrust(k += sz);\n    return lazy[k];\n \
    \ }\n};\n\ntemplate< typename E, typename H >\nDualSegmentTree< E, H > get_dual_segment_tree(int\
    \ N, const H& h, const E& ei) {\n  return {N, h, ei};\n}\n#line 6 \"test/verify/aoj-dsl-2-d.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  auto h = [](int a, int b) {\
    \ return b; };\n  auto seg = get_dual_segment_tree(N, h, INT_MAX);\n  while(Q--)\
    \ {\n    int com;\n    cin >> com;\n    if(com == 0) {\n      int l, r, x;\n \
    \     cin >> l >> r >> x;\n      seg.update(l, r + 1, x);\n    } else if(com ==\
    \ 1) {\n      int k;\n      cin >> k;\n      cout << seg[k] << \"\\n\";\n    }\n\
    \  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/segment-tree/dual-segment-tree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  auto h = [](int a, int b) {\
    \ return b; };\n  auto seg = get_dual_segment_tree(N, h, INT_MAX);\n  while(Q--)\
    \ {\n    int com;\n    cin >> com;\n    if(com == 0) {\n      int l, r, x;\n \
    \     cin >> l >> r >> x;\n      seg.update(l, r + 1, x);\n    } else if(com ==\
    \ 1) {\n      int k;\n      cin >> k;\n      cout << seg[k] << \"\\n\";\n    }\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/segment-tree/dual-segment-tree.hpp
  isVerificationFile: true
  path: test/verify/aoj-dsl-2-d.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dsl-2-d.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dsl-2-d.test.cpp
- /verify/test/verify/aoj-dsl-2-d.test.cpp.html
title: test/verify/aoj-dsl-2-d.test.cpp
---
