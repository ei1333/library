---
title: Static Range Frequency (区間の値の出現回数)
documentation_of: //other/static-range-frequency.hpp
---

数列が与えられたときに、ある値が出現する回数を求めるクエリを処理します。

# コンストラクタ

```cpp
StaticRangeFrequency< T >(const vector<T> &xs)
```

数列を `xs` で初期化します。

`T` は `vs` の各要素の型です。

## 計算量

- $O(n \log n)$

# query

```cpp
size_t query(int l, int r, T x) const
```

$xs[l, r)$ に $x$ が出現する回数を返します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log n)$
