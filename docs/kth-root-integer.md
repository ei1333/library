---
title: Kth Root Integer
documentation_of: //math/number-theory/kth-root-integer.hpp
---

# kth_root_integer

```
uint64_t kth_root_integer(uint64_t a, int k)
```

$\textrm{floor}{(a^{\frac {1} {k}})}$ を返します。

## 制約

- $0 \leq a \lt 2^{64}$
- $1 \leq k \leq 64$

## 計算量

- $O(k \log a)$
