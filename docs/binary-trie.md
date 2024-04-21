---
documentation_of: //structure/trie/binary-trie.hpp
---

## 概要

整数をビット列とみなして, トライ木のように持つデータ構造.


## 使い方

* `add(bit, idx = -1, delta = 1, xor_val = 0)`: トライ木の値 `bit` に `delta` を加える. `exist` には自分を含む部分木に追加された値の `delta` の総和, `idx` に対して $-1$ 以外を与えると `accept` にそのノードにマッチする全ての値のindexが格納される.
* `erase(bit, xor_val = 0)`: 値 `bit` に対応する `delta` に $-1$ を加える.
* `find(bit, xor_val = 0)`: 値 `bit` に対応するノードを返す. 存在しないとき `nullptr`.
* `count(bit, xor_val = 0)`: 値 `bit` に対応するノードの `delta` を返す. 存在しないとき $0$.
* `min_element(xor_val = 0)`: 最小値とそれに対応するノードを返す.
* `max_element(xor_val = 0)`: 最大値とそれに対応するノードを返す.
* `kth_element(k, xor_val = 0)`: $k$ 番目(0-indexed) に小さい値とそれに対応するノードを返す.
* `count_less(bit, xor_val = 0)`: 値 `bit` 未満の `delta` の総和を返す.

引数の最後の `xor_val` を指定すると, トライ木に存在する値全体に `xor_val` を xor とした場合の動作をする.

## 計算量

* クエリ: $O(\log V)$ 
