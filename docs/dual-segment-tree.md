---
title: Dual Segment Tree (双対セグメント木)
documentation_of: //structure/segment-tree/dual-segment-tree.hpp
---

双対セグメント木は、遅延伝搬セグメント木の作用素モノイドのみを取り出したセグメント木です。

# コンストラクタ

```cpp
DualSegmentTree< Act >(Act m, int n)
```

作用素 `m`、サイズ `n` で初期化します。各要素には作用素の単位元 `m.id()` が格納されます。

## 計算量

- $O(n)$

## Act について

`Act` は、次の構造体と関数を持つ構造体です。

```cpp
struct Act {
  using F = ?;
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
```

- 作用素の型 `F`
- 作用素の二項演算 `F composition(F f, F g)`
- 作用素の単位元 `id()`

作用素 `F` は、単位元 `id()` と比較するために `!=` 演算子が定義されている必要があり ます。

## LambdaAct について

`LambdaAct` は、ラムダ式を受け取って、構造体 `Act` のようにふるまう構造体です 。`LambdaAct` の引数に `F composition(F f, F g)`、`id()` の順で渡すことで初期化できます。

```cpp
template< typename Composition, typename Id >
LambdaAct(Composition _composition, Id _id)
```

作用素 `F` は、単位元 `id()` と比較するために `!=` 演算子が定義されている必要があります。

# get

```cpp
F get(int k)
```

`k` 番目の要素を `x` に変更します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# operator[]

```cpp
F operator[](int k)
```

`k` 番目の作用素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# apply

```cpp
void apply(int l, int r, const F &f)
```

$l \leq k \lt r$ を満たす $k$ に対して、作用素を適用します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log n)$
