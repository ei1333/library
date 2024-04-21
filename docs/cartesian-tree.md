---
documentation_of: //graph/others/cartesian-tree.hpp
---

## 概要

数列に対応する Cartesian tree を求める.

## 使い方

* `cartesian_tree(v)`: 数列 `v` に対応する Cartesian tree を返す. 各要素にはその要素の親の idx が格納される. ただし根は `-1`.

## 計算量

* $O(N)$
