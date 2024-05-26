---
title: Graph Template(グラフテンプレート)
documentation_of: //graph/graph-template.hpp
---

# Edge

辺を表す構造体です。

それぞれの `Edge` は以下の値を持ちます。

```cpp
int from, to;
T cost;
int idx;
```

頂点 `from` から `to` を繋ぐ重み `cost` の辺があることを意味します。

`idx` は辺の番号です。特に指定しない場合は、辺が追加された順番に番号が割り当てられます。

## コンストラクタ

```cpp
Edge< T >(int from, int to, T cost = 1, int idx = -1)
```

頂点 `from` から `to` を結ぶ重み `cost` の辺を追加します。

`T` は辺の重みの型です。

## int

```cpp
operator int() const
```

`to` を返します。

# Graph

グラフを隣接リストで表すための構造体です。

## コンストラクタ

```cpp
Graph< T >(int n)
```

頂点数 $n$ の空グラフを作ります。

`T` は辺の重みの型です。

### 計算量

- $O(n)$

## size

```cpp
size_t size() const
```

頂点数を返します。

### 計算量

- $O(1)$

## add_directed_edge

```cpp
void add_directed_edge(int from, int to, T cost = 1)
```

頂点 `from` から `to` を繋ぐ重み `cost` の有向辺を追加します。

### 制約

- $0 \leq from, to \lt n$

### 計算量

- $O(1)$

## add_edge

```cpp
void add_edge(int from, int to, T cost = 1)
```

頂点 `from` と `to` を繋ぐ重み `cost` の無向辺を追加します。

### 制約

- $0 \leq from, to \lt n$
- $from \neq to$

### 計算量

- $O(1)$

## read

```cpp
void read(int M, int padding = -1, bool weighted = false, bool directed = false)
```

$M$ 本の辺を標準入力 `cin` から読み込みます。

入力で与えられた頂点番号に `padding` を加算します。

`weighted = false` のとき重みなしのグラフ、`true` のとき重みつきのグラフを意味します。

`directed = false` のとき無向グラフ、`true` のとき有向グラフを意味します。

詳細は実際の実装を参照してください。

### 計算量

- $O(M)$

## operator[]

```cpp
(1) vector<Edge<T> > &operator[](int k)
(2) const vector<Edge<T> > &operator[](int k) const
```

頂点 $k$ から生えるすべての辺を返します。

### 制約

- $0 \leq k \lt n$

### 計算量

- $O(1)$
