---
documentation_of: //structure/segment-tree/lazy-segment-tree.hpp
---

## 概要

遅延伝搬を用いることで, 区間に対する更新が可能になる. コンストラクタに対し追加で作用素モノイドの情報も与える.

## 使い方

計算量のオーダーを表記していない関数は全て $O(\log n)$ で動作する.

* `LazySegmentTree(n, f, g, h, M1, OM0)`: サイズ `n` で初期化する. ここで `f` は2つの区間の要素をマージする二項演算, `g` は要素と作用素をマージする二項演算, `h` は作用素同士をマージする二項演算, `M1` はモノイドの単位元, `OM0` は作用素の単位元である. $O(n)$
* `LazySegmentTree(v, f, g, h, M1, OM0)`: 配列 `v` で初期化する. 第2引数以降は上と同様. $O(n)$
* `build(v)`: 配列 `v` で初期化する. $O(n)$
* `set(k, x)`: `k` 番目の要素を `x` に更新する.
* `get(k)`: `k` 番目の要素を返す.
* `operator[k]`: `k` 番目の要素を返す.
* `prod(l, r)`: 区間 $[l, r)$ に対して二項演算した結果を返す.
* `all_prod()`: 全体を二項演算した結果を返す. $O(1)$
* `apply(k, x)`: `k` 番目の要素に作用素 `x` を適用する.
* `apply(l, r, x)`: 区間 $[l, r)$ に対して作用素 `x` を適用する.
* `find_first(a, check)`: $[a,x)$ が `check` を満たす最初の要素位置 $x$ を返す. 存在しないとき $n$ を返す.
* `find_last(b, check)`: $[x,b)$ が `check` を満たす最後の要素位置 $x$ を返す. 存在しないとき $-1$ を返す.

`auto seg = get_lazy_segment_tree(N, f, g, h, M1, OM0);` のようにすると `decltype(f)` などを用いなくてすむ.
