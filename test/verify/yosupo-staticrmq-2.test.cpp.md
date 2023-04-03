---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/disjoint-sparse-table.hpp
    title: Disjoint-Sparse-Table
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/verify/yosupo-staticrmq-2.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-staticrmq-2.test.cpp\"\
    \n\n#line 1 \"structure/others/disjoint-sparse-table.hpp\"\n/**\n * @brief Disjoint-Sparse-Table\n\
    \ * @docs docs/disjoint-sparse-table.md\n */\ntemplate< typename Semigroup, typename\
    \ F >\nstruct DisjointSparseTable {\n  const F f;\n  vector< vector< Semigroup\
    \ > > st;\n  vector< int > lookup;\n\n  DisjointSparseTable(const vector< Semigroup\
    \ > &v, const F &f) : f(f) {\n    int b = 0;\n    while((1 << b) <= v.size())\
    \ ++b;\n    st.resize(b, vector< Semigroup >(v.size(), Semigroup()));\n    for(int\
    \ i = 0; i < v.size(); i++) st[0][i] = v[i];\n    for(int i = 1; i < b; i++) {\n\
    \      int shift = 1 << i;\n      for(int j = 0; j < v.size(); j += shift << 1)\
    \ {\n        int t = min(j + shift, (int) v.size());\n        st[i][t - 1] = v[t\
    \ - 1];\n        for(int k = t - 2; k >= j; k--) st[i][k] = f(v[k], st[i][k +\
    \ 1]);\n        if(v.size() <= t) break;\n        st[i][t] = v[t];\n        int\
    \ r = min(t + shift, (int) v.size());\n        for(int k = t + 1; k < r; k++)\
    \ st[i][k] = f(st[i][k - 1], v[k]);\n      }\n    }\n    lookup.resize(1 << b);\n\
    \    for(int i = 2; i < lookup.size(); i++) {\n      lookup[i] = lookup[i >> 1]\
    \ + 1;\n    }\n  }\n\n  Semigroup fold(int l, int r) {\n    if(l >= --r) return\
    \ st[0][l];\n    int p = lookup[l ^ r];\n    return f(st[p][l], st[p][r]);\n \
    \ }\n};\n\ntemplate< typename SemiGroup, typename F >\nDisjointSparseTable< SemiGroup,\
    \ F > get_disjoint_sparse_table(const vector< SemiGroup >& v, const F& f) {\n\
    \  return {v, f};\n}\n#line 6 \"test/verify/yosupo-staticrmq-2.test.cpp\"\n\n\
    int main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  cin >> A;\n\
    \  auto f = [](int a, int b) { return min(a, b); };\n  auto st = get_disjoint_sparse_table(A,\
    \ f);\n  while(Q--) {\n    int l, r;\n    cin >> l >> r;\n    cout << st.fold(l,\
    \ r) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../structure/others/disjoint-sparse-table.hpp\"\
    \n\nint main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > A(N);\n  cin\
    \ >> A;\n  auto f = [](int a, int b) { return min(a, b); };\n  auto st = get_disjoint_sparse_table(A,\
    \ f);\n  while(Q--) {\n    int l, r;\n    cin >> l >> r;\n    cout << st.fold(l,\
    \ r) << \"\\n\";\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/disjoint-sparse-table.hpp
  isVerificationFile: true
  path: test/verify/yosupo-staticrmq-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-staticrmq-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-staticrmq-2.test.cpp
- /verify/test/verify/yosupo-staticrmq-2.test.cpp.html
title: test/verify/yosupo-staticrmq-2.test.cpp
---
