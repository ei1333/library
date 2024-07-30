---
title: Segment Tree
documentation_of: //structure/segment-tree/segment-tree.hpp
---

完全二分木です。モノイドについて区間に対する演算が $O(\log N)$ で処理できます。

モノイドは次の条件を満たす代数的構造です。

* 結合律を満たします。つまり $S$ の各元 $a, b, c$ に対して, $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ を満たします。
* 単位元を持ちます。つまり $S$ の任意の元 $a$ をとってきたときに $a \cdot e = e \cdot a = a$ なる $e$ が存在します。

以下の実装では木を 1-indexed の配列で表現しています。ノード $k$ について、親ノードは $\frac k 2$, 子ノードは $2k$, $2k+1$ です。

# コンストラクタ

```cpp
(1) SegmentTree< Monoid >(Monoid m, int n)
(2) SegmentTree< Monoid >(Monoid m, const vector<S> &v) 
```

(1) モノイド `m`、サイズ `n` で初期化します。
(2) モノイド `m`、配列 `v` で初期化します。

`m` は各要素の型 `S`、二項演算 `op`、単位元 `e` を返す構造体です。

```cpp
struct Monoid {
  using S = int;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
};
```


## 計算量

- $O(n)$


# build

```cpp
void build(const vector<S> &v)
```

配列 `v` で初期化します。

## 計算量

- $O(n)$

# set

```cpp
void set(int k, const S &x)
```
 
`k` 番目の要素を `x` に変更します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# get

```cpp
S get(int k) const
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(1)$

# operator[]

```cpp
S operator[](const int &k) const
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(1)$

# apply

```cpp
void apply(int k, const S &x)
```

`k` 番目の要素を、その要素と `x` を二項演算した値に変更します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# prod

```cpp
S prod(int l, int r) const
```

区間 $[l, r)$ に対して二項演算した結果を返します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log n)$

# all_prod

```cpp
S all_prod() const
```

すべての要素を二項演算した結果を返す。

## 計算量

- $O(1)$

# find_first

```cpp
template <typename C>
int find_first(int l, const C &check) const 
```

$[a, x)$ が `check` を満たす最初の要素位置 $x$ を返します。存在しないとき $n$ を返します。

## 制約

- $0 \leq l \leq n$

## 計算量

- $O(\log n)$

# find_last

```cpp
template <typename C>
int find_last(int r, const C &check) const
```

$[x, b)$ が `check` を満たす最後の要素位置 $x$ を返します。存在しないとき $-1$ を返します。

## 制約

- $0 \leq r \leq n$

## 計算量

- $O(\log n)$
