---
title: Convex Layers
documentation_of: //geometry/convex-layers.hpp
---

二次元平面上に異なる $n$ 個の点があります。

凸包（及びその辺上）に含まれる点をすべて削除する、という操作をすべての点が消えるまで繰り返します。

このとき、それぞれの点が何度目の操作で削除されるかを求めます。

# convex_layers

```cpp
template <typename T, typename T2>
vector<int> convex_layers(const vector<pair<T, T> >& ps)
```

$ps$ の各点について Convex Layer を求めます。

`T` は 2 * 座標の最大値が収まる型、`T2` は (2 * 座標の最大値)^2 が収まる型を指定してください。

## 制約

- $ps$ は相異なる

## 計算量

- $O(n \log^2 n)$
