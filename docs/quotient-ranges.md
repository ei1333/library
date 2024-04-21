---
documentation_of: //math/number-theory/quotient-ranges.hpp
---

## 概要

整数 $N$ が与えられたとき, $N$ の商 ($\lfloor \frac N i \rfloor$) ($1 \leq i \leq N$) の値と対応する区間を列挙する.

## 使い方

* `quotient_ranges(N)`: 戻り値の各要素を \{\{$x$,$y$\},$z$\} とする。$x \leq i \lt y$ を満たす整数の商($\lfloor \frac N i \rfloor$) が $z$ であることを意味する。$x$ の昇順で返す.

## 計算量

* $O(\sqrt N)$
