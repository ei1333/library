---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/yukicoder-263.test.cpp
    title: test/verify/yukicoder-263.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-273.test.cpp
    title: test/verify/yukicoder-273.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-465.test.cpp
    title: test/verify/yukicoder-465.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: docs/palindromic-tree.md
    document_title: "Palindromic Tree(\u56DE\u6587\u6728)"
    links:
    - https://math314.hateblo.jp/entry/2016/12/19/005919
  bundledCode: "#line 1 \"string/palindromic-tree.hpp\"\n/**\n * @brief Palindromic\
    \ Tree(\u56DE\u6587\u6728)\n * @see https://math314.hateblo.jp/entry/2016/12/19/005919\n\
    \ * @docs docs/palindromic-tree.md\n */\ntemplate< typename T = char >\nstruct\
    \ PalindromicTree {\npublic:\n  struct Node {\n    map< T, int > link; // \u5B50\
    \u306Eidx\n    int suffix_link; // \u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306E\
    idx\n    int len; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u306E\u9577\u3055\n\
    \    vector< int > idx; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u3092\u6700\u9577\
    \u56DE\u6587\u63A5\u5C3E\u8F9E\u3068\u3059\u308Bidx\n    int delta_link; // \u5DEE\
    \u5206\u304C\u7570\u306A\u308B\u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306E\
    idx\n\n    Node() = default;\n\n    Node(int suf, int len) : suffix_link(suf),\
    \ len(len), delta_link(-1) {}\n  };\n\n  vector< Node > ns;\n  int ptr;\n  vector<\
    \ T > vs;\n\nprivate:\n  int find_prev_palindrome(int cur) const {\n    int pos\
    \ = (int) vs.size() - 1;\n    for(;;) {\n      int rev = pos - 1 - ns[cur].len;\n\
    \      if(rev >= 0 and vs[rev] == vs.back()) break;\n      cur = ns[cur].suffix_link;\n\
    \    }\n    return cur;\n  }\n\n  bool output_dfs(int v, int id, vector< T > &ret)\
    \ const {\n    if(v == id) return true;\n    for(auto &nxt: ns[v].link) {\n  \
    \    if(output_dfs(nxt.second, id, ret)) {\n        ret.emplace_back(nxt.first);\n\
    \        return true;\n      }\n    }\n    return false;\n  }\n\npublic:\n  PalindromicTree()\
    \ : ptr(0) {\n    ns.emplace_back(0, -1); // \u9577\u3055 -1\n    ns.emplace_back(0,\
    \ 0); // \u9577\u3055 0\n  }\n\n  PalindromicTree(const string &S) : PalindromicTree()\
    \ {\n    add(S);\n  }\n\n  int diff(int t) const {\n    if(ns[t].suffix_link <=\
    \ 0) return -1;\n    return ns[t].len - ns[ns[t].suffix_link].len;\n  }\n\n  int\
    \ add(const T &x) {\n    int idx = (int) vs.size();\n    vs.emplace_back(x);\n\
    \    int cur = find_prev_palindrome(ptr);\n    auto res = ns[cur].link.insert(make_pair(x,\
    \ (int) ns.size()));\n    ptr = res.first->second;\n    if(res.second) {\n   \
    \   ns.emplace_back(-1, ns[cur].len + 2);\n      if(ns.back().len == 1) {\n  \
    \      ns.back().suffix_link = 1;\n      } else {\n        ns.back().suffix_link\
    \ = ns[find_prev_palindrome(ns[cur].suffix_link)].link[x];\n      }\n      if(diff(ptr)\
    \ == diff(ns.back().suffix_link)) {\n        ns.back().delta_link = ns[ns.back().suffix_link].delta_link;\n\
    \      } else {\n        ns.back().delta_link = ns.back().suffix_link;\n     \
    \ }\n    }\n    ns[ptr].idx.emplace_back(idx);\n    return ptr;\n  }\n\n  // add(x)\
    \ \u306E\u3042\u3068\u306B\u547C\u3073\u51FA\u3059\n  // * init(node_idx, pos):\
    \   \u9802\u70B9 node_idx \u3092 S[pos,i] \u304C\u56DE\u6587\u306E\u3068\u304D\
    \u306E\u521D\u671F\u5024\u306B\u3059\u308B\n  // * apply(node_idx, pre_idx): \u9802\
    \u70B9 node_idx \u306B \u9802\u70B9 pre_idx \u306E\u7D50\u679C\u3092\u52A0\u3048\
    \u308B\n  // * update: S[i]\u3092\u672B\u5C3E\u3068\u3059\u308B\u56DE\u6587\u306E\
    \u9802\u70B9\u756A\u53F7\u306E\u96C6\u5408\n  template< typename I, typename U\
    \ >\n  vector< int > update_dp(const I &init, const U &apply) {\n    int i = (int)\
    \ vs.size() - 1;\n    int id = ptr;\n    vector< int > update;\n    while(ns[id].len\
    \ > 0) {\n      init(id, i + 1 - ns[ns[id].delta_link].len - diff(id));\n    \
    \  if(ns[id].suffix_link != ns[id].delta_link) {\n        apply(id, ns[id].suffix_link);\n\
    \      }\n      update.emplace_back(id);\n      id = ns[id].delta_link;\n    }\n\
    \    return update;\n  }\n\n  void add(const string &s) {\n    for(auto &x: s)\
    \ add(x);\n  }\n\n  vector< int > build_frequency() const {\n    vector< int >\
    \ ret(ns.size());\n    for(int i = (int) ns.size() - 1; i > 0; i--) {\n      ret[i]\
    \ += (int) ns[i].idx.size();\n      ret[ns[i].suffix_link] += ret[i];\n    }\n\
    \    return ret;\n  }\n\n  vector< T > output(int idx) const {\n    if(idx ==\
    \ 0) return {-1};\n    if(idx == 1) return {0};\n    vector< T > ret;\n    output_dfs(0,\
    \ idx, ret);\n    output_dfs(1, idx, ret);\n    int start = (int) ret.size() -\
    \ 1;\n    if(ns[idx].len & 1) --start;\n    for(int i = start; i >= 0; i--) {\n\
    \      ret.emplace_back(ret[i]);\n    }\n    return ret;\n  }\n\n  int size()\
    \ const {\n    return (int) ns.size();\n  }\n\n  Node &operator[](int idx) {\n\
    \    return ns[idx];\n  }\n};\n"
  code: "/**\n * @brief Palindromic Tree(\u56DE\u6587\u6728)\n * @see https://math314.hateblo.jp/entry/2016/12/19/005919\n\
    \ * @docs docs/palindromic-tree.md\n */\ntemplate< typename T = char >\nstruct\
    \ PalindromicTree {\npublic:\n  struct Node {\n    map< T, int > link; // \u5B50\
    \u306Eidx\n    int suffix_link; // \u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306E\
    idx\n    int len; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u306E\u9577\u3055\n\
    \    vector< int > idx; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u3092\u6700\u9577\
    \u56DE\u6587\u63A5\u5C3E\u8F9E\u3068\u3059\u308Bidx\n    int delta_link; // \u5DEE\
    \u5206\u304C\u7570\u306A\u308B\u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306E\
    idx\n\n    Node() = default;\n\n    Node(int suf, int len) : suffix_link(suf),\
    \ len(len), delta_link(-1) {}\n  };\n\n  vector< Node > ns;\n  int ptr;\n  vector<\
    \ T > vs;\n\nprivate:\n  int find_prev_palindrome(int cur) const {\n    int pos\
    \ = (int) vs.size() - 1;\n    for(;;) {\n      int rev = pos - 1 - ns[cur].len;\n\
    \      if(rev >= 0 and vs[rev] == vs.back()) break;\n      cur = ns[cur].suffix_link;\n\
    \    }\n    return cur;\n  }\n\n  bool output_dfs(int v, int id, vector< T > &ret)\
    \ const {\n    if(v == id) return true;\n    for(auto &nxt: ns[v].link) {\n  \
    \    if(output_dfs(nxt.second, id, ret)) {\n        ret.emplace_back(nxt.first);\n\
    \        return true;\n      }\n    }\n    return false;\n  }\n\npublic:\n  PalindromicTree()\
    \ : ptr(0) {\n    ns.emplace_back(0, -1); // \u9577\u3055 -1\n    ns.emplace_back(0,\
    \ 0); // \u9577\u3055 0\n  }\n\n  PalindromicTree(const string &S) : PalindromicTree()\
    \ {\n    add(S);\n  }\n\n  int diff(int t) const {\n    if(ns[t].suffix_link <=\
    \ 0) return -1;\n    return ns[t].len - ns[ns[t].suffix_link].len;\n  }\n\n  int\
    \ add(const T &x) {\n    int idx = (int) vs.size();\n    vs.emplace_back(x);\n\
    \    int cur = find_prev_palindrome(ptr);\n    auto res = ns[cur].link.insert(make_pair(x,\
    \ (int) ns.size()));\n    ptr = res.first->second;\n    if(res.second) {\n   \
    \   ns.emplace_back(-1, ns[cur].len + 2);\n      if(ns.back().len == 1) {\n  \
    \      ns.back().suffix_link = 1;\n      } else {\n        ns.back().suffix_link\
    \ = ns[find_prev_palindrome(ns[cur].suffix_link)].link[x];\n      }\n      if(diff(ptr)\
    \ == diff(ns.back().suffix_link)) {\n        ns.back().delta_link = ns[ns.back().suffix_link].delta_link;\n\
    \      } else {\n        ns.back().delta_link = ns.back().suffix_link;\n     \
    \ }\n    }\n    ns[ptr].idx.emplace_back(idx);\n    return ptr;\n  }\n\n  // add(x)\
    \ \u306E\u3042\u3068\u306B\u547C\u3073\u51FA\u3059\n  // * init(node_idx, pos):\
    \   \u9802\u70B9 node_idx \u3092 S[pos,i] \u304C\u56DE\u6587\u306E\u3068\u304D\
    \u306E\u521D\u671F\u5024\u306B\u3059\u308B\n  // * apply(node_idx, pre_idx): \u9802\
    \u70B9 node_idx \u306B \u9802\u70B9 pre_idx \u306E\u7D50\u679C\u3092\u52A0\u3048\
    \u308B\n  // * update: S[i]\u3092\u672B\u5C3E\u3068\u3059\u308B\u56DE\u6587\u306E\
    \u9802\u70B9\u756A\u53F7\u306E\u96C6\u5408\n  template< typename I, typename U\
    \ >\n  vector< int > update_dp(const I &init, const U &apply) {\n    int i = (int)\
    \ vs.size() - 1;\n    int id = ptr;\n    vector< int > update;\n    while(ns[id].len\
    \ > 0) {\n      init(id, i + 1 - ns[ns[id].delta_link].len - diff(id));\n    \
    \  if(ns[id].suffix_link != ns[id].delta_link) {\n        apply(id, ns[id].suffix_link);\n\
    \      }\n      update.emplace_back(id);\n      id = ns[id].delta_link;\n    }\n\
    \    return update;\n  }\n\n  void add(const string &s) {\n    for(auto &x: s)\
    \ add(x);\n  }\n\n  vector< int > build_frequency() const {\n    vector< int >\
    \ ret(ns.size());\n    for(int i = (int) ns.size() - 1; i > 0; i--) {\n      ret[i]\
    \ += (int) ns[i].idx.size();\n      ret[ns[i].suffix_link] += ret[i];\n    }\n\
    \    return ret;\n  }\n\n  vector< T > output(int idx) const {\n    if(idx ==\
    \ 0) return {-1};\n    if(idx == 1) return {0};\n    vector< T > ret;\n    output_dfs(0,\
    \ idx, ret);\n    output_dfs(1, idx, ret);\n    int start = (int) ret.size() -\
    \ 1;\n    if(ns[idx].len & 1) --start;\n    for(int i = start; i >= 0; i--) {\n\
    \      ret.emplace_back(ret[i]);\n    }\n    return ret;\n  }\n\n  int size()\
    \ const {\n    return (int) ns.size();\n  }\n\n  Node &operator[](int idx) {\n\
    \    return ns[idx];\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/palindromic-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/verify/yukicoder-273.test.cpp
  - test/verify/yukicoder-263.test.cpp
  - test/verify/yukicoder-465.test.cpp
documentation_of: string/palindromic-tree.hpp
layout: document
redirect_from:
- /library/string/palindromic-tree.hpp
- /library/string/palindromic-tree.hpp.html
title: "Palindromic Tree(\u56DE\u6587\u6728)"
---
## 概要

文字列 $S$ が与えられる. Parindromic Tree は $S$ に含まれるすべての回文を頂点とした木である.

長さが $-1$ と $0$ の超頂点を用意する. 各頂点からは, その頂点に対応する回文の両端に同じ文字を $1$ 文字加えてできる回文の頂点に辺を張ることで木を構成する. 特に長さ $1$ の回文は $-1$ の超頂点から, 長さ $2$ の回文は $0$ の超頂点から辺を張ることになる.

さらに Suffix Link として, 頂点の回文に含まれる最大の回文接尾辞に対応する頂点に辺を張る. 例えば eertree からは ee, reer からは r に Suffix Link が張られることになる. Suffix Link からなる木を Suffix Link Tree と呼ぶことにする.

Parindromic Tree は, 長さ $-1$ の超頂点, 長さ $0$ の超頂点を根とした木および Suffix Link Tree の $3$ つの木構造を同時に管理するデータ構造とみなせる.


文字列に含まれる全てのユニークな回文の個数は超頂点 $-1, 0$ を除いた頂点数, $i$ 番目の文字が最後尾となるような回文の個数は対応する頂点の Suffix Link Tree の深さと一致する.

## 使い方

* `PalindromicTree(S)`: 文字列 $S$ に対応する Palindromic Tree を構築する.
* `add(x)`: 末尾に文字 `x` を追加する. 追加した文字を末尾とする最長回文接尾辞の頂点番号を返す.
* `add(S)`: 末尾に文字列 `S` を追加する.
* `build_frequency()`: 各頂点に対応する回文の出現回数を返す.
* `output(idx)`: 頂点 `idx` に対応する回文を返す.
* `size()`: 頂点数を返す.
* `operator[idx]`: 頂点 `idx` に対応するノードを返す.

## 計算量

* $O(\|S\|)$
