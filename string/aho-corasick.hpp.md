---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-430.test.cpp
    title: test/verify/yukicoder-430.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/aho-corasick.md
    document_title: "Aho-Corasick(\u30A8\u30A4\u30DB\u2013\u30B3\u30E9\u30B7\u30C3\
      \u30AF\u6CD5)"
    links: []
  bundledCode: "#line 1 \"string/aho-corasick.hpp\"\n/**\n * @brief Aho-Corasick(\u30A8\
    \u30A4\u30DB\u2013\u30B3\u30E9\u30B7\u30C3\u30AF\u6CD5)\n * @docs docs/aho-corasick.md\n\
    \ */\ntemplate< int char_size, int margin >\nstruct AhoCorasick : Trie< char_size\
    \ + 1, margin > {\n  using Trie< char_size + 1, margin >::Trie;\n\n  const int\
    \ FAIL = char_size;\n  vector< int > correct;\n\n  void build(bool heavy = true)\
    \ {\n    correct.resize(this->size());\n    for(int i = 0; i < this->size(); i++)\
    \ {\n      correct[i] = (int) this->nodes[i].accept.size();\n    }\n    queue<\
    \ int > que;\n    for(int i = 0; i <= char_size; i++) {\n      if(~this->nodes[0].nxt[i])\
    \ {\n        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;\n        que.emplace(this->nodes[0].nxt[i]);\n\
    \      } else {\n        this->nodes[0].nxt[i] = 0;\n      }\n    }\n    while(!que.empty())\
    \ {\n      auto &now = this->nodes[que.front()];\n      int fail = now.nxt[FAIL];\n\
    \      correct[que.front()] += correct[fail];\n      que.pop();\n      for(int\
    \ i = 0; i < char_size; i++) {\n        if(~now.nxt[i]) {\n          this->nodes[now.nxt[i]].nxt[FAIL]\
    \ = this->nodes[fail].nxt[i];\n          if(heavy) {\n            auto &u = this->nodes[now.nxt[i]].accept;\n\
    \            auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;\n       \
    \     vector< int > accept;\n            set_union(begin(u), end(u), begin(v),\
    \ end(v), back_inserter(accept));\n            u = accept;\n          }\n    \
    \      que.emplace(now.nxt[i]);\n        } else {\n          now.nxt[i] = this->nodes[fail].nxt[i];\n\
    \        }\n      }\n    }\n  }\n\n  map< int, int > match(const string &str,\
    \ int now = 0) {\n    map< int, int > result;\n    for(auto &c : str) {\n    \
    \  now = this->nodes[now].nxt[c - margin];\n      for(auto &v : this->nodes[now].accept)\
    \ result[v] += 1;\n    }\n    return result;\n  }\n\n  pair< int64_t, int > move(const\
    \ char &c, int now = 0) {\n    now = this->nodes[now].nxt[c - margin];\n    return\
    \ {correct[now], now};\n  }\n\n  pair< int64_t, int > move(const string &str,\
    \ int now = 0) {\n    int64_t sum = 0;\n    for(auto &c : str) {\n      auto nxt\
    \ = move(c, now);\n      sum += nxt.first;\n      now = nxt.second;\n    }\n \
    \   return {sum, now};\n  }\n};\n"
  code: "/**\n * @brief Aho-Corasick(\u30A8\u30A4\u30DB\u2013\u30B3\u30E9\u30B7\u30C3\
    \u30AF\u6CD5)\n * @docs docs/aho-corasick.md\n */\ntemplate< int char_size, int\
    \ margin >\nstruct AhoCorasick : Trie< char_size + 1, margin > {\n  using Trie<\
    \ char_size + 1, margin >::Trie;\n\n  const int FAIL = char_size;\n  vector< int\
    \ > correct;\n\n  void build(bool heavy = true) {\n    correct.resize(this->size());\n\
    \    for(int i = 0; i < this->size(); i++) {\n      correct[i] = (int) this->nodes[i].accept.size();\n\
    \    }\n    queue< int > que;\n    for(int i = 0; i <= char_size; i++) {\n   \
    \   if(~this->nodes[0].nxt[i]) {\n        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL]\
    \ = 0;\n        que.emplace(this->nodes[0].nxt[i]);\n      } else {\n        this->nodes[0].nxt[i]\
    \ = 0;\n      }\n    }\n    while(!que.empty()) {\n      auto &now = this->nodes[que.front()];\n\
    \      int fail = now.nxt[FAIL];\n      correct[que.front()] += correct[fail];\n\
    \      que.pop();\n      for(int i = 0; i < char_size; i++) {\n        if(~now.nxt[i])\
    \ {\n          this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];\n\
    \          if(heavy) {\n            auto &u = this->nodes[now.nxt[i]].accept;\n\
    \            auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;\n       \
    \     vector< int > accept;\n            set_union(begin(u), end(u), begin(v),\
    \ end(v), back_inserter(accept));\n            u = accept;\n          }\n    \
    \      que.emplace(now.nxt[i]);\n        } else {\n          now.nxt[i] = this->nodes[fail].nxt[i];\n\
    \        }\n      }\n    }\n  }\n\n  map< int, int > match(const string &str,\
    \ int now = 0) {\n    map< int, int > result;\n    for(auto &c : str) {\n    \
    \  now = this->nodes[now].nxt[c - margin];\n      for(auto &v : this->nodes[now].accept)\
    \ result[v] += 1;\n    }\n    return result;\n  }\n\n  pair< int64_t, int > move(const\
    \ char &c, int now = 0) {\n    now = this->nodes[now].nxt[c - margin];\n    return\
    \ {correct[now], now};\n  }\n\n  pair< int64_t, int > move(const string &str,\
    \ int now = 0) {\n    int64_t sum = 0;\n    for(auto &c : str) {\n      auto nxt\
    \ = move(c, now);\n      sum += nxt.first;\n      now = nxt.second;\n    }\n \
    \   return {sum, now};\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/aho-corasick.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-430.test.cpp
documentation_of: string/aho-corasick.hpp
layout: document
redirect_from:
- /library/string/aho-corasick.hpp
- /library/string/aho-corasick.hpp.html
title: "Aho-Corasick(\u30A8\u30A4\u30DB\u2013\u30B3\u30E9\u30B7\u30C3\u30AF\u6CD5)"
---
## 概要

複数文字列に対するパターンマッチングオートマトンを構築する.

Trie のそれぞれのノードがオートマトンのある状態に相当する.

## 使い方

* `build()`: 現在のTrieをもとにオートマトンを構築する.
* `match(str, now)`: 現状態が `now` で, 文字列 `str` が現れた時に, 新たに各パターン文字列にマッチした回数を返す.
* `move(c, now)`: 現状態が `now` で, 文字 `c` が現れたときに, 新たにパターン文字列にマッチした個数と, 次状態を返す.

## 計算量

* `build()`: パターン文字列の長さの総和
* クエリ: $O(1)$
