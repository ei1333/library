---
documentation_of: //graph/shortest-path/dijkstra-fibonacchi-heap.hpp
---

## 概要

負辺のないグラフで単一始点全点間最短路を求めるアルゴリズム.

通常の dijkstra 法では `std::priority_queue` を使用していたが, これをフィボナッチヒープにすることで計算量を落とせる(実用上早くなるかは知らない).

* `dijkstra_fibonacchi_heap(g, s)`: 重み付きグラフ `g` で, 頂点 `s` から全点間の最短距離を求める. 到達できない頂点には, 型の最大値が格納される.

## 計算量

* $O(V \log V + E)$
~

