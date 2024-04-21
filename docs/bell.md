---
documentation_of: //math/fps/bell.hpp
---

## 概要

ベル数を求める。$n$ 番目(0-indexed) のベル数 $B_n$ は区別できる $n$ 個のボールを任意個のグループに分割する方法の数を与える。

ベル数の母関数 $B(x)$ は以下によって計算される。

$\displaystyle B(x) = \sum_{n=0}^{\infty} B_n \frac {x^n} {n!} = e^{e^x-1}$

## 使い方

* `bell(n)`: $B_0, B_1, \cdots, B_n$ を返す。

## 計算量

* $O(n \log n)$
