---
documentation_of: //graph/flow/gabow-edmonds.hpp
---

## 概要

一般グラフの最大マッチングを, GabowのEdmonds' Algorithmによって求める。

グラフ $G=(V, E)$ において, $M$ が $E$ の部分集合でかつ $M$ のどの $2$ 辺も共通の端点をもたないとき, $M$ を $G$ のマッチングといい, 辺の本数が最大であるマッチングを最大マッチングという.

## 使い方

* `GabowEdmonds(n)`: 頂点数 `n` で初期化する
* `add_edge(u, v)`: 頂点 `u`, `v` 間に無向辺を張る
* `max_matching()`: 最大マッチングを求め, その辺集合を返す.

## 計算量

* $O(VE \log V)$
