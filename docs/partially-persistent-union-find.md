---
title: Partially Persistent Union Find
documentation_of: //structure/union-find/partially-persistent-union-find.hpp
---

時刻付きで併合履歴を保持する Union-Find です。

各時刻 `t` における連結成分の代表元やサイズを問い合わせできます。

# コンストラクタ

```cpp
(1) PartiallyPersistentUnionFind()
(2) PartiallyPersistentUnionFind(int sz)
```

(2) は要素数 `sz` で初期化します。

## 制約

- $0 \leq sz$

## 計算量

- (2) $O(sz)$

# unite

```cpp
bool unite(int t, int x, int y)
```

時刻 `t` で要素 `x`, `y` の属する集合を併合します。  
同じ集合なら `false`、異なる集合を併合したなら `true` を返します。

## 制約

- `unite` を呼ぶ時刻 `t` は単調非減少
- $0 \leq x, y < sz$

## 計算量

- amortized $O(\alpha(sz))$

# find

```cpp
int find(int t, int x)
```

時刻 `t` において、要素 `x` が属する集合の代表元を返します。

## 制約

- $0 \leq x < sz$

## 計算量

- amortized $O(\alpha(sz))$

# size

```cpp
int size(int t, int x)
```

時刻 `t` において、要素 `x` が属する集合の要素数を返します。

## 制約

- $0 \leq x < sz$

## 計算量

- $O(\alpha(sz) + \log sz)$
