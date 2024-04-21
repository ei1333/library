---
documentation_of: //graph/flow/dinic-capacity-scaling.hpp
---

## 概要

最大流を求めるアルゴリズム.

すべての辺の容量が整数の場合, スケーリングを用いて Dinic の計算量を $O(EV \log U)$ に落とすことが出来る($U$ は辺の容量の最大値).

具体的には, フローを残余グラフ上で $k$ が大きい方から $2^k$ 単位で流すようにする.


## 使い方

* `DinicCapacityScaling(V)`: 頂点数 `V` で初期化する.
* `add_edge(from, to, cap, idx = -1)`: 頂点 `from` から `to` に容量 `cap` の辺を追加する.
* `max_flow(s, t)`: 頂点 `s` から `t` に最大流を流し, その流量を返す.

## 計算量

$O(EV \log U)$

$U$ は辺の容量の最大値
