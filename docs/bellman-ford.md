---
title: Bellman-Ford (単一始点最短路)
documentation_of: //graph/shortest-path/dijkstra.hpp
---

単一始点全点間最短路を求めるアルゴリズムです。負辺があっても動作します。経路上に負閉路がある場合はそれを検出します。

# bellman_ford

```cpp
template <typename T>
vector<T> bellman_ford(const Edges<T> &edges, int n, int s)
```

頂点数 $n$ 、辺集合が `edges` からなる有向グラフについて、始点 $s$ から各頂点への最短路の重みを求め、それを返します。

ただし、始点 $s$ からその頂点に到達できない場合は `T` の最大値、その頂点までの経路上に負閉路が存在する場合は `T` の最小値が格納されます。

## 制約

- $0 \leq s \lt n$

## 計算量

* $O(V E)$
