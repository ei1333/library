---
title: Extreme Vertex Set
documentation_of: //graph/others/extreme-vertex-set.hpp
---

重み付き無向グラフ $G$ が与えられたとき、$G$ の Extreme Vertex Set（極点集合）をすべて列挙します。

# extreme_vertex_set

```cpp
template<typename T>
Graph<T> extreme_vertex_set(int n, const Edges<T> &es)
```

頂点数 $n$、辺が `es` からなる $G$ の Extreme Vertex Set を返します。

$2n - 1$ 頂点の根付きで表されます。根は $2n - 2$ です。頂点 $[0, n)$ は葉で、もとのグラフの頂点に対応します。それぞれの部分木が Extreme Vertex Set の候補に対応し、部分木からその親に生える辺の重みが、カットのコストです。

## 制約

- $G$ は頂点数 $n$ からなる非負重み付き単純無向グラフ

## 計算量

- $O(nm + n^2 log n)$
