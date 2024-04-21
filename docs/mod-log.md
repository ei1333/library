---
documentation_of: //math/combinatorics/mod-log.hpp
---

## 概要
$a^x \equiv b \pmod p$ を満たす非負整数 $k$ の最小値を求める.

## 使い方

* `mod_log(a, b, p)`: $a^x \equiv b \pmod p$ を満たす非負整数 $x$ の最小値を返す. ただし, 存在しない場合 $-1$ を返す.

## 計算量

* $O(\sqrt p)$
