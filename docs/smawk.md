---
title: SMAWK
documentation_of: //dp/smawk.hpp
---

全単調行列の各行について、最適な列を線形時間で求める。行列の要素そのものを保持せず、2 列の優劣を判定する関数だけを受け取る。

# smawk

```cpp
template <typename F>
vector<int> smawk(int H, int W, F comp)
```

各行の最適な列番号を返す。`comp(i, j, k)` は、行 `i` において列 `k` が列 `j` より真に良いとき `true` を返すものとする。同値な候補では左側の列を選ぶ。

## 引数

- `H`: 行数
- `W`: 列数
- `comp`: 2 列の優劣を判定する関数

## 戻り値

長さ $H$ の配列を返し、その第 $i$ 要素は行 $i$ の最適な列番号である。$W = 0$ の場合は、すべての要素が $-1$ となる。

## 制約

- $0 \leq H$
- $0 \leq W$
- 行列が `comp` の定める順序について全単調である

## 計算量

- 時間: $O(H + W)$ 回の `comp` 呼び出し
- 空間: $O(H + W)$

# 参考文献

- Aggarwal, Klawe, Moran, Shor, Wilber, Geometric Applications of a Matrix-Searching Algorithm
