---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/offline-lca.hpp
    title: "Offline LCA(\u30AA\u30D5\u30E9\u30A4\u30F3\u6700\u5C0F\u5171\u901A\u7956\
      \u5148)"
  - icon: ':heavy_check_mark:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
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
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/verify/yosupo-lca-4.test.cpp\"\n#define PROBLEM \"\
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
    \ FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-lca-4.test.cpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 2 \"structure/union-find/union-find.hpp\"\
    \n\nstruct UnionFind {\n  vector< int > data;\n\n  UnionFind() = default;\n\n\
    \  explicit UnionFind(size_t sz) : data(sz, -1) {}\n\n  bool unite(int x, int\
    \ y) {\n    x = find(x), y = find(y);\n    if(x == y) return false;\n    if(data[x]\
    \ > data[y]) swap(x, y);\n    data[x] += data[y];\n    data[y] = x;\n    return\
    \ true;\n  }\n\n  int find(int k) {\n    if(data[k] < 0) return (k);\n    return\
    \ data[k] = find(data[k]);\n  }\n\n  int size(int k) {\n    return -data[find(k)];\n\
    \  }\n\n  bool same(int x, int y) {\n    return find(x) == find(y);\n  }\n\n \
    \ vector< vector< int > > groups() {\n    int n = (int) data.size();\n    vector<\
    \ vector< int > > ret(n);\n    for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n\
    \    }\n    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int >\
    \ &v) {\n      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n\
    #line 3 \"graph/tree/offline-lca.hpp\"\n\n/**\n * @brief Offline LCA(\u30AA\u30D5\
    \u30E9\u30A4\u30F3\u6700\u5C0F\u5171\u901A\u7956\u5148)\n **/\ntemplate< typename\
    \ T >\nvector< int > offline_lca(const Graph< T > &g, vector< pair< int, int >\
    \ > &qs, int root = 0) {\n  int n = (int) g.size();\n  UnionFind uf(n);\n  vector<\
    \ int > st(n), mark(n), ptr(n), ans(qs.size(), -1);\n  int top = 0;\n  st[top]\
    \ = root;\n  for(auto&[l, r]: qs) mark[l]++, mark[r]++;\n  vector< vector< pair<\
    \ int, int > > > q(n);\n  for(int i = 0; i < n; i++) {\n    q[i].reserve(mark[i]);\n\
    \    mark[i] = -1;\n    ptr[i] = (int) g[i].size();\n  }\n  for(int i = 0; i <\
    \ qs.size(); i++) {\n    q[qs[i].first].emplace_back(qs[i].second, i);\n    q[qs[i].second].emplace_back(qs[i].first,\
    \ i);\n  }\n  auto run = [&](int u) -> bool {\n    while(ptr[u]) {\n      int\
    \ v = g[u][--ptr[u]];\n      if(mark[v] == -1) {\n        st[++top] = v;\n   \
    \     return true;\n      }\n    }\n    return false;\n  };\n  while(~top) {\n\
    \    int u = st[top];\n    if(mark[u] == -1) {\n      mark[u] = u;\n    } else\
    \ {\n      uf.unite(u, g[u][ptr[u]]);\n      mark[uf.find(u)] = u;\n    }\n  \
    \  if(not run(u)) {\n      for(auto&[v, i]: q[u]) {\n        if(~mark[v] and ans[i]\
    \ == -1) {\n          ans[i] = mark[uf.find(v)];\n        }\n      }\n      --top;\n\
    \    }\n  }\n  return ans;\n}\n#line 6 \"test/verify/yosupo-lca-4.test.cpp\"\n\
    \n#line 1 \"other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-lca-4.test.cpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  Graph< int > g(N);\n  for(int i = 1; i < N; i++) {\n    int\
    \ x;\n    in.read(x);\n    g.add_directed_edge(x, i);\n  }\n  vector< pair< int,\
    \ int > > qs(Q);\n  for(auto&[l, r]: qs) in.read(l, r);\n  auto ans = offline_lca(g,\
    \ qs);\n  for(auto &p: ans) out.writeln(p);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../graph/tree/offline-lca.hpp\"\n\n#include \"../../other/scanner.hpp\"\
    \n#include \"../../other/printer.hpp\"\n\nint main() {\n  Scanner in(stdin);\n\
    \  Printer out(stdout);\n  int N, Q;\n  in.read(N, Q);\n  Graph< int > g(N);\n\
    \  for(int i = 1; i < N; i++) {\n    int x;\n    in.read(x);\n    g.add_directed_edge(x,\
    \ i);\n  }\n  vector< pair< int, int > > qs(Q);\n  for(auto&[l, r]: qs) in.read(l,\
    \ r);\n  auto ans = offline_lca(g, qs);\n  for(auto &p: ans) out.writeln(p);\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - graph/tree/offline-lca.hpp
  - graph/graph-template.hpp
  - structure/union-find/union-find.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-lca-4.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-lca-4.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-lca-4.test.cpp
- /verify/test/verify/yosupo-lca-4.test.cpp.html
title: test/verify/yosupo-lca-4.test.cpp
---
