---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-zalgorithm.test.cpp
    title: test/verify/yosupo-zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/z-algorithm.md
    document_title: Z Algorithm
    links:
    - https://heno239.hatenablog.com/entry/2020/07/07/140651
  bundledCode: "#line 1 \"string/z-algorithm.hpp\"\n/**\n * @brief Z Algorithm\n *\
    \ @see https://heno239.hatenablog.com/entry/2020/07/07/140651\n * @docs docs/z-algorithm.md\n\
    \ */\ntemplate< typename T = char >\nstruct ZAlgorithm {\nprivate:\n  vector<\
    \ T > s;\n  vector< int > deleted;\n  vector< vector< int > > delete_hist;\n \
    \ vector< int > z;\n  queue< int > cur;\npublic:\n  ZAlgorithm() : delete_hist{{}}\
    \ {}\n\n  template< typename S >\n  ZAlgorithm(const S &s) : ZAlgorithm() {\n\
    \    for(auto &c: s) add(c);\n  }\n\n  void add(const T &c) {\n    s.emplace_back(c);\n\
    \    delete_hist.emplace_back();\n    deleted.emplace_back(0);\n    z.emplace_back(0);\n\
    \    z[0]++;\n\n    int len = (int) s.size();\n    if(len == 1) return;\n    if(s[0]\
    \ == c) cur.emplace(len - 1);\n    else deleted[len - 1] = 1;\n\n    auto set\
    \ = [&](int t, int len) {\n      deleted[t] = 1;\n      delete_hist[len].emplace_back(t);\n\
    \      z[t] = len - t - 1;\n    };\n\n    while(not cur.empty()) {\n      int\
    \ t = cur.front();\n      if(deleted[t]) {\n        cur.pop();\n      } else if(s[len\
    \ - t - 1] == s.back()) {\n        break;\n      } else {\n        set(t, len);\n\
    \        cur.pop();\n      }\n    }\n\n    if(not cur.empty()) {\n      int t\
    \ = cur.front();\n      for(auto &p: delete_hist[len - t]) {\n        set(p +\
    \ t, len);\n      }\n    }\n  }\n\n  int get(int k) const {\n    return deleted[k]\
    \ ? z[k] : (int) s.size() - k;\n  }\n\n  int operator[](int k) const {\n    return\
    \ get(k);\n  }\n\n  vector< int > get() {\n    vector< int > ret(s.size());\n\
    \    for(int i = 0; i < (int) s.size(); i++) {\n      ret[i] = get(i);\n    }\n\
    \    return ret;\n  }\n};\n"
  code: "/**\n * @brief Z Algorithm\n * @see https://heno239.hatenablog.com/entry/2020/07/07/140651\n\
    \ * @docs docs/z-algorithm.md\n */\ntemplate< typename T = char >\nstruct ZAlgorithm\
    \ {\nprivate:\n  vector< T > s;\n  vector< int > deleted;\n  vector< vector< int\
    \ > > delete_hist;\n  vector< int > z;\n  queue< int > cur;\npublic:\n  ZAlgorithm()\
    \ : delete_hist{{}} {}\n\n  template< typename S >\n  ZAlgorithm(const S &s) :\
    \ ZAlgorithm() {\n    for(auto &c: s) add(c);\n  }\n\n  void add(const T &c) {\n\
    \    s.emplace_back(c);\n    delete_hist.emplace_back();\n    deleted.emplace_back(0);\n\
    \    z.emplace_back(0);\n    z[0]++;\n\n    int len = (int) s.size();\n    if(len\
    \ == 1) return;\n    if(s[0] == c) cur.emplace(len - 1);\n    else deleted[len\
    \ - 1] = 1;\n\n    auto set = [&](int t, int len) {\n      deleted[t] = 1;\n \
    \     delete_hist[len].emplace_back(t);\n      z[t] = len - t - 1;\n    };\n\n\
    \    while(not cur.empty()) {\n      int t = cur.front();\n      if(deleted[t])\
    \ {\n        cur.pop();\n      } else if(s[len - t - 1] == s.back()) {\n     \
    \   break;\n      } else {\n        set(t, len);\n        cur.pop();\n      }\n\
    \    }\n\n    if(not cur.empty()) {\n      int t = cur.front();\n      for(auto\
    \ &p: delete_hist[len - t]) {\n        set(p + t, len);\n      }\n    }\n  }\n\
    \n  int get(int k) const {\n    return deleted[k] ? z[k] : (int) s.size() - k;\n\
    \  }\n\n  int operator[](int k) const {\n    return get(k);\n  }\n\n  vector<\
    \ int > get() {\n    vector< int > ret(s.size());\n    for(int i = 0; i < (int)\
    \ s.size(); i++) {\n      ret[i] = get(i);\n    }\n    return ret;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z-algorithm.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-zalgorithm.test.cpp
documentation_of: string/z-algorithm.hpp
layout: document
redirect_from:
- /library/string/z-algorithm.hpp
- /library/string/z-algorithm.hpp.html
title: Z Algorithm
---
## 概要

文字列 $S$ が与えられたとき, それぞれの $i$ について $S$ と $S[i, \|S\|]$ の最長共通接頭辞の長さを記録した配列を線形時間で構築する.

具体例を以下に示す. 例えば $i = 5$ のときの最長共通接頭辞は "aaa", つまり $3$ 文字である.

<pre>
aaabaaaab
921034210
</pre>

## 使い方

* `ZAlgorithm()`: 空文字列で初期化する.
* `ZAlgorithm(s)`: 文字列 `s` で初期化する.
* `add(c)`: 文字列の末尾に `c` を追加する.
* `get(k)`: 現時点の文字列の  $S$ と $S[i, \|S\|]$ の最長共通接頭辞の長さを返す
* `get()`: 現時点の文字列の $S$ とすべての $i$ についての$S[i, \|S\|]$ の最長共通接頭辞の長さを返す.

## 計算量

* 全体で $O(\|S\|)$
