---
documentation_of: //structure/wavelet/wavelet-matrix.hpp
---

## 概要

$2$ 次元平面上にある点が事前に与えられているとき, オンラインでいろいろなクエリを処理するデータ構造.

基本的には事前に要素の値を要素数に圧縮する CompressedWaveletMatrix を用いると高速に動作する.

## 使い方
* `WaveletMatrix(v)`: 各要素の高さ `v` を初期値として構築する.
* `access(k)`: $k$ 番目の要素を返す.
* `rank(x, r)`: 区間 $[0, r)$ に含まれる `x` の個数を返す.
* `kth_smallest(l, r, k)`: 区間 $[l, r)$ に含まれる要素のうち $k$ 番目(0-indexed) に小さいものを返す.
* `kth_largest(l, r, k)`: 区間 $[l, r)$ に含まれる要素のうち $k$ 番目 (0-indexed) に大きいものを返す.
* `range_freq(l, r, lower, upper)`: 区間 $[l, r)$ に含まれる要素のうち $[lower, upper)$ である要素数を返す.
* `prev_value(l, r, upper)`: 区間 $[l, r)$ に含まれる要素のうち `upper` の次に小さいものを返す.
* `next_value(l, r, lower)`: 区間 $[l, r)$ に含まれる要素のうち `lower` の次に大きいものを返す.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(\log V)$

$V$ は値の最大値.
