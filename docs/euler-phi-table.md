---
documentation_of: //math/number-theory/euler-phi-table.hpp
---

## 概要

正の整数 $n$ が与えられたとき, $1$ から $n$ までの自然数のうち $n$ と互いに素なものの個数 $\phi(n)$ を求める.

以下の式で効率的に求めることができる.

$\phi(n)=n\displaystyle\prod_{i=1}^k(1-\dfrac{1}{p_i})$ (ただし $p_i$ は $n$ の素因数)

これは各素因数側から割っていっても同じように計算できるので, $n$ 以下のテーブルを効率的に構築可能である.

* `euler_phi_table(n)`: `n` 以下のオイラーの $\phi$ 関数テーブルを返す.

## 計算量

* $O(N \log \log N)$
