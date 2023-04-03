---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: math/fft/bitwise-or-convolution.hpp
    title: "Bitwise Or Convolution (Bitwise-OR\u7573\u307F\u8FBC\u307F)"
  - icon: ':heavy_check_mark:'
    path: math/fft/subset-zeta-moebius-transform.hpp
    title: "Subset Zeta/Moebius Transform (\u4E0B\u4F4D\u96C6\u5408\u306E\u30BC\u30FC\
      \u30BF/\u30E1\u30D3\u30A6\u30B9\u5909\u63DB)"
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
  bundledCode: "#line 1 \"test/verify/yosupo-bitwise-and-convolution-2.test.cpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-bitwise-and-convolution-2.test.cpp\"\
    \n\n#line 1 \"math/fft/subset-zeta-moebius-transform.hpp\"\n/**\n * @brief Subset\
    \ Zeta/Moebius Transform (\u4E0B\u4F4D\u96C6\u5408\u306E\u30BC\u30FC\u30BF/\u30E1\
    \u30D3\u30A6\u30B9\u5909\u63DB)\n */\ntemplate< typename T >\nvoid subset_zeta_transform(vector<\
    \ T > &f) {\n  const int n = (int) f.size();\n  assert((n & (n - 1)) == 0);\n\
    \  for(int i = 1; i < n; i <<= 1) {\n    for(int j = 0; j < n; j += i << 1) {\n\
    \      for(int k = 0; k < i; k++) {\n        f[j + k + i] += f[j + k];\n     \
    \ }\n    }\n  }\n}\n\ntemplate< typename T >\nvoid subset_moebius_transform(vector<\
    \ T > &f) {\n  const int n = (int) f.size();\n  assert((n & (n - 1)) == 0);\n\
    \  for(int i = 1; i < n; i <<= 1) {\n    for(int j = 0; j < n; j += i << 1) {\n\
    \      for(int k = 0; k < i; k++) {\n        f[j + k + i] -= f[j + k];\n     \
    \ }\n    }\n  }\n}\n#line 2 \"math/fft/bitwise-or-convolution.hpp\"\n\n/**\n *\
    \ @brief Bitwise Or Convolution (Bitwise-OR\u7573\u307F\u8FBC\u307F)\n */\ntemplate<\
    \ typename T >\nvector< T > bitwise_or_convolution(vector< T > f, vector< T >\
    \ g) {\n  const int n = (int) f.size();\n  assert(f.size() == g.size());\n  assert((n\
    \ & (n - 1)) == 0);\n  subset_zeta_transform(f);\n  subset_zeta_transform(g);\n\
    \  for(int i = 0; i < n; i++) f[i] *= g[i];\n  subset_moebius_transform(f);\n\
    \  return f;\n}\n#line 1 \"math/combinatorics/mod-int.hpp\"\ntemplate< int mod\
    \ >\nstruct ModInt {\n  int x;\n\n  ModInt() : x(0) {}\n\n  ModInt(int64_t y)\
    \ : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt &operator+=(const\
    \ ModInt &p) {\n    if((x += p.x) >= mod) x -= mod;\n    return *this;\n  }\n\n\
    \  ModInt &operator-=(const ModInt &p) {\n    if((x += mod - p.x) >= mod) x -=\
    \ mod;\n    return *this;\n  }\n\n  ModInt &operator*=(const ModInt &p) {\n  \
    \  x = (int) (1LL * x * p.x % mod);\n    return *this;\n  }\n\n  ModInt &operator/=(const\
    \ ModInt &p) {\n    *this *= p.inverse();\n    return *this;\n  }\n\n  ModInt\
    \ operator-() const { return ModInt(-x); }\n\n  ModInt operator+(const ModInt\
    \ &p) const { return ModInt(*this) += p; }\n\n  ModInt operator-(const ModInt\
    \ &p) const { return ModInt(*this) -= p; }\n\n  ModInt operator*(const ModInt\
    \ &p) const { return ModInt(*this) *= p; }\n\n  ModInt operator/(const ModInt\
    \ &p) const { return ModInt(*this) /= p; }\n\n  bool operator==(const ModInt &p)\
    \ const { return x == p.x; }\n\n  bool operator!=(const ModInt &p) const { return\
    \ x != p.x; }\n\n  ModInt inverse() const {\n    int a = x, b = mod, u = 1, v\
    \ = 0, t;\n    while(b > 0) {\n      t = a / b;\n      swap(a -= t * b, b);\n\
    \      swap(u -= t * v, v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt pow(int64_t\
    \ n) const {\n    ModInt ret(1), mul(x);\n    while(n > 0) {\n      if(n & 1)\
    \ ret *= mul;\n      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\
    \n  friend ostream &operator<<(ostream &os, const ModInt &p) {\n    return os\
    \ << p.x;\n  }\n\n  friend istream &operator>>(istream &is, ModInt &a) {\n   \
    \ int64_t t;\n    is >> t;\n    a = ModInt< mod >(t);\n    return (is);\n  }\n\
    \n  static int get_mod() { return mod; }\n};\n\nusing modint = ModInt< mod >;\n\
    #line 7 \"test/verify/yosupo-bitwise-and-convolution-2.test.cpp\"\n\n#line 1 \"\
    other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n */\nstruct\
    \ Scanner {\npublic:\n\n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n  template<\
    \ typename T, typename... E >\n  void read(T &t, E &... e) {\n    read_single(t);\n\
    \    read(e...);\n  }\n\nprivate:\n  static constexpr size_t line_size = 1 <<\
    \ 16;\n  static constexpr size_t int_digits = 20;\n  char line[line_size + 1]\
    \ = {};\n  FILE *fp = nullptr;\n  char *st = line;\n  char *ed = line;\n\n  void\
    \ read() {}\n\n  static inline bool is_space(char c) {\n    return c <= ' ';\n\
    \  }\n\n  void reread() {\n    ptrdiff_t len = ed - st;\n    memmove(line, st,\
    \ len);\n    char *tmp = line + len;\n    ed = tmp + fread(tmp, 1, line_size -\
    \ len, fp);\n    *ed = 0;\n    st = line;\n  }\n\n  void skip_space() {\n    while(true)\
    \ {\n      if(st == ed) reread();\n      while(*st && is_space(*st)) ++st;\n \
    \     if(st != ed) return;\n    }\n  }\n\n  template< typename T, enable_if_t<\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 10 \"test/verify/yosupo-bitwise-and-convolution-2.test.cpp\"\
    \n\nconst int MOD = 998244353;\nusing mint = ModInt< MOD >;\n\nint main() {\n\
    \  Scanner in(stdin);\n  Printer out(stdout);\n  int N;\n  in.read(N);\n  vector<\
    \ mint > a(1 << N), b(1 << N);\n  for(auto &x : a) {\n    int p;\n    in.read(p);\n\
    \    x = p;\n  }\n  for(auto &x : b) {\n    int p;\n    in.read(p);\n    x = p;\n\
    \  }\n  reverse(begin(a), end(a));\n  reverse(begin(b), end(b));\n  auto c = bitwise_or_convolution(a,\
    \ b);\n  reverse(begin(c), end(c));\n  for(int i = 0; i < (1 << N); i++) {\n \
    \   if(i) out.write(' ');\n    out.write(c[i].x);\n  }\n  out.writeln();\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/fft/bitwise-or-convolution.hpp\"\
    \n#include \"../../math/combinatorics/mod-int.hpp\"\n\n#include \"../../other/scanner.hpp\"\
    \n#include \"../../other/printer.hpp\"\n\nconst int MOD = 998244353;\nusing mint\
    \ = ModInt< MOD >;\n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n\
    \  int N;\n  in.read(N);\n  vector< mint > a(1 << N), b(1 << N);\n  for(auto &x\
    \ : a) {\n    int p;\n    in.read(p);\n    x = p;\n  }\n  for(auto &x : b) {\n\
    \    int p;\n    in.read(p);\n    x = p;\n  }\n  reverse(begin(a), end(a));\n\
    \  reverse(begin(b), end(b));\n  auto c = bitwise_or_convolution(a, b);\n  reverse(begin(c),\
    \ end(c));\n  for(int i = 0; i < (1 << N); i++) {\n    if(i) out.write(' ');\n\
    \    out.write(c[i].x);\n  }\n  out.writeln();\n}\n"
  dependsOn:
  - template/template.hpp
  - math/fft/bitwise-or-convolution.hpp
  - math/fft/subset-zeta-moebius-transform.hpp
  - math/combinatorics/mod-int.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-bitwise-and-convolution-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-bitwise-and-convolution-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-bitwise-and-convolution-2.test.cpp
- /verify/test/verify/yosupo-bitwise-and-convolution-2.test.cpp.html
title: test/verify/yosupo-bitwise-and-convolution-2.test.cpp
---
