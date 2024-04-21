---
documentation_of: //graph/others/topological-sort.hpp
---

## 概要

DAG(閉路のない有向グラフ) が与えられたとき, トポロジカルソートする.

入次数 $0$ の頂点から消すことを繰り返す.

## 使い方

* `topological_sort(g)`: DAG `g` をトポロジカルソートして, その頂点の順序を返す.

## 計算量

$O(E + V)$
