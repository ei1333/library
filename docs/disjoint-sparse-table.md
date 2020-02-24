## 概要

更新がない場合の半群に対する区間クエリを, 前計算 $O(n \log n)$, クエリ $O(1)$ で処理する.

* `DisjointSparseTable(v, f)`: 配列 `v` で初期化する. `f` は半群をマージする二項演算である.
* `query(l, r)`: 区間 $[l, r)$ を演算した結果を返す.

## 計算量

* `DisjointSparseTable(v, f)`: $O(N \log N)$
* `query(l, r)`: $O(1)$
