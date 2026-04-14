---
title: Trie
documentation_of: //structure/trie/trie.hpp
---

文字列集合を管理する Trie です。

`Trie< char_size, margin >` は、各文字 `c` を `c - margin` に写して遷移します。

# コンストラクタ

```cpp
Trie< char_size, margin >()
```

空の Trie を作成します。

# add

```cpp
(1) void add(const string& str, int id)
(2) void add(const string& str)
```

(1) 文字列 `str` を挿入し、終端ノードに `id` を登録します。  
(2) 文字列 `str` を挿入し、自動採番された `id` を登録します。

## 制約

- `str` の各文字 `c` について `0 <= c - margin < char_size`

## 計算量

- $O(|str|)$

# query

```cpp
(1) void query(const string& str, const function<void(int)>& f, int str_index, int node_index)
(2) void query(const string& str, const function<void(int)>& f)
```

`str` を先頭から辿り、到達した各ノードに登録された `id` を `f` に渡します。  
つまり、`str` の接頭辞と一致する挿入済み文字列の `id` を列挙します。

(2) は `(str_index, node_index) = (0, 0)` から開始するラッパです。

## 計算量

- $O(|str| + 列挙されるid数)$

# count

```cpp
int count() const
```

挿入した文字列数を返します（重複を含む）。

## 計算量

- $O(1)$

# size

```cpp
int size() const
```

Trie のノード数を返します。

## 計算量

- $O(1)$
