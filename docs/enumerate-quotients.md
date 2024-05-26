---
title: Enumerate Quotients (商列挙)
documentation_of: //math/number-theory/enumerate-quotients.hpp
---

整数 $n$ が与えられたとき, $n$ の商 ($\lfloor \frac n i \rfloor$) ($1 \leq i \leq n$) の値と対応する区間を列挙します。

# enumerate_quotients

```cpp
template <typename T>
vector< tuple< T, T, T > > enumerate_quotients(T n)
```

戻り値の各要素を $\{q, l, r\}$ としたとき、$l \leq i \lt r$ を満たす整数 $i$ の商($\lfloor \frac n i \rfloor$) が $q$ であることを意味します。$q$ の昇順で返します。

## 制約

- $1 \leq n$

## 計算量

- $O(\sqrt n)$
