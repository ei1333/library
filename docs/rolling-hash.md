---
documentation_of: //string/rolling-hash.hpp
---

## 概要

文字列の一致判定を mod $2^{61}-1$ のハッシュを用いて効率的に行う.

* `RollingHash(base)`: 基数 `base` のローリングハッシュを構築する.
* `generate_base()`: $2^{61} - 1$ 以下の乱数を返す。これを `base` とすると Hack されにくい.
* `build(s)`: 文字列 `s` のハッシュテーブルを返す.
* `query(s, l, r)`: `s` の区間 $[l, r)$ のハッシュ値を返す.
* `combine(h1, h2, h2len)`: ハッシュ値 `h1` と長さ `h2len` のハッシュ値 `h2` を結合する. `power[h2len]` での配列外参照に注意(TODO 実装).
* `lcp(a, l1, r1, b, l2, r2)`: ハッシュテーブル `a` の区間 $[l1, r1)$ と, ハッシュテーブル `b` の区間 $[l2, r2)$ の文字列の最長共通接頭辞の長さを返す.

## 計算量

* `build()`: $O(n)$
* `lcp()`: $O(\log n)$
* クエリ: $O(1)$
