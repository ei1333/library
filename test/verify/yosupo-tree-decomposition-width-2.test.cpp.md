---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/others/tree-decomposition-width-2.hpp
    title: "Tree Decomposition Width 2(\u6728\u5E452\u306E\u6728\u5206\u89E3)"
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
    PROBLEM: https://judge.yosupo.jp/problem/tree_decomposition_width_2
    links:
    - https://judge.yosupo.jp/problem/tree_decomposition_width_2
  bundledCode: "#line 1 \"test/verify/yosupo-tree-decomposition-width-2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_decomposition_width_2\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-tree-decomposition-width-2.test.cpp\"\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 7 \"test/verify/yosupo-tree-decomposition-width-2.test.cpp\"\
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
    \ 9 \"test/verify/yosupo-tree-decomposition-width-2.test.cpp\"\n\n#line 2 \"graph/others/tree-decomposition-width-2.hpp\"\
    \n\n/**\n * @brief Tree Decomposition Width 2(\u6728\u5E452\u306E\u6728\u5206\u89E3\
    )\n * @see https://ei1333.hateblo.jp/entry/2020/02/12/150319\n * @docs docs/tree-decomposition-width-2.md\n\
    \ */\nstruct DecompNode {\n  vector< int > bag, child;\n\n  DecompNode() = default;\n\
    };\n\nstruct TreeDecompositionWidth2 {\n\n  vector< vector< int > > g;\n\n  explicit\
    \ TreeDecompositionWidth2(int V) : g(V) {}\n\n  void add_edge(int a, int b) {\n\
    \    g[a].emplace_back(b);\n    g[b].emplace_back(a);\n  }\n\n  vector< DecompNode\
    \ > build() {\n    const int N = (int) g.size();\n\n    vector< int > used(N,\
    \ -1), deg(N);\n    queue< int > que;\n    for(int i = 0; i < N; i++) {\n    \
    \  deg[i] = (int) g[i].size();\n      if(deg[i] <= 2) que.emplace(i);\n    }\n\
    \n    vector< set< int > > exists(N);\n    for(int i = 0; i < N; i++) {\n    \
    \  for(auto &j : g[i]) {\n        if(i < j) exists[i].emplace(j);\n      }\n \
    \   }\n\n    vector< DecompNode > ret;\n    ret.emplace_back();\n    while(!que.empty())\
    \ {\n      int idx = que.front();\n      que.pop();\n      if(deg[idx] > 2 ||\
    \ used[idx] != -1) continue;\n\n      DecompNode r;\n      r.bag.emplace_back(idx);\n\
    \      int u = -1, v = -1;\n      for(auto &to : g[idx]) {\n        if(used[to]\
    \ == -1) {\n          (u == -1 ? u : v) = to;\n          r.bag.emplace_back(to);\n\
    \        } else if(used[to] >= 0) {\n          r.child.emplace_back(used[to]);\n\
    \          used[to] = -2;\n        }\n      }\n\n      if(u == -1) {\n\n     \
    \ } else if(v == -1) {\n        --deg[u];\n      } else {\n        if(u > v) swap(u,\
    \ v);\n        if(!exists[u].count(v)) {\n          g[u].emplace_back(v);\n  \
    \        g[v].emplace_back(u);\n          exists[u].emplace(v);\n        } else\
    \ {\n          --deg[u];\n          --deg[v];\n        }\n      }\n\n      for(auto\
    \ &to : g[idx]) {\n        if(deg[to] <= 2) que.emplace(to);\n      }\n\n    \
    \  used[idx] = (int) ret.size();\n      deg[idx] = 0;\n      ret.emplace_back(r);\n\
    \    }\n    for(int i = 0; i < N; i++) {\n      if(deg[i] > 0) return {};\n  \
    \  }\n    ret.front() = ret.back();\n    ret.pop_back();\n    return ret;\n  }\n\
    };\n\n\nvoid to_nice(vector< DecompNode > &g, int root = 0) {\n\n  for(auto &p\
    \ : g) {\n    sort(p.bag.begin(), p.bag.end());\n  }\n\n  stack< int > st;\n \
    \ st.emplace(root);\n\n  while(!st.empty()) {\n    int idx = st.top();\n    st.pop();\n\
    \n    // join\n    while(g[idx].child.size() > 2) {\n      DecompNode r;\n   \
    \   r.child.resize(2);\n      r.child[0] = g[idx].child.back();\n      g[idx].child.pop_back();\n\
    \      r.child[1] = g[idx].child.back();\n      g[idx].child.pop_back();\n   \
    \   r.bag = g[idx].bag;\n      g[idx].child.emplace_back((int) g.size());\n  \
    \    g.emplace_back(r);\n    }\n\n    if(g[idx].child.size() == 2) {\n      for(auto\
    \ &ch : g[idx].child) {\n        if(g[ch].bag != g[idx].bag) {\n          DecompNode\
    \ r;\n          r.child = {ch};\n          r.bag = g[idx].bag;\n          ch =\
    \ (int) g.size();\n          g.emplace_back(r);\n        }\n      }\n    }\n\n\
    \    // introduce / forget\n    if(g[idx].child.size() == 1) {\n      int &ch\
    \ = g[idx].child[0];\n\n      vector< int > latte, malta;\n      set_difference(g[idx].bag.begin(),\
    \ g[idx].bag.end(),\n                     g[ch].bag.begin(), g[ch].bag.end(),\n\
    \                     back_inserter(latte));\n      set_difference(g[ch].bag.begin(),\
    \ g[ch].bag.end(),\n                     g[idx].bag.begin(), g[idx].bag.end(),\n\
    \                     back_inserter(malta));\n      if(latte.size() + malta.size()\
    \ > 1) {\n        DecompNode r;\n        r.child = {ch};\n        r.bag = g[idx].bag;\n\
    \        if(!latte.empty()) {\n          r.bag.erase(find(r.bag.begin(), r.bag.end(),\
    \ latte.back()));\n        } else {\n          r.bag.emplace_back(malta.back());\n\
    \        }\n        ch = (int) g.size();\n        g.emplace_back(r);\n      }\n\
    \    }\n\n    // leaf\n    if(g[idx].child.empty()) {\n      if(g[idx].bag.size()\
    \ > 1) {\n        DecompNode r;\n        r.bag = g[idx].bag;\n        r.bag.pop_back();\n\
    \        g[idx].child.emplace_back((int) g.size());\n        g.emplace_back(r);\n\
    \      }\n    }\n\n    for(auto &ch : g[idx].child) {\n      st.emplace(ch);\n\
    \    }\n  }\n}\n#line 11 \"test/verify/yosupo-tree-decomposition-width-2.test.cpp\"\
    \n\nint main() {\n  string x;\n  int N, M;\n  Scanner pin(stdin);\n  Printer pout(stdout);\n\
    \  pin.read(x, x, N, M);\n  vector< int > A(M), B(M);\n  UnionFind uf(N);\n  for(int\
    \ i = 0; i < M; i++) {\n    pin.read(A[i], B[i]);\n    --A[i], --B[i];\n    uf.unite(A[i],\
    \ B[i]);\n  }\n  int root = -1;\n  for(int i = 0; i < N; i++) {\n    if(uf.find(i)\
    \ == i) {\n      if(root == -1) {\n        root = i;\n      } else {\n       \
    \ A.emplace_back(root);\n        B.emplace_back(i);\n      }\n    }\n  }\n  TreeDecompositionWidth2\
    \ td(N);\n  for(size_t i = 0; i < A.size(); i++) {\n    td.add_edge(A[i], B[i]);\n\
    \  }\n  auto tap = td.build();\n  if(tap.empty()) {\n    pout.writeln(\"-1\");\n\
    \    return 0;\n  }\n  pout.writeln(\"s\", \"td\", tap.size(), 2, N);\n  for(size_t\
    \ i = 0; i < tap.size(); i++) {\n    for(auto &t : tap[i].bag) ++t;\n    pout.writeln(\"\
    b\", i + 1, tap[i].bag);\n  }\n  for(size_t i = 0; i < tap.size(); i++) {\n  \
    \  for(auto &t : tap[i].child) pout.writeln(i + 1, t + 1);\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_decomposition_width_2\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../other/scanner.hpp\"\
    \n#include \"../../other/printer.hpp\"\n\n#include \"../../structure/union-find/union-find.hpp\"\
    \n\n#include \"../../graph/others/tree-decomposition-width-2.hpp\"\n\nint main()\
    \ {\n  string x;\n  int N, M;\n  Scanner pin(stdin);\n  Printer pout(stdout);\n\
    \  pin.read(x, x, N, M);\n  vector< int > A(M), B(M);\n  UnionFind uf(N);\n  for(int\
    \ i = 0; i < M; i++) {\n    pin.read(A[i], B[i]);\n    --A[i], --B[i];\n    uf.unite(A[i],\
    \ B[i]);\n  }\n  int root = -1;\n  for(int i = 0; i < N; i++) {\n    if(uf.find(i)\
    \ == i) {\n      if(root == -1) {\n        root = i;\n      } else {\n       \
    \ A.emplace_back(root);\n        B.emplace_back(i);\n      }\n    }\n  }\n  TreeDecompositionWidth2\
    \ td(N);\n  for(size_t i = 0; i < A.size(); i++) {\n    td.add_edge(A[i], B[i]);\n\
    \  }\n  auto tap = td.build();\n  if(tap.empty()) {\n    pout.writeln(\"-1\");\n\
    \    return 0;\n  }\n  pout.writeln(\"s\", \"td\", tap.size(), 2, N);\n  for(size_t\
    \ i = 0; i < tap.size(); i++) {\n    for(auto &t : tap[i].bag) ++t;\n    pout.writeln(\"\
    b\", i + 1, tap[i].bag);\n  }\n  for(size_t i = 0; i < tap.size(); i++) {\n  \
    \  for(auto &t : tap[i].child) pout.writeln(i + 1, t + 1);\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - other/scanner.hpp
  - other/printer.hpp
  - structure/union-find/union-find.hpp
  - graph/others/tree-decomposition-width-2.hpp
  isVerificationFile: true
  path: test/verify/yosupo-tree-decomposition-width-2.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-tree-decomposition-width-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-tree-decomposition-width-2.test.cpp
- /verify/test/verify/yosupo-tree-decomposition-width-2.test.cpp.html
title: test/verify/yosupo-tree-decomposition-width-2.test.cpp
---
