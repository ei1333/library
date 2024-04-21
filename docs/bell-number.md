---
documentation_of: //math/combinatorics/bell-number.hpp
---

## 概要

ベル数 $B(n,k)$ を求める.

区別できる $n$ 個のボールを区別できない $k$ 個以下の箱に分割する方法の数を与える.

特に $B(n,n)$ は $n$ 個のボールを任意個のグループに分割する方法の数である.

* `bell_number(n, k)`: $B(n, k)$ を返す.

## 計算量

* $O(\min(n, k) \log n)$
