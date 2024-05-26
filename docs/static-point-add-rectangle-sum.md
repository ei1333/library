---
title: Static Point Add Rectangle Sum
documentation_of: //other/static-point-add-rectangle-sum.hpp

---

2 次元平面上に重み付きの点が与えられます。

長方形内に含まれる点の重みの総和を求めるいくつかのクエリに答えます。

# コンストラクタ

```cpp
(1) StaticPointAddRectangleSum< T, C >()
(2) StaticPointAddRectangleSum< T, C >(int n, int q)
```

`T` は座標が収まる型、`C` は重みの総和が収まる型を指定してください。

(2) で点の個数 $n$、クエリの個数 $q$ を指定した場合、領域を `reserve` するので少しだけ効率的です。

# add_point

```cpp
void add_point(T x, T y, C w)
```

$(x, y)$ に重み $w$ の点を追加します。

# 計算量

- $O(1)$

# add_query

```cpp
void add_query(T l, T d, T r, T u)
```

$\lbrace (x,y):l \leq x \lt r, d \leq y \lt u\rbrace$ で表される長方形内にある点の重みの総和を求めるクエリを追加します。

## 制約

- $l \lt r$
- $d \lt u$

# 計算量

- $O(1)$

# calculate_queries

```cpp
vector<C> calculate_queries() const
```

それぞれのクエリの答えを返します。$i$ 番目の要素は $i$ 番目に追加したクエリの答えが格納されます。

## 計算量

- $O((n + q) \log (n + q))$
