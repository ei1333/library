---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-find-linear-recurrence.test.cpp
    title: test/verify/yosupo-find-linear-recurrence.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-sparse-matrix-det.test.cpp
    title: test/verify/yosupo-sparse-matrix-det.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Berlekamp Massey
    links: []
  bundledCode: "#line 1 \"math/fps/berlekamp-massey.hpp\"\n/**\n * @brief Berlekamp\
    \ Massey\n */\ntemplate< template< typename > class FPS, typename Mint >\nFPS<\
    \ Mint > berlekamp_massey(const FPS< Mint > &s) {\n  const int N = (int) s.size();\n\
    \  FPS< Mint > b = {Mint(-1)}, c = {Mint(-1)};\n  Mint y = Mint(1);\n  for(int\
    \ ed = 1; ed <= N; ed++) {\n    int l = int(c.size()), m = int(b.size());\n  \
    \  Mint x = 0;\n    for(int i = 0; i < l; i++) x += c[i] * s[ed - l + i];\n  \
    \  b.emplace_back(0);\n    m++;\n    if(x == Mint(0)) continue;\n    Mint freq\
    \ = x / y;\n    if(l < m) {\n      auto tmp = c;\n      c.insert(begin(c), m -\
    \ l, Mint(0));\n      for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m -\
    \ 1 - i];\n      b = tmp;\n      y = x;\n    } else {\n      for(int i = 0; i\
    \ < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];\n    }\n  }\n  return c;\n}\n"
  code: "/**\n * @brief Berlekamp Massey\n */\ntemplate< template< typename > class\
    \ FPS, typename Mint >\nFPS< Mint > berlekamp_massey(const FPS< Mint > &s) {\n\
    \  const int N = (int) s.size();\n  FPS< Mint > b = {Mint(-1)}, c = {Mint(-1)};\n\
    \  Mint y = Mint(1);\n  for(int ed = 1; ed <= N; ed++) {\n    int l = int(c.size()),\
    \ m = int(b.size());\n    Mint x = 0;\n    for(int i = 0; i < l; i++) x += c[i]\
    \ * s[ed - l + i];\n    b.emplace_back(0);\n    m++;\n    if(x == Mint(0)) continue;\n\
    \    Mint freq = x / y;\n    if(l < m) {\n      auto tmp = c;\n      c.insert(begin(c),\
    \ m - l, Mint(0));\n      for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m\
    \ - 1 - i];\n      b = tmp;\n      y = x;\n    } else {\n      for(int i = 0;\
    \ i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];\n    }\n  }\n  return c;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/berlekamp-massey.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-sparse-matrix-det.test.cpp
  - test/verify/yosupo-find-linear-recurrence.test.cpp
documentation_of: math/fps/berlekamp-massey.hpp
layout: document
redirect_from:
- /library/math/fps/berlekamp-massey.hpp
- /library/math/fps/berlekamp-massey.hpp.html
title: Berlekamp Massey
---
