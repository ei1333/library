---
title: Persistent Union Find (永続 Union Find)
documentation_of: //structure/union-find/persistent-union-find.hpp
---

永続配列を用いた永続 Union-Find です。

`PersistentUnionFind` オブジェクトをコピーしてから `unite` することで、併合前の状態を保持したまま新しい状態を作れます。

# コンストラクタ

```cpp
(1) PersistentUnionFind()
(2) PersistentUnionFind(int sz)
```

(2) は要素数 `sz` で初期化します。

## 制約

- $0 \leq sz$

## 計算量

- (2) $O(sz)$

# find

```cpp
int find(int k)
```

要素 `k` が属する集合の代表元を返します。

## 制約

- $0 \leq k < sz$

## 計算量

- $O(\log sz \cdot \alpha(sz))$

# size

```cpp
int size(int k)
```

要素 `k` が属する集合の要素数を返します。

## 制約

- $0 \leq k < sz$

## 計算量

- $O(\log sz \cdot \alpha(sz))$

# unite

```cpp
bool unite(int x, int y)
```

要素 `x` と `y` の属する集合を併合します。  
同じ集合なら `false`、異なる集合を併合したなら `true` を返します。

## 制約

- $0 \leq x, y < sz$

## 計算量

- $O(\log sz \cdot \alpha(sz))$
