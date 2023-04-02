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
  - icon: ':x:'
    path: test/verify/yosupo-staticrmq-5.test.cpp
    title: test/verify/yosupo-staticrmq-5.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-staticrmq-6.test.cpp
    title: test/verify/yosupo-staticrmq-6.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-subset-convolution.test.cpp
    title: test/verify/yosupo-subset-convolution.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-tree-decomposition-width-2.test.cpp
    title: test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-two-sat.test.cpp
    title: test/verify/yosupo-two-sat.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "Printer(\u9AD8\u901F\u51FA\u529B)"
    links: []
  bundledCode: "#line 1 \"other/printer.hpp\"\n/**\n * @brief Printer(\u9AD8\u901F\
    \u51FA\u529B)\n */\nstruct Printer {\npublic:\n  explicit Printer(FILE *fp) :\
    \ fp(fp) {}\n\n  ~Printer() { flush(); }\n\n  template< bool f = false, typename\
    \ T, typename... E >\n  void write(const T &t, const E &... e) {\n    if(f) write_single('\
    \ ');\n    write_single(t);\n    write< true >(e...);\n  }\n\n  template< typename...\
    \ T >\n  void writeln(const T &...t) {\n    write(t...);\n    write_single('\\\
    n');\n  }\n\n  void flush() {\n    fwrite(line, 1, st - line, fp);\n    st = line;\n\
    \  }\n\nprivate:\n  FILE *fp = nullptr;\n  static constexpr size_t line_size =\
    \ 1 << 16;\n  static constexpr size_t int_digits = 20;\n  char line[line_size\
    \ + 1] = {};\n  char *st = line;\n\n  template< bool f = false >\n  void write()\
    \ {}\n\n  void write_single(const char &t) {\n    if(st + 1 >= line + line_size)\
    \ flush();\n    *st++ = t;\n  }\n\n  template< typename T, enable_if_t< is_integral<\
    \ T >::value, int > = 0 >\n  void write_single(T s) {\n    if(st + int_digits\
    \ >= line + line_size) flush();\n    st += to_chars(st, st + int_digits, s).ptr\
    \ - st;\n  }\n\n  void write_single(const string &s) {\n    for(auto &c: s) write_single(c);\n\
    \  }\n\n  void write_single(const char *s) {\n    while(*s != 0) write_single(*s++);\n\
    \  }\n\n  template< typename T >\n  void write_single(const vector< T > &s) {\n\
    \    for(size_t i = 0; i < s.size(); i++) {\n      if(i) write_single(' ');\n\
    \      write_single(s[i]);\n    }\n  }\n};\n"
  code: "/**\n * @brief Printer(\u9AD8\u901F\u51FA\u529B)\n */\nstruct Printer {\n\
    public:\n  explicit Printer(FILE *fp) : fp(fp) {}\n\n  ~Printer() { flush(); }\n\
    \n  template< bool f = false, typename T, typename... E >\n  void write(const\
    \ T &t, const E &... e) {\n    if(f) write_single(' ');\n    write_single(t);\n\
    \    write< true >(e...);\n  }\n\n  template< typename... T >\n  void writeln(const\
    \ T &...t) {\n    write(t...);\n    write_single('\\n');\n  }\n\n  void flush()\
    \ {\n    fwrite(line, 1, st - line, fp);\n    st = line;\n  }\n\nprivate:\n  FILE\
    \ *fp = nullptr;\n  static constexpr size_t line_size = 1 << 16;\n  static constexpr\
    \ size_t int_digits = 20;\n  char line[line_size + 1] = {};\n  char *st = line;\n\
    \n  template< bool f = false >\n  void write() {}\n\n  void write_single(const\
    \ char &t) {\n    if(st + 1 >= line + line_size) flush();\n    *st++ = t;\n  }\n\
    \n  template< typename T, enable_if_t< is_integral< T >::value, int > = 0 >\n\
    \  void write_single(T s) {\n    if(st + int_digits >= line + line_size) flush();\n\
    \    st += to_chars(st, st + int_digits, s).ptr - st;\n  }\n\n  void write_single(const\
    \ string &s) {\n    for(auto &c: s) write_single(c);\n  }\n\n  void write_single(const\
    \ char *s) {\n    while(*s != 0) write_single(*s++);\n  }\n\n  template< typename\
    \ T >\n  void write_single(const vector< T > &s) {\n    for(size_t i = 0; i <\
    \ s.size(); i++) {\n      if(i) write_single(' ');\n      write_single(s[i]);\n\
    \    }\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other/printer.hpp
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
documentation_of: other/printer.hpp
layout: document
redirect_from:
- /library/other/printer.hpp
- /library/other/printer.hpp.html
title: "Printer(\u9AD8\u901F\u51FA\u529B)"
---
