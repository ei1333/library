---
title: Sum of Floor of Linear(一次関数の床関数の和)
documentation_of: //math/number-theory/sum-of-floor-of-linear.hpp
---

# sum_of_floor_of_linear

```
T sum_of_floor_of_linear(const T &n, const T &m, T a, T b)
```

$\displaystyle \sum_{i=0}^{n-1} \textrm{floor}{(\frac {a \times i + b} {m})}$ を返します。

## 制約

- $1 \ge n, m$
- $0 \leq a, b \leq m$ 

## 計算量

- $O(\log (n + m + a + b))$
