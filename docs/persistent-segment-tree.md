---
title: Persistent Segment Tree (永続セグメント木)
documentation_of: //structure/segment-tree/persistent-segment-tree.hpp
---

セグメント木は、モノイドについて区間に対する演算が $O(\log N)$ で処理できます。

モノイドは次の条件を満たす代数的構造です。

* 結合律を満たします。つまり $S$ の各元 $a, b, c$ に対して、$(a \cdot b) \cdot c = a \cdot (b \cdot c)$ を満たします。
* 単位元を持ちます。つまり $S$ の任意の元 $a$ をとってきたときに $a \cdot e = e \cdot a = a$ なる $e$ が存在します。

永続セグメント木は、セグメント木を永続にしたデータ構造です。

# コンストラクタ

```cpp
PersistentSegmentTree< Monoid >(Monoid m, int n)
```

モノイド `m`、サイズ `n` で初期化します。

## 計算量

- $O(1)$

## Monoid について

`Monoid` は、次の構造体と関数を持つ構造体です。

```cpp
struct Monoid {
  using S = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
};
```

- 型 `S`
- 二項演算 `S op(S a, S b)`
- 単位元 `e()`

例えば、区間和を求めたい場合は次の構造体を定義して、`SegmentTree` に渡します。

```cpp
struct RangeSum {
  using S = int;
  static constexpr S op(const S& a, const S& b) { return a + b; }
  static constexpr S e() { return 0; }
};

PersistentSegmentTree seg(RangeSum());
```

## LambdaMonoid について

`LambdaMonoid` は、ラムダ式を受け取って、構造体 `Monoid` のようにふるまう構造体です。`LambdaMonoid` の引数に二項演算 `S op(S a, S b)`、単位元 `e()` の順で渡すことで初期化できます。

```cpp
template< typename Op, typename E >
LambdaMonoid(Op _op, E _e)
```

例えば、区間和を求めたい場合はラムダ式を使って次のように書くこともできます。

```cpp
auto op = [](int a, int b) { return a + b; };
auto e = []() { return 0; };
PersistentSegmentTree seg(LambdaMonoid(op, e));
```

# build

```cpp
NP build(const vector<S> &v) const
```

配列 `v` で初期化して、セグメント木のポインタを返します。

## 制約

- コンストラクタで渡した `n` と `v` の長さが一致する

## 計算量

- $O(n)$

# set

```cpp
NP set(NP t, int k, const S &x) const
```
 
セグメント木 `t` の `k` 番目の要素を `x` に変更して、新しいセグメント木へのポインタを返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# get

```cpp
S get(NP t, int k) const
```

セグメント木 `t` の `k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(1)$

# apply

```cpp
void apply(NP t, int k, const S &x)
```

セグメント木 `t` の `k` 番目の要素を、その要素と `x` を二項演算した値に変更し、新しいセグメント木へのポインタを返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(\log n)$

# prod

```cpp
S prod(NP t, int l, int r) const
```

セグメント木 `t` の区間 $[l, r)$ に対して二項演算した結果を返します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log n)$

# all_prod

```cpp
S all_prod(NP t) const
```

セグメント木 `t` のすべての要素を二項演算した結果を返す。

## 計算量

- $O(1)$
