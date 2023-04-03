---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/matrix_det
    links:
    - https://judge.yosupo.jp/problem/matrix_det
  bundledCode: "#line 1 \"test/verify/yosupo-matrix-det.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/matrix_det\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-matrix-det.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-int.hpp\"\ntemplate< int mod >\nstruct ModInt\
    \ {\n  int x;\n\n  ModInt() : x(0) {}\n\n  ModInt(int64_t y) : x(y >= 0 ? y %\
    \ mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt &operator+=(const ModInt &p)\
    \ {\n    if((x += p.x) >= mod) x -= mod;\n    return *this;\n  }\n\n  ModInt &operator-=(const\
    \ ModInt &p) {\n    if((x += mod - p.x) >= mod) x -= mod;\n    return *this;\n\
    \  }\n\n  ModInt &operator*=(const ModInt &p) {\n    x = (int) (1LL * x * p.x\
    \ % mod);\n    return *this;\n  }\n\n  ModInt &operator/=(const ModInt &p) {\n\
    \    *this *= p.inverse();\n    return *this;\n  }\n\n  ModInt operator-() const\
    \ { return ModInt(-x); }\n\n  ModInt operator+(const ModInt &p) const { return\
    \ ModInt(*this) += p; }\n\n  ModInt operator-(const ModInt &p) const { return\
    \ ModInt(*this) -= p; }\n\n  ModInt operator*(const ModInt &p) const { return\
    \ ModInt(*this) *= p; }\n\n  ModInt operator/(const ModInt &p) const { return\
    \ ModInt(*this) /= p; }\n\n  bool operator==(const ModInt &p) const { return x\
    \ == p.x; }\n\n  bool operator!=(const ModInt &p) const { return x != p.x; }\n\
    \n  ModInt inverse() const {\n    int a = x, b = mod, u = 1, v = 0, t;\n    while(b\
    \ > 0) {\n      t = a / b;\n      swap(a -= t * b, b);\n      swap(u -= t * v,\
    \ v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt pow(int64_t n) const {\n\
    \    ModInt ret(1), mul(x);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream\
    \ &operator<<(ostream &os, const ModInt &p) {\n    return os << p.x;\n  }\n\n\
    \  friend istream &operator>>(istream &is, ModInt &a) {\n    int64_t t;\n    is\
    \ >> t;\n    a = ModInt< mod >(t);\n    return (is);\n  }\n\n  static int get_mod()\
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/yosupo-matrix-det.test.cpp\"\
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
    \  }\n};\n#line 8 \"test/verify/yosupo-matrix-det.test.cpp\"\n\nconst int MOD\
    \ = 998244353;\nusing mint = ModInt< MOD >;\n\nint main() {\n  int N;\n  cin >>\
    \ N;\n  Matrix< mint > mat(N);\n  for(int i = 0; i < N; i++) cin >> mat[i];\n\
    \  cout << mat.determinant() << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../math/matrix/matrix.hpp\"\n\nconst int MOD = 998244353;\n\
    using mint = ModInt< MOD >;\n\nint main() {\n  int N;\n  cin >> N;\n  Matrix<\
    \ mint > mat(N);\n  for(int i = 0; i < N; i++) cin >> mat[i];\n  cout << mat.determinant()\
    \ << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - math/matrix/matrix.hpp
  isVerificationFile: true
  path: test/verify/yosupo-matrix-det.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-matrix-det.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-matrix-det.test.cpp
- /verify/test/verify/yosupo-matrix-det.test.cpp.html
title: test/verify/yosupo-matrix-det.test.cpp
---
