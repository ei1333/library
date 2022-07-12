---
title: Incremental Bridge Connectivity
documentation_of: //graph/connected-components/incremental-bridge-connectivity.hpp
---

## 概要

辺の追加クエリのみ存在するとき, 二重辺連結成分を効率的に管理するデータ構造.

## 使い方

* `IncrementalBridgeConnectivity(sz)`: `sz` 頂点で初期化する.
* `find(k)`: 頂点 `k` が属する二重辺連結成分(の代表元)を求める.
* `bridge_size()`: 現在の橋の個数を返す.
* `add_edge(x, y)`: 頂点 `x` と `y` との間に無向辺を追加する.

## 計算量

ならし $O(n \log n)$

## 参考
[Incremental Bridge-Connectivity - data-structures](https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity)
