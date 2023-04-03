---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/dynamic-point-add-rectangle-sum.hpp
    title: Dynamic Point Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: other/printer.hpp
    title: "Printer(\u9AD8\u901F\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/scanner.hpp
    title: "Scanner(\u9AD8\u901F\u5165\u529B)"
  - icon: ':heavy_check_mark:'
    path: other/static-point-add-rectangle-sum.hpp
    title: Static Point Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
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
  bundledCode: "#line 1 \"test/verify/yosupo-point-add-rectangle-sum-3.test.cpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-point-add-rectangle-sum-3.test.cpp\"\
    \n\n#line 1 \"structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief Binary-Indexed-Tree(BIT)\n\
    \ * @docs docs/binary-indexed-tree.md\n */\ntemplate< typename T >\nstruct BinaryIndexedTree\
    \ {\nprivate:\n  int n;\n  vector< T > data;\n\npublic:\n  BinaryIndexedTree()\
    \ = default;\n\n  explicit BinaryIndexedTree(int n) : n(n) {\n    data.assign(n\
    \ + 1, T());\n  }\n\n  explicit BinaryIndexedTree(const vector< T > &v) :\n  \
    \    BinaryIndexedTree((int) v.size()) {\n    build(v);\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int i = 1; i <=\
    \ n; i++) data[i] = v[i - 1];\n    for(int i = 1; i <= n; i++) {\n      int j\
    \ = i + (i & -i);\n      if(j <= n) data[j] += data[i];\n    }\n  }\n\n  void\
    \ apply(int k, const T &x) {\n    for(++k; k <= n; k += k & -k) data[k] += x;\n\
    \  }\n\n  T prod(int r) const {\n    T ret = T();\n    for(; r > 0; r -= r & -r)\
    \ ret += data[r];\n    return ret;\n  }\n\n  T prod(int l, int r) const {\n  \
    \  return prod(r) - prod(l);\n  }\n\n  int lower_bound(T x) const {\n    int i\
    \ = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n      if(i + k\
    \ <= n && data[i + k] < x) {\n        x -= data[i + k];\n        i += k;\n   \
    \   }\n    }\n    return i;\n  }\n\n  int upper_bound(T x) const {\n    int i\
    \ = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n      if(i + k\
    \ <= n && data[i + k] <= x) {\n        x -= data[i + k];\n        i += k;\n  \
    \    }\n    }\n    return i;\n  }\n};\n#line 2 \"other/static-point-add-rectangle-sum.hpp\"\
    \n\n/**\n * @brief Static Point Add Rectangle Sum\n */\ntemplate< typename T,\
    \ typename C >\nstruct StaticPointAddRectangleSum {\n  using BIT = BinaryIndexedTree<\
    \ C >;\n\n  static_assert(is_integral< T >::value, \"template parameter T must\
    \ be integral type\");\n\n  struct Point {\n    T x, y;\n    C w;\n  };\n\n  struct\
    \ Query {\n    T l, d, r, u;\n  };\n\n  vector< Point > points;\n  vector< Query\
    \ > queries;\n\n  StaticPointAddRectangleSum() = default;\n\n  StaticPointAddRectangleSum(int\
    \ n, int q) {\n    points.reserve(n);\n    queries.reserve(q);\n  }\n\n  void\
    \ add_point(T x, T y, C w) {\n    points.emplace_back(Point{x, y, w});\n  }\n\n\
    \  // tatal weight of [l, r) * [d, u) points\n  void add_query(T l, T d, T r,\
    \ T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n  vector< C > calculate_queries()\
    \ {\n    int n = (int) points.size();\n    int q = (int) queries.size();\n   \
    \ vector< C > ans(q);\n    if(points.empty() or queries.empty()) {\n      return\
    \ ans;\n    }\n    sort(points.begin(), points.end(), [](const Point &a, const\
    \ Point &b) {\n      return a.y < b.y;\n    });\n    vector< T > ys;\n    ys.reserve(n);\n\
    \    for(Point &p: points) {\n      if(ys.empty() or ys.back() != p.y) ys.emplace_back(p.y);\n\
    \      p.y = (int) ys.size() - 1;\n    }\n    ys.shrink_to_fit();\n\n    struct\
    \ Q {\n      T x;\n      int d, u;\n      bool type;\n      int idx;\n    };\n\
    \    vector< Q > qs;\n    qs.reserve(q + q);\n    for(int i = 0; i < q; i++) {\n\
    \      auto &query = queries[i];\n      int d = lower_bound(ys.begin(), ys.end(),\
    \ query.d) - ys.begin();\n      int u = lower_bound(ys.begin(), ys.end(), query.u)\
    \ - ys.begin();\n      qs.emplace_back(Q{query.l, d, u, false, i});\n      qs.emplace_back(Q{query.r,\
    \ d, u, true, i});\n    }\n    sort(points.begin(), points.end(), [](const Point\
    \ &a, const Point &b) {\n      return a.x < b.x;\n    });\n    sort(qs.begin(),\
    \ qs.end(), [](const Q &a, const Q &b) {\n      return a.x < b.x;\n    });\n \
    \   int j = 0;\n    BIT bit(ys.size());\n    for(auto &query: qs) {\n      while(j\
    \ < n and points[j].x < query.x) {\n        bit.apply(points[j].y, points[j].w);\n\
    \        ++j;\n      }\n      if(query.type) ans[query.idx] += bit.prod(query.d,\
    \ query.u);\n      else ans[query.idx] -= bit.prod(query.d, query.u);\n    }\n\
    \    return ans;\n  }\n};\n#line 2 \"other/dynamic-point-add-rectangle-sum.hpp\"\
    \n\n/**\n * @brief Dynamic Point Add Rectangle Sum\n */\ntemplate< typename T,\
    \ typename C >\nstruct DynamicPointAddRectangleSum {\n  using StaticRectangleSumSolver\
    \ = StaticPointAddRectangleSum< T, C >;\n\n  static_assert(is_integral< T >::value,\
    \ \"template parameter T must be integral type\");\n\n  struct Point {\n    T\
    \ x, y;\n    C w;\n  };\n\n  struct Query {\n    T l, d, r, u;\n  };\n\n  vector<\
    \ variant< Point, Query > > queries;\n\n  DynamicPointAddRectangleSum() = default;\n\
    \n  DynamicPointAddRectangleSum(int q) {\n    queries.reserve(q);\n  }\n\n  void\
    \ add_point(T x, T y, C w) {\n    queries.emplace_back(Point{x, y, w});\n  }\n\
    \n  // tatal weight of [l, r) * [d, u) points\n  void add_query(T l, T d, T r,\
    \ T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n  vector< C > calculate_queries()\
    \ {\n    int q = (int) queries.size();\n    vector< int > rev(q);\n    int sz\
    \ = 0;\n    for(int i = 0; i < q; i++) {\n      if(holds_alternative< Query >(queries[i]))\
    \ {\n        rev[i] = sz++;\n      }\n    }\n    vector< C > ans(sz);\n    queue<\
    \ pair< int, int > > range;\n    range.emplace(0, q);\n    while(not range.empty())\
    \ {\n      auto[l, r] = range.front();\n      range.pop();\n      int m = (l +\
    \ r) >> 1;\n      StaticRectangleSumSolver solver;\n      for(int k = l; k < m;\
    \ k++) {\n        if(holds_alternative< Point >(queries[k])) {\n          auto\
    \ &point = get< Point >(queries[k]);\n          solver.add_point(point.x, point.y,\
    \ point.w);\n        }\n      }\n      for(int k = m; k < r; k++) {\n        if(holds_alternative<\
    \ Query >(queries[k])) {\n          auto &query = get< Query >(queries[k]);\n\
    \          solver.add_query(query.l, query.d, query.r, query.u);\n        }\n\
    \      }\n      auto sub = solver.calculate_queries();\n      for(int k = m, t\
    \ = 0; k < r; k++) {\n        if(holds_alternative< Query >(queries[k])) {\n \
    \         ans[rev[k]] += sub[t++];\n        }\n      }\n      if(l + 1 < m) range.emplace(l,\
    \ m);\n      if(m + 1 < r) range.emplace(m, r);\n    }\n    return ans;\n  }\n\
    };\n#line 6 \"test/verify/yosupo-point-add-rectangle-sum-3.test.cpp\"\n\n#line\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-point-add-rectangle-sum-3.test.cpp\"\
    \n\nint main() {\n  int N, Q;\n  Scanner in(stdin);\n  Printer out(stdout);\n\
    \  in.read(N, Q);\n  DynamicPointAddRectangleSum< int, int64 > dpars(N + Q);\n\
    \  for(int i = 0; i < N; i++) {\n    int x, y, z;\n    in.read(x, y, z);\n   \
    \ dpars.add_point(x, y, z);\n  }\n  for(int i = 0; i < Q; i++) {\n    int t;\n\
    \    in.read(t);\n    if(t == 0) {\n      int x, y, z;\n      in.read(x, y, z);\n\
    \      dpars.add_point(x, y, z);\n    } else {\n      int l, d, r, u;\n      in.read(l,\
    \ d, r, u);\n      dpars.add_query(l, d, r, u);\n    }\n  }\n  for(auto &&ans:\
    \ dpars.calculate_queries()) {\n    out.writeln(ans);\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../other/dynamic-point-add-rectangle-sum.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\nint main() {\n  int N, Q;\n  Scanner in(stdin);\n  Printer out(stdout);\n\
    \  in.read(N, Q);\n  DynamicPointAddRectangleSum< int, int64 > dpars(N + Q);\n\
    \  for(int i = 0; i < N; i++) {\n    int x, y, z;\n    in.read(x, y, z);\n   \
    \ dpars.add_point(x, y, z);\n  }\n  for(int i = 0; i < Q; i++) {\n    int t;\n\
    \    in.read(t);\n    if(t == 0) {\n      int x, y, z;\n      in.read(x, y, z);\n\
    \      dpars.add_point(x, y, z);\n    } else {\n      int l, d, r, u;\n      in.read(l,\
    \ d, r, u);\n      dpars.add_query(l, d, r, u);\n    }\n  }\n  for(auto &&ans:\
    \ dpars.calculate_queries()) {\n    out.writeln(ans);\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - other/dynamic-point-add-rectangle-sum.hpp
  - other/static-point-add-rectangle-sum.hpp
  - structure/others/binary-indexed-tree.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
- /verify/test/verify/yosupo-point-add-rectangle-sum-3.test.cpp.html
title: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
---
