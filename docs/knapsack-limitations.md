---
title: Knapsack Limitations(個数制限つきナップサック問題) $O(NW)$
documentation_of: //dp/knapsack-limitations.hpp
---

## 概要

個数制限つきナップサック問題を次に示す.

重さ $w_i$, 価値 $v_i$ であるような $N$ 種類の品物がある. $i$ 番目の品物は $m_i$ 個まで選ぶことができる. 重さの和が $W$ 以下となるように選ぶとき, 価値の最大値を求めよ.

スライド最大値を用いた動的計画法により効率的に計算可能.

* `knapsack_limitations(w, m, v, W, NG, comp)`: `W` 以下の範囲で, 各重さについて価値の最大値を求める. `NG` は到達ができない場合の値で, `comp` は比較演算子.

## 計算量

* $O(NW)$
