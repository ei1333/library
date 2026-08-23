---
title: Monotone Minima
documentation_of: //dp/monotone-minima.hpp
---

$H \times W$ 行列の各行について、最適な列を分割統治で求める。最適列の位置が行番号に対して広義単調増加する行列に利用できる。

Monge $\Rightarrow$ Totally Monotone(TM) $\Rightarrow$ Monotone なので、Monotone は弱い条件である。

# monotone_minima

```cpp
template <typename F>
vector<int> monotone_minima(int H, int W, F comp)
```

各行の最適な列番号を返す。`comp(i, j, k)` は、行 `i` において列 `k` が列 `j` より真に良いとき `true` を返すものとする。このインターフェースは `smawk` と共通である。同値な候補では左側の列を選ぶ。

## 引数

- `H`: 行数
- `W`: 列数
- `comp`: 2 列の優劣を判定する関数

## 戻り値

長さ $H$ の配列を返し、その第 $i$ 要素は行 $i$ の最適な列番号である。$W = 0$ の場合は、すべての要素が $-1$ となる。

## 制約

- $0 \leq H$
- $0 \leq W$
- 各行の最適列が広義単調増加する

## 計算量

- 時間: $O(W \log H + H)$ 回の `comp` 呼び出し
- 空間: $O(H)$
