---
title: Aho Corasick (エイホ–コラシック法)
documentation_of: //string/aho-corasick.hpp
---

複数文字列に対するパターンマッチングオートマトンを構築します。

Trie のそれぞれのノードがオートマトンのある状態に相当します。

# コンストラクタ

```cpp
AhoCorasick< char_size, margin >()
```

空の Trie を作ります。

文字の種類数 `char_size` で、全ての文字に対して `margin` を減算します。

# build

```cpp
void build(bool heavy = true)
```

現在の Trie をもとにオートマトンを構築します。

## 計算量

- O(追加した文字列の長さの総和)

# match

```cpp
unordered_map<int, int> match(const string &str, int now = 0)
```

現状態が `now` で, 文字列 `str` が現れた時に、新たに各パターン文字列にマッチした回数を返します。

## 計算量

- O(`str` の長さ)

# move

```cpp
(1) pair<int64_t, int> move(const char &c, int now = 0)
(2) pair<int64_t, int> move(const string &str, int now = 0)
```

(1) 現状態が `now` で、文字 `c` が現れたときに、新たにパターン文字列にマッチした個数と、次状態を返します。
(2) 現状態が `now` で、文字列 `str` が現れたときに、新たにパターン文字列にマッチした個数と、次状態を返します。

## 計算量

- (1) $O(1)$
- (2) O(`str` の長さ)
