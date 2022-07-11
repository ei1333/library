---
title: Cumulative Sum 2D(二次元累積和)
documentation_of: //dp/cumulative-sum-2d.hpp
---

## 概要

$2$ 次元の累積和. 前計算として事前に累積和をとることで, 矩形和を $O(1)$ で求めることが出来る.

* `add(x, y, z)`: 要素 $(x, y)$ に値 `z` を加える.
* `build()`: 累積和を構築する.
* `query(sx, sy, gx, gy)`: 左下 $(sx, sy)$, 右上 $(gx, gy)$ の矩形和を求める(半開区間で与えることに注意すること. 具体的には列 $gx$ と行 $gy$ は含まない).

## 計算量

* `add(x, y, z)`: $O(1)$
* `build()`: $O(WH)$
* `query(sx, sy, gx, gy)`: $O(1)$
