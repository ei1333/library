---
title: Range Tree (領域木)
documentation_of: //structure/segment-tree/range-tree.hpp
---

領域木は、セグメント木のノードにデータ構造をのせることで、二次元クエリを処理できるデータ構造です。

# コンストラクタ

```cpp
RangeTree< K, Monoid2D >(Monoid2D m)
```

Monoid2D `m` の領域木をつくります。`K` は座標の型です。

## 計算量

- $O(1)$

## Monoid2D について

`Monoid2D` は、次の構造体と関数を持つ構造体です。

```cpp
template< typename T >
struct Monoid2D {
  using S = ?;
  using D = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
  static constexpr D init(int n) {}
  static constexpr void apply(D& d, int k, const S& v) {}
  static constexpr S prod(D& d, int l, int r) {}
};
```

- 型 `S`
- セグメント木のノードにのせるデータ構造の型 `D`
- 二項演算 `S op(S a, S b)`
- 単位元 `e()`
- データ構造をサイズ `n` で初期化するための関数 `D init(n)`
- データ構造 `d` の `k` 番目の要素を `v` で更新するための関数 `apply(d, k, v)`
- データ構造 `d` の区間 `[l, r)` を畳み込む演算 `S prod(d, l, r)`

# add_point

```cpp
void add_point(K x, K y)
```

点 $(x, y)$ を追加します。

## 計算量

- $O(1)$

# build

```cpp
void build()
```

領域木を構築します。`add_point` ですべての点を追加したあとに呼び出します。

## 計算量

- $O(n \log n)$

# apply

```cpp
void apply(K x, K y, S a)
```
 
点 `(x, y)` の要素を `a` で更新します。

## 制約

- `build()` をすでに呼び出している
- $(x, y)$ は `add_point` で追加された点

## 計算量

- $O(f(n) \log n)$

$f(n)$ は Monoid2D の `apply` の計算量です。

# prod

```cpp
S prod(K l, K d, K r, K u)
```

$l \leq x \lt r$ かつ $d \leq y \lt u$ を満たす点 $(x, y)$ に対して二項演算した結果を返します。

## 制約

- `build()` をすでに呼び出している

## 計算量

- $O(g(n) \log n)$

$g(n)$ は Monoid2D の `prod` の計算量です。
