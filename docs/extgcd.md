---
title: Extgcd(拡張ユークリッドの互除法)
documentation_of: //math/number-theory/extgcd.hpp
---

# extgcd

```
T extgcd(T a, T b, T &x, T &y)
```

$\gcd(a, b)$ を返します。$(x, y)$ には $ax + by = \gcd(a, b)$ を満たす整数解が格納されます。整数解は複数考えられるが, $\|x\| + \|y\|$ が最小のものが格納されます。

## 制約

- $1 \leq a, b$

## 計算量

- $O(\log {\min(a, b)})$
