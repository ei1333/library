---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
    title: test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Stirling Second(\u7B2C\u4E8C\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\
      \u30B0\u6570)"
    links: []
  bundledCode: "#line 1 \"math/fps/stirling-second.hpp\"\n/**\n * @brief Stirling\
    \ Second(\u7B2C\u4E8C\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570)\n */\n\
    template< template< typename > class FPS, typename Mint >\nFPS< Mint > stirling_second(int\
    \ N) {\n  FPS< Mint > A(N + 1), B(N + 1);\n  Mint tmp = 1;\n  for(int i = 0; i\
    \ <= N; i++) {\n    Mint rev = Mint(1) / tmp;\n    A[i] = Mint(i).pow(N) * rev;\n\
    \    B[i] = Mint(1) * rev;\n    if(i & 1) B[i] *= -1;\n    tmp *= i + 1;\n  }\n\
    \  return (A * B).pre(N + 1);\n}\n"
  code: "/**\n * @brief Stirling Second(\u7B2C\u4E8C\u7A2E\u30B9\u30BF\u30FC\u30EA\
    \u30F3\u30B0\u6570)\n */\ntemplate< template< typename > class FPS, typename Mint\
    \ >\nFPS< Mint > stirling_second(int N) {\n  FPS< Mint > A(N + 1), B(N + 1);\n\
    \  Mint tmp = 1;\n  for(int i = 0; i <= N; i++) {\n    Mint rev = Mint(1) / tmp;\n\
    \    A[i] = Mint(i).pow(N) * rev;\n    B[i] = Mint(1) * rev;\n    if(i & 1) B[i]\
    \ *= -1;\n    tmp *= i + 1;\n  }\n  return (A * B).pre(N + 1);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/stirling-second.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/verify/yosupo-stirling-number-of-the-second-kind.test.cpp
documentation_of: math/fps/stirling-second.hpp
layout: document
redirect_from:
- /library/math/fps/stirling-second.hpp
- /library/math/fps/stirling-second.hpp.html
title: "Stirling Second(\u7B2C\u4E8C\u7A2E\u30B9\u30BF\u30FC\u30EA\u30F3\u30B0\u6570\
  )"
---
