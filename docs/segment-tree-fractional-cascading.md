---
title: Segment Tree (Fractinal Cascading)
documentation_of: //structure/segment-tree/segment-tree-fractional-cascading.hpp
---

二次元平面上の長方形内の点の個数を数えるクエリをセグメント木によって求めます。

Fractional Cascading による高速化により、クエリあたり $O(\log n)$ で処理できます。

# コンストラクタ

```cpp
SegmentTreeFractionalCascading< T >(const vector<T> &v) 
```

1. 配列 `v` で初期化します。

## 計算量

- $O(n \log n)$

# prod

```cpp
S prod(int a, int b, T l, T r) const
```

$a \leq k \lt b$ かつ $l \leq v_k \lt r$ を満たす $k$ の個数を返します。

## 制約

- $0 \leq a \leq b \leq n$

## 計算量

- $O(\log n)$
