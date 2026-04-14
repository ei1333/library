---
title: Wavelet Matrix Rectangle Sum
documentation_of: //structure/wavelet/wavelet-matrix-rectangle-sum.hpp
---

静的配列に対して、値範囲での重み総和を処理するデータ構造です。

`WaveletMatrixRectangleSum< T, MAXLOG, D >` は値配列 `v` と重み配列 `d` を受け取り、区間 `[l, r)` かつ値域 `[lower, upper)` の重み総和を返します。

# WaveletMatrixRectangleSum

# コンストラクタ

```cpp
(1) WaveletMatrixRectangleSum()
(2) WaveletMatrixRectangleSum(const vector<T>& v, const vector<D>& d)
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

- $O(MAXLOG)$

# CompressedWaveletMatrixRectangleSum

座標圧縮を内部で行うラッパです。値が疎な場合はこちらを使うと扱いやすくなります。

# コンストラクタ

```cpp
CompressedWaveletMatrixRectangleSum(const vector<T>& v, const vector<D>& d)
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

- $O(\log |v| + MAXLOG)$
