---
title: Wavelet Matrix Point Add Rectangle Sum
documentation_of: //structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
---

点更新付きで、値範囲の重み総和を処理するデータ構造です。

`WaveletMatrixPointAddRectangleSum< T, MAXLOG, D >` は値配列 `v` の位置は固定したまま、重み配列に対して一点加算と範囲和クエリを処理します。

# WaveletMatrixPointAddRectangleSum

# コンストラクタ

```cpp
(1) WaveletMatrixPointAddRectangleSum()
(2) WaveletMatrixPointAddRectangleSum(const vector<T>& v, const vector<D>& d)
```

(2) は `v[i]` に重み `d[i]` を対応づけて構築します。

## 制約

- `v.size() == d.size()`

## 計算量

- (2) $O(|v| \cdot MAXLOG)$

# rect_sum

```cpp
(1) D rect_sum(int l, int r, T upper)
(2) D rect_sum(int l, int r, T lower, T upper)
```

(1) 区間 `[l, r)` で `v[i] < upper` を満たす要素の重み総和を返します。  
(2) 区間 `[l, r)` で `lower <= v[i] < upper` を満たす要素の重み総和を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(MAXLOG \log N)$

# point_add

```cpp
void point_add(int k, const D& x)
```

`k` 番目要素の重みに `x` を加算します。

## 制約

- $0 \leq k < N$

## 計算量

- $O(MAXLOG \log N)$

# CompressedWaveletMatrixPointAddRectangleSum

座標圧縮を内部で行うラッパです。値が疎な場合はこちらを使うと扱いやすくなります。

# コンストラクタ

```cpp
CompressedWaveletMatrixPointAddRectangleSum(const vector<T>& v, const vector<D>& d)
```

配列 `v` を座標圧縮して構築します。

## 制約

- `v.size() == d.size()`

## 計算量

- $O(|v| \log |v| + |v| \cdot MAXLOG)$

# rect_sum

```cpp
(1) D rect_sum(int l, int r, T upper)
(2) D rect_sum(int l, int r, T lower, T upper)
```

(1) 区間 `[l, r)` で `v[i] < upper` を満たす要素の重み総和を返します。  
(2) 区間 `[l, r)` で `lower <= v[i] < upper` を満たす要素の重み総和を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(\log |v| + MAXLOG \log N)$

# point_add

```cpp
void point_add(int k, const D& x)
```

`k` 番目要素の重みに `x` を加算します。

## 制約

- $0 \leq k < N$

## 計算量

- $O(MAXLOG \log N)$
