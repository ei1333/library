---
title: Min Plus Convolution (Convex and Arbitary)
documentation_of: //dp/min-plus-convolution-convex-arbitary.hpp
---

凸数列と任意の数列の min-plus 畳み込みを SMAWK により線形時間で計算する。

# min_plus_convolution_convex_arbitary

```cpp
template <typename T>
vector<T> min_plus_convolution_convex_arbitary(const vector<T>& a,
                                               const vector<T>& b)
```

$a$ を凸数列、$b$ を任意の数列として、各 $k$ に対する $\min_{i+j=k}(a_i+b_j)$ を並べた配列を返す。どちらかが空なら空配列を返す。

## テンプレート引数

- `T`: 加算と `<` による比較が可能な要素型

## 引数

- `a`: 隣接差分が広義単調増加する凸数列
- `b`: 任意の数列

## 戻り値

両方の入力が空でない場合、長さ $\lvert a\rvert + \lvert b\rvert - 1$ の min-plus 畳み込みを返す。

## 前提条件

- `a` は凸数列である
- 配列長と要素の加算結果は、それぞれ `int` と `T` で表現できる

## 計算量

$N = \lvert a\rvert$, $M = \lvert b\rvert$ とする。

- 時間: $O(N + M)$
- 空間: $O(N + M)$

# 参考文献

- [Min Plus Convolution (Convex and Arbitrary)](https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary)
