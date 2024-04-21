---
documentation_of: //structure/segment-tree/dual-segment-tree.hpp
---

## 概要
双対セグメント木は遅延伝搬セグメント木の作用素モノイドのみを取り出したセグメント木を指す.

## 使い方

* `DualSegmentTree(n, h, OM0)`: サイズ `n` で初期化する. ここで `h` は2つの区間の作用素をマージする二項演算, `OM0` は作用素の単位元である.
* `update(l, r, x)`: 区間 $[l, r)$ に作用素 `x` を適用する.
* `operator[k]`: `k` 番目の作用素を返す.

`auto seg = get_dual_segment_tree(N, h, OM0);` のようにすると `decltype(h)` などを用いなくてすむ.

## 計算量

* クエリ: $O(\log N)$
