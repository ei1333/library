---
documentation_of: //graph/tree/tree-diameter.hpp
---

## 概要

木の直径を求める.

適当な頂点から DFS して最も遠い点 $u$ を求める, $u$ から DFS して最も遠い点 $v$ を見つけると, そのペア $(u, v)$ が直径の端点.

## 使い方

* `build()`: 木の直径を返す. `path` には直径を構成する辺が格納される.

## 計算量

$O(V)$
