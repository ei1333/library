---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/flow/hungarian.hpp
    title: "Hungarian(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5C0F\u91CD\u307F\
      \u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1163.test.cpp
    title: test/verify/aoj-1163.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-assignment.test.cpp
    title: test/verify/yosupo-assignment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-matrix-det.test.cpp
    title: test/verify/yosupo-matrix-det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-maximum-independent-set.test.cpp
    title: test/verify/yosupo-maximum-independent-set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/matrix.hpp\"\ntemplate< class T >\nstruct Matrix\
    \ {\n  vector< vector< T > > A;\n\n  Matrix() {}\n\n  Matrix(size_t n, size_t\
    \ m) : A(n, vector< T >(m, 0)) {}\n\n  Matrix(size_t n) : A(n, vector< T >(n,\
    \ 0)) {};\n\n  size_t size() const {\n     if(A.empty()) return 0;\n     assert(A.size()\
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
    \  }\n};\n"
  code: "template< class T >\nstruct Matrix {\n  vector< vector< T > > A;\n\n  Matrix()\
    \ {}\n\n  Matrix(size_t n, size_t m) : A(n, vector< T >(m, 0)) {}\n\n  Matrix(size_t\
    \ n) : A(n, vector< T >(n, 0)) {};\n\n  size_t size() const {\n     if(A.empty())\
    \ return 0;\n     assert(A.size() == A[0].size());\n     return A.size();\n  }\n\
    \n  size_t height() const {\n    return (A.size());\n  }\n\n  size_t width() const\
    \ {\n    return (A[0].size());\n  }\n\n  inline const vector< T > &operator[](int\
    \ k) const {\n    return (A.at(k));\n  }\n\n  inline vector< T > &operator[](int\
    \ k) {\n    return (A.at(k));\n  }\n\n  static Matrix I(size_t n) {\n    Matrix\
    \ mat(n);\n    for(int i = 0; i < n; i++) mat[i][i] = 1;\n    return (mat);\n\
    \  }\n\n  Matrix &operator+=(const Matrix &B) {\n    size_t n = height(), m =\
    \ width();\n    assert(n == B.height() && m == B.width());\n    for(int i = 0;\
    \ i < n; i++)\n      for(int j = 0; j < m; j++)\n        (*this)[i][j] += B[i][j];\n\
    \    return (*this);\n  }\n\n  Matrix &operator-=(const Matrix &B) {\n    size_t\
    \ n = height(), m = width();\n    assert(n == B.height() && m == B.width());\n\
    \    for(int i = 0; i < n; i++)\n      for(int j = 0; j < m; j++)\n        (*this)[i][j]\
    \ -= B[i][j];\n    return (*this);\n  }\n\n  Matrix &operator*=(const Matrix &B)\
    \ {\n    size_t n = height(), m = B.width(), p = width();\n    assert(p == B.height());\n\
    \    vector< vector< T > > C(n, vector< T >(m, 0));\n    for(int i = 0; i < n;\
    \ i++)\n      for(int j = 0; j < m; j++)\n        for(int k = 0; k < p; k++)\n\
    \          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);\n    A.swap(C);\n  \
    \  return (*this);\n  }\n\n  Matrix &operator^=(long long k) {\n    Matrix B =\
    \ Matrix::I(height());\n    while(k > 0) {\n      if(k & 1) B *= *this;\n    \
    \  *this *= *this;\n      k >>= 1LL;\n    }\n    A.swap(B.A);\n    return (*this);\n\
    \  }\n\n  Matrix operator+(const Matrix &B) const {\n    return (Matrix(*this)\
    \ += B);\n  }\n\n  Matrix operator-(const Matrix &B) const {\n    return (Matrix(*this)\
    \ -= B);\n  }\n\n  Matrix operator*(const Matrix &B) const {\n    return (Matrix(*this)\
    \ *= B);\n  }\n\n  Matrix operator^(const long long k) const {\n    return (Matrix(*this)\
    \ ^= k);\n  }\n\n  friend ostream &operator<<(ostream &os, Matrix &p) {\n    size_t\
    \ n = p.height(), m = p.width();\n    for(int i = 0; i < n; i++) {\n      os <<\
    \ \"[\";\n      for(int j = 0; j < m; j++) {\n        os << p[i][j] << (j + 1\
    \ == m ? \"]\\n\" : \",\");\n      }\n    }\n    return (os);\n  }\n\n\n  T determinant()\
    \ {\n    Matrix B(*this);\n    assert(width() == height());\n    T ret = 1;\n\
    \    for(int i = 0; i < width(); i++) {\n      int idx = -1;\n      for(int j\
    \ = i; j < width(); j++) {\n        if(B[j][i] != 0) idx = j;\n      }\n     \
    \ if(idx == -1) return (0);\n      if(i != idx) {\n        ret *= -1;\n      \
    \  swap(B[i], B[idx]);\n      }\n      ret *= B[i][i];\n      T vv = B[i][i];\n\
    \      for(int j = 0; j < width(); j++) {\n        B[i][j] /= vv;\n      }\n \
    \     for(int j = i + 1; j < width(); j++) {\n        T a = B[j][i];\n       \
    \ for(int k = 0; k < width(); k++) {\n          B[j][k] -= B[i][k] * a;\n    \
    \    }\n      }\n    }\n    return (ret);\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix.hpp
  requiredBy:
  - graph/flow/hungarian.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-1163.test.cpp
  - test/verify/yosupo-matrix-det.test.cpp
  - test/verify/yosupo-assignment.test.cpp
  - test/verify/yosupo-maximum-independent-set.test.cpp
documentation_of: math/matrix/matrix.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix.hpp
- /library/math/matrix/matrix.hpp.html
title: math/matrix/matrix.hpp
---
