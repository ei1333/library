---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-subset-convolution.test.cpp
    title: test/verify/yosupo-subset-convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Subset Convolution
    links: []
  bundledCode: "#line 1 \"math/fft/subset-convolution.hpp\"\n/**\n * @brief Subset\
    \ Convolution\n*/\ntemplate< typename Mint, int _s >\nstruct SubsetConvolution\
    \ {\n  using fps = array< Mint, _s + 1 >;\n  static array< int, (1 << _s) > pop_count;\n\
    \  static constexpr int s = _s;\n\n  SubsetConvolution() = default;\n\n  static\
    \ void init() {\n    if(pop_count.back() == 0) {\n      pop_count[0] = 0;\n  \
    \    for(int i = 1; i < (1 << s); i++) {\n        pop_count[i] = pop_count[i -\
    \ (i & -i)] + 1;\n      }\n    }\n  }\n\n  static inline void add(fps &f, const\
    \ fps &g, int d) {\n    for(int i = 0; i < d; i++) {\n      f[i] += g[i];\n  \
    \  }\n  }\n\n  static inline void sub(fps &f, const fps &g, int d) {\n    for(int\
    \ i = d; i <= s; i++) {\n      f[i] -= g[i];\n    }\n  }\n\n  static void zeta_transform(vector<\
    \ fps > &F) {\n    const int n = (int) F.size();\n    assert((n & (n - 1)) ==\
    \ 0);\n    init();\n    for(int i = 1; i < n; i <<= 1) {\n      for(int j = 0;\
    \ j < n; j += i << 1) {\n        for(int k = 0; k < i; k++) {\n          add(F[j\
    \ + k + i], F[j + k], pop_count[j + k + i]);\n        }\n      }\n    }\n  }\n\
    \n  static void moebius_transform(vector< fps > &F) {\n    const int n = (int)\
    \ F.size();\n    assert((n & (n - 1)) == 0);\n    init();\n    for(int i = 1;\
    \ i < n; i <<= 1) {\n      for(int j = 0; j < n; j += i << 1) {\n        for(int\
    \ k = 0; k < i; k++) {\n          sub(F[j + k + i], F[j + k], pop_count[j + k\
    \ + i]);\n        }\n      }\n    }\n  }\n\n  static vector< fps > lift(const\
    \ vector< Mint > &f) {\n    const int n = (int) f.size();\n    init();\n    vector<\
    \ fps > F(n);\n    for(int i = 0; i < n; i++) {\n      fill(begin(F[i]), end(F[i]),\
    \ Mint());\n      F[i][pop_count[i]] = f[i];\n    }\n    return F;\n  }\n\n  static\
    \ vector< Mint > unlift(const vector< fps > &F) {\n    const int n = (int) F.size();\n\
    \    init();\n    vector< Mint > f(n);\n    for(int i = 0; i < (int) F.size();\
    \ i++) {\n      f[i] = F[i][pop_count[i]];\n    }\n    return f;\n  }\n\n  static\
    \ void prod(vector< fps > &F, const vector< fps > &G) {\n    int n = (int) F.size();\n\
    \    int d = __builtin_ctz(n);\n    for(int i = 0; i < n; i++) {\n      fps h{};\n\
    \      for(int j = 0; j <= d; j++) {\n        for(int k = 0; k <= d - j; k++)\
    \ {\n          h[j + k] += F[i][j] * G[i][k];\n        }\n      }\n      F[i]\
    \ = move(h);\n    }\n  }\n\n  static vector< Mint > multiply(const vector< Mint\
    \ > &f, const vector< Mint > &g) {\n    auto F = lift(f), G = lift(g);\n    zeta_transform(F);\n\
    \    zeta_transform(G);\n    prod(F, G);\n    moebius_transform(F);\n    return\
    \ unlift(F);\n  }\n};\n\ntemplate< typename Mint, int s >\narray< int, (1 << s)\
    \ > SubsetConvolution< Mint, s >::pop_count;\n"
  code: "/**\n * @brief Subset Convolution\n*/\ntemplate< typename Mint, int _s >\n\
    struct SubsetConvolution {\n  using fps = array< Mint, _s + 1 >;\n  static array<\
    \ int, (1 << _s) > pop_count;\n  static constexpr int s = _s;\n\n  SubsetConvolution()\
    \ = default;\n\n  static void init() {\n    if(pop_count.back() == 0) {\n    \
    \  pop_count[0] = 0;\n      for(int i = 1; i < (1 << s); i++) {\n        pop_count[i]\
    \ = pop_count[i - (i & -i)] + 1;\n      }\n    }\n  }\n\n  static inline void\
    \ add(fps &f, const fps &g, int d) {\n    for(int i = 0; i < d; i++) {\n     \
    \ f[i] += g[i];\n    }\n  }\n\n  static inline void sub(fps &f, const fps &g,\
    \ int d) {\n    for(int i = d; i <= s; i++) {\n      f[i] -= g[i];\n    }\n  }\n\
    \n  static void zeta_transform(vector< fps > &F) {\n    const int n = (int) F.size();\n\
    \    assert((n & (n - 1)) == 0);\n    init();\n    for(int i = 1; i < n; i <<=\
    \ 1) {\n      for(int j = 0; j < n; j += i << 1) {\n        for(int k = 0; k <\
    \ i; k++) {\n          add(F[j + k + i], F[j + k], pop_count[j + k + i]);\n  \
    \      }\n      }\n    }\n  }\n\n  static void moebius_transform(vector< fps >\
    \ &F) {\n    const int n = (int) F.size();\n    assert((n & (n - 1)) == 0);\n\
    \    init();\n    for(int i = 1; i < n; i <<= 1) {\n      for(int j = 0; j < n;\
    \ j += i << 1) {\n        for(int k = 0; k < i; k++) {\n          sub(F[j + k\
    \ + i], F[j + k], pop_count[j + k + i]);\n        }\n      }\n    }\n  }\n\n \
    \ static vector< fps > lift(const vector< Mint > &f) {\n    const int n = (int)\
    \ f.size();\n    init();\n    vector< fps > F(n);\n    for(int i = 0; i < n; i++)\
    \ {\n      fill(begin(F[i]), end(F[i]), Mint());\n      F[i][pop_count[i]] = f[i];\n\
    \    }\n    return F;\n  }\n\n  static vector< Mint > unlift(const vector< fps\
    \ > &F) {\n    const int n = (int) F.size();\n    init();\n    vector< Mint >\
    \ f(n);\n    for(int i = 0; i < (int) F.size(); i++) {\n      f[i] = F[i][pop_count[i]];\n\
    \    }\n    return f;\n  }\n\n  static void prod(vector< fps > &F, const vector<\
    \ fps > &G) {\n    int n = (int) F.size();\n    int d = __builtin_ctz(n);\n  \
    \  for(int i = 0; i < n; i++) {\n      fps h{};\n      for(int j = 0; j <= d;\
    \ j++) {\n        for(int k = 0; k <= d - j; k++) {\n          h[j + k] += F[i][j]\
    \ * G[i][k];\n        }\n      }\n      F[i] = move(h);\n    }\n  }\n\n  static\
    \ vector< Mint > multiply(const vector< Mint > &f, const vector< Mint > &g) {\n\
    \    auto F = lift(f), G = lift(g);\n    zeta_transform(F);\n    zeta_transform(G);\n\
    \    prod(F, G);\n    moebius_transform(F);\n    return unlift(F);\n  }\n};\n\n\
    template< typename Mint, int s >\narray< int, (1 << s) > SubsetConvolution< Mint,\
    \ s >::pop_count;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fft/subset-convolution.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-subset-convolution.test.cpp
documentation_of: math/fft/subset-convolution.hpp
layout: document
redirect_from:
- /library/math/fft/subset-convolution.hpp
- /library/math/fft/subset-convolution.hpp.html
title: Subset Convolution
---
