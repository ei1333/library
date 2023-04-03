---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/strongly-connected-components.hpp
    title: "Strongly Connected Components(\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\
      )"
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  - icon: ':heavy_check_mark:'
    path: graph/others/two-satisfiability.hpp
    title: Two Satisfiability(2-SAT)
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
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"test/verify/yosupo-two-sat.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/two_sat\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-two-sat.test.cpp\"\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 7 \"test/verify/yosupo-two-sat.test.cpp\"\
    \n\n#line 2 \"graph/others/two-satisfiability.hpp\"\n\n#line 2 \"graph/connected-components/strongly-connected-components.hpp\"\
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
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/connected-components/strongly-connected-components.hpp\"\
    \n\ntemplate< typename T = int >\nstruct StronglyConnectedComponents : Graph<\
    \ T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > comp;\n  Graph< T > dag;\n  vector< vector< int > > group;\n\n  void build()\
    \ {\n    rg = Graph< T >(g.size());\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      for(auto &e : g[i]) {\n        rg.add_directed_edge(e.to, e.from, e.cost);\n\
    \      }\n    }\n    comp.assign(g.size(), -1);\n    used.assign(g.size(), 0);\n\
    \    for(size_t i = 0; i < g.size(); i++) dfs(i);\n    reverse(begin(order), end(order));\n\
    \    int ptr = 0;\n    for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;\n\
    \    dag = Graph< T >(ptr);\n    for(size_t i = 0; i < g.size(); i++) {\n    \
    \  for(auto &e : g[i]) {\n        int x = comp[e.from], y = comp[e.to];\n    \
    \    if(x == y) continue;\n        dag.add_directed_edge(x, y, e.cost);\n    \
    \  }\n    }\n    group.resize(ptr);\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      group[comp[i]].emplace_back(i);\n    }\n  }\n\n  int operator[](int\
    \ k) const {\n    return comp[k];\n  }\n\nprivate:\n  vector< int > order, used;\n\
    \  Graph< T > rg;\n\n  void dfs(int idx) {\n    if(exchange(used[idx], true))\
    \ return;\n    for(auto &to : g[idx]) dfs(to);\n    order.push_back(idx);\n  }\n\
    \n  void rdfs(int idx, int cnt) {\n    if(comp[idx] != -1) return;\n    comp[idx]\
    \ = cnt;\n    for(auto &to : rg.g[idx]) rdfs(to, cnt);\n  }\n};\n#line 4 \"graph/others/two-satisfiability.hpp\"\
    \n\n/**\n * @brief Two Satisfiability(2-SAT)\n * @docs docs/two-satisfiability.md\n\
    \ */\nstruct TwoSatisfiability : StronglyConnectedComponents< bool > {\npublic:\n\
    \  using StronglyConnectedComponents< bool >::g;\n  using StronglyConnectedComponents<\
    \ bool >::comp;\n  using StronglyConnectedComponents< bool >::add_edge;\n  size_t\
    \ sz;\n\n  explicit TwoSatisfiability(size_t v) : StronglyConnectedComponents<\
    \ bool >(v + v), sz(v) {}\n\n  void add_if(int u, int v) {\n    // u -> v <=>\
    \ !v -> !u\n    add_directed_edge(u, v);\n    add_directed_edge(rev(v), rev(u));\n\
    \  }\n\n  void add_or(int u, int v) {\n    // u or v <=> !u -> v\n    add_if(rev(u),\
    \ v);\n  }\n\n  void add_nand(int u, int v) {\n    // u nand v <=> u -> !v\n \
    \   add_if(u, rev(v));\n  }\n\n  void set_true(int u) {\n    // u <=> !u -> u\n\
    \    add_directed_edge(rev(u), u);\n  }\n\n  void set_false(int u) {\n    // !u\
    \ <=> u -> !u\n    add_directed_edge(u, rev(u));\n  }\n\n  inline int rev(int\
    \ x) {\n    if(x >= (int)sz) return x - sz;\n    return x + sz;\n  }\n\n  vector<\
    \ int > solve() {\n    StronglyConnectedComponents< bool >::build();\n    vector<\
    \ int > ret(sz);\n    for(size_t i = 0; i < sz; i++) {\n      if(comp[i] == comp[rev(i)])\
    \ return {};\n      ret[i] = comp[i] > comp[rev(i)];\n    }\n    return ret;\n\
    \  }\n};\n#line 9 \"test/verify/yosupo-two-sat.test.cpp\"\n\nint main() {\n  Scanner\
    \ input(stdin);\n  Printer output(stdout);\n\n  string s;\n  int N, M;\n  input.read(s,\
    \ s, N, M);\n  TwoSatisfiability two(N);\n  for(int i = 0; i < M; i++) {\n   \
    \ int a, b, c;\n    input.read(a, b, c);\n    if(a < 0) a = two.rev(-a - 1);\n\
    \    else --a;\n    if(b < 0) b = two.rev(-b - 1);\n    else --b;\n    two.add_or(a,\
    \ b);\n  }\n  auto ret = two.solve();\n  if(ret.empty()) {\n    output.writeln(\"\
    s UNSATISFIABLE\");\n  } else {\n    output.writeln(\"s SATISFIABLE\");\n    output.write(\"\
    v \");\n    for(size_t i = 0; i < ret.size(); i++) {\n      if(ret[i]) ret[i]\
    \ = i + 1;\n      else ret[i] = -i - 1;\n    }\n    output.write(ret);\n    output.writeln(\"\
    \ 0\");\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n\n#include \"\
    ../../template/template.hpp\"\n\n#include \"../../other/scanner.hpp\"\n#include\
    \ \"../../other/printer.hpp\"\n\n#include \"../../graph/others/two-satisfiability.hpp\"\
    \n\nint main() {\n  Scanner input(stdin);\n  Printer output(stdout);\n\n  string\
    \ s;\n  int N, M;\n  input.read(s, s, N, M);\n  TwoSatisfiability two(N);\n  for(int\
    \ i = 0; i < M; i++) {\n    int a, b, c;\n    input.read(a, b, c);\n    if(a <\
    \ 0) a = two.rev(-a - 1);\n    else --a;\n    if(b < 0) b = two.rev(-b - 1);\n\
    \    else --b;\n    two.add_or(a, b);\n  }\n  auto ret = two.solve();\n  if(ret.empty())\
    \ {\n    output.writeln(\"s UNSATISFIABLE\");\n  } else {\n    output.writeln(\"\
    s SATISFIABLE\");\n    output.write(\"v \");\n    for(size_t i = 0; i < ret.size();\
    \ i++) {\n      if(ret[i]) ret[i] = i + 1;\n      else ret[i] = -i - 1;\n    }\n\
    \    output.write(ret);\n    output.writeln(\" 0\");\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - other/scanner.hpp
  - other/printer.hpp
  - graph/others/two-satisfiability.hpp
  - graph/connected-components/strongly-connected-components.hpp
  - graph/graph-template.hpp
  isVerificationFile: true
  path: test/verify/yosupo-two-sat.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-two-sat.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-two-sat.test.cpp
- /verify/test/verify/yosupo-two-sat.test.cpp.html
title: test/verify/yosupo-two-sat.test.cpp
---
