---
documentation_of: //graph/shortest-path/k-shortest-path.hpp
---

## 概要

頂点 $s$ から $t$ へのパス(Path) のうち, 昇順 $k$ 個のパスの長さを Yen's Algorithm により求める. 

パス(Path, 道) は同じ頂点を通らない経路である.

verify が甘いため合っているかかなり不安です

* `k_shotest_path(g, s, t, k)`: 重み付き有向グラフ `g` の頂点 `s` から `t` へのパスのうち, 昇順 `k` 個のパスの長さとそのパスの辺番号の列を返す(パスの個数が `k` 個に満たないとき全てを返す).

## 計算量

* $O(KV ((E + v) \log V))$
