---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/incremental-bridge-connectivity.hpp
    title: Incremental Bridge Connectivity
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/three-edge-connected-components.hpp
    title: graph/connected-components/three-edge-connected-components.hpp
  - icon: ':warning:'
    path: graph/flow/burn-bury.hpp
    title: "Burn Bury(\u71C3\u3084\u3059\u57CB\u3081\u308B)"
  - icon: ':heavy_check_mark:'
    path: graph/mst/boruvka.hpp
    title: "Boruvka(\u6700\u5C0F\u5168\u57DF\u6728)"
  - icon: ':heavy_check_mark:'
    path: graph/mst/kruskal.hpp
    title: "Kruskal(\u6700\u5C0F\u5168\u57DF\u6728)"
  - icon: ':heavy_check_mark:'
    path: graph/others/bipartite-graph-edge-coloring.hpp
    title: "Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u8FBA\
      \u5F69\u8272)"
  - icon: ':heavy_check_mark:'
    path: graph/others/eulerian-trail.hpp
    title: "Eulerian Trail(\u30AA\u30A4\u30E9\u30FC\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: graph/tree/offline-lca.hpp
    title: "Offline LCA(\u30AA\u30D5\u30E9\u30A4\u30F3\u6700\u5C0F\u5171\u901A\u7956\
      \u5148)"
  - icon: ':heavy_check_mark:'
    path: other/mo-tree.hpp
    title: "Mo Tree(\u6728\u4E0A\u306EMo)"
  - icon: ':heavy_check_mark:'
    path: other/offline-rmq.hpp
    title: Offline RMQ
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2270.test.cpp
    title: test/verify/aoj-2270.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2821.test.cpp
    title: test/verify/aoj-2821.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-3139.test.cpp
    title: test/verify/aoj-3139.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dsl-1-a.test.cpp
    title: test/verify/aoj-dsl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-2-a-2.test.cpp
    title: test/verify/aoj-grl-2-a-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-2-a-3.test.cpp
    title: test/verify/aoj-grl-2-a-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bipartite-edge-coloring.test.cpp
    title: test/verify/yosupo-bipartite-edge-coloring.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca-4.test.cpp
    title: test/verify/yosupo-lca-4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-manhattanmst.test.cpp
    title: test/verify/yosupo-manhattanmst.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-6.test.cpp
    title: test/verify/yosupo-staticrmq-6.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-three-edge-connected-components.test.cpp
    title: test/verify/yosupo-three-edge-connected-components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-tree-decomposition-width-2.test.cpp
    title: test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-two-edge-connected-components-2.test.cpp
    title: test/verify/yosupo-two-edge-connected-components-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-583.test.cpp
    title: test/verify/yukicoder-583.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n"
  code: "#pragma once\n\nstruct UnionFind {\n  vector< int > data;\n\n  UnionFind()\
    \ = default;\n\n  explicit UnionFind(size_t sz) : data(sz, -1) {}\n\n  bool unite(int\
    \ x, int y) {\n    x = find(x), y = find(y);\n    if(x == y) return false;\n \
    \   if(data[x] > data[y]) swap(x, y);\n    data[x] += data[y];\n    data[y] =\
    \ x;\n    return true;\n  }\n\n  int find(int k) {\n    if(data[k] < 0) return\
    \ (k);\n    return data[k] = find(data[k]);\n  }\n\n  int size(int k) {\n    return\
    \ -data[find(k)];\n  }\n\n  bool same(int x, int y) {\n    return find(x) == find(y);\n\
    \  }\n\n  vector< vector< int > > groups() {\n    int n = (int) data.size();\n\
    \    vector< vector< int > > ret(n);\n    for(int i = 0; i < n; i++) {\n     \
    \ ret[find(i)].emplace_back(i);\n    }\n    ret.erase(remove_if(begin(ret), end(ret),\
    \ [&](const vector< int > &v) {\n      return v.empty();\n    }), end(ret));\n\
    \    return ret;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/union-find/union-find.hpp
  requiredBy:
  - other/offline-rmq.hpp
  - other/mo-tree.hpp
  - graph/connected-components/incremental-bridge-connectivity.hpp
  - graph/connected-components/three-edge-connected-components.hpp
  - graph/others/bipartite-graph-edge-coloring.hpp
  - graph/others/eulerian-trail.hpp
  - graph/tree/offline-lca.hpp
  - graph/flow/burn-bury.hpp
  - graph/mst/boruvka.hpp
  - graph/mst/kruskal.hpp
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - test/verify/yosupo-bipartite-edge-coloring.test.cpp
  - test/verify/aoj-2821.test.cpp
  - test/verify/yosupo-two-edge-connected-components-2.test.cpp
  - test/verify/aoj-3139.test.cpp
  - test/verify/yosupo-lca-4.test.cpp
  - test/verify/yosupo-staticrmq-6.test.cpp
  - test/verify/yukicoder-583.test.cpp
  - test/verify/aoj-2270.test.cpp
  - test/verify/yosupo-manhattanmst.test.cpp
  - test/verify/aoj-dsl-1-a.test.cpp
  - test/verify/aoj-grl-2-a-2.test.cpp
  - test/verify/yosupo-three-edge-connected-components.test.cpp
  - test/verify/aoj-grl-2-a-3.test.cpp
documentation_of: structure/union-find/union-find.hpp
layout: document
title: Union Find
---

集合を高速に扱うためのデータ構造です。集合を合併する操作(unite)と、ある要素がどの集合に属しているか(find)を問い合わせる操作を行うことができます。

# コンストラクタ

```
UnionFind(size_t n)
```

`n` 個の集合を作成します。集合 $i(0 \leq i \lt n)$ には要素 $i$ のみが属します。

## 制約

- $0 \leq n$

## 計算量

- $O(n)$

# unite

```
bool unite(int x, int y)
```

集合 `x` と `y` を併合します。併合済のとき `false`、未併合のとき `true` を返します。

## 制約

- $0 \leq x, y \lt n$

## 計算量

- amortized $O(\alpha(n))$ 

# find

```
int find(int k)
```

要素 `k` が属する集合の代表元を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- amortized $O(\alpha(n))$

# size

```
int size(int k)
```

要素 `k` が属する集合の要素数を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- amortized $O(\alpha(n))$

# same

```
bool same(int x, int y)
```

要素 `x` と `y` が同じ集合に属する場合 `true`、異なる集合に属する場合は `false` を返します。

## 制約

- $0 \leq x, y \lt n$

## 計算量

- amortized $O(\alpha(n))$

# groups

```
vector< vector< int > > groups()
```

それぞれの集合に含まれる要素を列挙し、それを返します。それぞれの集合内の要素は昇順に格納されますが、集合の順番は未定義です。


## 計算量

- $O(n)$
