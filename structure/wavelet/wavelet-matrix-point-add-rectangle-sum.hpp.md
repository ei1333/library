---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/succinct-indexable-dictionary.hpp
    title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/wavelet-matrix-point-add-rectangle-sum.md
    document_title: Wavelet Matrix Point Add Rectangle Sum
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
    \ val, int k) {\n    return (val ? rank(k) : k - rank(k));\n  }\n};\n#line 1 \"\
    structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief Binary-Indexed-Tree(BIT)\n\
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
    \    }\n    }\n    return i;\n  }\n};\n#line 3 \"structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp\"\
    \n\n/*\n * @brief Wavelet Matrix Point Add Rectangle Sum\n * @docs docs/wavelet-matrix-point-add-rectangle-sum.md\n\
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
    };\n"
  code: "#include \"succinct-indexable-dictionary.hpp\"\n#include \"../others/binary-indexed-tree.hpp\"\
    \n\n/*\n * @brief Wavelet Matrix Point Add Rectangle Sum\n * @docs docs/wavelet-matrix-point-add-rectangle-sum.md\n\
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
    };\n"
  dependsOn:
  - structure/wavelet/succinct-indexable-dictionary.hpp
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: false
  path: structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-point-add-rectangle-sum.test.cpp
documentation_of: structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
layout: document
redirect_from:
- /library/structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
- /library/structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp.html
title: Wavelet Matrix Point Add Rectangle Sum
---
## 概要

$2$ 次元平面上にある点の位置が事前に与えられているとき, オンラインである点に対する重みの加算と, 矩形内にある点の重みの総和を効率的に求めるデータ構造.

Wavelet-Matrix-Rectangle-Sum で用いた重みの累積和を持たせた配列をBinary-Indexed-Tree に置き換えると, ある点に対する重みの加算を効率的に行える.

基本的には事前に高さを要素数に圧縮する CompressedWaveletMatrixPointAddRectangleSum を用いると高速に動作する.

## 使い方
* `WaveletMatrixRectangleSum(v, d)`: 各要素の高さ `v` , 対応する要素の重み `d` >を初期値として構築する.
* `rect_sum(l, r, upper)`: 区間 $[l, r)$ の高さ $[0, upper)$ にある要素の重みの>
総和を返す.
* `rect_sum(l, r, lower, upper)`: 区間 $[l, r)$ の高さ $[lower, upper)$ にある要
素の重みの総和を返す.
* `point_add(k, x)`: 要素 $k$ の重みに $x$ を加算する.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(N \log N \log V)$

$V$ は値の最大値.
