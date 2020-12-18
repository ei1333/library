## 概要
オイラーツアーとスパーステーブルによって最小共通祖先を求める.

辺属性のオイラーツアーをする. すべての頂点について, その頂点 $k$ に最初に到達した時刻 $in[k]$ と深さ $dep[k]$ を求めておく. 頂点 $u, v$ の最小共通祖先は区間 $[in[u], in[v]]$ の要素のうち深さが最小となる頂点である. 区間の最小値なのでスパーステーブルにより前計算しておくと, クエリあたり $O(1)$ で処理できる.

## 使い方

* `build()`: 構築する.
* `lca(u, v)`: 頂点 `u`, `v` の最小共通祖先(LCA)を返す.

## 計算量

* `build()`: $O(V \log V)$
* `lca()`: $O(1)$