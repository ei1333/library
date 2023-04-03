---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1254.test.cpp
    title: test/verify/aoj-1254.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2306.test.cpp
    title: test/verify/aoj-2306.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-1-c.test.cpp
    title: test/verify/aoj-grl-1-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-chromatic-number.test.cpp
    title: test/verify/yosupo-chromatic-number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-650.test.cpp
    title: test/verify/yukicoder-650.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Square-Matrix(\u6B63\u65B9\u884C\u5217)"
    links: []
  bundledCode: "#line 1 \"math/matrix/square-matrix.hpp\"\n/**\n * @brief Square-Matrix(\u6B63\
    \u65B9\u884C\u5217)\n */\ntemplate< class T, size_t N >\nstruct SquareMatrix {\n\
    \  array< array< T, N >, N > A;\n\n  SquareMatrix() : A{{}} {}\n\n  size_t size()\
    \ const { return N; }\n\n  inline const array< T, N > &operator[](int k) const\
    \ {\n    return (A.at(k));\n  }\n\n  inline array< T, N > &operator[](int k) {\n\
    \    return (A.at(k));\n  }\n\n  static SquareMatrix add_identity() {\n    return\
    \ SquareMatrix();\n  }\n\n  static SquareMatrix mul_identity() {\n    SquareMatrix\
    \ mat;\n    for(size_t i = 0; i < N; i++) mat[i][i] = 1;\n    return mat;\n  }\n\
    \n  SquareMatrix &operator+=(const SquareMatrix &B) {\n    for(size_t i = 0; i\
    \ < N; i++) {\n      for(size_t j = 0; j < N; j++) {\n        (*this)[i][j] +=\
    \ B[i][j];\n      }\n    }\n    return *this;\n  }\n\n  SquareMatrix &operator-=(const\
    \ SquareMatrix &B) {\n    for(size_t i = 0; i < N; i++) {\n      for(size_t j\
    \ = 0; j < N; j++) {\n        (*this)[i][j] -= B[i][j];\n      }\n    }\n    return\
    \ *this;\n  }\n\n  SquareMatrix &operator*=(const SquareMatrix &B) {\n    array<\
    \ array< T, N >, N > C;\n    for(size_t i = 0; i < N; i++) {\n      for(size_t\
    \ j = 0; j < N; j++) {\n        for(size_t k = 0; k < N; k++) {\n          C[i][j]\
    \ = (C[i][j] + (*this)[i][k] * B[k][j]);\n        }\n      }\n    }\n    A.swap(C);\n\
    \    return (*this);\n  }\n\n  SquareMatrix &operator^=(uint64_t k) {\n    SquareMatrix\
    \ B = SquareMatrix::mul_identity();\n    while(k > 0) {\n      if(k & 1) B *=\
    \ *this;\n      *this *= *this;\n      k >>= 1LL;\n    }\n    A.swap(B.A);\n \
    \   return *this;\n  }\n\n  SquareMatrix operator+(const SquareMatrix &B) const\
    \ {\n    return SquareMatrix(*this) += B;\n  }\n\n  SquareMatrix operator-(const\
    \ SquareMatrix &B) const {\n    return SquareMatrix(*this) -= B;\n  }\n\n  SquareMatrix\
    \ operator*(const SquareMatrix &B) const {\n    return SquareMatrix(*this) *=\
    \ B;\n  }\n\n  SquareMatrix operator^(uint64_t k) const {\n    return SquareMatrix(*this)\
    \ ^= k;\n  }\n\n  friend ostream &operator<<(ostream &os, SquareMatrix &p) {\n\
    \    for(int i = 0; i < N; i++) {\n      os << \"[\";\n      for(int j = 0; j\
    \ < N; j++) {\n        os << p[i][j] << (j + 1 == N ? \"]\\n\" : \",\");\n   \
    \   }\n    }\n    return os;\n  }\n};\n"
  code: "/**\n * @brief Square-Matrix(\u6B63\u65B9\u884C\u5217)\n */\ntemplate< class\
    \ T, size_t N >\nstruct SquareMatrix {\n  array< array< T, N >, N > A;\n\n  SquareMatrix()\
    \ : A{{}} {}\n\n  size_t size() const { return N; }\n\n  inline const array< T,\
    \ N > &operator[](int k) const {\n    return (A.at(k));\n  }\n\n  inline array<\
    \ T, N > &operator[](int k) {\n    return (A.at(k));\n  }\n\n  static SquareMatrix\
    \ add_identity() {\n    return SquareMatrix();\n  }\n\n  static SquareMatrix mul_identity()\
    \ {\n    SquareMatrix mat;\n    for(size_t i = 0; i < N; i++) mat[i][i] = 1;\n\
    \    return mat;\n  }\n\n  SquareMatrix &operator+=(const SquareMatrix &B) {\n\
    \    for(size_t i = 0; i < N; i++) {\n      for(size_t j = 0; j < N; j++) {\n\
    \        (*this)[i][j] += B[i][j];\n      }\n    }\n    return *this;\n  }\n\n\
    \  SquareMatrix &operator-=(const SquareMatrix &B) {\n    for(size_t i = 0; i\
    \ < N; i++) {\n      for(size_t j = 0; j < N; j++) {\n        (*this)[i][j] -=\
    \ B[i][j];\n      }\n    }\n    return *this;\n  }\n\n  SquareMatrix &operator*=(const\
    \ SquareMatrix &B) {\n    array< array< T, N >, N > C;\n    for(size_t i = 0;\
    \ i < N; i++) {\n      for(size_t j = 0; j < N; j++) {\n        for(size_t k =\
    \ 0; k < N; k++) {\n          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);\n\
    \        }\n      }\n    }\n    A.swap(C);\n    return (*this);\n  }\n\n  SquareMatrix\
    \ &operator^=(uint64_t k) {\n    SquareMatrix B = SquareMatrix::mul_identity();\n\
    \    while(k > 0) {\n      if(k & 1) B *= *this;\n      *this *= *this;\n    \
    \  k >>= 1LL;\n    }\n    A.swap(B.A);\n    return *this;\n  }\n\n  SquareMatrix\
    \ operator+(const SquareMatrix &B) const {\n    return SquareMatrix(*this) +=\
    \ B;\n  }\n\n  SquareMatrix operator-(const SquareMatrix &B) const {\n    return\
    \ SquareMatrix(*this) -= B;\n  }\n\n  SquareMatrix operator*(const SquareMatrix\
    \ &B) const {\n    return SquareMatrix(*this) *= B;\n  }\n\n  SquareMatrix operator^(uint64_t\
    \ k) const {\n    return SquareMatrix(*this) ^= k;\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, SquareMatrix &p) {\n    for(int i = 0; i < N; i++) {\n      os << \"[\"\
    ;\n      for(int j = 0; j < N; j++) {\n        os << p[i][j] << (j + 1 == N ?\
    \ \"]\\n\" : \",\");\n      }\n    }\n    return os;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/square-matrix.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-2306.test.cpp
  - test/verify/aoj-1254.test.cpp
  - test/verify/yukicoder-650.test.cpp
  - test/verify/aoj-grl-1-c.test.cpp
  - test/verify/yosupo-chromatic-number.test.cpp
documentation_of: math/matrix/square-matrix.hpp
layout: document
redirect_from:
- /library/math/matrix/square-matrix.hpp
- /library/math/matrix/square-matrix.hpp.html
title: "Square-Matrix(\u6B63\u65B9\u884C\u5217)"
---
