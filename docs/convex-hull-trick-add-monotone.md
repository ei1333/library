---
title: Convex Hull Trick Add Monotone
documentation_of: ///structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
---

次のクエリを考えます。

1. $a$ $b$: 直線 $y = ax + b$ を追加する
2. $p$: $x = p$ での $y$ 座標の最小値を求める

与えられる $a$ が広義単調増加（または広義単調減少）のとき、追加クエリを $O(1)$、最小値クエリを $O(\log n)$ で処理します。

さらに $p$ が広義単調増加（または広義単調減少）のとき、最小値クエリを $O(1)$ で処理します。

# コンストラクタ

```cpp
ConvexHullTrickAddMonotone< T, isMin >()
```

`T` は値の型です。`isMin` が `true` のとき $y$ 座標の最小値、`false` のとき最大値を求めます。

## 計算量

- $O(1)$

# empty

```cpp
bool empty() const
```

直線が存在しないとき `true`、存在するとき `false` を返します。

## 計算量

- $O(1)$ 

# clear

```cpp
void clear()
```

すべての直線を削除します。

## 計算量

- $O(n)$

# add

```cpp
void add(T a, T b)
```

直線 $y = ax + b$ を追加します。

## 計算量

- amortized $O(1)$

# query

```cpp
T query(T x) const
```

`isMin` が `true` のとき $x$ での $y$ 座標の最小値、`false` のとき最大値を返します。

## 制約

- 直線が存在する
- 過去に `query_monotone_inc` と `query_monotone_dec` を呼びだしていない

## 計算量

- $O(\log n)$

# query_monotone_inc

```cpp
T query_monotone_inc(T x)
```

`isMin` が `true` のとき $x$ での $y$ 座標の最小値、`false` のとき最大値を返します。

## 制約

- 直線が存在する
- $x$ は広義単調増加
- 過去に `query` と `query_monotone_dec` を呼びだしていない

## 計算量

- amortized $O(1)$

# query_monotone_dec

```cpp
T query_monotone_dec(T x)
```

`isMin` が `true` のとき $x$ での $y$ 座標の最小値、`false` のとき最大値を返します。

## 制約

- 直線が存在する
- $x$ は広義単調減少
- 過去に `query` と `query_monotone_inc` を呼びだしていない

## 計算量

- amortized $O(1)$
