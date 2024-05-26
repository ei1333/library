---
title: Dynamic Rectangle Add Point Get
documentation_of: //other/dynamic-point-add-rectangle-sum.hpp
---

2 次元平面上に重み付きの長方形を追加するクエリと、ある点を含む長方形の重みの総和を求めるいくつかのクエリに答えます。

# コンストラクタ

```cpp
(1) DynamicRectangleAddPointGet< T, C >()
(2) DynamicRectangleAddPointGet< T, C >(int q)
```

`T` は座標が収まる型、$C$ は重みの総和が収まる型を指定してください。

(2) でクエリの個数 $q$ を指定した場合、領域を `reserve` するので少しだけ効率的です。

# add_rectangle

```cpp
add_rectangle(T l, T d, T r, T u, C w)
```

$\lbrace (x,y):l \leq x \leq r, d \leq y \leq u\rbrace$ で表される重み $w$ の長方形を追加するクエリを追加します。

## 制約

- $l \lt r$
- $r \lt u$

# 計算量

- $O(1)$

# add_query

```cpp
void add_query(T x, T y)
```

$(x, y)$ に含む長方形の重みの総和を求めるクエリを追加します。

# 計算量

- $O(1)$

# calculate_queries

```cpp
vector<C> calculate_queries() const
```

それぞれのクエリの答えを返します。$i$ 番目の要素は $i$ 番目に追加した `add_query` クエリの答えが格納されます。

## 計算量

- $O((n + q) \log^2 (n + q))$
