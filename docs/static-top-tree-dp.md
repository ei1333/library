---
title: Static Top Tree DP(Static Top Tree 上のDP)
documentation_of: //graph/tree/static-top-tree-dp.hpp
---

* `vertex(int u) -> Path`: 頂点 $u$ のみからなる path cluster を生成する
* `add_vertex(Point d, int v) -> Path`: point cluster $d$ の根に頂点 $v$ を代入して path cluster にする
* `add_edge(Path d, int e) -> Point`: Path cluster $d$ に、辺 $e$ を追加して virtual な根を生やし、point cluster にする
* `rake(Point l, Point r) -> Point`: point cluster $l, r$ をマージする
* `compress(Path p, Path c, int e) -> Path`: path cluster $p, c$ ($p$ が根に近い側にある) に、辺 $e$ を使ってマージする
