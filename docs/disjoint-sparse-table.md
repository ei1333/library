---
documentation_of: //structure/others/disjoint-sparse-table.hpp
---

## 概要

更新がない場合の半群に対する区間クエリを, 前計算 $O(n \log n)$, クエリ $O(1)$ で処理する.

## 使い方

* `DisjointSparseTable(v, f)`: 配列 `v` で初期化する. `f` は半群をマージする二項演算である.
* `fold(l, r)`: 区間 $[l, r)$ を演算した結果を返す.

## 計算量

* `DisjointSparseTable(v, f)`: $O(N \log N)$
* `fold(l, r)`: $O(1)$
