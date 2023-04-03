---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/rmq-lowest-common-ancestor.hpp
    title: "RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
  - icon: ':question:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':question:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':heavy_check_mark:'
    path: structure/others/sparse-table.hpp
    title: "Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)"
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
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/verify/yosupo-lca-2.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/lca\"\n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\
    \nusing namespace std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\
    \nconst int64 infll = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct\
    \ IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    cout << fixed << setprecision(10);\n    cerr << fixed << setprecision(10);\n\
    \  }\n} iosetup;\n\ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream\
    \ &os, const pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return\
    \ os;\n}\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream\
    \ &is, pair< T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\n\
    template< typename T >\nostream &operator<<(ostream &os, const vector< T > &v)\
    \ {\n  for(int i = 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 !=\
    \ v.size() ? \" \" : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\n\
    istream &operator>>(istream &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n\
    \  return is;\n}\n\ntemplate< typename T1, typename T2 >\ninline bool chmax(T1\
    \ &a, T2 b) { return a < b && (a = b, true); }\n\ntemplate< typename T1, typename\
    \ T2 >\ninline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }\n\n\
    template< typename T = int64 >\nvector< T > make_v(size_t a) {\n  return vector<\
    \ T >(a);\n}\n\ntemplate< typename T, typename... Ts >\nauto make_v(size_t a,\
    \ Ts... ts) {\n  return vector< decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n\
    }\n\ntemplate< typename T, typename V >\ntypename enable_if< is_class< T >::value\
    \ == 0 >::type fill_v(T &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T,\
    \ typename V >\ntypename enable_if< is_class< T >::value != 0 >::type fill_v(T\
    \ &t, const V &v) {\n  for(auto &e : t) fill_v(e, v);\n}\n\ntemplate< typename\
    \ F >\nstruct FixPoint : F {\n  explicit FixPoint(F &&f) : F(forward< F >(f))\
    \ {}\n\n  template< typename... Args >\n  decltype(auto) operator()(Args &&...\
    \ args) const {\n    return F::operator()(*this, forward< Args >(args)...);\n\
    \  }\n};\n \ntemplate< typename F >\ninline decltype(auto) MFP(F &&f) {\n  return\
    \ FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-lca-2.test.cpp\"\
    \n\n#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
    \u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T =\
    \ int >\nstruct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
    \n  Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost),\
    \ idx(idx) {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename\
    \ T = int >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n\
    \  Graph() = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t\
    \ size() const {\n    return g.size();\n  }\n\n  void add_directed_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\
    \n  void add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from,\
    \ to, cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void\
    \ read(int M, int padding = -1, bool weighted = false, bool directed = false)\
    \ {\n    for(int i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n\
    \      a += padding;\n      b += padding;\n      T c = T(1);\n      if(weighted)\
    \ cin >> c;\n      if(directed) add_directed_edge(a, b, c);\n      else add_edge(a,\
    \ b, c);\n    }\n  }\n\n  inline vector< Edge< T > > &operator[](const int &k)\
    \ {\n    return g[k];\n  }\n\n  inline const vector< Edge< T > > &operator[](const\
    \ int &k) const {\n    return g[k];\n  }\n};\n\ntemplate< typename T = int >\n\
    using Edges = vector< Edge< T > >;\n#line 2 \"graph/tree/rmq-lowest-common-ancestor.hpp\"\
    \n\n#line 1 \"structure/others/sparse-table.hpp\"\n/**\n * @brief Sparse-Table(\u30B9\
    \u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/sparse-table.md\n */\n\
    template< typename T, typename F >\nstruct SparseTable {\n  F f;\n  vector< vector<\
    \ T > > st;\n  vector< int > lookup;\n\n  SparseTable() = default;\n\n  explicit\
    \ SparseTable(const vector< T > &v, const F &f) : f(f) {\n    const int n = (int)\
    \ v.size();\n    const int b = 32 - __builtin_clz(n);\n    st.assign(b, vector<\
    \ T >(n));\n    for(int i = 0; i < v.size(); i++) {\n      st[0][i] = v[i];\n\
    \    }\n    for(int i = 1; i < b; i++) {\n      for(int j = 0; j + (1 << i) <=\
    \ n; j++) {\n        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);\n\
    \      }\n    }\n    lookup.resize(v.size() + 1);\n    for(int i = 2; i < lookup.size();\
    \ i++) {\n      lookup[i] = lookup[i >> 1] + 1;\n    }\n  }\n\n  inline T fold(int\
    \ l, int r) const {\n    int b = lookup[r - l];\n    return f(st[b][l], st[b][r\
    \ - (1 << b)]);\n  }\n};\n\ntemplate< typename T, typename F >\nSparseTable< T,\
    \ F > get_sparse_table(const vector< T > &v, const F &f) {\n  return SparseTable<\
    \ T, F >(v, f);\n}\n#line 5 \"graph/tree/rmq-lowest-common-ancestor.hpp\"\n\n\
    /**\n * @brief RMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148\
    )\n * @docs docs/rmq-lowest-common-ancestor.md\n **/\ntemplate< typename T = int\
    \ >\nstruct RMQLowestCommonAncestor : Graph< T > {\npublic:\n  using Graph< T\
    \ >::Graph;\n  using Graph< T >::g;\n  using F = function< int(int, int) >;\n\n\
    \  void build(int root = 0) {\n    ord.reserve(g.size() * 2 - 1);\n    dep.reserve(g.size()\
    \ * 2 - 1);\n    in.resize(g.size());\n    dfs(root, -1, 0);\n    vector< int\
    \ > vs(g.size() * 2 - 1);\n    iota(begin(vs), end(vs), 0);\n    F f = [&](int\
    \ a, int b) { return dep[a] < dep[b] ? a : b; };\n    st = get_sparse_table(vs,\
    \ f);\n  }\n\n  int lca(int x, int y) const {\n    if(in[x] > in[y]) swap(x, y);\n\
    \    return x == y ? x : ord[st.fold(in[x], in[y])];\n  }\n\nprivate:\n  vector<\
    \ int > ord, dep, in;\n  SparseTable< int, F > st;\n\n  void dfs(int idx, int\
    \ par, int d) {\n    in[idx] = (int) ord.size();\n    ord.emplace_back(idx);\n\
    \    dep.emplace_back(d);\n    for(auto &to : g[idx]) {\n      if(to != par) {\n\
    \        dfs(to, idx, d + 1);\n        ord.emplace_back(idx);\n        dep.emplace_back(d);\n\
    \      }\n    }\n  }\n};\n#line 7 \"test/verify/yosupo-lca-2.test.cpp\"\n\n#line\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 10 \"test/verify/yosupo-lca-2.test.cpp\"\
    \n\n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  RMQLowestCommonAncestor< int > g(N);\n  for(int i = 1; i\
    \ < N; i++) {\n    int x;\n    in.read(x);\n    g.add_directed_edge(x, i);\n \
    \ }\n  g.build();\n  for(int i = 0; i < Q; i++) {\n    int u, v;\n    in.read(u,\
    \ v);\n    out.writeln(g.lca(u, v));\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../graph/graph-template.hpp\"\n#include \"../../graph/tree/rmq-lowest-common-ancestor.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  RMQLowestCommonAncestor< int > g(N);\n  for(int i = 1; i\
    \ < N; i++) {\n    int x;\n    in.read(x);\n    g.add_directed_edge(x, i);\n \
    \ }\n  g.build();\n  for(int i = 0; i < Q; i++) {\n    int u, v;\n    in.read(u,\
    \ v);\n    out.writeln(g.lca(u, v));\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/graph-template.hpp
  - graph/tree/rmq-lowest-common-ancestor.hpp
  - structure/others/sparse-table.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-lca-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-lca-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-lca-2.test.cpp
- /verify/test/verify/yosupo-lca-2.test.cpp.html
title: test/verify/yosupo-lca-2.test.cpp
---
