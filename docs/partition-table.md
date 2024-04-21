---
documentation_of: //math/combinatorics/partition-table.hpp
---

## 概要

分割数 $P(n, k)$ は整数 $n$ をちょうど $k$ 個の非負整数の和で表す方法の数を与える. 順序が異なるものは同一視する.

* `partition_table(n, k)`: 各 $i \leq n, j \leq k$ に対し分割数 $P(n, k)$ を求める.

## 計算量

* $O(nk)$
