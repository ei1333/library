---
title: Sqrt Decomposition
documentation_of: //structure/others/sqrt-decomposition.hpp
---

平方分割を用いて、区間に対する加算・減算と条件付き総和クエリを処理するデータ構造です。

各要素 `i` は値 `data[i]` と整数値 `add[i] = block_add[block] + elem_add[i]` を持ちます。

- `add(a, b)` / `sub(a, b)` は `add[i]` を区間 `[a, b)` で `+1` / `-1`
- `query(a, b, x)` は区間 `[a, b)` で `add[i] == x` を満たす `data[i]` の総和
- `query_low(a, b)` は区間 `[a, b)` で `add[i] >= L` を満たす `data[i]` の総和

# コンストラクタ

```cpp
SqrtDecomposition(int N, E L = 0)
```

要素数 `N`、しきい値 `L` で初期化します。

## 制約

- $0 < N$

## 計算量

- $O(N)$

# build

```cpp
void build(const vector<E>& add, const vector<T>& dat)
```

初期の `add` と `data` を設定し、内部状態を再構築します。

## 制約

- `add.size() == N`
- `dat.size() == N`

## 計算量

- $O(N + \sum \text{block内の最大add値})$

# add

```cpp
void add(int a, int b)
```

区間 `[a, b)` の `add[i]` を `+1` します。

## 制約

- $0 \leq a \leq b \leq N$

## 計算量

- $O(\sqrt{N})$

# sub

```cpp
void sub(int a, int b)
```

区間 `[a, b)` の `add[i]` を `-1` します。

## 制約

- $0 \leq a \leq b \leq N$

## 計算量

- $O(\sqrt{N})$

# query

```cpp
T query(int a, int b, E x)
```

区間 `[a, b)` のうち `add[i] == x` を満たす要素の `data[i]` の総和を返します。

## 制約

- $0 \leq a \leq b \leq N$

## 計算量

- $O(\sqrt{N})$

# query_low

```cpp
T query_low(int a, int b)
```

区間 `[a, b)` のうち `add[i] >= L` を満たす要素の `data[i]` の総和を返します。

## 制約

- $0 \leq a \leq b \leq N$

## 計算量

- $O(\sqrt{N})$
