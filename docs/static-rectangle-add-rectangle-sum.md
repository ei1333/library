---
title: Static Rectangle Add Rectangle Sum
documentation_of: //other/static-rectangle-add-rectangle-sum.hpp
---

2 次元平面があります。

最初に、長方形内のすべての点に重みを加算するクエリが与えられます。

その後、長方形内に含まれる点の重みの総和を求めるいくつかのクエリに答えます。

# コンストラクタ

```cpp
(1) StaticRectangleAddRectangleSum< T, C >()
(2) StaticRectangleAddRectangleSum< T, C >(int n, int q)
```

`T` は座標が収まる型、`C` は重みの総和が収まる型を指定してください。

(2) で長方形の個数 $n$、クエリの個数 $q$ を指定した場合、領域を `reserve` するので少しだけ効率的です。

# add_point

```cpp
void add_rectangle(T l, T d, T r, T u, C w)
```

$\lbrace (x,y):l \leq x \lt r, d \leq y \lt u\rbrace$ で表される長方形内にある点に重み $w$ を加算します。

## 制約

- $l \lt r$
- $d \lt u$

## 計算量

- $O(1)$

# add_query

```cpp
void add_query(T l, T d, T r, T u)
```

$\lbrace (x,y):l \leq x \lt r, d \leq y \lt u\rbrace$ で表される長方形内にある点の重みの総和を求めるクエリを追加します。

## 制約

- $l \lt r$
- $d \lt u$

## 計算量

- $O(1)$

# calculate_queries

```cpp
vector<C> calculate_queries() const
```

それぞれのクエリの答えを返します。$i$ 番目の要素は $i$ 番目に追加したクエリの答えが格納されます。

## 計算量

- $O((n + q) \log (n + q))$
