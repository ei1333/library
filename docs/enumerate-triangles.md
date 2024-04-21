---
documentation_of: //graph/others/enumerate-triangles.hpp
---

## 概要

グラフの triangle, つまり互いに辺で隣接している $3$ 頂点を列挙する.

triangle の個数は高々 $M \sqrt {2M}$ 個である. それぞれの辺を次数が小さい頂点から大きい頂点に向かうように向きづけすると, DAG になる. このときどの頂点の出次数も $\sqrt {2M}$ を超えないことを示せる. その上で, 各辺についてその始点と終点から同じ頂点に辺が出ているかどうか調べれば良い.

## 使い方

* `enumerate_triangles(g)`: グラフ `g` の triangle を全て返す.

## 計算量

* $O(M \sqrt {M})$

$M$: 辺の本数
