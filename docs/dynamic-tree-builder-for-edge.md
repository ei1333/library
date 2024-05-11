---
title: Dynamic Tree Builder (for Edge)
documentation_of: //structure/dynamic-tree/dynamic-tree-builder-for-edge.hpp
---

Link Cut Tree や Top Tree などの動的木を簡単に構築するための Builder です。

辺に情報を乗せたい場合に使用します。動的木上では、辺も頂点とみなします。


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
void add_edge(int u, int v, const Info &info, int id = -1)
```

頂点 `u` と `v` との間に `info` を持つ辺を追加します。

## 制約

- $0 \leq u, v \lt n$
- $u \neq v$
- $-1 \leq id \lt n$
- `add_edge` は $n - 1$ 回呼び出される
- 頂点 $u$ と $v$ は異なる連結成分

## build

```
void build(int r = 0)
```

頂点 `r` を根とする動的木を構築する。

`vs` に各頂点へのポインタ、`es` に各辺へのポインタが格納されます。

## 計算量

- $O(n)$
