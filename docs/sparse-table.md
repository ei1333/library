---
documentation_of: //structure/others/sparse-table.hpp
---

## 概要

冪等半群に対する区間クエリを, 前計算 $\Theta (n \log n)$, クエリ $\Theta (1)$ で処理する.

* `SparseTable(v, f)`: 配列 `v`, 演算 $f$ で初期化する.
* `fold(l, r)`: 区間 $[l, r)$ の演算結果を返す.

## 計算量

* `SparseTable(v)`: $\Theta (N \log N)$
* `fold(l, r)`: $\Theta (1)$
