---
title: Rolling Hash (ローリングハッシュ)
documentation_of: //string/rolling-hash.hpp
---

文字列に対応するハッシュを mod $2^{61}-1$ で計算します。文字列 $S$ のハッシュは以下の計算式で求めます。

$\mathrm{hash}(S) = \displaystyle \sum_{i=0}^{N-1} S_i b^i \pmod {2^{61} - 1}$ 


# コンストラクタ

```cpp
(1) RollingHash()
(2) RollingHash(const string& s)
(3) RollingHash(const vector<T>& s)
```

1. 空文字列で初期化します。
2. `s` で初期化します。
3. `s` で初期化します。

## 計算量

- $O(n)$

# size

```cpp
int size() const
```

文字列の長さを返します。

## 計算量

- $O(1)$

# push_front

```cpp
void push_front(T c)
```

文字列の先頭に文字 `c` を追加します。

## 計算量

- $O(1)$

# push_back

```cpp
void push_back(T c)
```

文字列の末尾に文字 `c` を追加します。

## 計算量

- $O(1)$

# operator[]

```cpp
T operator[](int k) const
```

$k$ 番目 (0-indexed) の文字を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- $O(1)$

# get

```cpp
(1) mint get(int r) const
(2) mint get(int l, int r) const
```

1. $S[0, r)$ に対応するハッシュを返します。
2. $S[l, r)$ に対応するハッシュを返します。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- $O(1)$

# lcp

```cpp
(1) int lcp(const RollingHash& b) const
(2) int lcp(const RollingHash& b, int l1, int l2) const
```

1. 自身の文字列と、`b` に対応する文字列の LCP の長さを返します。
2. 自身の文字列の `l1` 文字目以降と、`b` に対応する文字列の `l2` 文字以降の文字列の LCP の長さを返します。

## 制約

- $l1 \leq n$
- $l2 \leq m$

## 計算量

- $O(\log n)$

# combine

```cpp
static mint combine(mint h1, int h1_len, mint h2)
```

長さ `h1_len` のハッシュ `h1` とハッシュ `h2` をこの順で結合したハッシュを返します。

## 計算量

- $O(1)$

# clear

```cpp
void clear()
```

文字列と対応するハッシュを空にします。

## 計算量

- $O(n)$

# merge

```cpp
void merge(RollingHash& b)
```

自身と `b` をこの順で結合します。副作用として `b` を空文字列にします。

## 計算量

- $O(\min(n, m))$
