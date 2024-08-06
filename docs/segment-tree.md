---
title: Segment Tree (セグメント木)
documentation_of: //structure/segment-tree/segment-tree.hpp
---

セグメント木は、モノイドについて区間に対する演算が $O(\log N)$ で処理できます。

モノイドは次の条件を満たす代数的構造です。

* 結合律を満たします。つまり $S$ の各元 $a, b, c$ に対して、$(a \cdot b) \cdot c = a \cdot (b \cdot c)$ を満たします。
* 単位元を持ちます。つまり $S$ の任意の元 $a$ をとってきたときに $a \cdot e = e \cdot a = a$ なる $e$ が存在します。

以下の実装では木を 1-indexed の配列で表現しています。ノード $k$ について、親ノードは $\frac k 2$, 子ノードは $2k$, $2k+1$ です。

# コンストラクタ

```cpp
(1) SegmentTree< Monoid >(Monoid m, int n)
(2) SegmentTree< Monoid >(Monoid m, const vector<S> &v) 
```

1. モノイド `m`、サイズ `n` で初期化します。各要素には単位元 `m.e()` が格納されます。
2. モノイド `m`、配列 `v` で初期化します。

## 計算量

- $O(n)$

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

SegmentTree seg(RangeSum(), n);
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
SegmentTree seg(LambdaMonoid(op, e), n);
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
S get(int k) const
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(1)$

# operator[]

```cpp
S operator[](int k) const
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

すべての要素を二項演算した結果を返します。

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
