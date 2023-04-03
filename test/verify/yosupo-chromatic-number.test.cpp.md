---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/others/chromatic-number.hpp
    title: "Chromatic Number(\u5F69\u8272\u6570)"
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
    PROBLEM: https://judge.yosupo.jp/problem/chromatic_number
    links:
    - https://judge.yosupo.jp/problem/chromatic_number
  bundledCode: "#line 1 \"test/verify/yosupo-chromatic-number.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/chromatic_number\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-chromatic-number.test.cpp\"\
    \n\n#line 2 \"graph/others/chromatic-number.hpp\"\n\n/**\n * @brief Chromatic\
    \ Number(\u5F69\u8272\u6570)\n * @docs docs/chromatic-number.md\n * @see https://www.slideshare.net/wata_orz/ss-12131479\n\
    \ */\ntemplate< typename Matrix >\nint chromatic_number(Matrix &g) {\n  int N\
    \ = (int) g.size();\n  vector< int > es(N);\n  for(int i = 0; i < (int) g.size();\
    \ i++) {\n    for(int j = 0; j < (int) g.size(); j++) {\n      if(g[i][j] != 0)\
    \ es[i] |= 1 << j;\n    }\n  }\n  vector< int > ind(1 << N);\n  ind[0] = 1;\n\
    \  for(int S = 1; S < (1 << N); S++) {\n    int u = __builtin_ctz(S);\n    ind[S]\
    \ = ind[S ^ (1 << u)] + ind[(S ^ (1 << u)) & ~es[u]];\n  }\n  vector< int > cnt((1\
    \ << N) + 1);\n  for(int i = 0; i < (1 << N); i++) {\n    cnt[ind[i]] += __builtin_parity(i)\
    \ ? -1 : 1;\n  }\n  vector< pair< unsigned, int > > hist;\n  for(int i = 1; i\
    \ <= (1 << N); i++) {\n    if(cnt[i]) hist.emplace_back(i, cnt[i]);\n  }\n  constexpr\
    \ int mods[] = {1000000007, 1000000011, 1000000021};\n  int ret = N;\n  for(int\
    \ k = 0; k < 3; k++) {\n    auto buf = hist;\n    for(int c = 1; c < ret; c++)\
    \ {\n      int64_t sum = 0;\n      for(auto&[i, x] : buf) {\n        sum += (x\
    \ = int64_t(x) * i % mods[k]);\n      }\n      if(sum % mods[k]) ret = c;\n  \
    \  }\n  }\n  return ret;\n}\n#line 1 \"math/matrix/square-matrix.hpp\"\n/**\n\
    \ * @brief Square-Matrix(\u6B63\u65B9\u884C\u5217)\n */\ntemplate< class T, size_t\
    \ N >\nstruct SquareMatrix {\n  array< array< T, N >, N > A;\n\n  SquareMatrix()\
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
    \ \"]\\n\" : \",\");\n      }\n    }\n    return os;\n  }\n};\n#line 7 \"test/verify/yosupo-chromatic-number.test.cpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  SquareMatrix< bool, 20 > g;\n\
    \  for(int i = 0; i < M; i++) {\n    int u, v;\n    cin >> u >> v;\n    g[u][v]\
    \ = g[v][u] = true;\n  }\n  cout << chromatic_number(g) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/chromatic_number\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../graph/others/chromatic-number.hpp\"\
    \n#include \"../../math/matrix/square-matrix.hpp\"\n\nint main() {\n  int N, M;\n\
    \  cin >> N >> M;\n  SquareMatrix< bool, 20 > g;\n  for(int i = 0; i < M; i++)\
    \ {\n    int u, v;\n    cin >> u >> v;\n    g[u][v] = g[v][u] = true;\n  }\n \
    \ cout << chromatic_number(g) << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/others/chromatic-number.hpp
  - math/matrix/square-matrix.hpp
  isVerificationFile: true
  path: test/verify/yosupo-chromatic-number.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-chromatic-number.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-chromatic-number.test.cpp
- /verify/test/verify/yosupo-chromatic-number.test.cpp.html
title: test/verify/yosupo-chromatic-number.test.cpp
---
