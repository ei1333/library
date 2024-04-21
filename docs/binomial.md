---
documentation_of: //math/combinatorics/binomial.hpp
---

## 概要

二項係数 ${}_n \mathrm{C} _k$ を $\displaystyle \frac {k(k-1)\dots (n-k+1)} {k(k-1)\dots 1}$ を利用して求める.

$k$ が小さい時に有効.

## 使い方

* `binomial(N, K)`: ${}_n \mathrm{C} _k$ を返す. 

## 計算量

* $O(K \log K)$

ただし逆元が $O(1)$ で求まる場合 $O(K)$
