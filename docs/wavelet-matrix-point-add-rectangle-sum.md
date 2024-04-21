---
documentation_of: //structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
---

## 概要

$2$ 次元平面上にある点の位置が事前に与えられているとき, オンラインである点に対する重みの加算と, 矩形内にある点の重みの総和を効率的に求めるデータ構造.

Wavelet-Matrix-Rectangle-Sum で用いた重みの累積和を持たせた配列をBinary-Indexed-Tree に置き換えると, ある点に対する重みの加算を効率的に行える.

基本的には事前に高さを要素数に圧縮する CompressedWaveletMatrixPointAddRectangleSum を用いると高速に動作する.

## 使い方
* `WaveletMatrixRectangleSum(v, d)`: 各要素の高さ `v` , 対応する要素の重み `d` >を初期値として構築する.
* `rect_sum(l, r, upper)`: 区間 $[l, r)$ の高さ $[0, upper)$ にある要素の重みの>
総和を返す.
* `rect_sum(l, r, lower, upper)`: 区間 $[l, r)$ の高さ $[lower, upper)$ にある要
素の重みの総和を返す.
* `point_add(k, x)`: 要素 $k$ の重みに $x$ を加算する.

## 計算量

* 構築: $O(N \log V)$
* クエリ: $O(N \log N \log V)$

$V$ は値の最大値.
