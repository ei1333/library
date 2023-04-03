---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Stirling First(\u7B2C\u4E00\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\
      \u30B0\u6570)"
    links: []
  bundledCode: "#line 1 \"math/fps/stirling-first.hpp\"\n/**\n * @brief Stirling First(\u7B2C\
    \u4E00\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570)\n */\ntemplate< template<\
    \ typename > class FPS, typename Mint >\nFPS< Mint > stirling_first(int N) {\n\
    \  if(N <= 0) return {Mint(1)};\n  auto f = stirling_first< FPS, Mint >(N >> 1);\n\
    \  f *= f.taylor_shift(-(N >> 1));\n  if(N & 1) f = (f << 1) - f * (N - 1);\n\
    \  return f;\n}\n"
  code: "/**\n * @brief Stirling First(\u7B2C\u4E00\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\
    \u30B0\u6570)\n */\ntemplate< template< typename > class FPS, typename Mint >\n\
    FPS< Mint > stirling_first(int N) {\n  if(N <= 0) return {Mint(1)};\n  auto f\
    \ = stirling_first< FPS, Mint >(N >> 1);\n  f *= f.taylor_shift(-(N >> 1));\n\
    \  if(N & 1) f = (f << 1) - f * (N - 1);\n  return f;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/stirling-first.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/verify/yosupo-stirling-number-of-the-first-kind.test.cpp
documentation_of: math/fps/stirling-first.hpp
layout: document
redirect_from:
- /library/math/fps/stirling-first.hpp
- /library/math/fps/stirling-first.hpp.html
title: "Stirling First(\u7B2C\u4E00\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570\
  )"
---
