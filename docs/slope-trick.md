---
documentation_of: //structure/others/slope-trick.hpp
---

## 概要
区分線形凸関数 $f(x)$ を効率的に扱うためのデータ構造。

$f(x)$ の傾きが変化する点を優先度付きキューに持つことで, 特定の操作を簡潔に行うことが可能となる。傾きを $1$ ずつ変化させていく場合はこの実装で良いが, それ以外の場合は平衡二分探索木などの高度なデータ構造を用いる必要がある。

主にDPの高速化に用いられることが多い。


## 使い方

* `query()`: $f(x)$ の最小値とそれを満たす $x$ の最小値および最大値を返す。
* `add_all(a)`: $f(x)$ に $a$ を加算する。
* `add_a_minus_x(a)`: $f(x)$ に $\max(a - x, 0)$ を加算する。
* `add_x_minus_a(a)`: $f(x)$ に $\max(x - a, 0)$ を加算する。
* `add_abs(a)`: $f(x)$ に$abs(x-a)$ を加算する。
* `clear_right()`: $f(x) = \min_{y \le x} f(y)$ に置き換える。
* `clear_left()`: $f(x) = \min_{y \ge x} f(y)$ に置き換える。
* `shift(a, b)`: $f(x) = \min_{x-b \le y \le x-a} f(y)$ に置き換える。$a \leq b$ を満たす必要がある。
* `shift(a)`: $f(x) = f(x - a)$ に置き換える。
* `get(x)`: $f(x)$ を返す。ただし $f$ を破壊する。
* `merge(g)`: $f(x)$ に $g(x)$ を加算する. ただし $g$ を破壊する。

## 計算量

* `query()`, `add_all()`, `clear_right()`, `clear_left()`, `shift()`: $O(1)$
* `get()`: $O(Q)$
* `merge()`: $f, g$ の大きさをそれぞれ $N, M$ として $O(\min(N, M) \log \max(N, M))$
* それ以外の操作: $O(\log Q)$
