---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-sparse-matrix-det.test.cpp
    title: test/verify/yosupo-sparse-matrix-det.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fps/sparse-matrix.hpp\"\ntemplate< typename T >\nusing\
    \ FPSGraph = vector< vector< pair< int, T > > >;\n\ntemplate< typename T >\nFormalPowerSeries<\
    \ T > random_poly(int n) {\n  mt19937 mt(1333333);\n  FormalPowerSeries< T > res(n);\n\
    \  uniform_int_distribution< int > rand(0, T::get_mod() - 1);\n  for(int i = 0;\
    \ i < n; i++) res[i] = rand(mt);\n  return res;\n}\n\ntemplate< typename T >\n\
    FormalPowerSeries< T > next_poly(const FormalPowerSeries< T > &dp, const FPSGraph<\
    \ T > &g) {\n  const int N = (int) dp.size();\n  FormalPowerSeries< T > nxt(N);\n\
    \  for(int i = 0; i < N; i++) {\n    for(auto &p : g[i]) nxt[p.first] += p.second\
    \ * dp[i];\n  }\n  return nxt;\n}\n\ntemplate< typename T >\nFormalPowerSeries<\
    \ T > minimum_poly(const FPSGraph< T > &g) {\n  const int N = (int) g.size();\n\
    \  auto dp = random_poly< T >(N), u = random_poly< T >(N);\n  FormalPowerSeries<\
    \ T > f(2 * N);\n  for(int i = 0; i < 2 * N; i++) {\n    for(auto &p : u.dot(dp))\
    \ f[i] += p;\n    dp = next_poly(dp, g);\n  }\n  return berlekamp_massey(f);\n\
    }\n\n/* O(N(N+S) + N log N log Q) (O(S): time complexity of nex) */\ntemplate<\
    \ typename T >\nFormalPowerSeries< T > sparse_pow(int64_t Q, FormalPowerSeries<\
    \ T > dp, const FPSGraph< T > &g) {\n  const int N = (int) dp.size();\n  auto\
    \ A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly(g));\n  FormalPowerSeries<\
    \ T > res(N);\n  for(int i = 0; i < A.size(); i++) {\n    res += dp * A[i];\n\
    \    dp = next_poly(dp, g);\n  }\n  return res;\n}\n\n/* O(N(N+S)) (S: none-zero\
    \ elements)*/\ntemplate< typename T >\nT sparse_determinant(FPSGraph< T > g) {\n\
    \  using FPS = FormalPowerSeries< T >;\n  int N = (int) g.size();\n  auto C =\
    \ random_poly< T >(N);\n  for(int i = 0; i < N; i++) for(auto &p : g[i]) p.second\
    \ *= C[i];\n  auto u = minimum_poly(g);\n  T acdet = u[0];\n  if(N % 2 == 0) acdet\
    \ *= -1;\n  T cdet = 1;\n  for(int i = 0; i < N; i++) cdet *= C[i];\n  return\
    \ acdet / cdet;\n}\n"
  code: "template< typename T >\nusing FPSGraph = vector< vector< pair< int, T > >\
    \ >;\n\ntemplate< typename T >\nFormalPowerSeries< T > random_poly(int n) {\n\
    \  mt19937 mt(1333333);\n  FormalPowerSeries< T > res(n);\n  uniform_int_distribution<\
    \ int > rand(0, T::get_mod() - 1);\n  for(int i = 0; i < n; i++) res[i] = rand(mt);\n\
    \  return res;\n}\n\ntemplate< typename T >\nFormalPowerSeries< T > next_poly(const\
    \ FormalPowerSeries< T > &dp, const FPSGraph< T > &g) {\n  const int N = (int)\
    \ dp.size();\n  FormalPowerSeries< T > nxt(N);\n  for(int i = 0; i < N; i++) {\n\
    \    for(auto &p : g[i]) nxt[p.first] += p.second * dp[i];\n  }\n  return nxt;\n\
    }\n\ntemplate< typename T >\nFormalPowerSeries< T > minimum_poly(const FPSGraph<\
    \ T > &g) {\n  const int N = (int) g.size();\n  auto dp = random_poly< T >(N),\
    \ u = random_poly< T >(N);\n  FormalPowerSeries< T > f(2 * N);\n  for(int i =\
    \ 0; i < 2 * N; i++) {\n    for(auto &p : u.dot(dp)) f[i] += p;\n    dp = next_poly(dp,\
    \ g);\n  }\n  return berlekamp_massey(f);\n}\n\n/* O(N(N+S) + N log N log Q) (O(S):\
    \ time complexity of nex) */\ntemplate< typename T >\nFormalPowerSeries< T > sparse_pow(int64_t\
    \ Q, FormalPowerSeries< T > dp, const FPSGraph< T > &g) {\n  const int N = (int)\
    \ dp.size();\n  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly(g));\n\
    \  FormalPowerSeries< T > res(N);\n  for(int i = 0; i < A.size(); i++) {\n   \
    \ res += dp * A[i];\n    dp = next_poly(dp, g);\n  }\n  return res;\n}\n\n/* O(N(N+S))\
    \ (S: none-zero elements)*/\ntemplate< typename T >\nT sparse_determinant(FPSGraph<\
    \ T > g) {\n  using FPS = FormalPowerSeries< T >;\n  int N = (int) g.size();\n\
    \  auto C = random_poly< T >(N);\n  for(int i = 0; i < N; i++) for(auto &p : g[i])\
    \ p.second *= C[i];\n  auto u = minimum_poly(g);\n  T acdet = u[0];\n  if(N %\
    \ 2 == 0) acdet *= -1;\n  T cdet = 1;\n  for(int i = 0; i < N; i++) cdet *= C[i];\n\
    \  return acdet / cdet;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/sparse-matrix.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-sparse-matrix-det.test.cpp
documentation_of: math/fps/sparse-matrix.hpp
layout: document
redirect_from:
- /library/math/fps/sparse-matrix.hpp
- /library/math/fps/sparse-matrix.hpp.html
title: math/fps/sparse-matrix.hpp
---
