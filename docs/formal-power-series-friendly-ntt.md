## 概要

NTT を利用可能な mod のもとで、形式的べき級数の各演算を効率的に行う。

TODO 解説


## 使い方

計算量が書かれていない演算は $O(n \log n)$ で動作する。引数で `deg` を渡すことで, `deg` 項まで計算して返すものもある(デフォルトでは基本的に $\mathrm{deg}(n)$ 項で打ち切る)。

* `+`: $f(x) + g(x)$ を返す。$O(n)$
* `-`: $f(x) - g(x)$ を返す。$O(n)$
* `*`: $f(x) \times g(x)$ を返す。
* `/`: $f(x) = q (x)\times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $q(x)$ を返す。
* `%`: $f(x) = q(x) \times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $g(x)$ を返す。
* `diff()`: $f(x)'$ を返す。
* `integral()`: $\int f(x) dx$ を返す。
* `inv()`: $\frac {1} {f(x)}$ を返す。$f(0) \neq 0$ を要求する。
* `log()`: $\log f(x)$ を返す。$f(0) = 1$ を要求する。
* `sqrt(get_sqrt)`: $\sqrt {f(x)}$、つまり $f(x) = g(x)^2$ を満たす $g(x)$ を返す。存在しない場合空配列を返す。$get_sqrt$ はあるmodint $y$ が与えられたときに $y = x^2$ を満たす $x$ を返すラムダ式で, これを渡さない場合は非 $0$ な最初の項が $1$ であることを要求する。
* `exp()`: $e^{f(x)}$ を返す。$f(0) = 0$ を要求する。
* `pow(k)`: $f^{k} (x)$ を返す。
* `mod_pow(k, g)`: $f^{k} (x) \pmod {g(x)}$ を返す。
* `taylor_shift(c)`: $g(x) = f(x + c)$ を満たす $g(x)$ を返す。
