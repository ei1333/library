---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':heavy_check_mark:'
    path: structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
    title: "Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u53162\u6B21\u5143\
      \u5EA7\u5727BIT)"
  - icon: ':heavy_check_mark:'
    path: structure/others/abstract-binary-indexed-tree.hpp
    title: "Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)"
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"test/verify/yosupo-point-add-rectangle-sum-2.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-point-add-rectangle-sum-2.test.cpp\"\
    \n\n#line 1 \"structure/others/abstract-binary-indexed-tree.hpp\"\n/**\n * @brief\
    \ Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)\n */\ntemplate< typename\
    \ T, typename F >\nstruct AbstractBinaryIndexedTree {\nprivate:\n  int n;\n  vector<\
    \ T > data;\n  const F f;\n  const T e;\n\npublic:\n  AbstractBinaryIndexedTree()\
    \ = default;\n\n  explicit AbstractBinaryIndexedTree(int n, const F f, const T\
    \ &e) : n(n), f(f), e(e) {\n    data.assign(n + 1, e);\n  }\n\n  explicit AbstractBinaryIndexedTree(const\
    \ vector< T > &v, const F f, const T &e) :\n      AbstractBinaryIndexedTree((int)\
    \ v.size(), f, e) {\n    build(v);\n  }\n\n  void build(const vector< T > &v)\
    \ {\n    assert(n == (int) v.size());\n    for(int i = 1; i <= n; i++) data[i]\
    \ = v[i - 1];\n    for(int i = 1; i <= n; i++) {\n      int j = i + (i & -i);\n\
    \      if(j <= n) data[j] = f(data[j], data[i]);\n    }\n  }\n\n  void apply(int\
    \ k, const T &x) {\n    for(++k; k <= n; k += k & -k) data[k] = f(data[k], x);\n\
    \  }\n\n  T prod(int r) const {\n    T ret{e};\n    for(; r > 0; r -= r & -r)\
    \ ret = f(ret, data[r]);\n    return ret;\n  }\n};\n\ntemplate< typename T, typename\
    \ F >\nAbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(int\
    \ n, const F &f, const T &e) {\n  return AbstractBinaryIndexedTree{n, f, e};\n\
    }\n\ntemplate< typename T, typename F >\nAbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(const\
    \ vector< T > &v, const F &f, const T &e) {\n  return AbstractBinaryIndexedTree{v,\
    \ f, e};\n}\n#line 2 \"structure/others/abstract-2d-binary-indexed-tree-compressed.hpp\"\
    \n\n/**\n * @brief Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u5316\
    2\u6B21\u5143\u5EA7\u5727BIT)\n */\ntemplate< typename T, typename F >\nstruct\
    \ Abstract2DBinaryIndexedTreeCompressed {\nprivate:\n  int n;\n  vector< AbstractBinaryIndexedTree<\
    \ T, F > > data;\n  const F f;\n  const T e;\n  vector< int > hs;\n  vector< vector<\
    \ int > > beet;\npublic:\n  Abstract2DBinaryIndexedTreeCompressed(const vector<\
    \ int > &hs, const F f, const T &e) :\n      n((int) hs.size()), hs(hs), f(f),\
    \ e(e) {\n    vector< int > ord(n);\n    iota(begin(ord), end(ord), 0);\n    sort(begin(ord),\
    \ end(ord), [&](int a, int b) {\n      return hs[a] < hs[b];\n    });\n    beet.resize(n\
    \ + 1);\n    for(auto &&i: ord) {\n      for(int k = i + 1; k <= n; k += k & -k)\
    \ {\n        beet[k].emplace_back(hs[i]);\n      }\n    }\n    data.reserve(n\
    \ + 1);\n    for(int k = 0; k <= n; k++) {\n      beet[k].erase(unique(begin(beet[k]),\
    \ end(beet[k])), end(beet[k]));\n      data.emplace_back((int) beet[k].size(),\
    \ f, e);\n    }\n  }\n\n  void apply(int k1, const T &x) {\n    int k2 = hs[k1];\n\
    \    for(++k1; k1 <= n; k1 += k1 & -k1) {\n      int p = lower_bound(begin(beet[k1]),\
    \ end(beet[k1]), k2) - begin(beet[k1]);\n      data[k1].apply(p, x);\n    }\n\
    \  }\n\n  T prod(int r1, int r2) const {\n    T ret{e};\n    for(; r1 > 0; r1\
    \ -= r1 & -r1) {\n      int p = lower_bound(begin(beet[r1]), end(beet[r1]), r2)\
    \ - begin(beet[r1]);\n      ret = f(ret, data[r1].prod(p));\n    }\n    return\
    \ ret;\n  }\n};\n\ntemplate< typename T, typename F >\nAbstract2DBinaryIndexedTreeCompressed<\
    \ T, F > get_abstract_2d_binary_indexed_tree_compressed(const vector< int > &hs,\
    \ const F &f, const T &e) {\n  return Abstract2DBinaryIndexedTreeCompressed{hs,\
    \ f, e};\n}\n#line 6 \"test/verify/yosupo-point-add-rectangle-sum-2.test.cpp\"\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-point-add-rectangle-sum-2.test.cpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > X(N), Y(N), W(N);\n  vector< pair< int, int\
    \ > > ps(N);\n  for(int i = 0; i < N; i++) {\n    in.read(X[i], Y[i], W[i]);\n\
    \    ps[i] = {X[i], Y[i]};\n  }\n  vector< int > A(Q), B(Q), C(Q), D(Q), E(Q);\n\
    \  for(int i = 0; i < Q; i++) {\n    in.read(A[i], B[i], C[i], D[i]);\n    if(A[i]\
    \ == 0) ps.emplace_back(B[i], C[i]);\n    else in.read(E[i]);\n  }\n  sort(begin(ps),\
    \ end(ps));\n  ps.erase(unique(begin(ps), end(ps)), end(ps));\n  vector< int >\
    \ H(ps.size());\n  for(int i = 0; i < N; i++) {\n    X[i] = lower_bound(begin(ps),\
    \ end(ps), make_pair(X[i], Y[i])) - begin(ps);\n  }\n  for(int i = 0; i < Q; i++)\
    \ {\n    if(A[i] == 0) {\n      B[i] = lower_bound(begin(ps), end(ps), make_pair(B[i],\
    \ C[i])) - begin(ps);\n    } else {\n      B[i] = lower_bound(begin(ps), end(ps),\
    \ make_pair(B[i], -inf)) - begin(ps);\n      D[i] = lower_bound(begin(ps), end(ps),\
    \ make_pair(D[i], -inf)) - begin(ps);\n    }\n  }\n  for(int i = 0; i < (int)\
    \ ps.size(); i++) {\n    H[i] = ps[i].second;\n  }\n  auto f = [](int64 a, int64\
    \ b) { return a + b; };\n  auto bit = get_abstract_2d_binary_indexed_tree_compressed(H,\
    \ f, 0LL);\n  for(int i = 0; i < N; i++) {\n    bit.apply(X[i], W[i]);\n  }\n\
    \  for(int i = 0; i < Q; i++) {\n    if(A[i] == 0) {\n      bit.apply(B[i], D[i]);\n\
    \    } else {\n      out.writeln(bit.prod(D[i], E[i]) - bit.prod(D[i], C[i]) -\
    \ bit.prod(B[i], E[i]) + bit.prod(B[i], C[i]));\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/others/abstract-2d-binary-indexed-tree-compressed.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > X(N), Y(N), W(N);\n  vector< pair< int, int\
    \ > > ps(N);\n  for(int i = 0; i < N; i++) {\n    in.read(X[i], Y[i], W[i]);\n\
    \    ps[i] = {X[i], Y[i]};\n  }\n  vector< int > A(Q), B(Q), C(Q), D(Q), E(Q);\n\
    \  for(int i = 0; i < Q; i++) {\n    in.read(A[i], B[i], C[i], D[i]);\n    if(A[i]\
    \ == 0) ps.emplace_back(B[i], C[i]);\n    else in.read(E[i]);\n  }\n  sort(begin(ps),\
    \ end(ps));\n  ps.erase(unique(begin(ps), end(ps)), end(ps));\n  vector< int >\
    \ H(ps.size());\n  for(int i = 0; i < N; i++) {\n    X[i] = lower_bound(begin(ps),\
    \ end(ps), make_pair(X[i], Y[i])) - begin(ps);\n  }\n  for(int i = 0; i < Q; i++)\
    \ {\n    if(A[i] == 0) {\n      B[i] = lower_bound(begin(ps), end(ps), make_pair(B[i],\
    \ C[i])) - begin(ps);\n    } else {\n      B[i] = lower_bound(begin(ps), end(ps),\
    \ make_pair(B[i], -inf)) - begin(ps);\n      D[i] = lower_bound(begin(ps), end(ps),\
    \ make_pair(D[i], -inf)) - begin(ps);\n    }\n  }\n  for(int i = 0; i < (int)\
    \ ps.size(); i++) {\n    H[i] = ps[i].second;\n  }\n  auto f = [](int64 a, int64\
    \ b) { return a + b; };\n  auto bit = get_abstract_2d_binary_indexed_tree_compressed(H,\
    \ f, 0LL);\n  for(int i = 0; i < N; i++) {\n    bit.apply(X[i], W[i]);\n  }\n\
    \  for(int i = 0; i < Q; i++) {\n    if(A[i] == 0) {\n      bit.apply(B[i], D[i]);\n\
    \    } else {\n      out.writeln(bit.prod(D[i], E[i]) - bit.prod(D[i], C[i]) -\
    \ bit.prod(B[i], E[i]) + bit.prod(B[i], C[i]));\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
  - structure/others/abstract-binary-indexed-tree.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:27:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
- /verify/test/verify/yosupo-point-add-rectangle-sum-2.test.cpp.html
title: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
---
