---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/offline-rmq.hpp
    title: Offline RMQ
  - icon: ':question:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':question:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':question:'
    path: structure/union-find/union-find.hpp
    title: Union Find
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
  bundledCode: "#line 1 \"test/verify/yosupo-staticrmq-6.test.cpp\"\n#define PROBLEM\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-staticrmq-6.test.cpp\"\
    \n\n#line 2 \"structure/union-find/union-find.hpp\"\n\nstruct UnionFind {\n  vector<\
    \ int > data;\n\n  UnionFind() = default;\n\n  explicit UnionFind(size_t sz) :\
    \ data(sz, -1) {}\n\n  bool unite(int x, int y) {\n    x = find(x), y = find(y);\n\
    \    if(x == y) return false;\n    if(data[x] > data[y]) swap(x, y);\n    data[x]\
    \ += data[y];\n    data[y] = x;\n    return true;\n  }\n\n  int find(int k) {\n\
    \    if(data[k] < 0) return (k);\n    return data[k] = find(data[k]);\n  }\n\n\
    \  int size(int k) {\n    return -data[find(k)];\n  }\n\n  bool same(int x, int\
    \ y) {\n    return find(x) == find(y);\n  }\n\n  vector< vector< int > > groups()\
    \ {\n    int n = (int) data.size();\n    vector< vector< int > > ret(n);\n   \
    \ for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n    }\n \
    \   ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int > &v) {\n\
    \      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n#line\
    \ 2 \"other/offline-rmq.hpp\"\n\n/**\n * @brief Offline RMQ\n **/\ntemplate< typename\
    \ Comp >\nvector< int > offline_rmq(vector< pair< int, int > > &qs, const Comp\
    \ &comp) {\n  int n = 0;\n  for(auto&[l, r]: qs) n = max(n, r);\n  UnionFind uf(n);\n\
    \  vector< int > st(n), mark(n), ans(qs.size());\n  int top = -1;\n  for(auto&[l,\
    \ r]: qs) mark[r - 1]++;\n  vector< vector< int > > q(n);\n  for(int i = 0; i\
    \ < n; i++) {\n    q[i].reserve(mark[i]);\n  }\n  for(int i = 0; i < qs.size();\
    \ i++) {\n    q[qs[i].second - 1].emplace_back(i);\n  }\n  for(int i = 0; i <\
    \ n; i++) {\n    while(~top and not comp(st[top], i)) {\n      uf.unite(st[top--],\
    \ i);\n    }\n    st[++top] = i;\n    mark[uf.find(i)] = i;\n    for(auto &j:\
    \ q[i]) {\n      ans[j] = mark[uf.find(qs[j].first)];\n    }\n  }\n  return ans;\n\
    }\n#line 6 \"test/verify/yosupo-staticrmq-6.test.cpp\"\n\n#line 1 \"other/scanner.hpp\"\
    \n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n */\nstruct Scanner {\npublic:\n\
    \n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n  template< typename T, typename...\
    \ E >\n  void read(T &t, E &... e) {\n    read_single(t);\n    read(e...);\n \
    \ }\n\nprivate:\n  static constexpr size_t line_size = 1 << 16;\n  static constexpr\
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
    \ read_single(vector< T > &s) {\n    for(auto &d : s) read(d);\n  }\n};\n#line\
    \ 1 \"other/printer.hpp\"\n/**\n * @brief Printer(\u9AD8\u901F\u51FA\u529B)\n\
    \ */\nstruct Printer {\npublic:\n  explicit Printer(FILE *fp) : fp(fp) {}\n\n\
    \  ~Printer() { flush(); }\n\n  template< bool f = false, typename T, typename...\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-staticrmq-6.test.cpp\"\
    \n\n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > A(N);\n  in.read(A);\n  vector< pair< int,\
    \ int > > qs(Q);\n  for(auto&[l, r]: qs) in.read(l, r);\n  auto ans = offline_rmq(qs,\
    \ [&](int a, int b) { return A[a] < A[b]; });\n  for(int i = 0; i < Q; i++) out.writeln(A[ans[i]]);\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../other/offline-rmq.hpp\"\n\
    \n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\n\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > A(N);\n  in.read(A);\n  vector< pair< int,\
    \ int > > qs(Q);\n  for(auto&[l, r]: qs) in.read(l, r);\n  auto ans = offline_rmq(qs,\
    \ [&](int a, int b) { return A[a] < A[b]; });\n  for(int i = 0; i < Q; i++) out.writeln(A[ans[i]]);\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - other/offline-rmq.hpp
  - structure/union-find/union-find.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-staticrmq-6.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-staticrmq-6.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-staticrmq-6.test.cpp
- /verify/test/verify/yosupo-staticrmq-6.test.cpp.html
title: test/verify/yosupo-staticrmq-6.test.cpp
---
