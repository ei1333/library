---
title: Binary Indexed Tree
documentation_of: //structure/others/binary-indexed-tree.hpp
---

Fenwick Tree とも呼ばれます。 数列に対し、ある要素に値を加える操作と、区間和を求める操作をそれぞれ対数時間で行うことが出来るデータ構造です。セグメント木や平衡二分探索木の機能を制限したものですが、実装が非常に単純で定数倍も軽いなどの利点があります。

# コンストラクタ

```cpp
(1) BinaryIndexedTree(int n)
(2) BinaryIndexedTree(const vector<T> &v)
```

1. 数列を長さ `n` で初期化します。各要素は $0$ です。
2. 数列の各要素を 配列 `v` で初期化します。

## 計算量

- $O(n)$

# build

```cpp
void build(const vector<T> &v)
```

数列の各要素を配列 `v` で初期化します。

## 制約

- `n` と `v` の長さが一致する

## 計算量

- $O(n)$

# apply

```cpp
void apply(int k, const T &x)
```

`k` 番目の要素に値 `x` を加えます。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# prod

```cpp
(1) T prod(int r) const 
(2) T prod(int l, int r) const
```

1. 数列の区間 $[0, r)$ の要素の総和を返します。
2. 数列の区間 $[l, r)$ の要素の総和を返します。

## 制約

- $0 \leq l \leq r \leq n$

# lower_bound

```cpp
int lower_bound(T x) const
```

数列の区間 $[0,k]$ の要素の総和が $x$ 以上となる最小の $k$ を返します。

## 制約

- 数列は広義単調増加

## 計算量

- $O(\log n)$

## upper_bound

```cpp
int upper_bound(T x) const
```

数列の区間 $[0,k]$ の要素の総和が $x$ を上回る最小の $k$ を返します。

## 制約

- 数列は広義単調増加

## 計算量

* $O(\log n)$
