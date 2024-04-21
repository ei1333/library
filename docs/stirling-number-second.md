---
documentation_of: //math/combinatorics/stirling-number-second.hpp
---

## 概要

第 2 種スターリング数 $\\{ {n \atop k} \\}$ を求める.

区別できる $n$ 個のボールを区別できない $k$ 個の箱に分割する方法の数を与える.

計算方法は包除原理の考え方に基づく. $k$ 個の箱のうち空箱があったら違反. 違反する個数で包除する. 具体的には $k$ 個の箱から $k-i$ 個選んだとして, それらの箱にボールを入れない方法の数 $({k \atop i})i^{n}$ を足し引きする.

$\displaystyle \\{ {n \atop k} \\} = { \frac {1}{k!} }  \sum_{i=0}^{k} {(-1)^{k-i} ({k \atop i})i^{n} }$

## 使い方

* `stirling_number_second(n, k)`: $\\{ \textstyle {n \atop k} \\}$ を返す.

## 計算量

* $O(k \log n)$
