---
documentation_of: //math/fps/kth-term-of-linearly-recurrent-sequence.hpp
---

## 概要

線形線形漸化的数列の第 $N$ 項を求める。

$k$ 項間漸化式 $a_n = \sum_{d=1}^{k} c_d a_{n-d} (n \ge d)$ が存在するとき数列 $a$ は線形漸化的数列であるという。線形漸化的数列 $a$ は、初項 $(a_1, \cdots, a_{d-1})$ と係数 $c = (c_1, \cdots, c_d), c_d \neq 0$ を用いることで定義される。$d$ を位数と呼ぶ。

位数 $d$ の線形漸化式が存在するとき、ある次数 $d$ の $Q(0)=1$ 満たす多項式 $Q(x)$ と次数 $d-1$ 以下の多項式 $P(x)$ が存在して、$G(x)=\frac {P(x)} {Q(x)}$ が母関数となる。具体的には、

$Q(x) = 1 - c_1x - c_2x^2 - \cdots - c_kx^k$

$P(x) = Q(x)(a_0 + a_1x + a_2x^2 + \cdots + a^{k-1}x^{k-1}) \pmod {x^k}$

とすればよい。$P(x)$ は $Q(x)$ と $a$ を畳み込むと求められる。

従って、数列 $a$ の第 $N$ 項を求めるために、 $\frac {P(x)} {Q(x)}$ の $x^N$ の係数を求めればよくて、Bostan-Mori Algorithm を用いることで効率的に計算できる。


## 計算量

$O(K \log K \log N)$
