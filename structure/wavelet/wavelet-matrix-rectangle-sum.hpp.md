---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-rectangle-sum.test.cpp
    title: test/verify/yosupo-rectangle-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/wavelet-matrix-rectangle-sum.md
    document_title: Wavelet Matrix Rectangle Sum
    links: []
  bundledCode: "#line 1 \"structure/wavelet/wavelet-matrix-rectangle-sum.hpp\"\n/*\n\
    \ * @brief Wavelet Matrix Rectangle Sum\n * @docs docs/wavelet-matrix-rectangle-sum.md\n\
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
    \  }\n};\n\n"
  code: "/*\n * @brief Wavelet Matrix Rectangle Sum\n * @docs docs/wavelet-matrix-rectangle-sum.md\n\
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
    \  }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/wavelet/wavelet-matrix-rectangle-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-rectangle-sum.test.cpp
documentation_of: structure/wavelet/wavelet-matrix-rectangle-sum.hpp
layout: document
redirect_from:
- /library/structure/wavelet/wavelet-matrix-rectangle-sum.hpp
- /library/structure/wavelet/wavelet-matrix-rectangle-sum.hpp.html
title: Wavelet Matrix Rectangle Sum
---
## 概要

$2$ 次元平面上にある重み付きの点が事前に与えられているとき, オンラインで矩形内にある点の重みの総和を効率的に求めるデータ構造.

普通のウェーブレット行列に対し重みの累積和を持たせた配列を用意すると, 矩形内の点の個数を数えるのと同じように重みの総和を求めることができる.

基本的には事前に高さを要素数に圧縮する CompressedWaveletMatrixRectangleSum を用いると高速に動作する.

## 使い方
* `WaveletMatrixRectangleSum(v, d)`: 各要素の高さ `v` , 対応する要素の重み `d` を初期値として構築する.
* `rect_sum(l, r, upper)`: 区間 $[l, r)$ の高さ $[0, upper)$ にある要素の重みの総和を返す.
* `rect_sum(l, r, lower, upper)`: 区間 $[l, r)$ の高さ $[lower, upper)$ にある要素の重みの総和を返す.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(\log V)$

$V$ は値の最大値.
