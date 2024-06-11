---
title: Longest Common Substring
documentation_of: //string/longest-common-substring.hpp
---

与えられた 2 つの文字列の最長共通部分文字列を求めます。

# longest_common_substring

```cpp
template< typename S >
tuple< int, int, int, int > longest_common_substring(const S& s, const S& t, bool compress = false)
```

$s$ と $t$ の最長共通部分列を $S[a, b)$、$T[c, d)$ とします。このとき、$\\{a, b, c, d\\}$ を返します。

`S` の値域が広い場合は、`compress = true` を与える必要があります。

## 計算量

$n = \max(\|s\|, \|t\|)$ とします。

- `compress = false`: $O(n)$
- `compress = true`: $O(n \log n)$
