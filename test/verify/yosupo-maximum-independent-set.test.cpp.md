---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/others/maximum-independent-set.hpp
    title: "Maximum Independent Set(\u6700\u5927\u72EC\u7ACB\u96C6\u5408)"
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: math/matrix/matrix.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"test/verify/yosupo-maximum-independent-set.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n\n\
    #line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-maximum-independent-set.test.cpp\"\
    \n\n#line 1 \"math/matrix/matrix.hpp\"\ntemplate< class T >\nstruct Matrix {\n\
    \  vector< vector< T > > A;\n\n  Matrix() {}\n\n  Matrix(size_t n, size_t m) :\
    \ A(n, vector< T >(m, 0)) {}\n\n  Matrix(size_t n) : A(n, vector< T >(n, 0)) {};\n\
    \n  size_t size() const {\n     if(A.empty()) return 0;\n     assert(A.size()\
    \ == A[0].size());\n     return A.size();\n  }\n\n  size_t height() const {\n\
    \    return (A.size());\n  }\n\n  size_t width() const {\n    return (A[0].size());\n\
    \  }\n\n  inline const vector< T > &operator[](int k) const {\n    return (A.at(k));\n\
    \  }\n\n  inline vector< T > &operator[](int k) {\n    return (A.at(k));\n  }\n\
    \n  static Matrix I(size_t n) {\n    Matrix mat(n);\n    for(int i = 0; i < n;\
    \ i++) mat[i][i] = 1;\n    return (mat);\n  }\n\n  Matrix &operator+=(const Matrix\
    \ &B) {\n    size_t n = height(), m = width();\n    assert(n == B.height() &&\
    \ m == B.width());\n    for(int i = 0; i < n; i++)\n      for(int j = 0; j < m;\
    \ j++)\n        (*this)[i][j] += B[i][j];\n    return (*this);\n  }\n\n  Matrix\
    \ &operator-=(const Matrix &B) {\n    size_t n = height(), m = width();\n    assert(n\
    \ == B.height() && m == B.width());\n    for(int i = 0; i < n; i++)\n      for(int\
    \ j = 0; j < m; j++)\n        (*this)[i][j] -= B[i][j];\n    return (*this);\n\
    \  }\n\n  Matrix &operator*=(const Matrix &B) {\n    size_t n = height(), m =\
    \ B.width(), p = width();\n    assert(p == B.height());\n    vector< vector< T\
    \ > > C(n, vector< T >(m, 0));\n    for(int i = 0; i < n; i++)\n      for(int\
    \ j = 0; j < m; j++)\n        for(int k = 0; k < p; k++)\n          C[i][j] =\
    \ (C[i][j] + (*this)[i][k] * B[k][j]);\n    A.swap(C);\n    return (*this);\n\
    \  }\n\n  Matrix &operator^=(long long k) {\n    Matrix B = Matrix::I(height());\n\
    \    while(k > 0) {\n      if(k & 1) B *= *this;\n      *this *= *this;\n    \
    \  k >>= 1LL;\n    }\n    A.swap(B.A);\n    return (*this);\n  }\n\n  Matrix operator+(const\
    \ Matrix &B) const {\n    return (Matrix(*this) += B);\n  }\n\n  Matrix operator-(const\
    \ Matrix &B) const {\n    return (Matrix(*this) -= B);\n  }\n\n  Matrix operator*(const\
    \ Matrix &B) const {\n    return (Matrix(*this) *= B);\n  }\n\n  Matrix operator^(const\
    \ long long k) const {\n    return (Matrix(*this) ^= k);\n  }\n\n  friend ostream\
    \ &operator<<(ostream &os, Matrix &p) {\n    size_t n = p.height(), m = p.width();\n\
    \    for(int i = 0; i < n; i++) {\n      os << \"[\";\n      for(int j = 0; j\
    \ < m; j++) {\n        os << p[i][j] << (j + 1 == m ? \"]\\n\" : \",\");\n   \
    \   }\n    }\n    return (os);\n  }\n\n\n  T determinant() {\n    Matrix B(*this);\n\
    \    assert(width() == height());\n    T ret = 1;\n    for(int i = 0; i < width();\
    \ i++) {\n      int idx = -1;\n      for(int j = i; j < width(); j++) {\n    \
    \    if(B[j][i] != 0) idx = j;\n      }\n      if(idx == -1) return (0);\n   \
    \   if(i != idx) {\n        ret *= -1;\n        swap(B[i], B[idx]);\n      }\n\
    \      ret *= B[i][i];\n      T vv = B[i][i];\n      for(int j = 0; j < width();\
    \ j++) {\n        B[i][j] /= vv;\n      }\n      for(int j = i + 1; j < width();\
    \ j++) {\n        T a = B[j][i];\n        for(int k = 0; k < width(); k++) {\n\
    \          B[j][k] -= B[i][k] * a;\n        }\n      }\n    }\n    return (ret);\n\
    \  }\n};\n#line 1 \"graph/others/maximum-independent-set.hpp\"\n/**\n * @brief\
    \ Maximum Independent Set(\u6700\u5927\u72EC\u7ACB\u96C6\u5408)\n */\ntemplate<\
    \ typename Matrix >\nvector< int > maximum_independent_set(const Matrix &g, int\
    \ trial = 1000000) {\n  int N = (int) g.size();\n  vector< uint64_t > bit(N);\n\
    \  assert(N <= 64);\n  for(int i = 0; i < N; i++) {\n    for(int j = 0; j < N;\
    \ j++) {\n      if(i != j) {\n        assert(g[i][j] == g[j][i]);\n        if(g[i][j])\
    \ bit[i] |= uint64_t(1) << j;\n      }\n    }\n  }\n\n  vector< int > ord(N);\n\
    \  iota(begin(ord), end(ord), 0);\n  mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());\n\
    \  int ret = 0;\n  uint64_t ver = 0;\n  for(int i = 0; i < trial; i++) {\n   \
    \ shuffle(begin(ord), end(ord), mt);\n    uint64_t used = 0;\n    int add = 0;\n\
    \    for(int j : ord) {\n      if(used & bit[j]) continue;\n      used |= uint64_t(1)\
    \ << j;\n      ++add;\n    }\n    if(ret < add) {\n      ret = add;\n      ver\
    \ = used;\n    }\n  }\n  vector< int > ans;\n  for(int i = 0; i < N; i++) {\n\
    \    if((ver >> i) & 1) ans.emplace_back(i);\n  }\n  return ans;\n}\n#line 7 \"\
    test/verify/yosupo-maximum-independent-set.test.cpp\"\n\nint main() {\n  int N,\
    \ M;\n  cin >> N >> M;\n  Matrix< bool > mat(N);\n  for(int i = 0; i < M; i++)\
    \ {\n    int a, b;\n    cin >> a >> b;\n    mat[a][b] = true;\n    mat[b][a] =\
    \ true;\n  }\n  auto ret = maximum_independent_set(mat);\n  cout << ret.size()\
    \ << endl;\n  cout << ret << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/matrix/matrix.hpp\"\
    \n#include \"../../graph/others/maximum-independent-set.hpp\"\n\nint main() {\n\
    \  int N, M;\n  cin >> N >> M;\n  Matrix< bool > mat(N);\n  for(int i = 0; i <\
    \ M; i++) {\n    int a, b;\n    cin >> a >> b;\n    mat[a][b] = true;\n    mat[b][a]\
    \ = true;\n  }\n  auto ret = maximum_independent_set(mat);\n  cout << ret.size()\
    \ << endl;\n  cout << ret << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/matrix/matrix.hpp
  - graph/others/maximum-independent-set.hpp
  isVerificationFile: true
  path: test/verify/yosupo-maximum-independent-set.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-maximum-independent-set.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-maximum-independent-set.test.cpp
- /verify/test/verify/yosupo-maximum-independent-set.test.cpp.html
title: test/verify/yosupo-maximum-independent-set.test.cpp
---
