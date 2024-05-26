---
title: Static Range Count Distinct (区間の値の種類数)
documentation_of: //other/static-range-count-distinct.hpp
---

数列が与えられたときに、区間の値の種類数を求めるクエリを処理します。

# コンストラクタ

```cpp
StaticRangeCountDistinct< T >(const vector<T> &vs)
```

数列を `vs` で初期化します。

`T` は `vs` の各要素の型です。

## 計算量

- $O(n)$

# add_query

```cpp
void add_query(int l, int r)
```

$vs[l, r)$ に現れる値の種類数を求めるクエリを追加します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(1)$

# calculate_queries

```cpp
vector< size_t > calclate_queries() const
```

それぞれのクエリの答えを返します。$i$ 番目の要素は $i$ 番目に追加したクエリの答えが格納されます。

## 計算量

- $O((n + q) \log n)$
