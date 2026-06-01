---
title: Priority Sum Structure
documentation_of: //structure/others/priority-sum-structure.hpp
---

`PrioritySumStructure` は、要素の追加・削除を行いながら、優先度の高い $k$ 個の総和を管理するデータ構造です。

`MaximumSum` は大きい方から $k$ 個、`MinimumSum` は小さい方から $k$ 個の総和を管理します。

```cpp
template <typename T>
using MaximumSum = PrioritySumStructure<T, greater<T>, less<T> >;

template <typename T>
using MinimumSum = PrioritySumStructure<T, less<T>, greater<T> >;
```

# コンストラクタ

```cpp
PrioritySumStructure<T>(int k)
```

優先度の高い $k$ 個の総和を管理するデータ構造を初期化します。

## 計算量

- $O(1)$

# query

```cpp
T query() const
```

現在の要素のうち、優先度の高い $k$ 個の総和を返します。

`MaximumSum` では大きい方から $k$ 個、`MinimumSum` では小さい方から $k$ 個の総和を返します。

## 計算量

- $O(1)$

# kth_element

```cpp
T kth_element()
```

現在の $k$ 番目 (1-indexed) の要素を返します。

`MaximumSum` では $k$ 番目に大きい値、`MinimumSum` では $k$ 番目に小さい値を返します。

## 計算量

- amortized $O(\log n)$

# insert

```cpp
void insert(T x)
```

要素 $x$ を追加します。

## 計算量

- amortized $O(\log n)$

# erase

```cpp
void erase(T x)
```

要素 $x$ を 1 つ削除します。

## 制約

- $x$ が存在する

## 計算量

- amortized $O(\log n)$

# set_k

```cpp
void set_k(size_t kk)
```

管理する要素の個数を `kk` に変更します。

## 計算量

- amortized $O(\log n)$

# get_k

```cpp
size_t get_k() const
```

現在の $k$ を返します。

## 計算量

- $O(1)$

# size

```cpp
size_t size() const
```

現在の要素数を返します。

## 計算量

- $O(1)$
