---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-184.test.cpp
    title: test/verify/yukicoder-184.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/binary-basis.hpp\"\ntemplate< typename T >\n\
    struct BinaryBasis {\n  vector< T > basis;\n  bool update;\n\n  BinaryBasis()\
    \ : update(false) {}\n\n  bool add(T bit) {\n    for(auto &p : basis) {\n    \
    \  bit = min(bit, bit ^ p);\n    }\n    if(bit) {\n      basis.emplace_back(bit);\n\
    \      return update = true;\n    } else {\n      return false;\n    }\n  }\n\n\
    \  bool check(T bit) const {\n    for(auto &p : basis) {\n      bit = min(bit,\
    \ bit ^ p);\n    }\n    return bit == 0;\n  }\n\n  void normalize() {\n    sweep();\n\
    \    for(int i = (int) basis.size() - 1; i >= 0; i--) {\n      for(int j = i -\
    \ 1; j >= 0; j--) chmin(basis[i], basis[i] ^ basis[j]);\n    }\n  }\n\n  void\
    \ sweep() {\n    if(exchange(update, false)) {\n      sort(begin(basis), end(basis));\n\
    \    }\n  }\n\n  bool operator==(BinaryBasis< T > &a) {\n    normalize(), a.normalize();\n\
    \    return basis == a.basis;\n  }\n\n  T get_kth(int64_t k) { /* 0-indexed */\n\
    \    if((1LL << basis.size()) <= k) {\n      return -1;\n    }\n    T ret = T();\n\
    \    sweep();\n    for(int i = (int) basis.size() - 1; i >= 0; i--) {\n      if(k\
    \ < (1LL << i)) {\n        ret = min(ret, ret ^ basis[i]);\n      } else {\n \
    \       k -= 1LL << i;\n        ret = max(ret, ret ^ basis[i]);\n      }\n   \
    \ }\n    return ret;\n  }\n\n  size_t size() const {\n    return basis.size();\n\
    \  }\n};\n"
  code: "template< typename T >\nstruct BinaryBasis {\n  vector< T > basis;\n  bool\
    \ update;\n\n  BinaryBasis() : update(false) {}\n\n  bool add(T bit) {\n    for(auto\
    \ &p : basis) {\n      bit = min(bit, bit ^ p);\n    }\n    if(bit) {\n      basis.emplace_back(bit);\n\
    \      return update = true;\n    } else {\n      return false;\n    }\n  }\n\n\
    \  bool check(T bit) const {\n    for(auto &p : basis) {\n      bit = min(bit,\
    \ bit ^ p);\n    }\n    return bit == 0;\n  }\n\n  void normalize() {\n    sweep();\n\
    \    for(int i = (int) basis.size() - 1; i >= 0; i--) {\n      for(int j = i -\
    \ 1; j >= 0; j--) chmin(basis[i], basis[i] ^ basis[j]);\n    }\n  }\n\n  void\
    \ sweep() {\n    if(exchange(update, false)) {\n      sort(begin(basis), end(basis));\n\
    \    }\n  }\n\n  bool operator==(BinaryBasis< T > &a) {\n    normalize(), a.normalize();\n\
    \    return basis == a.basis;\n  }\n\n  T get_kth(int64_t k) { /* 0-indexed */\n\
    \    if((1LL << basis.size()) <= k) {\n      return -1;\n    }\n    T ret = T();\n\
    \    sweep();\n    for(int i = (int) basis.size() - 1; i >= 0; i--) {\n      if(k\
    \ < (1LL << i)) {\n        ret = min(ret, ret ^ basis[i]);\n      } else {\n \
    \       k -= 1LL << i;\n        ret = max(ret, ret ^ basis[i]);\n      }\n   \
    \ }\n    return ret;\n  }\n\n  size_t size() const {\n    return basis.size();\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/binary-basis.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-184.test.cpp
documentation_of: math/matrix/binary-basis.hpp
layout: document
redirect_from:
- /library/math/matrix/binary-basis.hpp
- /library/math/matrix/binary-basis.hpp.html
title: math/matrix/binary-basis.hpp
---
