---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: structure/wavelet/succinct-indexable-dictionary.hpp
    title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1549.test.cpp
    title: test/verify/aoj-1549.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2674.test.cpp
    title: test/verify/aoj-2674.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-range-kth-smallest.test.cpp
    title: test/verify/yosupo-range-kth-smallest.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/wavelet-matrix.md
    document_title: "Wavelet Matrix(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\
      \u5217)"
    links: []
  bundledCode: "#line 1 \"structure/wavelet/succinct-indexable-dictionary.hpp\"\n\
    /**\n * @brief Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)\n */\n\
    struct SuccinctIndexableDictionary {\n  size_t length;\n  size_t blocks;\n  vector<\
    \ unsigned > bit, sum;\n\n  SuccinctIndexableDictionary() = default;\n\n  SuccinctIndexableDictionary(size_t\
    \ length) : length(length), blocks((length + 31) >> 5) {\n    bit.assign(blocks,\
    \ 0U);\n    sum.assign(blocks, 0U);\n  }\n\n  void set(int k) {\n    bit[k >>\
    \ 5] |= 1U << (k & 31);\n  }\n\n  void build() {\n    sum[0] = 0U;\n    for(int\
    \ i = 1; i < blocks; i++) {\n      sum[i] = sum[i - 1] + __builtin_popcount(bit[i\
    \ - 1]);\n    }\n  }\n\n  bool operator[](int k) {\n    return (bool((bit[k >>\
    \ 5] >> (k & 31)) & 1));\n  }\n\n  int rank(int k) {\n    return (sum[k >> 5]\
    \ + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));\n  }\n\n  int rank(bool\
    \ val, int k) {\n    return (val ? rank(k) : k - rank(k));\n  }\n};\n#line 2 \"\
    structure/wavelet/wavelet-matrix.hpp\"\n\n/*\n * @brief Wavelet Matrix(\u30A6\u30A7\
    \u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217)\n * @docs docs/wavelet-matrix.md\n\
    \ */\ntemplate< typename T, int MAXLOG >\nstruct WaveletMatrix {\n  size_t length;\n\
    \  SuccinctIndexableDictionary matrix[MAXLOG];\n  int mid[MAXLOG];\n\n  WaveletMatrix()\
    \ = default;\n\n  WaveletMatrix(vector< T > v) : length(v.size()) {\n    vector<\
    \ T > l(length), r(length);\n    for(int level = MAXLOG - 1; level >= 0; level--)\
    \ {\n      matrix[level] = SuccinctIndexableDictionary(length + 1);\n      int\
    \ left = 0, right = 0;\n      for(int i = 0; i < length; i++) {\n        if(((v[i]\
    \ >> level) & 1)) {\n          matrix[level].set(i);\n          r[right++] = v[i];\n\
    \        } else {\n          l[left++] = v[i];\n        }\n      }\n      mid[level]\
    \ = left;\n      matrix[level].build();\n      v.swap(l);\n      for(int i = 0;\
    \ i < right; i++) {\n        v[left + i] = r[i];\n      }\n    }\n  }\n\n  pair<\
    \ int, int > succ(bool f, int l, int r, int level) {\n    return {matrix[level].rank(f,\
    \ l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};\n  }\n\n  //\
    \ v[k]\n  T access(int k) {\n    T ret = 0;\n    for(int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n      bool f = matrix[level][k];\n      if(f) ret |= T(1)\
    \ << level;\n      k = matrix[level].rank(f, k) + mid[level] * f;\n    }\n   \
    \ return ret;\n  }\n\n  T operator[](const int &k) {\n    return access(k);\n\
    \  }\n\n  // count i s.t. (0 <= i < r) && v[i] == x\n  int rank(const T &x, int\
    \ r) {\n    int l = 0;\n    for(int level = MAXLOG - 1; level >= 0; level--) {\n\
    \      tie(l, r) = succ((x >> level) & 1, l, r, level);\n    }\n    return r -\
    \ l;\n  }\n\n  // k-th(0-indexed) smallest number in v[l,r)\n  T kth_smallest(int\
    \ l, int r, int k) {\n    assert(0 <= k && k < r - l);\n    T ret = 0;\n    for(int\
    \ level = MAXLOG - 1; level >= 0; level--) {\n      int cnt = matrix[level].rank(false,\
    \ r) - matrix[level].rank(false, l);\n      bool f = cnt <= k;\n      if(f) {\n\
    \        ret |= T(1) << level;\n        k -= cnt;\n      }\n      tie(l, r) =\
    \ succ(f, l, r, level);\n    }\n    return ret;\n  }\n\n  // k-th(0-indexed) largest\
    \ number in v[l,r)\n  T kth_largest(int l, int r, int k) {\n    return kth_smallest(l,\
    \ r, r - l - k - 1);\n  }\n\n  // count i s.t. (l <= i < r) && (v[i] < upper)\n\
    \  int range_freq(int l, int r, T upper) {\n    int ret = 0;\n    for(int level\
    \ = MAXLOG - 1; level >= 0; level--) {\n      bool f = ((upper >> level) & 1);\n\
    \      if(f) ret += matrix[level].rank(false, r) - matrix[level].rank(false, l);\n\
    \      tie(l, r) = succ(f, l, r, level);\n    }\n    return ret;\n  }\n\n  //\
    \ count i s.t. (l <= i < r) && (lower <= v[i] < upper)\n  int range_freq(int l,\
    \ int r, T lower, T upper) {\n    return range_freq(l, r, upper) - range_freq(l,\
    \ r, lower);\n  }\n\n  // max v[i] s.t. (l <= i < r) && (v[i] < upper)\n  T prev_value(int\
    \ l, int r, T upper) {\n    int cnt = range_freq(l, r, upper);\n    return cnt\
    \ == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n  }\n\n  // min v[i] s.t. (l <=\
    \ i < r) && (lower <= v[i])\n  T next_value(int l, int r, T lower) {\n    int\
    \ cnt = range_freq(l, r, lower);\n    return cnt == r - l ? T(-1) : kth_smallest(l,\
    \ r, cnt);\n  }\n};\n\ntemplate< typename T, int MAXLOG >\nstruct CompressedWaveletMatrix\
    \ {\n  WaveletMatrix< int, MAXLOG > mat;\n  vector< T > ys;\n\n  CompressedWaveletMatrix(const\
    \ vector< T > &v) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletMatrix< int, MAXLOG >(t);\n\
    \  }\n\n  inline int get(const T& x) {\n    return lower_bound(begin(ys), end(ys),\
    \ x) - begin(ys);\n  }\n\n  T access(int k) {\n    return ys[mat.access(k)];\n\
    \  }\n\n  T operator[](const int &k) {\n    return access(k);\n  }\n\n  int rank(const\
    \ T &x, int r) {\n    auto pos = get(x);\n    if(pos == ys.size() || ys[pos] !=\
    \ x) return 0;\n    return mat.rank(pos, r);\n  }\n\n  T kth_smallest(int l, int\
    \ r, int k) {\n    return ys[mat.kth_smallest(l, r, k)];\n  }\n\n  T kth_largest(int\
    \ l, int r, int k) {\n    return ys[mat.kth_largest(l, r, k)];\n  }\n\n  int range_freq(int\
    \ l, int r, T upper) {\n    return mat.range_freq(l, r, get(upper));\n  }\n\n\
    \  int range_freq(int l, int r, T lower, T upper) {\n    return mat.range_freq(l,\
    \ r, get(lower), get(upper));\n  }\n\n  T prev_value(int l, int r, T upper) {\n\
    \    auto ret = mat.prev_value(l, r, get(upper));\n    return ret == -1 ? T(-1)\
    \ : ys[ret];\n  }\n\n  T next_value(int l, int r, T lower) {\n    auto ret = mat.next_value(l,\
    \ r, get(lower));\n    return ret == -1 ? T(-1) : ys[ret];\n  }\n};\n"
  code: "#include \"succinct-indexable-dictionary.hpp\"\n\n/*\n * @brief Wavelet Matrix(\u30A6\
    \u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217)\n * @docs docs/wavelet-matrix.md\n\
    \ */\ntemplate< typename T, int MAXLOG >\nstruct WaveletMatrix {\n  size_t length;\n\
    \  SuccinctIndexableDictionary matrix[MAXLOG];\n  int mid[MAXLOG];\n\n  WaveletMatrix()\
    \ = default;\n\n  WaveletMatrix(vector< T > v) : length(v.size()) {\n    vector<\
    \ T > l(length), r(length);\n    for(int level = MAXLOG - 1; level >= 0; level--)\
    \ {\n      matrix[level] = SuccinctIndexableDictionary(length + 1);\n      int\
    \ left = 0, right = 0;\n      for(int i = 0; i < length; i++) {\n        if(((v[i]\
    \ >> level) & 1)) {\n          matrix[level].set(i);\n          r[right++] = v[i];\n\
    \        } else {\n          l[left++] = v[i];\n        }\n      }\n      mid[level]\
    \ = left;\n      matrix[level].build();\n      v.swap(l);\n      for(int i = 0;\
    \ i < right; i++) {\n        v[left + i] = r[i];\n      }\n    }\n  }\n\n  pair<\
    \ int, int > succ(bool f, int l, int r, int level) {\n    return {matrix[level].rank(f,\
    \ l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};\n  }\n\n  //\
    \ v[k]\n  T access(int k) {\n    T ret = 0;\n    for(int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n      bool f = matrix[level][k];\n      if(f) ret |= T(1)\
    \ << level;\n      k = matrix[level].rank(f, k) + mid[level] * f;\n    }\n   \
    \ return ret;\n  }\n\n  T operator[](const int &k) {\n    return access(k);\n\
    \  }\n\n  // count i s.t. (0 <= i < r) && v[i] == x\n  int rank(const T &x, int\
    \ r) {\n    int l = 0;\n    for(int level = MAXLOG - 1; level >= 0; level--) {\n\
    \      tie(l, r) = succ((x >> level) & 1, l, r, level);\n    }\n    return r -\
    \ l;\n  }\n\n  // k-th(0-indexed) smallest number in v[l,r)\n  T kth_smallest(int\
    \ l, int r, int k) {\n    assert(0 <= k && k < r - l);\n    T ret = 0;\n    for(int\
    \ level = MAXLOG - 1; level >= 0; level--) {\n      int cnt = matrix[level].rank(false,\
    \ r) - matrix[level].rank(false, l);\n      bool f = cnt <= k;\n      if(f) {\n\
    \        ret |= T(1) << level;\n        k -= cnt;\n      }\n      tie(l, r) =\
    \ succ(f, l, r, level);\n    }\n    return ret;\n  }\n\n  // k-th(0-indexed) largest\
    \ number in v[l,r)\n  T kth_largest(int l, int r, int k) {\n    return kth_smallest(l,\
    \ r, r - l - k - 1);\n  }\n\n  // count i s.t. (l <= i < r) && (v[i] < upper)\n\
    \  int range_freq(int l, int r, T upper) {\n    int ret = 0;\n    for(int level\
    \ = MAXLOG - 1; level >= 0; level--) {\n      bool f = ((upper >> level) & 1);\n\
    \      if(f) ret += matrix[level].rank(false, r) - matrix[level].rank(false, l);\n\
    \      tie(l, r) = succ(f, l, r, level);\n    }\n    return ret;\n  }\n\n  //\
    \ count i s.t. (l <= i < r) && (lower <= v[i] < upper)\n  int range_freq(int l,\
    \ int r, T lower, T upper) {\n    return range_freq(l, r, upper) - range_freq(l,\
    \ r, lower);\n  }\n\n  // max v[i] s.t. (l <= i < r) && (v[i] < upper)\n  T prev_value(int\
    \ l, int r, T upper) {\n    int cnt = range_freq(l, r, upper);\n    return cnt\
    \ == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n  }\n\n  // min v[i] s.t. (l <=\
    \ i < r) && (lower <= v[i])\n  T next_value(int l, int r, T lower) {\n    int\
    \ cnt = range_freq(l, r, lower);\n    return cnt == r - l ? T(-1) : kth_smallest(l,\
    \ r, cnt);\n  }\n};\n\ntemplate< typename T, int MAXLOG >\nstruct CompressedWaveletMatrix\
    \ {\n  WaveletMatrix< int, MAXLOG > mat;\n  vector< T > ys;\n\n  CompressedWaveletMatrix(const\
    \ vector< T > &v) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletMatrix< int, MAXLOG >(t);\n\
    \  }\n\n  inline int get(const T& x) {\n    return lower_bound(begin(ys), end(ys),\
    \ x) - begin(ys);\n  }\n\n  T access(int k) {\n    return ys[mat.access(k)];\n\
    \  }\n\n  T operator[](const int &k) {\n    return access(k);\n  }\n\n  int rank(const\
    \ T &x, int r) {\n    auto pos = get(x);\n    if(pos == ys.size() || ys[pos] !=\
    \ x) return 0;\n    return mat.rank(pos, r);\n  }\n\n  T kth_smallest(int l, int\
    \ r, int k) {\n    return ys[mat.kth_smallest(l, r, k)];\n  }\n\n  T kth_largest(int\
    \ l, int r, int k) {\n    return ys[mat.kth_largest(l, r, k)];\n  }\n\n  int range_freq(int\
    \ l, int r, T upper) {\n    return mat.range_freq(l, r, get(upper));\n  }\n\n\
    \  int range_freq(int l, int r, T lower, T upper) {\n    return mat.range_freq(l,\
    \ r, get(lower), get(upper));\n  }\n\n  T prev_value(int l, int r, T upper) {\n\
    \    auto ret = mat.prev_value(l, r, get(upper));\n    return ret == -1 ? T(-1)\
    \ : ys[ret];\n  }\n\n  T next_value(int l, int r, T lower) {\n    auto ret = mat.next_value(l,\
    \ r, get(lower));\n    return ret == -1 ? T(-1) : ys[ret];\n  }\n};\n"
  dependsOn:
  - structure/wavelet/succinct-indexable-dictionary.hpp
  isVerificationFile: false
  path: structure/wavelet/wavelet-matrix.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/aoj-1549.test.cpp
  - test/verify/yosupo-range-kth-smallest.test.cpp
  - test/verify/aoj-2674.test.cpp
documentation_of: structure/wavelet/wavelet-matrix.hpp
layout: document
redirect_from:
- /library/structure/wavelet/wavelet-matrix.hpp
- /library/structure/wavelet/wavelet-matrix.hpp.html
title: "Wavelet Matrix(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217)"
---
## 概要

$2$ 次元平面上にある点が事前に与えられているとき, オンラインでいろいろなクエリを処理するデータ構造.

基本的には事前に要素の値を要素数に圧縮する CompressedWaveletMatrix を用いると高速に動作する.

## 使い方
* `WaveletMatrix(v)`: 各要素の高さ `v` を初期値として構築する.
* `access(k)`: $k$ 番目の要素を返す.
* `rank(x, r)`: 区間 $[0, r)$ に含まれる `x` の個数を返す.
* `kth_smallest(l, r, k)`: 区間 $[l, r)$ に含まれる要素のうち $k$ 番目(0-indexed) に小さいものを返す.
* `kth_largest(l, r, k)`: 区間 $[l, r)$ に含まれる要素のうち $k$ 番目 (0-indexed) に大きいものを返す.
* `range_freq(l, r, lower, upper)`: 区間 $[l, r)$ に含まれる要素のうち $[lower, upper)$ である要素数を返す.
* `prev_value(l, r, upper)`: 区間 $[l, r)$ に含まれる要素のうち `upper` の次に小さいものを返す.
* `next_value(l, r, lower)`: 区間 $[l, r)$ に含まれる要素のうち `lower` の次に大きいものを返す.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(\log V)$

$V$ は値の最大値.
