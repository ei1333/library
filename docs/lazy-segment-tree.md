---
title: Lazy Segment Tree (遅延伝搬セグメント木)
documentation_of: //structure/segment-tree/lazy-segment-tree.hpp
---

セグメント木に遅延伝搬の機能を追加することで、区間に対して一様に作用素を作用させる操作が可能になります。

# コンストラクタ

```cpp
(1) LazySegmentTree< ActedMonoid >(ActedMonoid m, int n)
(2) LazySegmentTree< ActedMonoid >(ActedMonoid m, const vector<S> &v)
```

1. 作用素付きモノイド `m`、サイズ `n` で初期化します。各要素には単位元 `m.e()` が格納されます。
2. 作用素付きモノイド `m`、配列 `v` で初期化します。

## 計算量

- $O(n)$

## ActedMonoid について

`ActedMonoid` は、次の構造体と関数を持つ構造体です。

```cpp
struct ActedMonoid {
  using S = ?;
  using F = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
  static constexpr F mapping(const S& x, const F &f) {}
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
```

- モノイドの型 `S`
- 作用素の型 `F`
- モノイドの二項演算 `S op(S a, S b)`
- モノイドの単位元 `e()`
- 作用素をモノイドに適用する関数 `S mapping(S x, F f)`
- 作用素の二項演算 `F composition(F f, F g)`
- 作用素の単位元 `id()`

作用素 `F` は、単位元 `id()` と比較するために `!=` 演算子が定義されている必要があります。


## LambdaActedMonoid について

`LambdaActedMonoid` は、ラムダ式を受け取って、構造体 `ActedMonoid` のようにふるまう構造体です 。`LambdaActedMonoid` の引数に `S op(S a, S b)`、`e()`、`S mapping(S x, F f)`、`F composition(F f, F g)`、`id()` の順で渡すことで初期化できます。

```cpp
template< typename Op, typename E, typename Mapping, typename Composition, typename Id >
LambdaActedMonoid(Op _op, E _e, Mapping _mapping, Composition _composition, Id _id)
```

# build

```cpp
void build(const vector<S> &v)
```

配列 `v` で初期化します。

## 制約

- コンストラクタで渡した `n` と `v` の長さが一致する

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
S get(int k)
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# operator[]

```cpp
S operator[](int k)
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# prod

```cpp
S prod(int l, int r)
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

すべての要素を二項演算した結果を返します。

## 計算量

- $O(1)$

# apply

```cpp
(1) void apply(int k, const F &f)
(2) void apply(int l, int r, const F &f)
```

1. `k` 番目の要素に対して作用素を適用します。
2. $l \leq k \lt r$ を満たす $k$ に対して作用素を適用します。

## 制約

- $0 \leq k \lt n$
- $0 \leq l \leq r \leq n$ 

## 計算量

- $O(\log n)$

# find_first

```cpp
template <typename C>
int find_first(int l, const C &check)
```

$[a, x)$ が `check` を満たす最初の要素位置 $x$ を返します。存在しないとき $n$ を返します。

## 制約

- $0 \leq l \leq n$

## 計算量

- $O(\log n)$

# find_last

```cpp
template <typename C>
int find_last(int r, const C &check)
```

$[x, b)$ が `check` を満たす最後の要素位置 $x$ を返します。存在しないとき $-1$ を返 します。

## 制約

- $0 \leq r \leq n$

## 計算量

- $O(\log n)$
