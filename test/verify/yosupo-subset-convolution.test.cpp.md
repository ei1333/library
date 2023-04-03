---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics/montgomery-mod-int.hpp
    title: Montgomery ModInt
  - icon: ':heavy_check_mark:'
    path: math/fft/subset-convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':question:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"test/verify/yosupo-subset-convolution.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n#line 1 \"\
    template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing\
    \ int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL <<\
    \ 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n\
    \    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed <<\
    \ setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-subset-convolution.test.cpp\"\
    \n\n#line 1 \"math/fft/subset-convolution.hpp\"\n/**\n * @brief Subset Convolution\n\
    */\ntemplate< typename Mint, int _s >\nstruct SubsetConvolution {\n  using fps\
    \ = array< Mint, _s + 1 >;\n  static array< int, (1 << _s) > pop_count;\n  static\
    \ constexpr int s = _s;\n\n  SubsetConvolution() = default;\n\n  static void init()\
    \ {\n    if(pop_count.back() == 0) {\n      pop_count[0] = 0;\n      for(int i\
    \ = 1; i < (1 << s); i++) {\n        pop_count[i] = pop_count[i - (i & -i)] +\
    \ 1;\n      }\n    }\n  }\n\n  static inline void add(fps &f, const fps &g, int\
    \ d) {\n    for(int i = 0; i < d; i++) {\n      f[i] += g[i];\n    }\n  }\n\n\
    \  static inline void sub(fps &f, const fps &g, int d) {\n    for(int i = d; i\
    \ <= s; i++) {\n      f[i] -= g[i];\n    }\n  }\n\n  static void zeta_transform(vector<\
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
    \ > SubsetConvolution< Mint, s >::pop_count;\n#line 6 \"test/verify/yosupo-subset-convolution.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/montgomery-mod-int.hpp\"\n/**\n * @brief Montgomery\
    \ ModInt\n */\ntemplate< uint32_t mod, bool fast = false >\nstruct MontgomeryModInt\
    \ {\n  using mint = MontgomeryModInt;\n  using i32 = int32_t;\n  using i64 = int64_t;\n\
    \  using u32 = uint32_t;\n  using u64 = uint64_t;\n\n  static constexpr u32 get_r()\
    \ {\n    u32 ret = mod;\n    for(i32 i = 0; i < 4; i++) ret *= 2 - mod * ret;\n\
    \    return ret;\n  }\n\n  static constexpr u32 r = get_r();\n  static constexpr\
    \ u32 n2 = -u64(mod) % mod;\n\n  static_assert(r * mod == 1, \"invalid, r * mod\
    \ != 1\");\n  static_assert(mod < (1 << 30), \"invalid, mod >= 2 ^ 30\");\n  static_assert((mod\
    \ & 1) == 1, \"invalid, mod % 2 == 0\");\n\n  u32 x;\n\n  MontgomeryModInt() :\
    \ x{} {}\n\n  MontgomeryModInt(const i64 &a)\n      : x(reduce(u64(fast ? a :\
    \ (a % mod + mod)) * n2)) {}\n\n  static constexpr u32 reduce(const u64 &b) {\n\
    \    return u32(b >> 32) + mod - u32((u64(u32(b) * r) * mod) >> 32);\n  }\n\n\
    \  mint &operator+=(const mint &p) {\n    if(i32(x += p.x - 2 * mod) < 0) x +=\
    \ 2 * mod;\n    return *this;\n  }\n\n  mint &operator-=(const mint &p) {\n  \
    \  if(i32(x -= p.x) < 0) x += 2 * mod;\n    return *this;\n  }\n\n  mint &operator*=(const\
    \ mint &p) {\n    x = reduce(u64(x) * p.x);\n    return *this;\n  }\n\n  mint\
    \ &operator/=(const mint &p) {\n    *this *= p.inverse();\n    return *this;\n\
    \  }\n\n  mint operator-() const { return mint() - *this; }\n\n  mint operator+(const\
    \ mint &p) const { return mint(*this) += p; }\n\n  mint operator-(const mint &p)\
    \ const { return mint(*this) -= p; }\n\n  mint operator*(const mint &p) const\
    \ { return mint(*this) *= p; }\n\n  mint operator/(const mint &p) const { return\
    \ mint(*this) /= p; }\n\n  bool operator==(const mint &p) const { return (x >=\
    \ mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }\n\n  bool operator!=(const\
    \ mint &p) const { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod\
    \ : p.x); }\n\n  u32 get() const {\n    u32 ret = reduce(x);\n    return ret >=\
    \ mod ? ret - mod : ret;\n  }\n\n  mint pow(u64 n) const {\n    mint ret(1), mul(*this);\n\
    \    while(n > 0) {\n      if(n & 1) ret *= mul;\n      mul *= mul;\n      n >>=\
    \ 1;\n    }\n    return ret;\n  }\n\n  mint inverse() const {\n    return pow(mod\
    \ - 2);\n  }\n\n  friend ostream &operator<<(ostream &os, const mint &p) {\n \
    \   return os << p.get();\n  }\n\n  friend istream &operator>>(istream &is, mint\
    \ &a) {\n    i64 t;\n    is >> t;\n    a = mint(t);\n    return is;\n  }\n\n \
    \ static u32 get_mod() { return mod; }\n};\n\nusing modint = MontgomeryModInt<\
    \ mod >;\n#line 8 \"test/verify/yosupo-subset-convolution.test.cpp\"\n\n#line\
    \ 1 \"other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n\
    \ */\nstruct Scanner {\npublic:\n\n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n\
    \  template< typename T, typename... E >\n  void read(T &t, E &... e) {\n    read_single(t);\n\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 11 \"test/verify/yosupo-subset-convolution.test.cpp\"\
    \n\nconst int MOD = 998244353;\nusing mint = MontgomeryModInt< MOD, true >;\n\n\
    int main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N;\n  in.read(N);\n\
    \  vector< mint > f(1 << N), g(1 << N);\n  for(auto &a : f) {\n    int x;\n  \
    \  in.read(x);\n    a = x;\n  }\n  for(auto &a : g) {\n    int x;\n    in.read(x);\n\
    \    a = x;\n  }\n  auto h = SubsetConvolution< mint, 20 >::multiply(f, g);\n\
    \  for(auto &a : h) {\n    out.write(a.get());\n    out.write(' ');\n  }\n  out.writeln();\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../math/fft/subset-convolution.hpp\"\
    \n\n#include \"../../math/combinatorics/montgomery-mod-int.hpp\"\n\n#include \"\
    ../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\n\nconst int MOD\
    \ = 998244353;\nusing mint = MontgomeryModInt< MOD, true >;\n\nint main() {\n\
    \  Scanner in(stdin);\n  Printer out(stdout);\n  int N;\n  in.read(N);\n  vector<\
    \ mint > f(1 << N), g(1 << N);\n  for(auto &a : f) {\n    int x;\n    in.read(x);\n\
    \    a = x;\n  }\n  for(auto &a : g) {\n    int x;\n    in.read(x);\n    a = x;\n\
    \  }\n  auto h = SubsetConvolution< mint, 20 >::multiply(f, g);\n  for(auto &a\
    \ : h) {\n    out.write(a.get());\n    out.write(' ');\n  }\n  out.writeln();\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - math/fft/subset-convolution.hpp
  - math/combinatorics/montgomery-mod-int.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-subset-convolution.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-subset-convolution.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-subset-convolution.test.cpp
- /verify/test/verify/yosupo-subset-convolution.test.cpp.html
title: test/verify/yosupo-subset-convolution.test.cpp
---
