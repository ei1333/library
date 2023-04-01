---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1549-2.test.cpp
    title: test/verify/aoj-1549-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2674-2.test.cpp
    title: test/verify/aoj-2674-2.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-range-kth-smallest-2.test.cpp
    title: test/verify/yosupo-range-kth-smallest-2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/wavelet-tree.md
    document_title: "Wavelet Tree(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u6728\
      )"
    links: []
  bundledCode: "#line 1 \"structure/wavelet/wavelet-tree.hpp\"\n/*\n * @brief Wavelet\
    \ Tree(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u6728)\n * @docs docs/wavelet-tree.md\n\
    \ */\ntemplate< typename T, int MAXLOG >\nstruct WaveletTree {\n\n  struct Node\
    \ {\n    SuccinctIndexableDictionary sid;\n    Node *ch[2];\n\n    Node() = default;\n\
    \n    Node(size_t length) : sid(length + 1), ch{nullptr} {}\n\n  };\n\n  Node\
    \ *root;\n\n  Node *build(vector< T > &v, vector< T > &rbuff, int bit, int l,\
    \ int r) {\n    if(l >= r || bit == -1) return nullptr;\n    Node *node = new\
    \ Node(r - l);\n    int left = 0, right = 0;\n    for(int k = l; k < r; k++) {\n\
    \      if(((v[k] >> bit) & 1)) {\n        rbuff[right++] = v[k];\n        node->sid.set(k\
    \ - l);\n      } else {\n        v[l + left++] = v[k];\n      }\n    }\n    for(int\
    \ k = 0; k < right; k++) {\n      v[l + left + k] = rbuff[k];\n    }\n    node->sid.build();\n\
    \    node->ch[0] = build(v, rbuff, bit - 1, l, l + left);\n    node->ch[1] = build(v,\
    \ rbuff, bit - 1, l + left, r);\n    return node;\n  }\n\n  WaveletTree() = default;\n\
    \n  WaveletTree(vector< T > v) {\n    vector< T > rbuff(v.size());\n    root =\
    \ build(v, rbuff, MAXLOG - 1, 0, v.size());\n  }\n\n  int rank(Node *t, int l,\
    \ int r, const T &x, int level) {\n    if(l >= r || t == nullptr) return 0;\n\
    \    if(level == -1) return r - l;\n    bool f = (x >> level) & 1;\n    l = t->sid.rank(f,\
    \ l), r = t->sid.rank(f, r);\n    return rank(t->ch[f], l, r, x, level - 1);\n\
    \  }\n\n  int rank(const T &x, int r) {\n    return rank(root, 0, r, x, MAXLOG\
    \ - 1);\n  }\n\n  T kth_smallest(Node *t, int l, int r, int k, int level) {\n\
    \    if(l >= r || t == nullptr) return 0;\n    int cnt = t->sid.rank(false, r)\
    \ - t->sid.rank(false, l);\n    bool f = cnt <= k;\n    l = t->sid.rank(f, l),\
    \ r = t->sid.rank(f, r);\n    if(f) return kth_smallest(t->ch[f], l, r, k - cnt,\
    \ level - 1) | ((T(1) << level));\n    return kth_smallest(t->ch[f], l, r, k,\
    \ level - 1);\n  }\n\n  // k-th(0-indexed) smallest number in v[l,r)\n  T kth_smallest(int\
    \ l, int r, int k) {\n    assert(0 <= k && k < r - l);\n    return kth_smallest(root,\
    \ l, r, k, MAXLOG - 1);\n  }\n\n  // k-th(0-indexed) largest number in v[l,r)\n\
    \  T kth_largest(int l, int r, int k) {\n    return kth_smallest(l, r, r - l -\
    \ k - 1);\n  }\n\n  int range_freq(Node *t, int l, int r, T upper, int level)\
    \ {\n    if(t == nullptr || l >= r) return 0;\n    bool f = ((upper >> level)\
    \ & 1);\n    int ret = 0;\n    if(f) ret += t->sid.rank(false, r) - t->sid.rank(false,\
    \ l);\n    l = t->sid.rank(f, l), r = t->sid.rank(f, r);\n    return range_freq(t->ch[f],\
    \ l, r, upper, level - 1) + ret;\n  }\n\n  // count i s.t. (l <= i < r) && (v[i]\
    \ < upper)\n  int range_freq(int l, int r, T upper) {\n    return range_freq(root,\
    \ l, r, upper, MAXLOG - 1);\n  }\n\n  // count i s.t. (l <= i < r) && (lower <=\
    \ v[i] < upper)\n  int range_freq(int l, int r, T lower, T upper) {\n    return\
    \ range_freq(l, r, upper) - range_freq(l, r, lower);\n  }\n\n  // max v[i] s.t.\
    \ (l <= i < r) && (v[i] < upper)\n  T prev_value(int l, int r, T upper) {\n  \
    \  int cnt = range_freq(l, r, upper);\n    return cnt == 0 ? T(-1) : kth_smallest(l,\
    \ r, cnt - 1);\n  }\n\n  // min v[i] s.t. (l <= i < r) && (lower <= v[i])\n  T\
    \ next_value(int l, int r, T lower) {\n    int cnt = range_freq(l, r, lower);\n\
    \    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);\n  }\n};\n\ntemplate<\
    \ typename T, int MAXLOG >\nstruct CompressedWaveletTree {\n  WaveletTree< int,\
    \ MAXLOG > mat;\n  vector< T > ys;\n\n  CompressedWaveletTree(const vector< T\
    \ > &v) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletTree< int, MAXLOG >(t);\n\
    \  }\n\n  inline int get(const T &x) {\n    return lower_bound(begin(ys), end(ys),\
    \ x) - begin(ys);\n  }\n\n  int rank(const T &x, int r) {\n    auto pos = get(x);\n\
    \    if(pos == ys.size() || ys[pos] != x) return 0;\n    return mat.rank(pos,\
    \ r);\n  }\n\n  T kth_smallest(int l, int r, int k) {\n    return ys[mat.kth_smallest(l,\
    \ r, k)];\n  }\n\n  T kth_largest(int l, int r, int k) {\n    return ys[mat.kth_largest(l,\
    \ r, k)];\n  }\n\n  int range_freq(int l, int r, T upper) {\n    return mat.range_freq(l,\
    \ r, get(upper));\n  }\n\n  int range_freq(int l, int r, T lower, T upper) {\n\
    \    return mat.range_freq(l, r, get(lower), get(upper));\n  }\n\n  T prev_value(int\
    \ l, int r, T upper) {\n    auto ret = mat.prev_value(l, r, get(upper));\n   \
    \ return ret == -1 ? T(-1) : ys[ret];\n  }\n\n  T next_value(int l, int r, T lower)\
    \ {\n    auto ret = mat.next_value(l, r, get(lower));\n    return ret == -1 ?\
    \ T(-1) : ys[ret];\n  }\n};\n\n"
  code: "/*\n * @brief Wavelet Tree(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u6728\
    )\n * @docs docs/wavelet-tree.md\n */\ntemplate< typename T, int MAXLOG >\nstruct\
    \ WaveletTree {\n\n  struct Node {\n    SuccinctIndexableDictionary sid;\n   \
    \ Node *ch[2];\n\n    Node() = default;\n\n    Node(size_t length) : sid(length\
    \ + 1), ch{nullptr} {}\n\n  };\n\n  Node *root;\n\n  Node *build(vector< T > &v,\
    \ vector< T > &rbuff, int bit, int l, int r) {\n    if(l >= r || bit == -1) return\
    \ nullptr;\n    Node *node = new Node(r - l);\n    int left = 0, right = 0;\n\
    \    for(int k = l; k < r; k++) {\n      if(((v[k] >> bit) & 1)) {\n        rbuff[right++]\
    \ = v[k];\n        node->sid.set(k - l);\n      } else {\n        v[l + left++]\
    \ = v[k];\n      }\n    }\n    for(int k = 0; k < right; k++) {\n      v[l + left\
    \ + k] = rbuff[k];\n    }\n    node->sid.build();\n    node->ch[0] = build(v,\
    \ rbuff, bit - 1, l, l + left);\n    node->ch[1] = build(v, rbuff, bit - 1, l\
    \ + left, r);\n    return node;\n  }\n\n  WaveletTree() = default;\n\n  WaveletTree(vector<\
    \ T > v) {\n    vector< T > rbuff(v.size());\n    root = build(v, rbuff, MAXLOG\
    \ - 1, 0, v.size());\n  }\n\n  int rank(Node *t, int l, int r, const T &x, int\
    \ level) {\n    if(l >= r || t == nullptr) return 0;\n    if(level == -1) return\
    \ r - l;\n    bool f = (x >> level) & 1;\n    l = t->sid.rank(f, l), r = t->sid.rank(f,\
    \ r);\n    return rank(t->ch[f], l, r, x, level - 1);\n  }\n\n  int rank(const\
    \ T &x, int r) {\n    return rank(root, 0, r, x, MAXLOG - 1);\n  }\n\n  T kth_smallest(Node\
    \ *t, int l, int r, int k, int level) {\n    if(l >= r || t == nullptr) return\
    \ 0;\n    int cnt = t->sid.rank(false, r) - t->sid.rank(false, l);\n    bool f\
    \ = cnt <= k;\n    l = t->sid.rank(f, l), r = t->sid.rank(f, r);\n    if(f) return\
    \ kth_smallest(t->ch[f], l, r, k - cnt, level - 1) | ((T(1) << level));\n    return\
    \ kth_smallest(t->ch[f], l, r, k, level - 1);\n  }\n\n  // k-th(0-indexed) smallest\
    \ number in v[l,r)\n  T kth_smallest(int l, int r, int k) {\n    assert(0 <= k\
    \ && k < r - l);\n    return kth_smallest(root, l, r, k, MAXLOG - 1);\n  }\n\n\
    \  // k-th(0-indexed) largest number in v[l,r)\n  T kth_largest(int l, int r,\
    \ int k) {\n    return kth_smallest(l, r, r - l - k - 1);\n  }\n\n  int range_freq(Node\
    \ *t, int l, int r, T upper, int level) {\n    if(t == nullptr || l >= r) return\
    \ 0;\n    bool f = ((upper >> level) & 1);\n    int ret = 0;\n    if(f) ret +=\
    \ t->sid.rank(false, r) - t->sid.rank(false, l);\n    l = t->sid.rank(f, l), r\
    \ = t->sid.rank(f, r);\n    return range_freq(t->ch[f], l, r, upper, level - 1)\
    \ + ret;\n  }\n\n  // count i s.t. (l <= i < r) && (v[i] < upper)\n  int range_freq(int\
    \ l, int r, T upper) {\n    return range_freq(root, l, r, upper, MAXLOG - 1);\n\
    \  }\n\n  // count i s.t. (l <= i < r) && (lower <= v[i] < upper)\n  int range_freq(int\
    \ l, int r, T lower, T upper) {\n    return range_freq(l, r, upper) - range_freq(l,\
    \ r, lower);\n  }\n\n  // max v[i] s.t. (l <= i < r) && (v[i] < upper)\n  T prev_value(int\
    \ l, int r, T upper) {\n    int cnt = range_freq(l, r, upper);\n    return cnt\
    \ == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n  }\n\n  // min v[i] s.t. (l <=\
    \ i < r) && (lower <= v[i])\n  T next_value(int l, int r, T lower) {\n    int\
    \ cnt = range_freq(l, r, lower);\n    return cnt == r - l ? T(-1) : kth_smallest(l,\
    \ r, cnt);\n  }\n};\n\ntemplate< typename T, int MAXLOG >\nstruct CompressedWaveletTree\
    \ {\n  WaveletTree< int, MAXLOG > mat;\n  vector< T > ys;\n\n  CompressedWaveletTree(const\
    \ vector< T > &v) : ys(v) {\n    sort(begin(ys), end(ys));\n    ys.erase(unique(begin(ys),\
    \ end(ys)), end(ys));\n    vector< int > t(v.size());\n    for(int i = 0; i <\
    \ v.size(); i++) t[i] = get(v[i]);\n    mat = WaveletTree< int, MAXLOG >(t);\n\
    \  }\n\n  inline int get(const T &x) {\n    return lower_bound(begin(ys), end(ys),\
    \ x) - begin(ys);\n  }\n\n  int rank(const T &x, int r) {\n    auto pos = get(x);\n\
    \    if(pos == ys.size() || ys[pos] != x) return 0;\n    return mat.rank(pos,\
    \ r);\n  }\n\n  T kth_smallest(int l, int r, int k) {\n    return ys[mat.kth_smallest(l,\
    \ r, k)];\n  }\n\n  T kth_largest(int l, int r, int k) {\n    return ys[mat.kth_largest(l,\
    \ r, k)];\n  }\n\n  int range_freq(int l, int r, T upper) {\n    return mat.range_freq(l,\
    \ r, get(upper));\n  }\n\n  int range_freq(int l, int r, T lower, T upper) {\n\
    \    return mat.range_freq(l, r, get(lower), get(upper));\n  }\n\n  T prev_value(int\
    \ l, int r, T upper) {\n    auto ret = mat.prev_value(l, r, get(upper));\n   \
    \ return ret == -1 ? T(-1) : ys[ret];\n  }\n\n  T next_value(int l, int r, T lower)\
    \ {\n    auto ret = mat.next_value(l, r, get(lower));\n    return ret == -1 ?\
    \ T(-1) : ys[ret];\n  }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/wavelet/wavelet-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-range-kth-smallest-2.test.cpp
  - test/verify/aoj-2674-2.test.cpp
  - test/verify/aoj-1549-2.test.cpp
documentation_of: structure/wavelet/wavelet-tree.hpp
layout: document
redirect_from:
- /library/structure/wavelet/wavelet-tree.hpp
- /library/structure/wavelet/wavelet-tree.hpp.html
title: "Wavelet Tree(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u6728)"
---
## 概要

$2$ 次元平面上にある点が事前に与えられているとき, オンラインでいろいろなクエリを処理するデータ構造.

基本的には事前に要素の値を要素数に圧縮する CompressedWaveletTree を用いると高速に動作する.

ウェーブレット行列を用いたほうが時間と空間の計算量が良いため, 使い所なし. 悲しい.

## 使い方
* `WaveletTree(v)`: 各要素の高さ `v` を初期値として構築する.
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
