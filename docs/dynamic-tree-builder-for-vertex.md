---
title: Dynamic Tree Builder (for Vertex)
documentation_of: //structure/dynamic-tree/dynamic-tree-builder-for-edge.hpp
---

Link Cut Tree や Top Tree などの動的木を簡単に構築するための Builder です。

# コンストラクタ

```
DynamicTreeBuilderForEdge< DynamicTree, TreeDPInfo >(int n)
```

頂点数 `n` の動的木を作成します。各頂点に対し `set_vertex`、各辺に対し `add_edge` を呼び出したあとに、`build` を呼び出すことを期待しています。

## 計算量

- $O(n)$

# set_vertex

```
void set_vertex(int u, const Info &info)
```

頂点 `u` の `Info` を `info` に設定します。

## 制約

- $0 \leq u \lt n$

## 計算量

- $O(1)$

# add_edge

```
void add_edge(int u, int v)
```

頂点 `u` と `v` との間に辺を追加します。

## 制約

- $0 \leq u, v \lt n$
- $u \neq v$
- `add_edge` は $n - 1$ 回呼び出される
- 頂点 $u$ と $v$ は異なる連結成分

## build

```
void build(int r = 0)
```

頂点 `r` を根とする動的木を構築する。

`vs` に各頂点へのポインタが格納されます。

## 計算量

- $O(n)$
