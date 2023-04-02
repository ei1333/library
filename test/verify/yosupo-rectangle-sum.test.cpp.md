---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/succinct-indexable-dictionary.hpp
    title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/wavelet-matrix-rectangle-sum.hpp
    title: Wavelet Matrix Rectangle Sum
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "#line 1 \"test/verify/yosupo-rectangle-sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-rectangle-sum.test.cpp\"\
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
    \ (val ? rank(k) : k - rank(k));\n  }\n};\n#line 1 \"structure/wavelet/wavelet-matrix-rectangle-sum.hpp\"\
    \n/*\n * @brief Wavelet Matrix Rectangle Sum\n * @docs docs/wavelet-matrix-rectangle-sum.md\n\
    \ */\ntemplate< typename T, int MAXLOG, typename D >\nstruct WaveletMatrixRectangleSum\
    \ {\n  size_t length;\n  SuccinctIndexableDictionary matrix[MAXLOG];\n  vector<\
    \ D > ds[MAXLOG];\n  int mid[MAXLOG];\n\n  WaveletMatrixRectangleSum() = default;\n\
    \n  WaveletMatrixRectangleSum(const vector< T > &v, const vector< D > &d) : length(v.size())\
    \ {\n    assert(v.size() == d.size());\n    vector< int > l(length), r(length),\
    \ ord(length);\n    iota(begin(ord), end(ord), 0);\n    for(int level = MAXLOG\
    \ - 1; level >= 0; level--) {\n      matrix[level] = SuccinctIndexableDictionary(length\
    \ + 1);\n      int left = 0, right = 0;\n      for(int i = 0; i < length; i++)\
    \ {\n        if(((v[ord[i]] >> level) & 1)) {\n          matrix[level].set(i);\n\
    \          r[right++] = ord[i];\n        } else {\n          l[left++] = ord[i];\n\
    \        }\n      }\n      mid[level] = left;\n      matrix[level].build();\n\
    \      ord.swap(l);\n      for(int i = 0; i < right; i++) {\n        ord[left\
    \ + i] = r[i];\n      }\n      ds[level].resize(length + 1);\n      ds[level][0]\
    \ = D();\n      for(int i = 0; i < length; i++) {\n        ds[level][i + 1] =\
    \ ds[level][i] + d[ord[i]];\n      }\n    }\n  }\n\n  pair< int, int > succ(bool\
    \ f, int l, int r, int level) {\n    return {matrix[level].rank(f, l) + mid[level]\
    \ * f, matrix[level].rank(f, r) + mid[level] * f};\n  }\n\n  // count d[i] s.t.\
    \ (l <= i < r) && (v[i] < upper)\n  D rect_sum(int l, int r, T upper) {\n    D\
    \ ret = 0;\n    for(int level = MAXLOG - 1; level >= 0; level--) {\n      bool\
    \ f = ((upper >> level) & 1);\n      if(f) ret += ds[level][matrix[level].rank(false,\
    \ r)] - ds[level][matrix[level].rank(false, l)];\n      tie(l, r) = succ(f, l,\
    \ r, level);\n    }\n    return ret;\n  }\n\n  D rect_sum(int l, int r, T lower,\
    \ T upper) {\n    return rect_sum(l, r, upper) - rect_sum(l, r, lower);\n  }\n\
    };\n\ntemplate< typename T, int MAXLOG, typename D >\nstruct CompressedWaveletMatrixRectangleSum\
    \ {\n  WaveletMatrixRectangleSum< int, MAXLOG, D > mat;\n  vector< T > ys;\n\n\
    \  CompressedWaveletMatrixRectangleSum(const vector< T > &v, const vector< D >\
    \ &d) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletMatrixRectangleSum< int,\
    \ MAXLOG, D >(t, d);\n  }\n\n  inline int get(const T &x) {\n    return lower_bound(begin(ys),\
    \ end(ys), x) - begin(ys);\n  }\n\n  D rect_sum(int l, int r, T upper) {\n   \
    \ return mat.rect_sum(l, r, get(upper));\n  }\n\n  D rect_sum(int l, int r, T\
    \ lower, T upper) {\n    return mat.rect_sum(l, r, get(lower), get(upper));\n\
    \  }\n};\n\n#line 7 \"test/verify/yosupo-rectangle-sum.test.cpp\"\n\nint main()\
    \ {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > x(N), y(N), w(N);\n  vector<\
    \ pair< int, int > > xs(N);\n  for(int i = 0; i < N; i++) {\n    cin >> x[i] >>\
    \ y[i] >> w[i];\n    xs[i] = {x[i], i};\n  }\n  sort(begin(xs), end(xs));\n  vector<\
    \ int > ys(N);\n  vector< int64 > ws(N);\n  for(int i = 0; i < N; i++) {\n   \
    \ x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], i)) - begin(xs);\n  \
    \  ys[x[i]] = y[i];\n    ws[x[i]] = w[i];\n  }\n  CompressedWaveletMatrixRectangleSum<\
    \ int, 18, int64 > mat(ys, ws);\n  while(Q--) {\n    int l, r, d, u;\n    cin\
    \ >> l >> d >> r >> u;\n    l = lower_bound(begin(xs), end(xs), make_pair(l, -1))\
    \ - begin(xs);\n    r = lower_bound(begin(xs), end(xs), make_pair(r, -1)) - begin(xs);\n\
    \    cout << mat.rect_sum(l, r, d, u) << \"\\n\";\n  }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../structure/wavelet/succinct-indexable-dictionary.hpp\"\
    \n#include \"../../structure/wavelet/wavelet-matrix-rectangle-sum.hpp\"\n\nint\
    \ main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< int > x(N), y(N), w(N);\n\
    \  vector< pair< int, int > > xs(N);\n  for(int i = 0; i < N; i++) {\n    cin\
    \ >> x[i] >> y[i] >> w[i];\n    xs[i] = {x[i], i};\n  }\n  sort(begin(xs), end(xs));\n\
    \  vector< int > ys(N);\n  vector< int64 > ws(N);\n  for(int i = 0; i < N; i++)\
    \ {\n    x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], i)) - begin(xs);\n\
    \    ys[x[i]] = y[i];\n    ws[x[i]] = w[i];\n  }\n  CompressedWaveletMatrixRectangleSum<\
    \ int, 18, int64 > mat(ys, ws);\n  while(Q--) {\n    int l, r, d, u;\n    cin\
    \ >> l >> d >> r >> u;\n    l = lower_bound(begin(xs), end(xs), make_pair(l, -1))\
    \ - begin(xs);\n    r = lower_bound(begin(xs), end(xs), make_pair(r, -1)) - begin(xs);\n\
    \    cout << mat.rect_sum(l, r, d, u) << \"\\n\";\n  }\n}\n\n"
  dependsOn:
  - template/template.hpp
  - structure/wavelet/succinct-indexable-dictionary.hpp
  - structure/wavelet/wavelet-matrix-rectangle-sum.hpp
  isVerificationFile: true
  path: test/verify/yosupo-rectangle-sum.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-rectangle-sum.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-rectangle-sum.test.cpp
- /verify/test/verify/yosupo-rectangle-sum.test.cpp.html
title: test/verify/yosupo-rectangle-sum.test.cpp
---
