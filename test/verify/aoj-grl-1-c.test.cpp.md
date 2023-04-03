---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/shortest-path/warshall-floyd.hpp
    title: "Warshall Floyd(\u5168\u70B9\u5BFE\u9593\u6700\u77ED\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: math/matrix/square-matrix.hpp
    title: "Square-Matrix(\u6B63\u65B9\u884C\u5217)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
  bundledCode: "#line 1 \"test/verify/aoj-grl-1-c.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-1-c.test.cpp\"\
    \n\n#line 1 \"math/matrix/square-matrix.hpp\"\n/**\n * @brief Square-Matrix(\u6B63\
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
    \   }\n    }\n    return os;\n  }\n};\n#line 1 \"graph/shortest-path/warshall-floyd.hpp\"\
    \n/**\n * @brief Warshall Floyd(\u5168\u70B9\u5BFE\u9593\u6700\u77ED\u8DEF)\n\
    \ */\ntemplate< typename Matrix, typename T >\nvoid warshall_floyd(Matrix &g,\
    \ T INF) {\n  for(size_t k = 0; k < g.size(); k++) {\n    for(size_t i = 0; i\
    \ < g.size(); i++) {\n      for(size_t j = 0; j < g.size(); j++) {\n        if(g[i][k]\
    \ == INF || g[k][j] == INF) continue;\n        g[i][j] = min(g[i][j], g[i][k]\
    \ + g[k][j]);\n      }\n    }\n  }\n}\n#line 7 \"test/verify/aoj-grl-1-c.test.cpp\"\
    \n\nint main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  SquareMatrix< int,\
    \ 100 > mat;\n  for(int i = 0; i < 100; i++) {\n    for(int j = 0; j < 100; j++)\
    \ {\n      if(i != j) mat[i][j] = INT_MAX;\n    }\n  }\n  for(int i = 0; i < E;\
    \ i++) {\n    int x, y, z;\n    scanf(\"%d %d %d\", &x, &y, &z);\n    mat[x][y]\
    \ = z;\n  }\n  warshall_floyd(mat, INT_MAX);\n  for(int i = 0; i < V; i++) {\n\
    \    if(mat[i][i] < 0) {\n      puts(\"NEGATIVE CYCLE\");\n      return 0;\n \
    \   }\n  }\n  for(int i = 0; i < V; i++) {\n    for(int j = 0; j < V; j++) {\n\
    \      if(j > 0) putchar(' ');\n      if(mat[i][j] == INT_MAX) printf(\"INF\"\
    );\n      else printf(\"%d\", mat[i][j]);\n    }\n    putchar('\\n');\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/matrix/square-matrix.hpp\"\
    \n#include \"../../graph/shortest-path/warshall-floyd.hpp\"\n\nint main() {\n\
    \  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  SquareMatrix< int, 100 > mat;\n \
    \ for(int i = 0; i < 100; i++) {\n    for(int j = 0; j < 100; j++) {\n      if(i\
    \ != j) mat[i][j] = INT_MAX;\n    }\n  }\n  for(int i = 0; i < E; i++) {\n   \
    \ int x, y, z;\n    scanf(\"%d %d %d\", &x, &y, &z);\n    mat[x][y] = z;\n  }\n\
    \  warshall_floyd(mat, INT_MAX);\n  for(int i = 0; i < V; i++) {\n    if(mat[i][i]\
    \ < 0) {\n      puts(\"NEGATIVE CYCLE\");\n      return 0;\n    }\n  }\n  for(int\
    \ i = 0; i < V; i++) {\n    for(int j = 0; j < V; j++) {\n      if(j > 0) putchar('\
    \ ');\n      if(mat[i][j] == INT_MAX) printf(\"INF\");\n      else printf(\"%d\"\
    , mat[i][j]);\n    }\n    putchar('\\n');\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/matrix/square-matrix.hpp
  - graph/shortest-path/warshall-floyd.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-1-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-1-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-1-c.test.cpp
- /verify/test/verify/aoj-grl-1-c.test.cpp.html
title: test/verify/aoj-grl-1-c.test.cpp
---
