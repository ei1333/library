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
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/succinct-indexable-dictionary.hpp
    title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
    title: Wavelet Matrix Point Add Rectangle Sum
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
  bundledCode: "#line 1 \"test/verify/yosupo-point-add-rectangle-sum.test.cpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-point-add-rectangle-sum.test.cpp\"\
    \n\n#line 1 \"structure/wavelet/succinct-indexable-dictionary.hpp\"\n/**\n * @brief\
    \ Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)\n */\nstruct SuccinctIndexableDictionary\
    \ {\n  size_t length;\n  size_t blocks;\n  vector< unsigned > bit, sum;\n\n  SuccinctIndexableDictionary()\
    \ = default;\n\n  SuccinctIndexableDictionary(size_t length) : length(length),\
    \ blocks((length + 31) >> 5) {\n    bit.assign(blocks, 0U);\n    sum.assign(blocks,\
    \ 0U);\n  }\n\n  void set(int k) {\n    bit[k >> 5] |= 1U << (k & 31);\n  }\n\n\
    \  void build() {\n    sum[0] = 0U;\n    for(int i = 1; i < blocks; i++) {\n \
    \     sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);\n    }\n  }\n\n  bool\
    \ operator[](int k) {\n    return (bool((bit[k >> 5] >> (k & 31)) & 1));\n  }\n\
    \n  int rank(int k) {\n    return (sum[k >> 5] + __builtin_popcount(bit[k >> 5]\
    \ & ((1U << (k & 31)) - 1)));\n  }\n\n  int rank(bool val, int k) {\n    return\
    \ (val ? rank(k) : k - rank(k));\n  }\n};\n#line 1 \"structure/others/binary-indexed-tree.hpp\"\
    \n/**\n * @brief Binary-Indexed-Tree(BIT)\n * @docs docs/binary-indexed-tree.md\n\
    \ */\ntemplate< typename T >\nstruct BinaryIndexedTree {\nprivate:\n  int n;\n\
    \  vector< T > data;\n\npublic:\n  BinaryIndexedTree() = default;\n\n  explicit\
    \ BinaryIndexedTree(int n) : n(n) {\n    data.assign(n + 1, T());\n  }\n\n  explicit\
    \ BinaryIndexedTree(const vector< T > &v) :\n      BinaryIndexedTree((int) v.size())\
    \ {\n    build(v);\n  }\n\n  void build(const vector< T > &v) {\n    assert(n\
    \ == (int) v.size());\n    for(int i = 1; i <= n; i++) data[i] = v[i - 1];\n \
    \   for(int i = 1; i <= n; i++) {\n      int j = i + (i & -i);\n      if(j <=\
    \ n) data[j] += data[i];\n    }\n  }\n\n  void apply(int k, const T &x) {\n  \
    \  for(++k; k <= n; k += k & -k) data[k] += x;\n  }\n\n  T prod(int r) const {\n\
    \    T ret = T();\n    for(; r > 0; r -= r & -r) ret += data[r];\n    return ret;\n\
    \  }\n\n  T prod(int l, int r) const {\n    return prod(r) - prod(l);\n  }\n\n\
    \  int lower_bound(T x) const {\n    int i = 0;\n    for(int k = 1 << (__lg(n)\
    \ + 1); k > 0; k >>= 1) {\n      if(i + k <= n && data[i + k] < x) {\n       \
    \ x -= data[i + k];\n        i += k;\n      }\n    }\n    return i;\n  }\n\n \
    \ int upper_bound(T x) const {\n    int i = 0;\n    for(int k = 1 << (__lg(n)\
    \ + 1); k > 0; k >>= 1) {\n      if(i + k <= n && data[i + k] <= x) {\n      \
    \  x -= data[i + k];\n        i += k;\n      }\n    }\n    return i;\n  }\n};\n\
    #line 3 \"structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp\"\n\n/*\n\
    \ * @brief Wavelet Matrix Point Add Rectangle Sum\n * @docs docs/wavelet-matrix-point-add-rectangle-sum.md\n\
    \ */\ntemplate< typename T, int MAXLOG, typename D >\nstruct WaveletMatrixPointAddRectangleSum\
    \ {\n  size_t length;\n  SuccinctIndexableDictionary matrix[MAXLOG];\n  BinaryIndexedTree<\
    \ D > ds[MAXLOG];\n  vector< T > v;\n  int mid[MAXLOG];\n\n  WaveletMatrixPointAddRectangleSum()\
    \ = default;\n\n  WaveletMatrixPointAddRectangleSum(const vector< T > &v, const\
    \ vector< D > &d) : length(v.size()), v(v) {\n    assert(v.size() == d.size());\n\
    \    vector< int > l(length), r(length), ord(length);\n    iota(begin(ord), end(ord),\
    \ 0);\n    vector< D > dd(length);\n    for(int level = MAXLOG - 1; level >= 0;\
    \ level--) {\n      matrix[level] = SuccinctIndexableDictionary(length + 1);\n\
    \      int left = 0, right = 0;\n      for(int i = 0; i < length; i++) {\n   \
    \     if(((v[ord[i]] >> level) & 1)) {\n          matrix[level].set(i);\n    \
    \      r[right++] = ord[i];\n        } else {\n          l[left++] = ord[i];\n\
    \        }\n      }\n      mid[level] = left;\n      matrix[level].build();\n\
    \      ord.swap(l);\n      for(int i = 0; i < right; i++) {\n        ord[left\
    \ + i] = r[i];\n      }\n      for(int i = 0; i < length; i++) {\n        dd[i]\
    \ = d[ord[i]];\n      }\n      ds[level] = BinaryIndexedTree< D >(dd);\n    }\n\
    \  }\n\n  pair< int, int > succ(bool f, int l, int r, int level) {\n    return\
    \ {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level]\
    \ * f};\n  }\n\n  // count d[i] s.t. (l <= i < r) && (v[i] < upper)\n  D rect_sum(int\
    \ l, int r, T upper) {\n    D ret = 0;\n    for(int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n      if(((upper >> level) & 1)) {\n        auto nxt = succ(false,\
    \ l, r, level);\n        ret += ds[level].prod(nxt.first, nxt.second);\n     \
    \   l = l - nxt.first + mid[level];\n        r = r - nxt.second + mid[level];\n\
    \      } else {\n        tie(l, r) = succ(false, l, r, level);\n      }\n    }\n\
    \    return ret;\n  }\n\n  D rect_sum(int l, int r, T lower, T upper) {\n    return\
    \ rect_sum(l, r, upper) - rect_sum(l, r, lower);\n  }\n\n  void point_add(int\
    \ k, const D &x) {\n    auto &y = v[k];\n    for(int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n      bool f = ((y >> level) & 1);\n      k = matrix[level].rank(f,\
    \ k) + mid[level] * f;\n      ds[level].apply(k, x);\n    }\n  }\n};\n\ntemplate<\
    \ typename T, int MAXLOG, typename D >\nstruct CompressedWaveletMatrixPointAddRectangleSum\
    \ {\n  WaveletMatrixPointAddRectangleSum< int, MAXLOG, D > mat;\n  vector< T >\
    \ ys;\n\n  CompressedWaveletMatrixPointAddRectangleSum(const vector< T > &v, const\
    \ vector< D > &d) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletMatrixPointAddRectangleSum<\
    \ int, MAXLOG, D >(t, d);\n  }\n\n  inline int get(const T &x) {\n    return lower_bound(begin(ys),\
    \ end(ys), x) - begin(ys);\n  }\n\n  D rect_sum(int l, int r, T upper) {\n   \
    \ return mat.rect_sum(l, r, get(upper));\n  }\n\n  D rect_sum(int l, int r, T\
    \ lower, T upper) {\n    return mat.rect_sum(l, r, get(lower), get(upper));\n\
    \  }\n\n  void point_add(int k, const D &x) {\n    mat.point_add(k, x);\n  }\n\
    };\n#line 6 \"test/verify/yosupo-point-add-rectangle-sum.test.cpp\"\n\n#line 1\
    \ \"other/scanner.hpp\"\n/**\n * @brief Scanner(\u9AD8\u901F\u5165\u529B)\n */\n\
    struct Scanner {\npublic:\n\n  explicit Scanner(FILE *fp) : fp(fp) {}\n\n  template<\
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
    \      write_single(s[i]);\n    }\n  }\n};\n#line 9 \"test/verify/yosupo-point-add-rectangle-sum.test.cpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > x(N), y(N), w(N);\n  vector< pair< int, int\
    \ > > xs;\n  xs.reserve(N + Q);\n  for(int i = 0; i < N; i++) {\n    in.read(x[i],\
    \ y[i], w[i]);\n    xs.emplace_back(x[i], y[i]);\n  }\n  vector< int > t(Q), a(Q),\
    \ b(Q), c(Q), d(Q);\n  for(int i = 0; i < Q; i++) {\n    in.read(t[i], a[i], b[i],\
    \ c[i]);\n    if(t[i] == 0) xs.emplace_back(a[i], b[i]);\n    else in.read(d[i]);\n\
    \  }\n  sort(begin(xs), end(xs));\n  xs.erase(unique(begin(xs), end(xs)), end(xs));\n\
    \  vector< int > ys(xs.size());\n  for(int i = 0; i < xs.size(); i++) ys[i] =\
    \ xs[i].second;\n  vector< int64 > ws(xs.size());\n  for(int i = 0; i < N; i++)\
    \ {\n    x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], y[i])) - begin(xs);\n\
    \    ws[x[i]] += w[i];\n  }\n  for(int i = 0; i < Q; i++) {\n    if(t[i] == 0)\
    \ {\n      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], b[i])) - begin(xs);\n\
    \    } else {\n      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], -1))\
    \ - begin(xs);\n      c[i] = lower_bound(begin(xs), end(xs), make_pair(c[i], -1))\
    \ - begin(xs);\n    }\n  }\n  CompressedWaveletMatrixPointAddRectangleSum< int,\
    \ 18, int64 > mat(ys, ws);\n  for(int i = 0; i < Q; i++) {\n    if(t[i] == 0)\
    \ {\n      mat.point_add(a[i], c[i]);\n    } else {\n      out.writeln(mat.rect_sum(a[i],\
    \ c[i], b[i], d[i]));\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp\"\
    \n\n#include \"../../other/scanner.hpp\"\n#include \"../../other/printer.hpp\"\
    \n\nint main() {\n  Scanner in(stdin);\n  Printer out(stdout);\n  int N, Q;\n\
    \  in.read(N, Q);\n  vector< int > x(N), y(N), w(N);\n  vector< pair< int, int\
    \ > > xs;\n  xs.reserve(N + Q);\n  for(int i = 0; i < N; i++) {\n    in.read(x[i],\
    \ y[i], w[i]);\n    xs.emplace_back(x[i], y[i]);\n  }\n  vector< int > t(Q), a(Q),\
    \ b(Q), c(Q), d(Q);\n  for(int i = 0; i < Q; i++) {\n    in.read(t[i], a[i], b[i],\
    \ c[i]);\n    if(t[i] == 0) xs.emplace_back(a[i], b[i]);\n    else in.read(d[i]);\n\
    \  }\n  sort(begin(xs), end(xs));\n  xs.erase(unique(begin(xs), end(xs)), end(xs));\n\
    \  vector< int > ys(xs.size());\n  for(int i = 0; i < xs.size(); i++) ys[i] =\
    \ xs[i].second;\n  vector< int64 > ws(xs.size());\n  for(int i = 0; i < N; i++)\
    \ {\n    x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], y[i])) - begin(xs);\n\
    \    ws[x[i]] += w[i];\n  }\n  for(int i = 0; i < Q; i++) {\n    if(t[i] == 0)\
    \ {\n      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], b[i])) - begin(xs);\n\
    \    } else {\n      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], -1))\
    \ - begin(xs);\n      c[i] = lower_bound(begin(xs), end(xs), make_pair(c[i], -1))\
    \ - begin(xs);\n    }\n  }\n  CompressedWaveletMatrixPointAddRectangleSum< int,\
    \ 18, int64 > mat(ys, ws);\n  for(int i = 0; i < Q; i++) {\n    if(t[i] == 0)\
    \ {\n      mat.point_add(a[i], c[i]);\n    } else {\n      out.writeln(mat.rect_sum(a[i],\
    \ c[i], b[i], d[i]));\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
  - structure/wavelet/succinct-indexable-dictionary.hpp
  - structure/others/binary-indexed-tree.hpp
  - other/scanner.hpp
  - other/printer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-point-add-rectangle-sum.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-point-add-rectangle-sum.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-point-add-rectangle-sum.test.cpp
- /verify/test/verify/yosupo-point-add-rectangle-sum.test.cpp.html
title: test/verify/yosupo-point-add-rectangle-sum.test.cpp
---
