## 概要

対数 $\log f(x)$ を求める.

つまり $\displaystyle f(x) = e ^ {g(x)} = \sum_{k=0}^{\infty} \frac {g(x)^k} {k!}$ を満たす $g(x)$ を求める. ただし $[x^0] f(x) = 1$.

$\log f(x) = \int \frac {f'(x)} {f(x)} dx$ に基づいて計算する.

## 使い方

* `log(deg)`: $\log f(x)$ の先頭 `deg` 項を返す. ただし $[x^0] f(x) = 1$.
 
## 計算量

* $O(N \log N)$
