---
title: Suffix Array (接尾辞配列)
documentation_of: //string/suffix-array.hpp
---

文字列や整数列などの列 `vs` に対して、各接尾辞の辞書順を管理する配列を構築します。

`SuffixArray< T >` は `vector<int>` を継承しており、`sa[i]` が辞書順で `i` 番目の接尾辞の開始位置を表します。

# コンストラクタ

```cpp
SuffixArray(const T& vs, bool compress = false)
```

列 `vs` から接尾辞配列を構築します。

`compress = true` のとき、値を座標圧縮してから構築します。  
`compress = false` のとき、`vs` の最小値を基準に平行移動して構築します。

## 計算量

- $O(|vs|)$

# output

```cpp
void output() const
```

構築済みの接尾辞配列を標準出力に整形して出力します。

# lt_substr

```cpp
bool lt_substr(const string& t, int si = 0, int ti = 0)
```

`vs[si, |vs|)` が `t[ti, |t|)` より辞書順で小さいかを返します。

## 計算量

- $O(\min(|vs|-si, |t|-ti))$

# lower_bound

```cpp
int lower_bound(const T& t)
```

`t <= vs[sa[i], |vs|)` を満たす最小の `i` を返します。

## 計算量

- $O(|t| \log |vs|)$

# equal_range

```cpp
pair<int, int> equal_range(T& t)
```

`t` を接頭辞にもつ接尾辞の範囲 `[l, r)` を返します。

返り値の `l` 以上 `r` 未満の `i` について、`vs[sa[i], ...]` は `t` で始まります。

## 制約

- `t` は空でない
- `t.back()++` と `t.back()--` が可能

## 計算量

- $O(|t| \log |vs|)$
