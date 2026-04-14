---
title: Succinct Indexable Dictionary (完備辞書)
documentation_of: //structure/wavelet/succinct-indexable-dictionary.hpp
---

ビット列に対して `set` と `rank` を高速に処理するデータ構造です。

# コンストラクタ

```cpp
(1) SuccinctIndexableDictionary()
(2) SuccinctIndexableDictionary(size_t length)
```

(2) は長さ `length` のビット列を確保します。初期値はすべて `0` です。

## 制約

- $0 \leq length$

## 計算量

- (2) $O(length)$

# set

```cpp
void set(int k)
```

`k` 番目のビットを `1` にします。

## 制約

- $0 \leq k < length$

## 計算量

- $O(1)$

# build

```cpp
void build()
```

`rank` クエリ用の累積情報を構築します。

`set` でビットを更新した後は、`rank` を使う前に `build` を呼んでください。

## 計算量

- $O(length)$

# operator[]

```cpp
bool operator[](int k)
```

`k` 番目のビット値を返します。

## 制約

- $0 \leq k < length$

## 計算量

- $O(1)$

# rank

```cpp
(1) int rank(int k)
(2) int rank(bool val, int k)
```

(1) 区間 `[0, k)` に含まれる `1` の個数を返します。  
(2) 区間 `[0, k)` に含まれる `val` の個数を返します。

## 制約

- $0 \leq k < length$

## 計算量

- $O(1)$
