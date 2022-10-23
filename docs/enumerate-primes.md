---
title: Enumerate Primes(素数列挙)
documentation_of: //math/number-theory/enumerate-primes.hpp
---

エラトステネスの篩を用いて素数を列挙します。


# enumerate_primes

```
vector< int > enumerate_primes(int n)
```

$n$ 以下の素数を昇順に返します。

## 制約

- $0 \le n$

## 計算量

- $O(n \log \log n)$
