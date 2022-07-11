---
title: Knapsack 01(0-1ナップサック問題) $O(N \sum {v_i})$
documentation_of: //dp/knapsack-01-2.hpp
---

## 概要

0-1 ナップサック問題を次に示す.

重さ $w_i$, 価値 $v_i$ であるような $N$ 個の品物がある. 重さの和が $W$ 以下となるように選ぶとき, 価値の最大値を求めよ.

* `knapsack_01_2(w, v, W)`: 重さが `W` 以下で価値の和の最大値を返す.

## 計算量

* $O(N \sum {v_i})$
