---
title: Cumulative Sum(一次元累積和)
documentation_of: //dp/cumulative-sum.hpp
---

## 概要

$1$ 次元の累積和. 前計算として事前に累積和をとることで, 区間の和を $O(1)$ で求めることが出来る.


## 使い方

* `add(k, x)`: 要素 `k` に値 `x` を加える.
* `build()`: 累積和を構築する.
* `fold(r)`: 区間 $[0, k)$ の和を返す.
* `fold(l, r)`: 区間 $[l, r)$ の和を返す.

## 計算量

* `add(k, x)`: $O(1)$
* `build()`: $O(N)$
* `fold(r)`: $O(1)$
* `fold(l, r)`: $O(1)$
