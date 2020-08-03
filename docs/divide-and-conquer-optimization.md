## 概要

$dp[i][j] = \min_{0 \leq k \lt j}\\{dp[i-1][k]+f(k,j)\\}$ の形のDPを高速化するテク.

$f(k,j)$ は $0 \leq k \lt j \leq W$ で定義される $2$ 変数関数.

各行について Monotone-Minima を適用する.


* `divide_and_conquer_optimization(H, W, INF, f)`: dp 配列を返す.

## 計算量

* $O(HW \log W)$
