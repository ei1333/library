---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/three-edge-connected-components.hpp
    title: graph/connected-components/three-edge-connected-components.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-three-edge-connected-components.test.cpp
    title: test/verify/yosupo-three-edge-connected-components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-two-edge-connected-components-2.test.cpp
    title: test/verify/yosupo-two-edge-connected-components-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/connected-components/incremental-bridge-connectivity.hpp\"\
    \n\n#line 2 \"structure/union-find/union-find.hpp\"\n\nstruct UnionFind {\n  vector<\
    \ int > data;\n\n  UnionFind() = default;\n\n  explicit UnionFind(size_t sz) :\
    \ data(sz, -1) {}\n\n  bool unite(int x, int y) {\n    x = find(x), y = find(y);\n\
    \    if(x == y) return false;\n    if(data[x] > data[y]) swap(x, y);\n    data[x]\
    \ += data[y];\n    data[y] = x;\n    return true;\n  }\n\n  int find(int k) {\n\
    \    if(data[k] < 0) return (k);\n    return data[k] = find(data[k]);\n  }\n\n\
    \  int size(int k) {\n    return -data[find(k)];\n  }\n\n  bool same(int x, int\
    \ y) {\n    return find(x) == find(y);\n  }\n\n  vector< vector< int > > groups()\
    \ {\n    int n = (int) data.size();\n    vector< vector< int > > ret(n);\n   \
    \ for(int i = 0; i < n; i++) {\n      ret[find(i)].emplace_back(i);\n    }\n \
    \   ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int > &v) {\n\
    \      return v.empty();\n    }), end(ret));\n    return ret;\n  }\n};\n#line\
    \ 4 \"graph/connected-components/incremental-bridge-connectivity.hpp\"\n\nstruct\
    \ IncrementalBridgeConnectivity {\nprivate:\n  UnionFind cc, bcc;\n  vector< int\
    \ > bbf;\n  size_t bridge;\n\n  int size() {\n    return bbf.size();\n  }\n\n\
    \  int par(int x) {\n    return bbf[x] == size() ? size() : bcc.find(bbf[x]);\n\
    \  }\n\n  int lca(int x, int y) {\n    unordered_set< int > used;\n    for(;;)\
    \ {\n      if(x != size()) {\n        if(!used.insert(x).second) return x;\n \
    \       x = par(x);\n      }\n      swap(x, y);\n    }\n  }\n\n  void compress(int\
    \ x, int y) {\n    while(bcc.find(x) != bcc.find(y)) {\n      int nxt = par(x);\n\
    \      bbf[x] = bbf[y];\n      bcc.unite(x, y);\n      x = nxt;\n      --bridge;\n\
    \    }\n  }\n\n  void link(int x, int y) {\n    int v = x, pre = y;\n    while(v\
    \ != size()) {\n      int nxt = par(v);\n      bbf[v] = pre;\n      pre = v;\n\
    \      v = nxt;\n    }\n  }\n\npublic:\n  IncrementalBridgeConnectivity() = default;\n\
    \n  explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), bbf(sz,\
    \ sz), bridge(0) {}\n\n  int find(int k) {\n    return bcc.find(k);\n  }\n\n \
    \ size_t bridge_size() const {\n    return bridge;\n  }\n\n  void add_edge(int\
    \ x, int y) {\n    x = bcc.find(x);\n    y = bcc.find(y);\n    if(cc.find(x) ==\
    \ cc.find(y)) {\n      int w = lca(x, y);\n      compress(x, w);\n      compress(y,\
    \ w);\n    } else {\n      if(cc.size(x) > cc.size(y)) swap(x, y);\n      link(x,\
    \ y);\n      cc.unite(x, y);\n      ++bridge;\n    }\n  }\n};\n"
  code: "#pragma once\n\n#include \"../../structure/union-find/union-find.hpp\"\n\n\
    struct IncrementalBridgeConnectivity {\nprivate:\n  UnionFind cc, bcc;\n  vector<\
    \ int > bbf;\n  size_t bridge;\n\n  int size() {\n    return bbf.size();\n  }\n\
    \n  int par(int x) {\n    return bbf[x] == size() ? size() : bcc.find(bbf[x]);\n\
    \  }\n\n  int lca(int x, int y) {\n    unordered_set< int > used;\n    for(;;)\
    \ {\n      if(x != size()) {\n        if(!used.insert(x).second) return x;\n \
    \       x = par(x);\n      }\n      swap(x, y);\n    }\n  }\n\n  void compress(int\
    \ x, int y) {\n    while(bcc.find(x) != bcc.find(y)) {\n      int nxt = par(x);\n\
    \      bbf[x] = bbf[y];\n      bcc.unite(x, y);\n      x = nxt;\n      --bridge;\n\
    \    }\n  }\n\n  void link(int x, int y) {\n    int v = x, pre = y;\n    while(v\
    \ != size()) {\n      int nxt = par(v);\n      bbf[v] = pre;\n      pre = v;\n\
    \      v = nxt;\n    }\n  }\n\npublic:\n  IncrementalBridgeConnectivity() = default;\n\
    \n  explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), bbf(sz,\
    \ sz), bridge(0) {}\n\n  int find(int k) {\n    return bcc.find(k);\n  }\n\n \
    \ size_t bridge_size() const {\n    return bridge;\n  }\n\n  void add_edge(int\
    \ x, int y) {\n    x = bcc.find(x);\n    y = bcc.find(y);\n    if(cc.find(x) ==\
    \ cc.find(y)) {\n      int w = lca(x, y);\n      compress(x, w);\n      compress(y,\
    \ w);\n    } else {\n      if(cc.size(x) > cc.size(y)) swap(x, y);\n      link(x,\
    \ y);\n      cc.unite(x, y);\n      ++bridge;\n    }\n  }\n};\n"
  dependsOn:
  - structure/union-find/union-find.hpp
  isVerificationFile: false
  path: graph/connected-components/incremental-bridge-connectivity.hpp
  requiredBy:
  - graph/connected-components/three-edge-connected-components.hpp
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-two-edge-connected-components-2.test.cpp
  - test/verify/yosupo-three-edge-connected-components.test.cpp
documentation_of: graph/connected-components/incremental-bridge-connectivity.hpp
layout: document
title: Incremental Bridge Connectivity
---

## 概要

辺の追加クエリのみ存在するとき, 二重辺連結成分を効率的に管理するデータ構造.

## 使い方

* `IncrementalBridgeConnectivity(sz)`: `sz` 頂点で初期化する.
* `find(k)`: 頂点 `k` が属する二重辺連結成分(の代表元)を求める.
* `bridge_size()`: 現在の橋の個数を返す.
* `add_edge(x, y)`: 頂点 `x` と `y` との間に無向辺を追加する.

## 計算量

ならし $O(n \log n)$

## 参考
[Incremental Bridge-Connectivity - data-structures](https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity)
