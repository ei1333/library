---
documentation_of: //structure/segment-tree/segment-tree.hpp
---

## 概要

完全二分木である. モノイドについて区間に対する演算が $O(\log N)$ で処理できる.

モノイドは次の条件を満たす代数的構造である.

* 結合律を満たす. つまり $S$ の各元 $a, b, c$ に対して, $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ が満たされる.
* 単位元をもつ. つまり $S$ の任意の元 $a$ をとってきたときに $a \cdot e = e \cdot a = a$ なる $e$ が存在する.

実装では木を 1-indexed の配列で表現している. ノード $k$ について, 親ノードは $\frac k 2$, 子ノードは $2k$, $2k+1$ である.

## 使い方

計算量のオーダーを表記していない関数は全て $O(\log n)$ で動作する.

* `SegmentTree(n, f, M1)`: サイズ `n` で初期化する. ここで `f` は2つの区間の要素をマージする二項演算, `M1` はモノイドの単位元である. $O(n)$
* `SegmentTree(v, f, M1)`: 配列 `v` で初期化する. `f` と `M1` は上と同様. $O(n)$
* `build(v)`: 配列 `v` で初期化する. $O(n)$
* `set(k, x)`: `k` 番目の要素を `x` に変更する. 
* `get(k)`: `k` 番目の要素を返す. $O(1)$
* `operator[k]`: `k` 番目の要素を返す. $O(1)$
* `apply(k, x)`: `k` 番目の要素をその要素と `x` を二項演算した値に変更する. 
* `prod(l, r)`: 区間 $[l, r)$ に対して二項演算した結果を返す.
* `all_prod()`: 全体を二項演算した結果を返す. $O(1)$
* `find_first(a, check)`: $[a, x)$ が `check` を満たす最初の要素位置 $x$ を返す. 存在しないとき $n$ を返す. $O(\log n)$
* `find_last(b, check)`: $[x, b)$ が `check` を満たす最後の要素位置 $x$ を返す. 存在しないとき $-1$ を返す. $(\log n)$

`auto seg = get_segment_tree(N, f, M1);` のようにすると `decltype(f)` を用いなくてすむ.
