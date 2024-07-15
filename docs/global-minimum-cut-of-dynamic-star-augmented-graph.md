---
title: Global Minimum Cut of Dynamic Star Augmented Graph
documentation_of: //graph/flow/global-minimum-cut-of-dynamic-star-augmented-graph.hpp
---

重み付き無向グラフ $G$ が与えられます。

頂点 $N$ を追加して、頂点 $i$ と頂点 $N$ との間に重み $a_i$ の辺を張ることによって得られるグラフを $H$ とします。

このとき、「$H$ 上の頂点 $x_i$ と頂点 $N$ との間に張られている辺の重みを $y_i$ に変更して、$H$ の全域最小カットの重みを求めるクエリ」を効率的に処理します。

# コンストラクタ

```cpp
GlobalMinimumCutofDynamicStarAugmentedGraph< T >(int n, const Edges<T> &es)
```

頂点数 $n$、辺が `es` からなる $G$ として $H$ を初期化します。

## 制約

- $G$ は頂点数 $n$ からなる非負重み付き単純無向グラフ

## 計算量

- $O(nm + n^2 \log n)$

# update

```cpp
T update(int v, T cost)
```

頂点 $v$ と頂点 $N$ との間に張られている辺の重みを `cost` に変更して、$H$ の全域最小カットの重みを返します。

## 制約

- $0 \leq v \lt n$

## 計算量

- $O(\log^2 n)$
