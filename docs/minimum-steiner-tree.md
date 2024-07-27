---
title: Minimum Steiner Tree (最小シュタイナー木)
documentation_of: //graph/others/minimum-steiner-tree.hpp
---

シュタイナー木は、terminal の頂点集合を含むような木（もとのグラフの部分グラフ）です。このうち、シュタイナー木を構成する辺の重みの和が最小となる木を、最小シュタイナー木と呼びます。

最小シュタイナー木を求めることは NP 困難ですが、terminal の個数が小さい場合 $O(3^n)$ の部分集合 DP を用ることで、効率的に求めることができます。

# コンストラクタ

```cpp
MinimumSteinerTree<T>(const Graph<T> &g, const vector<int> &terminal)
```

最小シュタイナー木を求め、`cost` に最小シュタイナー木のコストを格納します。

副作用として `dp[S][v]` には `terminal` の頂点集合 `S` と頂点 `v` を連結にするためのコストを格納します。

それぞれについて、連結にできない場合は `infty` を格納します。

## 制約

- `terminal` は空でない
- `terminal` の各要素は $0$ 以上 $n$ 未満

## 計算量

- $O(n 3^t + (n + m) 2^t \log n)$

$t$ は `terminal` の個数です。

# restore

```cpp
Edges<T> restore() const
```

最小シュタイナー木を構成する辺集合を返します。

## 計算量

- $O(n)$

