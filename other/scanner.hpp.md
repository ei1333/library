---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/dmoj-ds5.test.cpp
    title: test/verify/dmoj-ds5.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bitwise-and-convolution-2.test.cpp
    title: test/verify/yosupo-bitwise-and-convolution-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bitwise-and-convolution-3.test.cpp
    title: test/verify/yosupo-bitwise-and-convolution-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bitwise-and-convolution.test.cpp
    title: test/verify/yosupo-bitwise-and-convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bitwise-xor-convolution.test.cpp
    title: test/verify/yosupo-bitwise-xor-convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-division-of-polynomials.test.cpp
    title: test/verify/yosupo-division-of-polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-2.test.cpp
    title: test/verify/yosupo-lca-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-3.test.cpp
    title: test/verify/yosupo-lca-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-4.test.cpp
    title: test/verify/yosupo-lca-4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca.test.cpp
    title: test/verify/yosupo-lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-rectangle-sum-2.test.cpp
    title: test/verify/yosupo-rectangle-sum-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-5.test.cpp
    title: test/verify/yosupo-staticrmq-5.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-6.test.cpp
    title: test/verify/yosupo-staticrmq-6.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-subset-convolution.test.cpp
    title: test/verify/yosupo-subset-convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-tree-decomposition-width-2.test.cpp
    title: test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-two-sat.test.cpp
    title: test/verify/yosupo-two-sat.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "Scanner(\u9AD8\u901F\u5165\u529B)"
    links: []
  bundledCode: "#line 1 \"other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\
    \u5165\u529B)\n */\nstruct Scanner {\npublic:\n\n  explicit Scanner(FILE *fp)\
    \ : fp(fp) {}\n\n  template< typename T, typename... E >\n  void read(T &t, E\
    \ &... e) {\n    read_single(t);\n    read(e...);\n  }\n\nprivate:\n  static constexpr\
    \ size_t line_size = 1 << 16;\n  static constexpr size_t int_digits = 20;\n  char\
    \ line[line_size + 1] = {};\n  FILE *fp = nullptr;\n  char *st = line;\n  char\
    \ *ed = line;\n\n  void read() {}\n\n  static inline bool is_space(char c) {\n\
    \    return c <= ' ';\n  }\n\n  void reread() {\n    ptrdiff_t len = ed - st;\n\
    \    memmove(line, st, len);\n    char *tmp = line + len;\n    ed = tmp + fread(tmp,\
    \ 1, line_size - len, fp);\n    *ed = 0;\n    st = line;\n  }\n\n  void skip_space()\
    \ {\n    while(true) {\n      if(st == ed) reread();\n      while(*st && is_space(*st))\
    \ ++st;\n      if(st != ed) return;\n    }\n  }\n\n  template< typename T, enable_if_t<\
    \ is_integral< T >::value, int > = 0 >\n  void read_single(T &s) {\n    skip_space();\n\
    \    if(st + int_digits >= ed) reread();\n    bool neg = false;\n    if(is_signed<\
    \ T >::value && *st == '-') {\n      neg = true;\n      ++st;\n    }\n    typename\
    \ make_unsigned< T >::type y = *st++ - '0';\n    while(*st >= '0') {\n      y\
    \ = 10 * y + *st++ - '0';\n    }\n    s = (neg ? -y : y);\n  }\n\n  template<\
    \ typename T, enable_if_t< is_same< T, string >::value, int > = 0 >\n  void read_single(T\
    \ &s) {\n    s = \"\";\n    skip_space();\n    while(true) {\n      char *base\
    \ = st;\n      while(*st && !is_space(*st)) ++st;\n      s += string(base, st);\n\
    \      if(st != ed) return;\n      reread();\n    }\n  }\n\n  template< typename\
    \ T >\n  void read_single(vector< T > &s) {\n    for(auto &d : s) read(d);\n \
    \ }\n};\n"
  code: "/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n */\nstruct Scanner {\n\
    public:\n\n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n  template< typename T,\
    \ typename... E >\n  void read(T &t, E &... e) {\n    read_single(t);\n    read(e...);\n\
    \  }\n\nprivate:\n  static constexpr size_t line_size = 1 << 16;\n  static constexpr\
    \ size_t int_digits = 20;\n  char line[line_size + 1] = {};\n  FILE *fp = nullptr;\n\
    \  char *st = line;\n  char *ed = line;\n\n  void read() {}\n\n  static inline\
    \ bool is_space(char c) {\n    return c <= ' ';\n  }\n\n  void reread() {\n  \
    \  ptrdiff_t len = ed - st;\n    memmove(line, st, len);\n    char *tmp = line\
    \ + len;\n    ed = tmp + fread(tmp, 1, line_size - len, fp);\n    *ed = 0;\n \
    \   st = line;\n  }\n\n  void skip_space() {\n    while(true) {\n      if(st ==\
    \ ed) reread();\n      while(*st && is_space(*st)) ++st;\n      if(st != ed) return;\n\
    \    }\n  }\n\n  template< typename T, enable_if_t< is_integral< T >::value, int\
    \ > = 0 >\n  void read_single(T &s) {\n    skip_space();\n    if(st + int_digits\
    \ >= ed) reread();\n    bool neg = false;\n    if(is_signed< T >::value && *st\
    \ == '-') {\n      neg = true;\n      ++st;\n    }\n    typename make_unsigned<\
    \ T >::type y = *st++ - '0';\n    while(*st >= '0') {\n      y = 10 * y + *st++\
    \ - '0';\n    }\n    s = (neg ? -y : y);\n  }\n\n  template< typename T, enable_if_t<\
    \ is_same< T, string >::value, int > = 0 >\n  void read_single(T &s) {\n    s\
    \ = \"\";\n    skip_space();\n    while(true) {\n      char *base = st;\n    \
    \  while(*st && !is_space(*st)) ++st;\n      s += string(base, st);\n      if(st\
    \ != ed) return;\n      reread();\n    }\n  }\n\n  template< typename T >\n  void\
    \ read_single(vector< T > &s) {\n    for(auto &d : s) read(d);\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other/scanner.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-rectangle-sum-2.test.cpp
  - test/verify/yosupo-subset-convolution.test.cpp
  - test/verify/yosupo-lca-2.test.cpp
  - test/verify/yosupo-bitwise-and-convolution-3.test.cpp
  - test/verify/yosupo-bitwise-and-convolution-2.test.cpp
  - test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - test/verify/yosupo-lca.test.cpp
  - test/verify/yosupo-staticrmq-5.test.cpp
  - test/verify/yosupo-division-of-polynomials.test.cpp
  - test/verify/dmoj-ds5.test.cpp
  - test/verify/yosupo-bitwise-xor-convolution.test.cpp
  - test/verify/yosupo-lca-3.test.cpp
  - test/verify/yosupo-two-sat.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - test/verify/yosupo-lca-4.test.cpp
  - test/verify/yosupo-staticrmq-6.test.cpp
  - test/verify/yosupo-bitwise-and-convolution.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
documentation_of: other/scanner.hpp
layout: document
redirect_from:
- /library/other/scanner.hpp
- /library/other/scanner.hpp.html
title: "Scanner(\u9AD8\u901F\u5165\u529B)"
---
