# うしライブラリ

[![Actions Status](https://github.com/ei1333/library/workflows/verify/badge.svg)](https://github.com/ei1333/library/actions)

競技プログラミング用のライブラリ(C++14) 

[Library](https://ei1333.github.io/library/index.html)

使い方などは [https://ei1333.github.io/luzhiled/](https://ei1333.github.io/luzhiled/) を参照してください（更新をサボっているため最新ではない場合があります）


## テンプレート

- [テンプレート](https://github.com/ei1333/library/tree/master/template/template.cpp)

## データ構造

#### Union-Find

- [Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find/union-find.cpp)
- [部分永続Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find/partially-persistent-union-find.cpp)
- [完全永続Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find/persistent-union-find.cpp)
- [Undo可能Union-Find](https://github.com/ei1333/library/blob/master/structure/union-find/union-find-undo.cpp)
- [重み付きUnion-Find](https://github.com/ei1333/library/blob/master/structure/union-find/weighted-union-find.cpp)
- [二部グラフの頂点彩色](https://github.com/ei1333/library/blob/master/structure/union-find/bipartite-graph.cpp)

#### Segment-Tree
- [Segment-Tree](https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree.cpp)
- [双対Segment-Tree](https://github.com/ei1333/library/blob/master/structure/segment-tree/duel-segment-tree.cpp)
- [遅延伝搬Segment-Tree](https://github.com/ei1333/library/blob/master/structure/segment-tree/lazy-segment-tree.cpp)
- [二次元Segment-Tree(一点更新矩形取得)](https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree-2d.cpp)
- [二次元Segment-Tree(矩形更新一点取得)](https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree-2d-2.cpp)
- [永続Segment-Tree](https://github.com/ei1333/library/blob/master/structure/segment-tree/persistent-segment-tree.cpp)
- [Segment-Tree-Beats](https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree-beats.cpp)

#### Trie
- [Trie](https://github.com/ei1333/library/blob/master/structure/trie/trie.cpp)
- [Binary-Trie](https://github.com/ei1333/library/blob/master/structure/trie/binary-trie.cpp)
- [永続Binary-Trie](https://github.com/ei1333/library/blob/master/structure/trie/persistent-binary-trie.cpp)

#### Convex-Hull-Trick
- [Conxex-Hull-Trick(追加クエリの傾きが単調)](https://github.com/ei1333/library/blob/master/structure/convex-hull-trick/convex-hull-trick-add-monotone.cpp)
- [Li-Chao-Tree](https://github.com/ei1333/library/blob/master/structure/convex-hull-trick/li-chao-tree.cpp)
- [動的Li-Chao-Tree](https://github.com/ei1333/library/blob/master/structure/convex-hull-trick/dynamic-li-chao-tree.cpp)
- [永続動的Li-Chao-Tree](https://github.com/ei1333/library/blob/master/structure/convex-hull-trick/persistent-dynamic-li-chao-tree.cpp)

#### Link-Cut-Tree
- [Link-Cut-Tree](https://github.com/ei1333/library/blob/master/structure/others/link-cut-tree.cpp)
- [Link-Cut-Tree(部分木クエリ)](https://github.com/ei1333/library/blob/master/structure/others/link-cut-tree-subtree.cpp)

#### 平衡二分探索木
- [RBST(列として)](https://github.com/ei1333/library/blob/master/structure/bbst/randomized-binary-search-tree.cpp)
- [RBST(multisetとして)](https://github.com/ei1333/library/blob/master/structure/bbst/randomized-binary-search-tree-set.cpp)
- [赤黒木](https://github.com/ei1333/library/blob/master/structure/bbst/red-black-tree.cpp)
- [永続赤黒木](https://github.com/ei1333/library/blob/master/structure/bbst/persistent-red-black-tree.cpp)

### Heap
- [Skew-Heap](https://github.com/ei1333/library/blob/master/structure/heap/skew-heap.cpp)
- [Fibonacchi-Heap](https://github.com/ei1333/library/blob/master/structure/heap/fibonacchi-heap.cpp)
- [Radix-Heap](https://github.com/ei1333/library/blob/master/structure/heap/radix-heap.cpp)

#### その他
- [Binary-Indexed-Tree](https://github.com/ei1333/library/blob/master/structure/others/binary-indexed-tree.cpp)
- [Sparse-Table](https://github.com/ei1333/library/blob/master/structure/others/sparse-table.cpp)
- [Disjoint-Sparse-Table](https://github.com/ei1333/library/blob/master/structure/others/disjoint-sparse-table.cpp)
- [永続配列](https://github.com/ei1333/library/blob/master/structure/others/persistent-array.cpp)
- [列の平方分割](https://github.com/ei1333/library/blob/master/structure/others/sqrt-decomposition.cpp)
- [長方形の和集合の面積](https://github.com/ei1333/library/blob/master/structure/others/union-rectangle.cpp)
- [スライド区間の昇順k個の和](https://github.com/ei1333/library/blob/master/structure/others/priority-sum-structure.cpp)
- [Sliding-Window-Aggregation](https://github.com/ei1333/library/blob/master/structure/others/sliding-window-aggregation.cpp)

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

- [最大流(Ford-Fulkerson) O(FE)](https://github.com/ei1333/library/blob/master/graph/flow/ford-fulkerson.cpp)
- [最大流(Dinic) O(EV^2)](https://github.com/ei1333/library/blob/master/graph/flow/dinic.cpp)
- [最大流(Dinic) 容量スケーリング O(EV logU)](https://github.com/ei1333/library/blob/master/graph/flow/dinic-capacity-scaling.cpp)
- [最大流(Push-Relabel) O(V^2 sqrt(E))](https://github.com/ei1333/library/blob/master/graph/flow/push-relabel.cpp)
- [最小流量制限付き最大流, 循環流](https://github.com/ei1333/library/blob/master/graph/flow/maxflow-lower-bound.cpp)
- [最小費用流(Primal-Dual) O(FE logV)](https://github.com/ei1333/library/blob/master/graph/flow/primal-dual.cpp)
- [二部グラフの最大マッチング O(EV)](https://github.com/ei1333/library/blob/master/graph/flow/bipartite-matching.cpp)
- [二部グラフの最大マッチング(HopCroft-Karp) O(E sqrt(V))](https://github.com/ei1333/library/blob/master/graph/flow/hopcroft-karp.cpp)
- [二部グラフの最小重み最大マッチング(Hungarian) O(V^3)](https://github.com/ei1333/library/blob/master/graph/flow/hungarian.cpp)
- [一般グラフの最大マッチング(GabowEdmonds) O(VE logV)](https://github.com/ei1333/library/blob/master/graph/flow/gabow-edmonds.cpp)

#### 連結成分分解

- [二重辺連結成分分解](https://github.com/ei1333/library/blob/master/graph/connected-components/two-edge-connected-components.cpp)
- [二重頂点連結成分分解](https://github.com/ei1333/library/blob/master/graph/connected-components/bi-connected-components.cpp)
- [強連結成分分解](https://github.com/ei1333/library/blob/master/graph/connected-components/strongly-connected-components.cpp)

#### 最短路

- [グリッド上の幅優先探索 O(HW)](https://github.com/ei1333/library/blob/master/graph/shortest-path/grid-bfs.cpp)
- [単一始点最短路(Bellman-Ford) O(VE)](https://github.com/ei1333/library/blob/master/graph/shortest-path/bellman-ford.cpp)
- [単一始点最短路(SPFA) O(VE)](https://github.com/ei1333/library/blob/master/graph/shortest-path/shortest-path-faster-algorithm.cpp)
- [単一始点最短路(Dijkstra) O((E + V) logV)](https://github.com/ei1333/library/blob/master/graph/shortest-path/dijkstra.cpp)
- [単一始点最短路(Dijkstra with Fibonacch-Heap) O(V logV + E)](https://github.com/ei1333/library/blob/master/graph/shortest-path/dijkstra-fibonacchi-heap.cpp)
- [単一始点最短路(Dijkstra with Radix-Heap) O((E + V) logU)](https://github.com/ei1333/library/blob/master/graph/shortest-path/dijkstra-radix-heap.cpp)
- [全点対間最短路(Warshall-Floyd) O(V^3)](https://github.com/ei1333/library/blob/master/graph/shortest-path/warshall-floyd.cpp)

#### 最小全域木

- [最小全域木(Borůvka)](https://github.com/ei1333/library/blob/master/graph/mst/boruvka.cpp)
- [最小全域木(Kruskal)](https://github.com/ei1333/library/blob/master/graph/mst/kruskal.cpp)
- [最小全域木(Prim)](https://github.com/ei1333/library/blob/master/graph/mst/prim.cpp)
- [最小全域木(Prim with Fibonacchi-Heap)](https://github.com/ei1333/library/blob/master/graph/mst/prim-fibonacchi-heap.cpp)

#### 木

- [重心分解](https://github.com/ei1333/library/blob/master/graph/tree/centroid-decomposition.cpp)
- [最終共通祖先(ダブリング)](https://github.com/ei1333/library/blob/master/graph/tree/doubling-lowest-common-ancestor.cpp)
- [HL分解](https://github.com/ei1333/library/blob/master/graph/tree/heavy-light-decomposition.cpp)
- [全方位木DP](https://github.com/ei1333/library/blob/master/graph/tree/rerooting.cpp)
- [木の直径](https://github.com/ei1333/library/blob/master/graph/tree/tree-diameter.cpp)
- [木の重心](https://github.com/ei1333/library/blob/master/graph/tree/centroid.cpp)
- [木の同型性 O(V logV)](https://github.com/ei1333/library/blob/master/graph/tree/tree-isomorphism.cpp)
- [根付き木に変換](https://github.com/ei1333/library/blob/master/graph/tree/convert-rooted-tree.cpp)

#### その他

- [オイラー路の復元](https://github.com/ei1333/library/blob/master/graph/others/eulerian-trail.cpp)
- [彩色数 O(2^V V)](https://github.com/ei1333/library/blob/master/graph/others/chromatic-number.cpp)
- [最小全域有向木(Chu-Liu/Edmond) O(E logV)](https://github.com/ei1333/library/blob/master/graph/others/chu-liu-edmond.cpp)
- [橋/関節点](https://github.com/ei1333/library/blob/master/graph/others/lowlink.cpp)
- [最大クリーク O(2^sqrt(2E) V)](https://github.com/ei1333/library/blob/master/graph/others/maximum-clique.cpp)
- [最大独立集合(乱択)](https://github.com/ei1333/library/blob/master/graph/others/maximum-independent-set.cpp)
- [トポロジカルソート](https://github.com/ei1333/library/blob/master/graph/others/topological-sort.cpp)
- [DAGの到達可能性クエリ(オフライン) O((V+E)Q/64)](https://github.com/ei1333/library/blob/master/graph/others/offline-dag-reachability.cpp)
- [Dominator-Tree](https://github.com/ei1333/library/blob/master/graph/others/dominator-tree.cpp)

## 数学

#### 数論
- [オイラーのφ関数(値) O(sqrt(N))](https://github.com/ei1333/library/blob/master/math/number-theory/euler-phi.cpp)
- [オイラーのφ関数(テーブル) O(N loglogN)](https://github.com/ei1333/library/blob/master/math/number-theory/euler-phi-table.cpp)
- [商の列挙](https://github.com/ei1333/library/blob/master/math/number-theory/quotient-range.cpp)
- [拡張ユークリッドの互除法 O(logN)](https://github.com/ei1333/library/blob/master/math/number-theory/extgcd.cpp)
- [約数列挙 O(sqrt(N)](https://github.com/ei1333/library/blob/master/math/number-theory/divisor.cpp)
- [素因数分解 O(sqrt(N))](https://github.com/ei1333/library/blob/master/math/number-theory/prime-factor.cpp)
- [素数判定 (確率的素数判定) / 素因数分解 (Pollard-Rho)](https://github.com/ei1333/library/blob/master/math/number-theory/fast-prime-factorization.cpp)
- [進数変換](https://github.com/ei1333/library/blob/master/math/number-theory/convert-base.cpp)

#### 組合せ

- [ModInt](https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp)
- [任意ModInt](https://github.com/ei1333/library/blob/master/math/combinatorics/arbitrary-mod-int.cpp)
- [組合せ](https://github.com/ei1333/library/blob/master/math/combinatorics/combination.cpp)
- [累乗 O(logN)](https://github.com/ei1333/library/blob/master/math/combinatorics/mod-pow.cpp)
- [Mod-Sqrt](https://github.com/ei1333/library/blob/master/math/combinatorics/mod-sqrt.cpp)
- [ベル数(値) O(min(N,K) logN)](https://github.com/ei1333/library/blob/master/math/combinatorics/bell-number.cpp)
- [ラグランジュ補間](https://github.com/ei1333/library/blob/master/math/combinatorics/lagrange-polynomial.cpp)
- [二項係数(値) O(K)](https://github.com/ei1333/library/blob/master/math/combinatorics/binomial.cpp)
- [二項係数(テーブル) O(N^2)](https://github.com/ei1333/library/blob/master/math/combinatorics/binomial-table.cpp)
- [第2種スターリング数 O(K logN)](https://github.com/ei1333/library/blob/master/math/combinatorics/stirling-number-second.cpp)
- [階乗 mod p O(sqrt(p) log p)](https://github.com/ei1333/library/blob/master/math/combinatorics/factorial.cpp)
- [離散対数問題 O(sqrt(p))](https://github.com/ei1333/library/blob/master/math/combinatorics/mod-log.cpp)

#### FFT
- [高速フーリエ変換(FFT)](https://github.com/ei1333/library/blob/master/math/fft/fast-fourier-transform.cpp)
- [高速フーリエ変換(NTT)](https://github.com/ei1333/library/blob/master/math/fft/number-theoretic-transform.cpp)
- [高速フーリエ変換(NTT) ModInt](https://github.com/ei1333/library/blob/master/math/fft/number-theoretic-transform-friendly-mod-int.cpp)
- [任意mod畳み込み (30bit)](https://github.com/ei1333/library/blob/master/math/fft/arbitrary-mod-convolution.cpp)
- [任意mod畳み込み (38bit)](https://github.com/ei1333/library/blob/master/math/fft/arbitrary-mod-convolution-long.cpp)

#### 形式的冪級数
- [形式的冪級数](https://github.com/ei1333/library/blob/master/math/fps/formal-power-series.cpp)
- [Multipoint-Evaluation O(N log^2N)](https://github.com/ei1333/library/blob/master/math/fps/multipoint-evaluation.cpp)
- [Polynomial-Interpolation O(N log^2N)](https://github.com/ei1333/library/blob/master/math/fps/polynomial-interpolation.cpp)
- [ベルヌーイ数, スターリング数などの列挙](https://github.com/ei1333/library/blob/master/math/fps/formal-power-series-seq.cpp)
- [Berlekamp-Massey O(N^2)](https://github.com/ei1333/library/blob/master/math/fps/berlekamp-massey.cpp)
- [疎行列の行列累乗/行列式](https://github.com/ei1333/library/blob/master/math/fps/sparse-matrix.cpp)

#### 行列
- [行列](https://github.com/ei1333/library/blob/master/math/matrix.cpp)

## その他

- [Mo's algorithm](https://github.com/ei1333/library/blob/master/other/mo.cpp)
- [Mo's alogirhtm(ロールバッグ平方分割)](https://github.com/ei1333/library/blob/master/other/mo-rollback.cpp)
- [Offline-Dynamic-Connectivity](https://github.com/ei1333/library/blob/master/other/offline-dynamic-connectivity.cpp)
- [サイコロ](https://github.com/ei1333/library/blob/master/other/dice.cpp)
- [タイマー](https://github.com/ei1333/library/blob/master/other/timer.cpp)
- [乱数生成器](https://github.com/ei1333/library/blob/master/other/random-number-generator.cpp)
- [座標圧縮](https://github.com/ei1333/library/blob/master/other/compress.cpp)
- [高速入力](https://github.com/ei1333/library/blob/master/other/fast-input.cpp)

