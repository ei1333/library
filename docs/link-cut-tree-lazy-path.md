---
documentation_of: //structure/lct/link-cut-tree-lazy-path.hpp
---

## 概要

Link Cut Tree とは動的木の一つで, 辺の追加や削除などの木構造の動的な変化がある場合でも効率的にクエリを処理できる.


## 使い方

* `LinkCutTree(f, g, h, s, e0)`: コンストラクタ. `f` は 2 つの要素の値をマージする二項演算, `g` は要素と作用素をマージする二項演算, `h` は作用素同士をマージする二項演算, `s` は要素を反転する演算を指す. また　`e0` は作用素の単位元を指す.
* `alloc(v)`: 要素の値を `v` としたノードを生成する.
* `build(vs)`: 各要素の値を `vs[i]` としたノードを生成し, その配列を返す.
* `expose(t)`: `t` と根をつなげて, `t` を splay Tree の根にする.
* `evert(t)`: `t` を根に変更する.
* `link(child, parent)`: `child` の親を `parent` にする. `child` と `parent` は別の連結成分で, `child` が根であることを要求する.
* `cut(child)`: `child` の親と `child` を切り離す.
* `is_connected(u, v)`: `u` と `v` が同じ連結成分に属する場合は `true`, そうでなければ `false` を返す.
* `lca(u, v)`: `u` と `v` の lca を返す. `u` と `v` が異なる連結成分なら `nullptr` を返す.
* `get_kth(x, k)`: `x` から根までのパスに出現するノードを並べたとき, 0-indexed で `k` 番目のノードを返す.
* `query(u)`: `u` から根までのパス上の頂点の値を二項演算でまとめた結果を返す.
* `query(u, v)`: `u` から `v` までのパス上の頂点の値を二項演算でまとめた結果を返す.
* `set_key(t, v)`: `t` の値を `v` に変更する.
* `set_propagate(t, e)`: `t` から根までのパス上の頂点に作用素 `e` を加える.
* `set_propagate(u, v, e)`: `u` から `v` までのパス上の頂点に作用素 `e` を加える.

## 計算量

* 各クエリ ならし $O(\log n)$
