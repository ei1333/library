---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/verify/yosupo-static-range-inversions-query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-static-range-inversions-query.test.cpp\"\
    \n\n#line 1 \"other/mo.hpp\"\n/**\n * @brief Mo's Algorithm\n */\nstruct Mo {\n\
    \  int n;\n  vector< pair< int, int > > lr;\n\n  explicit Mo(int n) : n(n) {}\n\
    \n  void add(int l, int r) { /* [l, r) */\n    lr.emplace_back(l, r);\n  }\n\n\
    \  template< typename AL, typename AR, typename EL, typename ER, typename O >\n\
    \  void build(const AL &add_left, const AR &add_right, const EL &erase_left, const\
    \ ER &erase_right, const O &out) {\n    int q = (int) lr.size();\n    int bs =\
    \ n / min< int >(n, sqrt(q));\n    vector< int > ord(q);\n    iota(begin(ord),\
    \ end(ord), 0);\n    sort(begin(ord), end(ord), [&](int a, int b) {\n      int\
    \ ablock = lr[a].first / bs, bblock = lr[b].first / bs;\n      if(ablock != bblock)\
    \ return ablock < bblock;\n      return (ablock & 1) ? lr[a].second > lr[b].second\
    \ : lr[a].second < lr[b].second;\n    });\n    int l = 0, r = 0;\n    for(auto\
    \ idx : ord) {\n      while(l > lr[idx].first) add_left(--l);\n      while(r <\
    \ lr[idx].second) add_right(r++);\n      while(l < lr[idx].first) erase_left(l++);\n\
    \      while(r > lr[idx].second) erase_right(--r);\n      out(idx);\n    }\n \
    \ }\n\n  template< typename A, typename E, typename O >\n  void build(const A\
    \ &add, const E &erase, const O &out) {\n    build(add, add, erase, erase, out);\n\
    \  }\n};\n#line 1 \"structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief\
    \ Binary-Indexed-Tree(BIT)\n * @docs docs/binary-indexed-tree.md\n */\ntemplate<\
    \ typename T >\nstruct BinaryIndexedTree {\nprivate:\n  int n;\n  vector< T >\
    \ data;\n\npublic:\n  BinaryIndexedTree() = default;\n\n  explicit BinaryIndexedTree(int\
    \ n) : n(n) {\n    data.assign(n + 1, T());\n  }\n\n  explicit BinaryIndexedTree(const\
    \ vector< T > &v) :\n      BinaryIndexedTree((int) v.size()) {\n    build(v);\n\
    \  }\n\n  void build(const vector< T > &v) {\n    assert(n == (int) v.size());\n\
    \    for(int i = 1; i <= n; i++) data[i] = v[i - 1];\n    for(int i = 1; i <=\
    \ n; i++) {\n      int j = i + (i & -i);\n      if(j <= n) data[j] += data[i];\n\
    \    }\n  }\n\n  void apply(int k, const T &x) {\n    for(++k; k <= n; k += k\
    \ & -k) data[k] += x;\n  }\n\n  T prod(int r) const {\n    T ret = T();\n    for(;\
    \ r > 0; r -= r & -r) ret += data[r];\n    return ret;\n  }\n\n  T prod(int l,\
    \ int r) const {\n    return prod(r) - prod(l);\n  }\n\n  int lower_bound(T x)\
    \ const {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1)\
    \ {\n      if(i + k <= n && data[i + k] < x) {\n        x -= data[i + k];\n  \
    \      i += k;\n      }\n    }\n    return i;\n  }\n\n  int upper_bound(T x) const\
    \ {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n \
    \     if(i + k <= n && data[i + k] <= x) {\n        x -= data[i + k];\n      \
    \  i += k;\n      }\n    }\n    return i;\n  }\n};\n#line 7 \"test/verify/yosupo-static-range-inversions-query.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  for(auto\
    \ &a : A) cin >> a;\n  Mo mo(N);\n  for(int i = 0; i < Q; i++) {\n    int l, r;\n\
    \    cin >> l >> r;\n    mo.add(l, r);\n  }\n  vector< int > xs{A};\n  sort(begin(xs),\
    \ end(xs));\n  xs.erase(unique(begin(xs), end(xs)), end(xs));\n  for(auto &a :\
    \ A) a = lower_bound(begin(xs), end(xs), a) - begin(xs);\n  BinaryIndexedTree<\
    \ int > bit(xs.size());\n  int64_t inv = 0, all = 0;\n  vector< int64_t > ans(Q);\n\
    \  auto add_left = [&](int idx) {\n    inv += bit.prod(A[idx]);\n    bit.apply(A[idx],\
    \ 1);\n    all++;\n  };\n  auto add_right = [&](int idx) {\n    inv += all - bit.prod(A[idx]\
    \ + 1);\n    bit.apply(A[idx], 1);\n    ++all;\n  };\n  auto erase_left = [&](int\
    \ idx) {\n    inv -= bit.prod(A[idx]);\n    bit.apply(A[idx], -1);\n    --all;\n\
    \  };\n  auto erase_right = [&](int idx) {\n    inv -= all - bit.prod(A[idx] +\
    \ 1);\n    bit.apply(A[idx], -1);\n    --all;\n  };\n  auto out = [&](int idx)\
    \ {\n    ans[idx] = inv;\n  };\n  mo.build(add_left, add_right, erase_left, erase_right,\
    \ out);\n  for(auto &p : ans) cout << p << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../other/mo.hpp\"\
    \n#include \"../../structure/others/binary-indexed-tree.hpp\"\n\nint main() {\n\
    \  int N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  for(auto &a : A) cin\
    \ >> a;\n  Mo mo(N);\n  for(int i = 0; i < Q; i++) {\n    int l, r;\n    cin >>\
    \ l >> r;\n    mo.add(l, r);\n  }\n  vector< int > xs{A};\n  sort(begin(xs), end(xs));\n\
    \  xs.erase(unique(begin(xs), end(xs)), end(xs));\n  for(auto &a : A) a = lower_bound(begin(xs),\
    \ end(xs), a) - begin(xs);\n  BinaryIndexedTree< int > bit(xs.size());\n  int64_t\
    \ inv = 0, all = 0;\n  vector< int64_t > ans(Q);\n  auto add_left = [&](int idx)\
    \ {\n    inv += bit.prod(A[idx]);\n    bit.apply(A[idx], 1);\n    all++;\n  };\n\
    \  auto add_right = [&](int idx) {\n    inv += all - bit.prod(A[idx] + 1);\n \
    \   bit.apply(A[idx], 1);\n    ++all;\n  };\n  auto erase_left = [&](int idx)\
    \ {\n    inv -= bit.prod(A[idx]);\n    bit.apply(A[idx], -1);\n    --all;\n  };\n\
    \  auto erase_right = [&](int idx) {\n    inv -= all - bit.prod(A[idx] + 1);\n\
    \    bit.apply(A[idx], -1);\n    --all;\n  };\n  auto out = [&](int idx) {\n \
    \   ans[idx] = inv;\n  };\n  mo.build(add_left, add_right, erase_left, erase_right,\
    \ out);\n  for(auto &p : ans) cout << p << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - other/mo.hpp
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: true
  path: test/verify/yosupo-static-range-inversions-query.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-static-range-inversions-query.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-static-range-inversions-query.test.cpp
- /verify/test/verify/yosupo-static-range-inversions-query.test.cpp.html
title: test/verify/yosupo-static-range-inversions-query.test.cpp
---
