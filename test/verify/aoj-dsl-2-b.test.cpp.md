---
data:
  _extendedDependsOn:
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "#line 1 \"test/verify/aoj-dsl-2-b.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dsl-2-b.test.cpp\"\
    \n\n#line 1 \"structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief Binary-Indexed-Tree(BIT)\n\
    \ * @docs docs/binary-indexed-tree.md\n */\ntemplate< typename T >\nstruct BinaryIndexedTree\
    \ {\nprivate:\n  int n;\n  vector< T > data;\n\npublic:\n  BinaryIndexedTree()\
    \ = default;\n\n  explicit BinaryIndexedTree(int n) : n(n) {\n    data.assign(n\
    \ + 1, T());\n  }\n\n  explicit BinaryIndexedTree(const vector< T > &v) :\n  \
    \    BinaryIndexedTree((int) v.size()) {\n    build(v);\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int i = 1; i <=\
    \ n; i++) data[i] = v[i - 1];\n    for(int i = 1; i <= n; i++) {\n      int j\
    \ = i + (i & -i);\n      if(j <= n) data[j] += data[i];\n    }\n  }\n\n  void\
    \ apply(int k, const T &x) {\n    for(++k; k <= n; k += k & -k) data[k] += x;\n\
    \  }\n\n  T prod(int r) const {\n    T ret = T();\n    for(; r > 0; r -= r & -r)\
    \ ret += data[r];\n    return ret;\n  }\n\n  T prod(int l, int r) const {\n  \
    \  return prod(r) - prod(l);\n  }\n\n  int lower_bound(T x) const {\n    int i\
    \ = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n      if(i + k\
    \ <= n && data[i + k] < x) {\n        x -= data[i + k];\n        i += k;\n   \
    \   }\n    }\n    return i;\n  }\n\n  int upper_bound(T x) const {\n    int i\
    \ = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n      if(i + k\
    \ <= n && data[i + k] <= x) {\n        x -= data[i + k];\n        i += k;\n  \
    \    }\n    }\n    return i;\n  }\n};\n#line 6 \"test/verify/aoj-dsl-2-b.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  BinaryIndexedTree< int > bit(N);\n\
    \  while(Q--) {\n    int T, X, Y;\n    cin >> T >> X >> Y;\n    if(T == 0) bit.apply(X\
    \ - 1, Y);\n    else cout << bit.prod(X - 1, Y) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/others/binary-indexed-tree.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  BinaryIndexedTree< int > bit(N);\n\
    \  while(Q--) {\n    int T, X, Y;\n    cin >> T >> X >> Y;\n    if(T == 0) bit.apply(X\
    \ - 1, Y);\n    else cout << bit.prod(X - 1, Y) << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: true
  path: test/verify/aoj-dsl-2-b.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dsl-2-b.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dsl-2-b.test.cpp
- /verify/test/verify/aoj-dsl-2-b.test.cpp.html
title: test/verify/aoj-dsl-2-b.test.cpp
---
