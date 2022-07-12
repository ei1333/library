---
title: Bi Connected Components(二重頂点連結成分分解)
documentation_of: //graph/connected-components/bi-connected-components.hpp
---

## 概要

二重連結成分分解とも. 二重頂点連結成分とは, $1$ 個の頂点を取り除いても連結である部分グラフである. 

関節点は, その頂点とそれを端点とする辺を削除したときの部分グラフが非連結になるような頂点を指す. したがって, 関節点を列挙した後に頑張ると列挙できる.


* `build()`: 二重頂点連結成分分解する. `bc` には各二重頂点連結成分に属する辺が格納される.

## 計算量

* $O(E + V)$
