---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/segment-tree/segment-tree.hpp
    title: "Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
  bundledCode: "#line 1 \"test/verify/aoj-dsl-2-a.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dsl-2-a.test.cpp\"\
    \n\n#line 1 \"structure/segment-tree/segment-tree.hpp\"\n/**\n * @brief Segment\
    \ Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs docs/segment-tree.md\n\
    \ */\ntemplate< typename T, typename F >\nstruct SegmentTree {\n  int n, sz;\n\
    \  vector< T > seg;\n\n  const F f;\n  const T ti;\n\n  SegmentTree() = default;\n\
    \n  explicit SegmentTree(int n, const F f, const T &ti) : n(n), f(f), ti(ti) {\n\
    \    sz = 1;\n    while(sz < n) sz <<= 1;\n    seg.assign(2 * sz, ti);\n  }\n\n\
    \  explicit SegmentTree(const vector< T > &v, const F f, const T &ti) :\n    \
    \  SegmentTree((int) v.size(), f, ti) {\n    build(v);\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int k = 0; k <\
    \ n; k++) seg[k + sz] = v[k];\n    for(int k = sz - 1; k > 0; k--) {\n      seg[k]\
    \ = f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  void set(int k, const\
    \ T &x) {\n    k += sz;\n    seg[k] = x;\n    while(k >>= 1) {\n      seg[k] =\
    \ f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  T get(int k) const {\n \
    \   return seg[k + sz];\n  }\n\n  T operator[](const int &k) const {\n    return\
    \ get(k);\n  }\n\n  void apply(int k, const T &x) {\n    k += sz;\n    seg[k]\
    \ = f(seg[k], x);\n    while(k >>= 1) {\n      seg[k] = f(seg[2 * k + 0], seg[2\
    \ * k + 1]);\n    }\n  }\n\n  T prod(int l, int r) const {\n    T L = ti, R =\
    \ ti;\n    for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n      if(l & 1) L\
    \ = f(L, seg[l++]);\n      if(r & 1) R = f(seg[--r], R);\n    }\n    return f(L,\
    \ R);\n  }\n\n  T all_prod() const {\n    return seg[1];\n  }\n\n  template< typename\
    \ C >\n  int find_first(int l, const C &check) const {\n    if(l >= n) return\
    \ n;\n    l += sz;\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>=\
    \ 1;\n      if(check(f(sum, seg[l]))) {\n        while(l < sz) {\n          l\
    \ <<= 1;\n          auto nxt = f(sum, seg[l]);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            l++;\n          }\n        }\n        return\
    \ l + 1 - sz;\n      }\n      sum = f(sum, seg[l++]);\n    } while((l & -l) !=\
    \ l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int r,\
    \ const C &check) const {\n    if(r <= 0) return -1;\n    r += sz;\n    T sum\
    \ = ti;\n    do {\n      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n     \
    \ if(check(f(seg[r], sum))) {\n        while(r < sz) {\n          r = (r << 1)\
    \ + 1;\n          auto nxt = f(seg[r], sum);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            r--;\n          }\n        }\n        return\
    \ r - sz;\n      }\n      sum = f(seg[r], sum);\n    } while((r & -r) != r);\n\
    \    return -1;\n  }\n};\n\ntemplate< typename T, typename F >\nSegmentTree< T,\
    \ F > get_segment_tree(int N, const F &f, const T &ti) {\n  return SegmentTree{N,\
    \ f, ti};\n}\n\ntemplate< typename T, typename F >\nSegmentTree< T, F > get_segment_tree(const\
    \ vector< T > &v, const F &f, const T &ti) {\n  return SegmentTree{v, f, ti};\n\
    }\n#line 6 \"test/verify/aoj-dsl-2-a.test.cpp\"\n\nint main() {\n  int N, Q;\n\
    \  scanf(\"%d %d\", &N, &Q);\n  auto seg = get_segment_tree(N, [](int a, int b)\
    \ { return min(a, b); }, INT_MAX);\n  while(Q--) {\n    int T, X, Y;\n    scanf(\"\
    %d %d %d\", &T, &X, &Y);\n    if(T == 0) seg.set(X, Y);\n    else printf(\"%d\\\
    n\", seg.prod(X, Y + 1));\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/segment-tree/segment-tree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  scanf(\"%d %d\", &N, &Q);\n  auto seg = get_segment_tree(N,\
    \ [](int a, int b) { return min(a, b); }, INT_MAX);\n  while(Q--) {\n    int T,\
    \ X, Y;\n    scanf(\"%d %d %d\", &T, &X, &Y);\n    if(T == 0) seg.set(X, Y);\n\
    \    else printf(\"%d\\n\", seg.prod(X, Y + 1));\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/segment-tree/segment-tree.hpp
  isVerificationFile: true
  path: test/verify/aoj-dsl-2-a.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dsl-2-a.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dsl-2-a.test.cpp
- /verify/test/verify/aoj-dsl-2-a.test.cpp.html
title: test/verify/aoj-dsl-2-a.test.cpp
---
