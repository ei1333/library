---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dsl-2-b-2.test.cpp
    title: test/verify/aoj-dsl-2-b-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-set-xor-min.test.cpp
    title: test/verify/yosupo-set-xor-min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/binary-trie.md
    document_title: Binary-Trie
    links: []
  bundledCode: "#line 1 \"structure/trie/binary-trie.hpp\"\n/**\n * @brief Binary-Trie\n\
    \ * @docs docs/binary-trie.md\n */\ntemplate< typename T, int MAX_LOG, typename\
    \ D = int >\nstruct BinaryTrie {\npublic:\n  struct Node {\n    Node *nxt[2];\n\
    \    D exist;\n    vector< int > accept;\n\n    Node() : nxt{nullptr, nullptr},\
    \ exist(0) {}\n  };\n\n  Node *root;\n\n  explicit BinaryTrie() : root(new Node())\
    \ {}\n\n  explicit BinaryTrie(Node *root) : root(root) {}\n\n  void add(const\
    \ T &bit, int idx = -1, D delta = 1, T xor_val = 0) {\n    root = add(root, bit,\
    \ idx, MAX_LOG, delta, xor_val);\n  }\n\n  void erase(const T &bit, T xor_val\
    \ = 0) {\n    add(bit, -1, -1, xor_val);\n  }\n\n  Node *find(const T &bit, T\
    \ xor_val = 0) {\n    return find(root, bit, MAX_LOG, xor_val);\n  }\n\n  D count(const\
    \ T &bit, T xor_val = 0) {\n    auto node = find(bit, xor_val);\n    return node\
    \ ? node->exist : 0;\n  }\n\n  pair< T, Node * > min_element(T xor_val = 0) {\n\
    \    assert(root->exist > 0);\n    return kth_element(0, xor_val);\n  }\n\n  pair<\
    \ T, Node * > max_element(T xor_val = 0) {\n    assert(root->exist > 0);\n   \
    \ return kth_element(root->exist - 1, xor_val);\n  }\n\n  pair< T, Node * > kth_element(D\
    \ k, T xor_val = 0) { // 0-indexed\n    assert(0 <= k && k < root->exist);\n \
    \   return kth_element(root, k, MAX_LOG, xor_val);\n  }\n\n  D count_less(const\
    \ T &bit, T xor_val = 0) { // < bit\n    return count_less(root, bit, MAX_LOG,\
    \ xor_val);\n  }\n\nprivate:\n\n  virtual Node *clone(Node *t) { return t; }\n\
    \n  Node *add(Node *t, T bit, int idx, int depth, D x, T xor_val, bool need =\
    \ true) {\n    if(need) t = clone(t);\n    if(depth == -1) {\n      t->exist +=\
    \ x;\n      if(idx >= 0) t->accept.emplace_back(idx);\n    } else {\n      bool\
    \ f = (xor_val >> depth) & 1;\n      auto &to = t->nxt[f ^ ((bit >> depth) & 1)];\n\
    \      if(!to) to = new Node(), need = false;\n      to = add(to, bit, idx, depth\
    \ - 1, x, xor_val, need);\n      t->exist += x;\n    }\n    return t;\n  }\n\n\
    \  Node *find(Node *t, T bit, int depth, T xor_val) {\n    if(depth == -1) {\n\
    \      return t;\n    } else {\n      bool f = (xor_val >> depth) & 1;\n     \
    \ auto &to = t->nxt[f ^ ((bit >> depth) & 1)];\n      return to ? find(to, bit,\
    \ depth - 1, xor_val) : nullptr;\n    }\n  }\n\n  pair< T, Node * > kth_element(Node\
    \ *t, D k, int bit_index, T xor_val) { // 0-indexed\n    if(bit_index == -1) {\n\
    \      return {0, t};\n    } else {\n      bool f = (xor_val >> bit_index) & 1;\n\
    \      if((t->nxt[f] ? t->nxt[f]->exist : 0) <= k) {\n        auto ret = kth_element(t->nxt[f\
    \ ^ 1], k - (t->nxt[f] ? t->nxt[f]->exist : 0), bit_index - 1, xor_val);\n   \
    \     ret.first |= T(1) << bit_index;\n        return ret;\n      } else {\n \
    \       return kth_element(t->nxt[f], k, bit_index - 1, xor_val);\n      }\n \
    \   }\n  }\n\n  D count_less(Node *t, const T &bit, int bit_index, T xor_val)\
    \ {\n    if(bit_index == -1) return 0;\n    D ret = 0;\n    bool f = (xor_val\
    \ >> bit_index) & 1;\n    if((bit >> bit_index & 1) and t->nxt[f]) ret += t->nxt[f]->exist;\n\
    \    if(t->nxt[f ^ (bit >> bit_index & 1)]) ret += count_less(t->nxt[f ^ (bit\
    \ >> bit_index & 1)], bit, bit_index - 1, xor_val);\n    return ret;\n  }\n};\n"
  code: "/**\n * @brief Binary-Trie\n * @docs docs/binary-trie.md\n */\ntemplate<\
    \ typename T, int MAX_LOG, typename D = int >\nstruct BinaryTrie {\npublic:\n\
    \  struct Node {\n    Node *nxt[2];\n    D exist;\n    vector< int > accept;\n\
    \n    Node() : nxt{nullptr, nullptr}, exist(0) {}\n  };\n\n  Node *root;\n\n \
    \ explicit BinaryTrie() : root(new Node()) {}\n\n  explicit BinaryTrie(Node *root)\
    \ : root(root) {}\n\n  void add(const T &bit, int idx = -1, D delta = 1, T xor_val\
    \ = 0) {\n    root = add(root, bit, idx, MAX_LOG, delta, xor_val);\n  }\n\n  void\
    \ erase(const T &bit, T xor_val = 0) {\n    add(bit, -1, -1, xor_val);\n  }\n\n\
    \  Node *find(const T &bit, T xor_val = 0) {\n    return find(root, bit, MAX_LOG,\
    \ xor_val);\n  }\n\n  D count(const T &bit, T xor_val = 0) {\n    auto node =\
    \ find(bit, xor_val);\n    return node ? node->exist : 0;\n  }\n\n  pair< T, Node\
    \ * > min_element(T xor_val = 0) {\n    assert(root->exist > 0);\n    return kth_element(0,\
    \ xor_val);\n  }\n\n  pair< T, Node * > max_element(T xor_val = 0) {\n    assert(root->exist\
    \ > 0);\n    return kth_element(root->exist - 1, xor_val);\n  }\n\n  pair< T,\
    \ Node * > kth_element(D k, T xor_val = 0) { // 0-indexed\n    assert(0 <= k &&\
    \ k < root->exist);\n    return kth_element(root, k, MAX_LOG, xor_val);\n  }\n\
    \n  D count_less(const T &bit, T xor_val = 0) { // < bit\n    return count_less(root,\
    \ bit, MAX_LOG, xor_val);\n  }\n\nprivate:\n\n  virtual Node *clone(Node *t) {\
    \ return t; }\n\n  Node *add(Node *t, T bit, int idx, int depth, D x, T xor_val,\
    \ bool need = true) {\n    if(need) t = clone(t);\n    if(depth == -1) {\n   \
    \   t->exist += x;\n      if(idx >= 0) t->accept.emplace_back(idx);\n    } else\
    \ {\n      bool f = (xor_val >> depth) & 1;\n      auto &to = t->nxt[f ^ ((bit\
    \ >> depth) & 1)];\n      if(!to) to = new Node(), need = false;\n      to = add(to,\
    \ bit, idx, depth - 1, x, xor_val, need);\n      t->exist += x;\n    }\n    return\
    \ t;\n  }\n\n  Node *find(Node *t, T bit, int depth, T xor_val) {\n    if(depth\
    \ == -1) {\n      return t;\n    } else {\n      bool f = (xor_val >> depth) &\
    \ 1;\n      auto &to = t->nxt[f ^ ((bit >> depth) & 1)];\n      return to ? find(to,\
    \ bit, depth - 1, xor_val) : nullptr;\n    }\n  }\n\n  pair< T, Node * > kth_element(Node\
    \ *t, D k, int bit_index, T xor_val) { // 0-indexed\n    if(bit_index == -1) {\n\
    \      return {0, t};\n    } else {\n      bool f = (xor_val >> bit_index) & 1;\n\
    \      if((t->nxt[f] ? t->nxt[f]->exist : 0) <= k) {\n        auto ret = kth_element(t->nxt[f\
    \ ^ 1], k - (t->nxt[f] ? t->nxt[f]->exist : 0), bit_index - 1, xor_val);\n   \
    \     ret.first |= T(1) << bit_index;\n        return ret;\n      } else {\n \
    \       return kth_element(t->nxt[f], k, bit_index - 1, xor_val);\n      }\n \
    \   }\n  }\n\n  D count_less(Node *t, const T &bit, int bit_index, T xor_val)\
    \ {\n    if(bit_index == -1) return 0;\n    D ret = 0;\n    bool f = (xor_val\
    \ >> bit_index) & 1;\n    if((bit >> bit_index & 1) and t->nxt[f]) ret += t->nxt[f]->exist;\n\
    \    if(t->nxt[f ^ (bit >> bit_index & 1)]) ret += count_less(t->nxt[f ^ (bit\
    \ >> bit_index & 1)], bit, bit_index - 1, xor_val);\n    return ret;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/trie/binary-trie.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-set-xor-min.test.cpp
  - test/verify/aoj-dsl-2-b-2.test.cpp
documentation_of: structure/trie/binary-trie.hpp
layout: document
redirect_from:
- /library/structure/trie/binary-trie.hpp
- /library/structure/trie/binary-trie.hpp.html
title: Binary-Trie
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
