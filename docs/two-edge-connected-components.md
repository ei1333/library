---
title: Two Edge Connected Components(二重辺連結成分分解)
documentation_of: //graph/connected-components/two-edge-connected-components.hpp
---

## 概要

二辺連結成分分解とも. 二重辺連結成分とは, $1$ 本の辺を取り除いても連結である部分グラフである. つまり, 橋を含まない部分グラフなので, 橋を列挙することで二重辺連結成分を列挙できる.

二重辺連結成分で縮約後の頂点と橋からなるグラフは森になっている.


* `build()`: 二重辺連結成分分解する. `tree` には縮約後の頂点からなる森が格納される. `comp` には各頂点が属する二重辺連結成分の頂点番号が格納される. `group` には各二重辺連結成分について, それに属する頂点が格納される.

## 計算量

* $O(E + V)$
