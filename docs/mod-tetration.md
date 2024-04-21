---
documentation_of: //math/combinatorics/mod-tetration.hpp
---

## 概要
${a \uparrow \uparrow b} \bmod m$ を求める. $\uparrow \uparrow$ はテトレーション演算で $a^{a^{a^{a^{\ldots}}}}$ ($a$ が $b$ 個続く) を指す.

## 使い方

* `mod_tetration(a, b, m)`: ${a \uparrow \uparrow b} \bmod m$ を返す. 

## 計算量

* $O(\sqrt m)$
