---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-static-range-sum.test.cpp
    title: test/verify/yosupo-static-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"dp/cumulative-sum.hpp\"\ntemplate< class T >\nstruct CumulativeSum\
    \ {\n  vector< T > data;\n\n  CumulativeSum() = default;\n\n  explicit CumulativeSum(size_t\
    \ sz) : data(sz + 1, 0) {}\n\n  void add(int k, const T &x) {\n    data[k + 1]\
    \ += x;\n  }\n\n  void build() {\n    for(int i = 1; i < data.size(); i++) {\n\
    \      data[i] += data[i - 1];\n    }\n  }\n\n  T fold(int r) const {\n    if(r\
    \ < 0) return 0;\n    return data[min(r, (int) data.size() - 1)];\n  }\n\n  T\
    \ fold(int l, int r) const {\n    return fold(r) - fold(l);\n  }\n};\n"
  code: "template< class T >\nstruct CumulativeSum {\n  vector< T > data;\n\n  CumulativeSum()\
    \ = default;\n\n  explicit CumulativeSum(size_t sz) : data(sz + 1, 0) {}\n\n \
    \ void add(int k, const T &x) {\n    data[k + 1] += x;\n  }\n\n  void build()\
    \ {\n    for(int i = 1; i < data.size(); i++) {\n      data[i] += data[i - 1];\n\
    \    }\n  }\n\n  T fold(int r) const {\n    if(r < 0) return 0;\n    return data[min(r,\
    \ (int) data.size() - 1)];\n  }\n\n  T fold(int l, int r) const {\n    return\
    \ fold(r) - fold(l);\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: dp/cumulative-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-static-range-sum.test.cpp
documentation_of: dp/cumulative-sum.hpp
layout: document
title: "Cumulative Sum(\u4E00\u6B21\u5143\u7D2F\u7A4D\u548C)"
---

## 概要

$1$ 次元の累積和. 前計算として事前に累積和をとることで, 区間の和を $O(1)$ で求めることが出来る.


## 使い方

* `add(k, x)`: 要素 `k` に値 `x` を加える.
* `build()`: 累積和を構築する.
* `fold(r)`: 区間 $[0, k)$ の和を返す.
* `fold(l, r)`: 区間 $[l, r)$ の和を返す.

## 計算量

* `add(k, x)`: $O(1)$
* `build()`: $O(N)$
* `fold(r)`: $O(1)$
* `fold(l, r)`: $O(1)$
