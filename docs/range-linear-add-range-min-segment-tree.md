---
title: Range Linear Add Range Min Segment Tree
documentation_of: //structure/segment-tree/range-linear-add-range-min-segment-tree.hpp
---

区間等差数列加算クエリと区間 min を求めるクエリを扱うセグメント木です。

セグメント木のノードに下側凸包を持ちます。

# コンストラクタ

```cpp
RangeLinearAddRangeMinSegmentTree< T, T2, T3 >(const vector< T > &vs, const T &ti)
```

`vs` で初期化します。`ti` は単位元です。

`T` は 1 要素が収まる型、`T2` は `T` の最大値 * 要素数、`T3` は `T` の最大値 * (要素数)^2 が収まる型を指定してください。

`T` は加算後に取りうる値の最大値であることに注意してください。

## 計算量

- $O(n \log^2 n)$

# prod

```cpp
T prod(int l, int r)
```

区間 $[l, r)$ の要素のうち、最小値を求めます。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log^2 n)$

## apply

```cpp
void apply(int l, int r, T a, T b)
```

区間 $[l, r)$ の各要素 $i$ について、$a \times i + b$ を加算します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(\log^2 n)$
