# うしライブラリ

[![Travis](https://img.shields.io/travis/ei1333/library/master.svg)](https://travis-ci.org/ei1333/library)

競技プログラミング用のライブラリ(C++14)

使い方などは [https://ei1333.github.io/luzhiled/](https://ei1333.github.io/luzhiled/) を参照してください

## テンプレート

- [テンプレート](https://github.com/ei1333/library/tree/master/template)

## データ構造

#### Union-Find

- [Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find.cpp)
- [部分永続Union-Find](https://github.com/ei1333/library/blob/master/structure/partially-persistent-union-find.cpp)
- [完全永続Union-Find](https://github.com/ei1333/library/blob/master/structure/persistent-union-find.cpp)
- [Undo可能Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find-undo.cpp)
- [重み付きUnion-Find](https://github.com/ei1333/library/blob/master/structure/weighted-union-find.cpp)
- [二部グラフの頂点彩色](https://github.com/ei1333/library/blob/master/structure/bipartite-graph.cpp)

#### Segment-Tree
- [Segment-Tree](https://github.com/ei1333/library/blob/master/structure/segment-tree.cpp)
- [双対Segment-Tree](https://github.com/ei1333/library/blob/master/structure/duel-segment-tree.cpp)
- [遅延伝搬Segment-Tree](https://github.com/ei1333/library/blob/master/structure/lazy-segment-tree.cpp)
- [二次元Segment-Tree(一点更新矩形取得)](https://github.com/ei1333/library/blob/master/structure/segment-tree-2d.cpp)
- [二次元Segment-Tree(矩形更新一点取得)](https://github.com/ei1333/library/blob/master/structure/segment-tree-2d-2.cpp)
- [永続Segment-Tree](https://github.com/ei1333/library/blob/master/structure/persistent-segment-tree.cpp)

#### Trie
- [Trie](https://github.com/ei1333/library/blob/master/structure/trie.cpp)
- [Binary-Trie](https://github.com/ei1333/library/blob/master/structure/binary-trie.cpp)
- [永続Binary-Trie](https://github.com/ei1333/library/blob/master/structure/persistent-binary-trie.cpp)

#### Convex-Hull-Trick
- [Conxex-Hull-Trick(追加クエリの傾きが単調)](https://github.com/ei1333/library/blob/master/structure/convex-hull-trick-add-monotone.cpp)
- [Li-Chao-Tree](https://github.com/ei1333/library/blob/master/structure/li-chao-tree.cpp)

#### Link-Cut-Tree
- [Link-Cut-Tree](https://github.com/ei1333/library/blob/master/structure/link-cut-tree.cpp)
- [Link-Cut-Tree(部分木クエリ)](https://github.com/ei1333/library/blob/master/structure/link-cut-tree-subtree.cpp)

#### 平衡二分探索木
- [RBST(列として)](https://github.com/ei1333/library/blob/master/structure/randomized-binary-search-tree.cpp)
- [RBST(multisetとして)](https://github.com/ei1333/library/blob/master/structure/randomized-binary-search-tree-set.cpp)
- [赤黒木](https://github.com/ei1333/library/blob/master/structure/red-black-tree.cpp)
- [永続赤黒木](https://github.com/ei1333/library/blob/master/structure/persistent-red-black-tree.cpp)

### Heap
- [Skew-Heap](https://github.com/ei1333/library/blob/master/structure/skew-heap.cpp)

#### その他
- [Binary-Indexed-Tree](https://github.com/ei1333/library/blob/master/structure/binary-indexed-tree.cpp)
- [Sparse-Table](https://github.com/ei1333/library/blob/master/structure/sparse-table.cpp)
- [Disjoint-Sparse-Table](https://github.com/ei1333/library/blob/master/structure/disjoint-sparse-table.cpp)
- [永続配列](https://github.com/ei1333/library/blob/master/structure/persistent-array.cpp)
- [列の平方分割](https://github.com/ei1333/library/blob/master/structure/sqrt-decomposition.cpp)
- [長方形の和集合の面積](https://github.com/ei1333/library/blob/master/structure/union-rectangle.cpp)
- [スライド区間の昇順k個の和](https://github.com/ei1333/library/blob/master/structure/priority-sum-structure.cpp)

## DP

#### ナップサック問題
- [個数制限付きナップサック O(NW)](https://github.com/ei1333/library/blob/master/dp/knapsack-limitations.cpp)
- [個数制限付きナップサック O(N^2 max(v_i)^2)](https://github.com/ei1333/library/blob/master/dp/knapsack-limitations-2.cpp)

#### 累積和
- [一次元累積和](https://github.com/ei1333/library/blob/master/dp/cumulative-sum.cpp)
- [二次元累積和](https://github.com/ei1333/library/blob/master/dp/cumulative-sum-2d.cpp)

#### その他
- [Divide-And-Conquer-Optimization](https://github.com/ei1333/library/blob/master/dp/divide-and-conquer-optimization.cpp)
- [最適二分探索木](https://github.com/ei1333/library/blob/master/dp/hu-tucker.cpp)
- [ヒストグラム中の最大長方形](https://github.com/ei1333/library/blob/master/dp/largest-rectangle.cpp)
- [最長増加部分列(LIS)](https://github.com/ei1333/library/blob/master/dp/longest-increasing-subsequence.cpp)
- [Monotone-Minima](https://github.com/ei1333/library/blob/master/dp/monotone-minima.cpp)
- [オンラインオフライン変換](https://github.com/ei1333/library/blob/master/dp/online-offline-dp.cpp)
- [スライド最小値](https://github.com/ei1333/library/blob/master/dp/slide-min.cpp)

## 文字列

- [複数文字列検索(Aho-Corasick)](https://github.com/ei1333/library/blob/master/string/aho-corasick.cpp)
- [接尾辞配列(Suffix-Array)](https://github.com/ei1333/library/blob/master/string/suffix-array.cpp)
- [高さ配列(LCP-Array)](https://github.com/ei1333/library/blob/master/string/longest-common-prefix-array.cpp)
- [最長回文(Manacher)](https://github.com/ei1333/library/blob/master/string/manacher.cpp)
- [最長共通接頭辞(Z-Algorithm)](https://github.com/ei1333/library/blob/master/string/z-algorithm.cpp)
- [ローリングハッシュ](https://github.com/ei1333/library/blob/master/string/rolling-hash.cpp)

## 二次元幾何

- [テンプレート](https://github.com/ei1333/library/blob/master/geometry/template.cpp)

## グラフ

- [テンプレート](https://github.com/ei1333/library/blob/master/graph/template.cpp)

#### フロー

- [最大流(Ford-Fulkerson) O(FE)](https://github.com/ei1333/library/blob/master/graph/ford-fulkerson.cpp)
- [最大流(Dinic) O(EV^2)](https://github.com/ei1333/library/blob/master/graph/dinic.cpp)
- [最大流(Push-Relabel) O(V^2 sqrt(E))](https://github.com/ei1333/library/blob/master/graph/push-relabel.cpp)
- [最小流量制限付き最大流, 循環流](https://github.com/ei1333/library/blob/master/graph/maxflow-lower-bound.cpp)
- [最小費用流(Primal-Dual) O(FE logV)](https://github.com/ei1333/library/blob/master/graph/primal-dual.cpp)
- [二部グラフの最大マッチング O(EV)](https://github.com/ei1333/library/blob/master/graph/bipartite-matching.cpp)
- [二部グラフの最大マッチング(HopCroft-Karp) O(E sqrt(V))](https://github.com/ei1333/library/blob/master/graph/hopcroft-karp.cpp)

TODO

## 木

- [重心分解](https://github.com/ei1333/library/blob/master/tree/centroid-decomposition.cpp)
- [最終共通祖先(ダブリング)](https://github.com/ei1333/library/blob/master/tree/doubling-lowest-common-ancestor.cpp)
- [HL分解](https://github.com/ei1333/library/blob/master/tree/heavy-light-decomposition.cpp)
- [全方位木DP](https://github.com/ei1333/library/blob/master/tree/rerooting.cpp)
- [木の直径](https://github.com/ei1333/library/blob/master/tree/tree-diameter.cpp)
- [根付き木に変換](https://github.com/ei1333/library/blob/master/tree/convert-rooted-tree.cpp)

## 数学
TODO

## その他
TODO
