---
documentation_of: //structure/wavelet/wavelet-matrix-rectangle-sum.hpp
---

## 概要

$2$ 次元平面上にある重み付きの点が事前に与えられているとき, オンラインで矩形内にある点の重みの総和を効率的に求めるデータ構造.

普通のウェーブレット行列に対し重みの累積和を持たせた配列を用意すると, 矩形内の点の個数を数えるのと同じように重みの総和を求めることができる.

基本的には事前に高さを要素数に圧縮する CompressedWaveletMatrixRectangleSum を用いると高速に動作する.

## 使い方
* `WaveletMatrixRectangleSum(v, d)`: 各要素の高さ `v` , 対応する要素の重み `d` を初期値として構築する.
* `rect_sum(l, r, upper)`: 区間 $[l, r)$ の高さ $[0, upper)$ にある要素の重みの総和を返す.
* `rect_sum(l, r, lower, upper)`: 区間 $[l, r)$ の高さ $[lower, upper)$ にある要素の重みの総和を返す.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(\log V)$

$V$ は値の最大値.
