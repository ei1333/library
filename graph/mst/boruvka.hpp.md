---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-2-a-3.test.cpp
    title: test/verify/aoj-grl-2-a-3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/boruvka.md
    document_title: "Boruvka(\u6700\u5C0F\u5168\u57DF\u6728)"
    links: []
  bundledCode: "#line 2 \"structure/union-find/union-find.hpp\"\n\nstruct UnionFind\
    \ {\n  vector< int > data;\n\n  UnionFind() = default;\n\n  explicit UnionFind(size_t\
    \ sz) : data(sz, -1) {}\n\n  bool unite(int x, int y) {\n    x = find(x), y =\
    \ find(y);\n    if(x == y) return false;\n    if(data[x] > data[y]) swap(x, y);\n\
    \    data[x] += data[y];\n    data[y] = x;\n    return true;\n  }\n\n  int find(int\
    \ k) {\n    if(data[k] < 0) return (k);\n    return data[k] = find(data[k]);\n\
    \  }\n\n  int size(int k) {\n    return -data[find(k)];\n  }\n\n  bool same(int\
    \ x, int y) {\n    return find(x) == find(y);\n  }\n\n  vector< vector< int >\
    \ > groups() {\n    int n = (int) data.size();\n    vector< vector< int > > ret(n);\n\
    \    for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n    }\n\
    \    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int > &v) {\n\
    \      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n#line\
    \ 2 \"graph/mst/boruvka.hpp\"\n\n/**\n * @brief Boruvka(\u6700\u5C0F\u5168\u57DF\
    \u6728)\n * @docs docs/boruvka.md\n */\ntemplate< typename T >\nstruct Boruvka\
    \ {\nprivate:\n  size_t V;\n  UnionFind uf;\n  const T INF;\n\npublic:\n  explicit\
    \ Boruvka(size_t V, T INF = numeric_limits< T >::max()) : V(V), uf(V), INF(INF)\
    \ {}\n\n  inline int find(int k) {\n    return uf.find(k);\n  }\n\n  template<\
    \ typename F >\n  T build(const F &update) {\n    T ret = T();\n    while(uf.size(0)\
    \ < (int)V) {\n      vector< pair< T, int > > v(V, make_pair(INF, -1));\n    \
    \  update(v);\n      bool con = false;\n      for(int i = 0; i < (int)V; i++)\
    \ {\n        if(v[i].second >= 0 && uf.unite(i, v[i].second)) {\n          ret\
    \ += v[i].first;\n          con = true;\n        }\n      }\n      if(!con) return\
    \ INF;\n    }\n    return ret;\n  }\n};\n"
  code: "#include \"../../structure/union-find/union-find.hpp\"\n\n/**\n * @brief\
    \ Boruvka(\u6700\u5C0F\u5168\u57DF\u6728)\n * @docs docs/boruvka.md\n */\ntemplate<\
    \ typename T >\nstruct Boruvka {\nprivate:\n  size_t V;\n  UnionFind uf;\n  const\
    \ T INF;\n\npublic:\n  explicit Boruvka(size_t V, T INF = numeric_limits< T >::max())\
    \ : V(V), uf(V), INF(INF) {}\n\n  inline int find(int k) {\n    return uf.find(k);\n\
    \  }\n\n  template< typename F >\n  T build(const F &update) {\n    T ret = T();\n\
    \    while(uf.size(0) < (int)V) {\n      vector< pair< T, int > > v(V, make_pair(INF,\
    \ -1));\n      update(v);\n      bool con = false;\n      for(int i = 0; i < (int)V;\
    \ i++) {\n        if(v[i].second >= 0 && uf.unite(i, v[i].second)) {\n       \
    \   ret += v[i].first;\n          con = true;\n        }\n      }\n      if(!con)\
    \ return INF;\n    }\n    return ret;\n  }\n};\n"
  dependsOn:
  - structure/union-find/union-find.hpp
  isVerificationFile: false
  path: graph/mst/boruvka.hpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-grl-2-a-3.test.cpp
documentation_of: graph/mst/boruvka.hpp
layout: document
redirect_from:
- /library/graph/mst/boruvka.hpp
- /library/graph/mst/boruvka.hpp.html
title: "Boruvka(\u6700\u5C0F\u5168\u57DF\u6728)"
---
## 概要

最小全域木(全域木のうち, その辺群の重みの総和が最小になる木)を求める. それぞれの連結成分について, 他の連結成分を結ぶ重みが最小の辺を求めて縮約を繰り返すことにより最小全域木を求める. 繰り返し回数は $O(\log V)$ 回なので、普通の最小全域木であれば $O(E \log V)$ で求めることができる.

## 使い方
* `build(update)`: 最小全域木を求める. `update` の引数の型は `vector< pair< T, int > >&` (参照渡しなので注意). 引数で渡された要素のうち, それぞれの代表元について, 最小コストで向かえる連結成分の {コスト, その代表元(頂点番号でも良い)} を格納する処理をする(わからないと思うので詳細はverify コードを参照してください). 各頂点 $k$ の代表元を求める際には `find(k)` を呼び出すこと.
* `find(k)`: 現在の頂点 `k` が属する連結成分の代表元を返す.

## 計算量

* $O(E \log V)$
