---
title: Divisor(約数列挙)
documentation_of: //math/number-theory/divisor.hpp
---

与えられた整数の約数を列挙します。

# divisor

```
vector< int64_t > divisor(int64_t n)
```

`n` の約数を昇順に返します。

## 制約

- $1 \le n$

## 計算量

- $O(\sqrt n)$
