---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft/superset-zeta-moebius-transform-simd.hpp
    title: "Superset Zeta/Moebius Transform SIMD (\u4E0A\u4F4D\u96C6\u5408\u306E\u30BC\
      \u30FC\u30BF/\u30E1\u30D3\u30A6\u30B9\u5909\u63DB, SIMD)"
  - icon: ':heavy_check_mark:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/verify/yosupo-bitwise-and-convolution-3.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\n\
    #line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll\
    \ = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
    \ {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed\
    \ << setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
    \ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream &os, const\
    \ pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream &is, pair<\
    \ T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename\
    \ T >\nostream &operator<<(ostream &os, const vector< T > &v) {\n  for(int i =\
    \ 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \"\
    \ : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream\
    \ &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate<\
    \ typename T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b &&\
    \ (a = b, true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64\
    \ >\nvector< T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate<\
    \ typename T, typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector<\
    \ decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename\
    \ T, typename V >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T\
    \ &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename\
    \ enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto\
    \ &e : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n\
    \  explicit FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename...\
    \ Args >\n  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-bitwise-and-convolution-3.test.cpp\"\
    \n\n#line 1 \"math/fft/superset-zeta-moebius-transform-simd.hpp\"\n#include <immintrin.h>\n\
    \n/**\n * @brief Superset Zeta/Moebius Transform SIMD (\u4E0A\u4F4D\u96C6\u5408\
    \u306E\u30BC\u30FC\u30BF/\u30E1\u30D3\u30A6\u30B9\u5909\u63DB, SIMD)\n */\n__attribute__((target(\"\
    avx2\")))\nvoid superset_zeta_transform_simd(int *buf, int mod, int n) {\n  assert((n\
    \ & (n - 1)) == 0);\n  auto m_zero = _mm256_set1_epi32(0);\n  auto m_mod_one =\
    \ _mm256_set1_epi32(mod - 1);\n  auto m_mod = _mm256_set1_epi32(mod);\n  auto\
    \ m_zero2 = _mm_set1_epi32(0);\n  auto m_mod_one2 = _mm_set1_epi32(mod - 1);\n\
    \  auto m_mod2 = _mm_set1_epi32(mod);\n  for(int i = 1; i < n; i <<= 1) {\n  \
    \  for(int j = 0; j < n; j += i << 1) {\n      if(i <= 2) {\n        for(int k\
    \ = 0; k < i; k++) {\n          buf[j + k] += buf[j + k + i];\n          if(buf[j\
    \ + k] >= mod) buf[j + k] -= mod;\n        }\n      } else if(i == 4) {\n    \
    \    for(int k = 0; k < i; k += 4) {\n          auto a = _mm_loadu_si128((__m128i\
    \ *) (buf + j + k));\n          auto b = _mm_loadu_si128((__m128i *) (buf + j\
    \ + k + i));\n          a = _mm_add_epi32(a, b);\n          a = _mm_sub_epi32(a,\
    \ _mm_and_si128(_mm_cmpgt_epi32(a, m_mod_one2), m_mod2));\n          _mm_storeu_si128((__m128i\
    \ *) (buf + j + k), a);\n        }\n      } else {\n        for(int k = 0; k <\
    \ i; k += 8) {\n          auto a = _mm256_loadu_si256((__m256i *) (buf + j + k));\n\
    \          auto b = _mm256_loadu_si256((__m256i *) (buf + j + k + i));\n     \
    \     a = _mm256_add_epi32(a, b);\n          a = _mm256_sub_epi32(a, _mm256_and_si256(_mm256_cmpgt_epi32(a,\
    \ m_mod_one), m_mod));\n          _mm256_storeu_si256((__m256i *) (buf + j + k),\
    \ a);\n        }\n      }\n    }\n  }\n}\n\n\n__attribute__((target(\"avx2\")))\n\
    void superset_moebius_transform_simd(int *buf, int mod, int n) {\n  assert((n\
    \ & (n - 1)) == 0);\n  auto m_zero = _mm256_set1_epi32(0);\n  auto m_mod = _mm256_set1_epi32(mod);\n\
    \  auto m_zero2 = _mm_set1_epi32(0);\n  auto m_mod2 = _mm_set1_epi32(mod);\n \
    \ for(int i = 1; i < n; i <<= 1) {\n    for(int j = 0; j < n; j += i << 1) {\n\
    \      if(i <= 2) {\n        for(int k = 0; k < i; k++) {\n          buf[j + k]\
    \ += mod - buf[j + k + i];\n          if(buf[j + k] >= mod) buf[j + k] -= mod;\n\
    \        }\n      } else if(i == 4) {\n        for(int k = 0; k < i; k += 4) {\n\
    \          auto a = _mm_loadu_si128((__m128i * )(buf + j + k));\n          auto\
    \ b = _mm_loadu_si128((__m128i * )(buf + j + k + i));\n          a = _mm_sub_epi32(a,\
    \ b);\n          a = _mm_add_epi32(a, _mm_and_si128(_mm_cmpgt_epi32(m_zero2, a),\
    \ m_mod2));\n          _mm_storeu_si128((__m128i * )(buf + j + k), a);\n     \
    \   }\n      } else {\n        for(int k = 0; k < i; k += 8) {\n          auto\
    \ a = _mm256_loadu_si256((__m256i * )(buf + j + k));\n          auto b = _mm256_loadu_si256((__m256i\
    \ * )(buf + j + k + i));\n          a = _mm256_sub_epi32(a, b);\n          a =\
    \ _mm256_add_epi32(a, _mm256_and_si256(_mm256_cmpgt_epi32(m_zero, a), m_mod));\n\
    \          _mm256_storeu_si256((__m256i * )(buf + j + k), a);\n        }\n   \
    \   }\n    }\n  }\n}\n\ntemplate< int mod >\nint *bitwise_and_convolution_simd(int\
    \ *f, int *g, int n) {\n  assert((n & (n - 1)) == 0);\n  superset_zeta_transform_simd(f,\
    \ mod, n);\n  superset_zeta_transform_simd(g, mod, n);\n  for(int i = 0; i < n;\
    \ i++) f[i] = (1uLL * f[i] * g[i]) % mod;\n  superset_moebius_transform_simd(f,\
    \ mod, n);\n  return f;\n}\n#line 6 \"test/verify/yosupo-bitwise-and-convolution-3.test.cpp\"\
    \n\n#line 1 \"other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B\
    )\n */\nstruct Scanner {\npublic:\n\n  explicit Scanner(FILE *fp) : fp(fp) {}\n\
    \n  template< typename T, typename... E >\n  void read(T &t, E &... e) {\n   \
    \ read_single(t);\n    read(e...);\n  }\n\nprivate:\n  static constexpr size_t\
    \ line_size = 1 << 16;\n  static constexpr size_t int_digits = 20;\n  char line[line_size\
    \ + 1] = {};\n  FILE *fp = nullptr;\n  char *st = line;\n  char *ed = line;\n\n\
    \  void read() {}\n\n  static inline bool is_space(char c) {\n    return c <=\
    \ ' ';\n  }\n\n  void reread() {\n    ptrdiff_t len = ed - st;\n    memmove(line,\
    \ st, len);\n    char *tmp = line + len;\n    ed = tmp + fread(tmp, 1, line_size\
    \ - len, fp);\n    *ed = 0;\n    st = line;\n  }\n\n  void skip_space() {\n  \
    \  while(true) {\n      if(st == ed) reread();\n      while(*st && is_space(*st))\
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
    \ }\n};\n#line 1 \"other/printer.hpp\"\n/**\n * @brief Printer(\u9AD8\u901F\u51FA\
    \u529B)\n */\nstruct Printer {\npublic:\n  explicit Printer(FILE *fp) : fp(fp)\
    \ {}\n\n  ~Printer() { flush(); }\n\n  template< bool f = false, typename T, typename...\
    \ E >\n  void write(const T &t, const E &... e) {\n    if(f) write_single(' ');\n\
    \    write_single(t);\n    write< true >(e...);\n  }\n\n  template< typename...\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-bitwise-and-convolution-3.test.cpp\"\
    \n\nconst int MOD = 998244353;\n\nint main() {\n  Scanner in(stdin);\n  Printer\
    \ out(stdout);\n  int N;\n  in.read(N);\n  int a[1 << N], b[1 << N];\n  for(int\
    \ i = 0; i < (1 << N); i++) in.read(a[i]);\n  for(int i = 0; i < (1 << N); i++)\
    \ in.read(b[i]);\n  bitwise_and_convolution_simd< MOD >(a, b, 1 << N);\n  for(int\
    \ i = 0; i < (1 << N); i++) {\n    if(i) out.write(' ');\n    out.write(a[i]);\n\
    \  }\n  out.writeln();\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/fft/superset-zeta-moebius-transform-simd.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\nconst int MOD = 998244353;\n\nint main() {\n  Scanner in(stdin);\n  Printer\
    \ out(stdout);\n  int N;\n  in.read(N);\n  int a[1 << N], b[1 << N];\n  for(int\
    \ i = 0; i < (1 << N); i++) in.read(a[i]);\n  for(int i = 0; i < (1 << N); i++)\
    \ in.read(b[i]);\n  bitwise_and_convolution_simd< MOD >(a, b, 1 << N);\n  for(int\
    \ i = 0; i < (1 << N); i++) {\n    if(i) out.write(' ');\n    out.write(a[i]);\n\
    \  }\n  out.writeln();\n}\n"
  dependsOn:
  - template/template.hpp
  - math/fft/superset-zeta-moebius-transform-simd.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-bitwise-and-convolution-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-bitwise-and-convolution-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-bitwise-and-convolution-3.test.cpp
- /verify/test/verify/yosupo-bitwise-and-convolution-3.test.cpp.html
title: test/verify/yosupo-bitwise-and-convolution-3.test.cpp
---
