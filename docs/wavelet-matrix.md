---
title: Wavelet Matrix (ウェーブレット行列)
documentation_of: //structure/wavelet/wavelet-matrix.hpp
---

静的配列に対して順序統計・値範囲頻度クエリを処理するデータ構造です。

値をそのまま扱う `WaveletMatrix< T, MAXLOG >` と、座標圧縮して扱う `CompressedWaveletMatrix< T, MAXLOG >` が提供されています。

# WaveletMatrix

# コンストラクタ

```cpp
(1) WaveletMatrix()
(2) WaveletMatrix(vector<T> v)
```

(2) は配列 `v` から構築します。`MAXLOG` は扱う値域のビット幅です。

## 計算量

- (2) $O(|v| \cdot MAXLOG)$

# access

```cpp
T access(int k)
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k < N$

## 計算量

- $O(MAXLOG)$

# rank

```cpp
int rank(const T& x, int r)
```

区間 `[0, r)` に含まれる値 `x` の個数を返します。

## 制約

- $0 \leq r \leq N$

## 計算量

- $O(MAXLOG)$

# kth_smallest

```cpp
T kth_smallest(int l, int r, int k)
```

区間 `[l, r)` の中で `k` 番目 (0-indexed) に小さい値を返します。

## 制約

- $0 \leq l \leq r \leq N$
- $0 \leq k < r - l$

## 計算量

- $O(MAXLOG)$

# kth_largest

```cpp
T kth_largest(int l, int r, int k)
```

区間 `[l, r)` の中で `k` 番目 (0-indexed) に大きい値を返します。

## 制約

- $0 \leq l \leq r \leq N$
- $0 \leq k < r - l$

## 計算量

- $O(MAXLOG)$

# range_freq

```cpp
(1) int range_freq(int l, int r, T upper)
(2) int range_freq(int l, int r, T lower, T upper)
```

(1) 区間 `[l, r)` で `v[i] < upper` を満たす個数を返します。  
(2) 区間 `[l, r)` で `lower <= v[i] < upper` を満たす個数を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(MAXLOG)$

# prev_value

```cpp
T prev_value(int l, int r, T upper)
```

区間 `[l, r)` で `v[i] < upper` を満たす値の最大値を返します。存在しないときは `T(-1)` を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(MAXLOG)$

# next_value

```cpp
T next_value(int l, int r, T lower)
```

区間 `[l, r)` で `lower <= v[i]` を満たす値の最小値を返します。存在しないときは `T(-1)` を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(MAXLOG)$

# CompressedWaveletMatrix

座標圧縮を内部で行うラッパです。値が疎な場合はこちらを使うと扱いやすくなります。

# コンストラクタ

```cpp
CompressedWaveletMatrix(const vector<T>& v)
```

配列 `v` から座標圧縮済みの Wavelet Matrix を構築します。

## 計算量

- $O(|v| \log |v| + |v| \cdot MAXLOG)$

# access

```cpp
T access(int k)
```

`k` 番目の要素を返します。

## 制約

- $0 \leq k < N$

## 計算量

- $O(MAXLOG)$

# rank

```cpp
int rank(const T& x, int r)
```

区間 `[0, r)` に含まれる値 `x` の個数を返します。

## 制約

- $0 \leq r \leq N$

## 計算量

- $O(\log |v| + MAXLOG)$

# kth_smallest

```cpp
T kth_smallest(int l, int r, int k)
```

区間 `[l, r)` の中で `k` 番目 (0-indexed) に小さい値を返します。

## 制約

- $0 \leq l \leq r \leq N$
- $0 \leq k < r - l$

## 計算量

- $O(MAXLOG)$

# kth_largest

```cpp
T kth_largest(int l, int r, int k)
```

区間 `[l, r)` の中で `k` 番目 (0-indexed) に大きい値を返します。

## 制約

- $0 \leq l \leq r \leq N$
- $0 \leq k < r - l$

## 計算量

- $O(MAXLOG)$

# range_freq

```cpp
(1) int range_freq(int l, int r, T upper)
(2) int range_freq(int l, int r, T lower, T upper)
```

(1) 区間 `[l, r)` で `v[i] < upper` を満たす個数を返します。  
(2) 区間 `[l, r)` で `lower <= v[i] < upper` を満たす個数を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(\log |v| + MAXLOG)$

# prev_value

```cpp
T prev_value(int l, int r, T upper)
```

区間 `[l, r)` で `v[i] < upper` を満たす値の最大値を返します。存在しないときは `T(-1)` を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(\log |v| + MAXLOG)$

# next_value

```cpp
T next_value(int l, int r, T lower)
```

区間 `[l, r)` で `lower <= v[i]` を満たす値の最小値を返します。存在しないときは `T(-1)` を返します。

## 制約

- $0 \leq l \leq r \leq N$

## 計算量

- $O(\log |v| + MAXLOG)$
