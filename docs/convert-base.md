---
title: Convert Base(進数変換)
documentation_of: //math/number-theory/convert-base.hpp"
---

与えられた 10 進数を進数変換します。

# convert_base

```
vector< T > convert_base(T x, T b)
```

`x` を `b` 進数に変換した結果を返します。

## 計算量

- $O(\log_b x)$
