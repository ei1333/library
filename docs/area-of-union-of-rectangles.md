---
title: Area of Union of Rectangles (長方形の和集合の面積)
documentation_of: //other/area-of-union-of-rectangles.hpp
---

いくつかの長方形が与えられたときに、長方形の和集合の面積を求めます。

遅延伝搬セグメント木に、最小値と最小値の個数を求めるモノイドをのせます。

# コンストラクタ

```cpp
(1) AreaOfUnionOfRectangles< T >()
(2) AreaOfUnionOfRectangles< T >(int n)
```

`T` は座標が収まる型を指定してください。

(2) で長方形の個数 $n$ を指定した場合、領域を `reserve` するので少しだけ効率的です。

# add_rectangle

```cpp
void add_rectangle(T l, T d, T r, T u)
```

$\lbrace (x,y):l \leq x \leq r, d \leq y \leq u\rbrace$ で表される長方形を追加します。

## 制約

- $l \lt r$
- $d \lt u$

## 計算量

- $O(1)$ 

# calc

```cpp
template<typename T2>
T2 calc() const
```

長方形の和集合の面積を返します。

`T2` は面積が収まる型を指定してください。

## 計算量

- $O(n \log n)$
