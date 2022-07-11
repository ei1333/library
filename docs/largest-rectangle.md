---
title: Largest Rectangle(最大長方形)
documentation_of: //dp/largest-rectangle.hpp
---

## 概要

ヒストグラム中の最大長方形の面積を求める.

ヒストグラムを左から見る. スタックに自分より左にあるヒストグラムの高さと位置を単調増加になるように管理すると効率的に解ける.

* `largest_rectangle(height)`: ヒストグラムが `height` のとき最大長方形の面積を返す.

## 計算量

* $O(N)$
