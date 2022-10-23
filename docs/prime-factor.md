---
title: Prime Factor(素因数分解)
documentation_of: //math/number-theory/prime-factor.hpp
---

# prime_factor

```
map< int64_t, int > prime_factor(int64_t n)
```

$n$ を素因数分解した結果を連想配列で返します。連想配列の添字は素因数、値は指数です。

## 制約

- $0 \le n$

## 計算量

- $O(\sqrt n)$
