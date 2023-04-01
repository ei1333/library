---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: structure/develop/vertex-set-path-composite.hpp
    title: Vertex Set Path Composite
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-convolution-mod-2.test.cpp
    title: test/verify/yosupo-convolution-mod-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-dynamic-tree-vertex-set-path-composite-3.test.cpp
    title: test/verify/yosupo-dynamic-tree-vertex-set-path-composite-3.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-subset-convolution.test.cpp
    title: test/verify/yosupo-subset-convolution.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-1720.test.cpp
    title: test/verify/yukicoder-1720.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Montgomery ModInt
    links: []
  bundledCode: "#line 1 \"math/combinatorics/montgomery-mod-int.hpp\"\n/**\n * @brief\
    \ Montgomery ModInt\n */\ntemplate< uint32_t mod, bool fast = false >\nstruct\
    \ MontgomeryModInt {\n  using mint = MontgomeryModInt;\n  using i32 = int32_t;\n\
    \  using i64 = int64_t;\n  using u32 = uint32_t;\n  using u64 = uint64_t;\n\n\
    \  static constexpr u32 get_r() {\n    u32 ret = mod;\n    for(i32 i = 0; i <\
    \ 4; i++) ret *= 2 - mod * ret;\n    return ret;\n  }\n\n  static constexpr u32\
    \ r = get_r();\n  static constexpr u32 n2 = -u64(mod) % mod;\n\n  static_assert(r\
    \ * mod == 1, \"invalid, r * mod != 1\");\n  static_assert(mod < (1 << 30), \"\
    invalid, mod >= 2 ^ 30\");\n  static_assert((mod & 1) == 1, \"invalid, mod % 2\
    \ == 0\");\n\n  u32 x;\n\n  MontgomeryModInt() : x{} {}\n\n  MontgomeryModInt(const\
    \ i64 &a)\n      : x(reduce(u64(fast ? a : (a % mod + mod)) * n2)) {}\n\n  static\
    \ constexpr u32 reduce(const u64 &b) {\n    return u32(b >> 32) + mod - u32((u64(u32(b)\
    \ * r) * mod) >> 32);\n  }\n\n  mint &operator+=(const mint &p) {\n    if(i32(x\
    \ += p.x - 2 * mod) < 0) x += 2 * mod;\n    return *this;\n  }\n\n  mint &operator-=(const\
    \ mint &p) {\n    if(i32(x -= p.x) < 0) x += 2 * mod;\n    return *this;\n  }\n\
    \n  mint &operator*=(const mint &p) {\n    x = reduce(u64(x) * p.x);\n    return\
    \ *this;\n  }\n\n  mint &operator/=(const mint &p) {\n    *this *= p.inverse();\n\
    \    return *this;\n  }\n\n  mint operator-() const { return mint() - *this; }\n\
    \n  mint operator+(const mint &p) const { return mint(*this) += p; }\n\n  mint\
    \ operator-(const mint &p) const { return mint(*this) -= p; }\n\n  mint operator*(const\
    \ mint &p) const { return mint(*this) *= p; }\n\n  mint operator/(const mint &p)\
    \ const { return mint(*this) /= p; }\n\n  bool operator==(const mint &p) const\
    \ { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }\n\n \
    \ bool operator!=(const mint &p) const { return (x >= mod ? x - mod : x) != (p.x\
    \ >= mod ? p.x - mod : p.x); }\n\n  u32 get() const {\n    u32 ret = reduce(x);\n\
    \    return ret >= mod ? ret - mod : ret;\n  }\n\n  mint pow(u64 n) const {\n\
    \    mint ret(1), mul(*this);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  mint inverse()\
    \ const {\n    return pow(mod - 2);\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, const mint &p) {\n    return os << p.get();\n  }\n\n  friend istream &operator>>(istream\
    \ &is, mint &a) {\n    i64 t;\n    is >> t;\n    a = mint(t);\n    return is;\n\
    \  }\n\n  static u32 get_mod() { return mod; }\n};\n\nusing modint = MontgomeryModInt<\
    \ mod >;\n"
  code: "/**\n * @brief Montgomery ModInt\n */\ntemplate< uint32_t mod, bool fast\
    \ = false >\nstruct MontgomeryModInt {\n  using mint = MontgomeryModInt;\n  using\
    \ i32 = int32_t;\n  using i64 = int64_t;\n  using u32 = uint32_t;\n  using u64\
    \ = uint64_t;\n\n  static constexpr u32 get_r() {\n    u32 ret = mod;\n    for(i32\
    \ i = 0; i < 4; i++) ret *= 2 - mod * ret;\n    return ret;\n  }\n\n  static constexpr\
    \ u32 r = get_r();\n  static constexpr u32 n2 = -u64(mod) % mod;\n\n  static_assert(r\
    \ * mod == 1, \"invalid, r * mod != 1\");\n  static_assert(mod < (1 << 30), \"\
    invalid, mod >= 2 ^ 30\");\n  static_assert((mod & 1) == 1, \"invalid, mod % 2\
    \ == 0\");\n\n  u32 x;\n\n  MontgomeryModInt() : x{} {}\n\n  MontgomeryModInt(const\
    \ i64 &a)\n      : x(reduce(u64(fast ? a : (a % mod + mod)) * n2)) {}\n\n  static\
    \ constexpr u32 reduce(const u64 &b) {\n    return u32(b >> 32) + mod - u32((u64(u32(b)\
    \ * r) * mod) >> 32);\n  }\n\n  mint &operator+=(const mint &p) {\n    if(i32(x\
    \ += p.x - 2 * mod) < 0) x += 2 * mod;\n    return *this;\n  }\n\n  mint &operator-=(const\
    \ mint &p) {\n    if(i32(x -= p.x) < 0) x += 2 * mod;\n    return *this;\n  }\n\
    \n  mint &operator*=(const mint &p) {\n    x = reduce(u64(x) * p.x);\n    return\
    \ *this;\n  }\n\n  mint &operator/=(const mint &p) {\n    *this *= p.inverse();\n\
    \    return *this;\n  }\n\n  mint operator-() const { return mint() - *this; }\n\
    \n  mint operator+(const mint &p) const { return mint(*this) += p; }\n\n  mint\
    \ operator-(const mint &p) const { return mint(*this) -= p; }\n\n  mint operator*(const\
    \ mint &p) const { return mint(*this) *= p; }\n\n  mint operator/(const mint &p)\
    \ const { return mint(*this) /= p; }\n\n  bool operator==(const mint &p) const\
    \ { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }\n\n \
    \ bool operator!=(const mint &p) const { return (x >= mod ? x - mod : x) != (p.x\
    \ >= mod ? p.x - mod : p.x); }\n\n  u32 get() const {\n    u32 ret = reduce(x);\n\
    \    return ret >= mod ? ret - mod : ret;\n  }\n\n  mint pow(u64 n) const {\n\
    \    mint ret(1), mul(*this);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  mint inverse()\
    \ const {\n    return pow(mod - 2);\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, const mint &p) {\n    return os << p.get();\n  }\n\n  friend istream &operator>>(istream\
    \ &is, mint &a) {\n    i64 t;\n    is >> t;\n    a = mint(t);\n    return is;\n\
    \  }\n\n  static u32 get_mod() { return mod; }\n};\n\nusing modint = MontgomeryModInt<\
    \ mod >;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics/montgomery-mod-int.hpp
  requiredBy:
  - structure/develop/vertex-set-path-composite.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-subset-convolution.test.cpp
  - test/verify/yosupo-convolution-mod-2.test.cpp
  - test/verify/yosupo-dynamic-tree-vertex-set-path-composite-3.test.cpp
  - test/verify/yukicoder-1720.test.cpp
documentation_of: math/combinatorics/montgomery-mod-int.hpp
layout: document
redirect_from:
- /library/math/combinatorics/montgomery-mod-int.hpp
- /library/math/combinatorics/montgomery-mod-int.hpp.html
title: Montgomery ModInt
---
