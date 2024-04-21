---
documentation_of: //graph/mst/prim-fibonacchi-heap.hpp
---

## 概要

最小全域木(全域木のうち, その辺群の重みの総和が最小になる木)を求める.

通常の prim 法では `std::priority_queue` を使用していたが, これをフィボナッチヒープにすることで計算量を落とせる(実用上早くなるかは知らない).

* `prim_fibonacchi_heap(g)`: 連結な重み付きグラフ `g` の最小全域木を求める. `cost` には辺の重みの総和, `edges` にはそれを構成する辺が格納される.

## 計算量

* $O(V \log V + E)$ 
