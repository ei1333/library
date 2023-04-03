---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':question:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':heavy_check_mark:'
    path: structure/others/linear-rmq.hpp
    title: Linear-RMQ
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/verify/yosupo-staticrmq-5.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-staticrmq-5.test.cpp\"\
    \n\n#line 1 \"structure/others/linear-rmq.hpp\"\n/**\n * @brief Linear-RMQ\n **/\n\
    template< typename Comp >\nstruct LinearRMQ {\n\n  vector< int > small;\n  vector<\
    \ vector< int > > large;\n\n  LinearRMQ() = default;\n\n  Comp comp;\n\n  static\
    \ inline int msb(int c) {\n    return 31 - __builtin_clz(c);\n  }\n\n  static\
    \ inline int ctz(int c) {\n    return __builtin_ctz(c);\n  }\n\n  inline int get_min(int\
    \ l, int r) const {\n    return comp(l, r) ? l : r;\n  }\n\n  explicit LinearRMQ(size_t\
    \ n, const Comp &comp) : comp(comp) {\n    vector< int > st;\n    st.reserve(32);\n\
    \    large.emplace_back();\n    large.front().reserve(n / 32);\n    small.reserve(n);\n\
    \    for(int i = 0; i < n; i++) {\n      while(!st.empty() && !comp(st.back(),\
    \ i)) {\n        st.pop_back();\n      }\n      small.emplace_back(st.empty()\
    \ ? 0 : small[st.back()]);\n      small.back() |= 1 << (i % 32);\n      st.emplace_back(i);\n\
    \      if((i + 1) % 32 == 0) {\n        large.front().emplace_back(st.front());\n\
    \        st.clear();\n      }\n    }\n    for(int i = 1; (i << 1) <= n / 32; i\
    \ <<= 1) {\n      vector< int > v;\n      int csz = n / 32 + 1 - (i << 1);\n \
    \     v.reserve(csz);\n      for(int k = 0; k < csz; k++) {\n        v.emplace_back(get_min(large.back()[k],\
    \ large.back()[k + i]));\n      }\n      large.emplace_back(move(v));\n    }\n\
    \  }\n\n  int fold(int l, int r) const {\n    --r;\n    int left = l / 32 + 1;\n\
    \    int right = r / 32;\n    if(left < right) {\n      auto p = msb(right - left);\n\
    \      return get_min(\n          get_min((left - 1) * 32 + ctz(small[left * 32\
    \ - 1] & ~0 << l % 32), large[p][left]),\n          get_min(large[p][right - (1\
    \ << p)], right * 32 + ctz(small[r])));\n    } else if(left == right) {\n    \
    \  return get_min((left - 1) * 32 + ctz(small[left * 32 - 1] & ~0 << l % 32),\n\
    \                     left * 32 + ctz(small[r]));\n    } else {\n      return\
    \ right * 32 + ctz(small[r] & ~0 << l % 32);\n    }\n  }\n};\n\ntemplate< typename\
    \ Comp >\nLinearRMQ< Comp > get_linear_rmq(int n, const Comp &comp) {\n  return\
    \ LinearRMQ< Comp >(n, comp);\n}\n#line 6 \"test/verify/yosupo-staticrmq-5.test.cpp\"\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-staticrmq-5.test.cpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > A(N);\n  in.read(A);\n  auto f = [&](int a,\
    \ int b) { return A[a] < A[b]; };\n  auto seg = get_linear_rmq(N, f);\n  while(Q--)\
    \ {\n    int l, r;\n    in.read(l, r);\n    out.writeln(A[seg.fold(l, r)]);\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../structure/others/linear-rmq.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > A(N);\n  in.read(A);\n  auto f = [&](int a,\
    \ int b) { return A[a] < A[b]; };\n  auto seg = get_linear_rmq(N, f);\n  while(Q--)\
    \ {\n    int l, r;\n    in.read(l, r);\n    out.writeln(A[seg.fold(l, r)]);\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/linear-rmq.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-staticrmq-5.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-staticrmq-5.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-staticrmq-5.test.cpp
- /verify/test/verify/yosupo-staticrmq-5.test.cpp.html
title: test/verify/yosupo-staticrmq-5.test.cpp
---
