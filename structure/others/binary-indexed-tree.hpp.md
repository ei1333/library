---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other/dynamic-point-add-rectangle-sum.hpp
    title: Dynamic Point Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: other/static-point-add-rectangle-sum.hpp
    title: Static Point Add Rectangle Sum
  - icon: ':warning:'
    path: other/static-rectangle-add-rectangle-sum.hpp
    title: Static Rectangle Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
    title: Wavelet Matrix Point Add Rectangle Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2270.test.cpp
    title: test/verify/aoj-2270.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dsl-2-b.test.cpp
    title: test/verify/aoj-dsl-2-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-rectangle-sum-2.test.cpp
    title: test/verify/yosupo-rectangle-sum-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-static-range-inversions-query.test.cpp
    title: test/verify/yosupo-static-range-inversions-query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/binary-indexed-tree.md
    document_title: Binary-Indexed-Tree(BIT)
    links: []
  bundledCode: "#line 1 \"structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief\
    \ Binary-Indexed-Tree(BIT)\n * @docs docs/binary-indexed-tree.md\n */\ntemplate<\
    \ typename T >\nstruct BinaryIndexedTree {\nprivate:\n  int n;\n  vector< T >\
    \ data;\n\npublic:\n  BinaryIndexedTree() = default;\n\n  explicit BinaryIndexedTree(int\
    \ n) : n(n) {\n    data.assign(n + 1, T());\n  }\n\n  explicit BinaryIndexedTree(const\
    \ vector< T > &v) :\n      BinaryIndexedTree((int) v.size()) {\n    build(v);\n\
    \  }\n\n  void build(const vector< T > &v) {\n    assert(n == (int) v.size());\n\
    \    for(int i = 1; i <= n; i++) data[i] = v[i - 1];\n    for(int i = 1; i <=\
    \ n; i++) {\n      int j = i + (i & -i);\n      if(j <= n) data[j] += data[i];\n\
    \    }\n  }\n\n  void apply(int k, const T &x) {\n    for(++k; k <= n; k += k\
    \ & -k) data[k] += x;\n  }\n\n  T prod(int r) const {\n    T ret = T();\n    for(;\
    \ r > 0; r -= r & -r) ret += data[r];\n    return ret;\n  }\n\n  T prod(int l,\
    \ int r) const {\n    return prod(r) - prod(l);\n  }\n\n  int lower_bound(T x)\
    \ const {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1)\
    \ {\n      if(i + k <= n && data[i + k] < x) {\n        x -= data[i + k];\n  \
    \      i += k;\n      }\n    }\n    return i;\n  }\n\n  int upper_bound(T x) const\
    \ {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n \
    \     if(i + k <= n && data[i + k] <= x) {\n        x -= data[i + k];\n      \
    \  i += k;\n      }\n    }\n    return i;\n  }\n};\n"
  code: "/**\n * @brief Binary-Indexed-Tree(BIT)\n * @docs docs/binary-indexed-tree.md\n\
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
    \  x -= data[i + k];\n        i += k;\n      }\n    }\n    return i;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/others/binary-indexed-tree.hpp
  requiredBy:
  - structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
  - other/static-rectangle-add-rectangle-sum.hpp
  - other/static-point-add-rectangle-sum.hpp
  - other/dynamic-point-add-rectangle-sum.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-rectangle-sum-2.test.cpp
  - test/verify/aoj-dsl-2-b.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - test/verify/aoj-2270.test.cpp
  - test/verify/yosupo-static-range-inversions-query.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
documentation_of: structure/others/binary-indexed-tree.hpp
layout: document
redirect_from:
- /library/structure/others/binary-indexed-tree.hpp
- /library/structure/others/binary-indexed-tree.hpp.html
title: Binary-Indexed-Tree(BIT)
---
## 概要

Fenwick Tree とも呼ばれる. 数列に対し, ある要素に値を加える操作と, 区間和を求める操作をそれぞれ対数時間で行うことが出来るデータ構造. セグメント木や平衡二分探索
木の機能を制限したものであるが, 実装が非常に単純で定数倍も軽いなどの利点がある.

## 使い方

* `BinaryIndexedTree(sz)`: 長さ `sz` の $0$ で初期化された配列で構築する.
* `BinaryIndexedTree(vs)`: 配列 `vs` で構築する.
* `apply(k, x)`: 要素 `k` に値 `x` を加える.
* `prod(r)`: 区間 $[0,r)$ の総和を求める.
* `prod(l, r)`: 区間 $[l, r)$ の総和を求める.
* `lower_bound(x)`: 区間 $[0,k]$ の総和が `x` 以上となる最小の $k$ を返す. 数列が単調増加であることを要求する.
* `upper_bound(x)`: 区間 $[0,k]$ の総和が `x` を上回る最小の $k$ を返す. 数列>が単調増加であることを要求する.

## 計算量

* 構築: $O(N)$
* クエリ: $O(\log N)$
