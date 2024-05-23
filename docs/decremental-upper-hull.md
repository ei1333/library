---
title: Decremental Upper Hull
documentation_of: //structure/others/decremental-upper-hull.hpp
---

二次元平面上に異なる $n$ 個の点があります。

点の削除クエリのみ与えられるときに、上側凸包を効率的に求めることができるデータ構造です。

点の位置を反転して与えることで、下側凸包も求められます。

# コンストラクタ

```cpp
DecrementalUpperHull< T, T2 >(const vector<Point> &ps)
```

`T` は 2 * 座標の最大値が収まる型、`T2` は (2 * 座標の最大値)^2 が収まる型を指定してください。

## 制約

- $ps$ はソートされている
- $ps$ は相異なる

## 計算量

- $O(n \log n)$

# size

```cpp
size_t size()
```

削除されずに残っている点の個数を返します。

## 計算量

- $O(1)$

# empty

```cpp
bool empty()
```

すべての点が削除されている場合は `true`、そうでない場合は `false` を返します。

## 計算量

- $O(1)$

# erase

```cpp
bool erase(int k)
```

$k$ 番目の点がすでに削除されている場合は `false` を返します。

$k$ 番目の点が残っている場合は、その点を削除して `true` を返します。

## 計算量

- amortized $O(\log n)$

# get_hull

```cpp
vector<int> get_hull()
```

残っている点たちから構成される上側凸包の点の index を昇順で返します。

## 計算量

- $O(k)$

$k$ は上側凸包に用いられた点の個数です。
