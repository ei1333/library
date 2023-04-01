---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2405.test.cpp
    title: test/verify/aoj-2405.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-tree-decomposition-width-2.test.cpp
    title: test/verify/yosupo-tree-decomposition-width-2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/tree-decomposition-width-2.md
    document_title: "Tree Decomposition Width 2(\u6728\u5E452\u306E\u6728\u5206\u89E3\
      )"
    links:
    - https://ei1333.hateblo.jp/entry/2020/02/12/150319
  bundledCode: "#line 2 \"graph/others/tree-decomposition-width-2.hpp\"\n\n/**\n *\
    \ @brief Tree Decomposition Width 2(\u6728\u5E452\u306E\u6728\u5206\u89E3)\n *\
    \ @see https://ei1333.hateblo.jp/entry/2020/02/12/150319\n * @docs docs/tree-decomposition-width-2.md\n\
    \ */\nstruct DecompNode {\n  vector< int > bag, child;\n\n  DecompNode() = default;\n\
    };\n\nstruct TreeDecompositionWidth2 {\n\n  vector< vector< int > > g;\n\n  explicit\
    \ TreeDecompositionWidth2(int V) : g(V) {}\n\n  void add_edge(int a, int b) {\n\
    \    g[a].emplace_back(b);\n    g[b].emplace_back(a);\n  }\n\n  vector< DecompNode\
    \ > build() {\n    const int N = (int) g.size();\n\n    vector< int > used(N,\
    \ -1), deg(N);\n    queue< int > que;\n    for(int i = 0; i < N; i++) {\n    \
    \  deg[i] = (int) g[i].size();\n      if(deg[i] <= 2) que.emplace(i);\n    }\n\
    \n    vector< set< int > > exists(N);\n    for(int i = 0; i < N; i++) {\n    \
    \  for(auto &j : g[i]) {\n        if(i < j) exists[i].emplace(j);\n      }\n \
    \   }\n\n    vector< DecompNode > ret;\n    ret.emplace_back();\n    while(!que.empty())\
    \ {\n      int idx = que.front();\n      que.pop();\n      if(deg[idx] > 2 ||\
    \ used[idx] != -1) continue;\n\n      DecompNode r;\n      r.bag.emplace_back(idx);\n\
    \      int u = -1, v = -1;\n      for(auto &to : g[idx]) {\n        if(used[to]\
    \ == -1) {\n          (u == -1 ? u : v) = to;\n          r.bag.emplace_back(to);\n\
    \        } else if(used[to] >= 0) {\n          r.child.emplace_back(used[to]);\n\
    \          used[to] = -2;\n        }\n      }\n\n      if(u == -1) {\n\n     \
    \ } else if(v == -1) {\n        --deg[u];\n      } else {\n        if(u > v) swap(u,\
    \ v);\n        if(!exists[u].count(v)) {\n          g[u].emplace_back(v);\n  \
    \        g[v].emplace_back(u);\n          exists[u].emplace(v);\n        } else\
    \ {\n          --deg[u];\n          --deg[v];\n        }\n      }\n\n      for(auto\
    \ &to : g[idx]) {\n        if(deg[to] <= 2) que.emplace(to);\n      }\n\n    \
    \  used[idx] = (int) ret.size();\n      deg[idx] = 0;\n      ret.emplace_back(r);\n\
    \    }\n    for(int i = 0; i < N; i++) {\n      if(deg[i] > 0) return {};\n  \
    \  }\n    ret.front() = ret.back();\n    ret.pop_back();\n    return ret;\n  }\n\
    };\n\n\nvoid to_nice(vector< DecompNode > &g, int root = 0) {\n\n  for(auto &p\
    \ : g) {\n    sort(p.bag.begin(), p.bag.end());\n  }\n\n  stack< int > st;\n \
    \ st.emplace(root);\n\n  while(!st.empty()) {\n    int idx = st.top();\n    st.pop();\n\
    \n    // join\n    while(g[idx].child.size() > 2) {\n      DecompNode r;\n   \
    \   r.child.resize(2);\n      r.child[0] = g[idx].child.back();\n      g[idx].child.pop_back();\n\
    \      r.child[1] = g[idx].child.back();\n      g[idx].child.pop_back();\n   \
    \   r.bag = g[idx].bag;\n      g[idx].child.emplace_back((int) g.size());\n  \
    \    g.emplace_back(r);\n    }\n\n    if(g[idx].child.size() == 2) {\n      for(auto\
    \ &ch : g[idx].child) {\n        if(g[ch].bag != g[idx].bag) {\n          DecompNode\
    \ r;\n          r.child = {ch};\n          r.bag = g[idx].bag;\n          ch =\
    \ (int) g.size();\n          g.emplace_back(r);\n        }\n      }\n    }\n\n\
    \    // introduce / forget\n    if(g[idx].child.size() == 1) {\n      int &ch\
    \ = g[idx].child[0];\n\n      vector< int > latte, malta;\n      set_difference(g[idx].bag.begin(),\
    \ g[idx].bag.end(),\n                     g[ch].bag.begin(), g[ch].bag.end(),\n\
    \                     back_inserter(latte));\n      set_difference(g[ch].bag.begin(),\
    \ g[ch].bag.end(),\n                     g[idx].bag.begin(), g[idx].bag.end(),\n\
    \                     back_inserter(malta));\n      if(latte.size() + malta.size()\
    \ > 1) {\n        DecompNode r;\n        r.child = {ch};\n        r.bag = g[idx].bag;\n\
    \        if(!latte.empty()) {\n          r.bag.erase(find(r.bag.begin(), r.bag.end(),\
    \ latte.back()));\n        } else {\n          r.bag.emplace_back(malta.back());\n\
    \        }\n        ch = (int) g.size();\n        g.emplace_back(r);\n      }\n\
    \    }\n\n    // leaf\n    if(g[idx].child.empty()) {\n      if(g[idx].bag.size()\
    \ > 1) {\n        DecompNode r;\n        r.bag = g[idx].bag;\n        r.bag.pop_back();\n\
    \        g[idx].child.emplace_back((int) g.size());\n        g.emplace_back(r);\n\
    \      }\n    }\n\n    for(auto &ch : g[idx].child) {\n      st.emplace(ch);\n\
    \    }\n  }\n}\n"
  code: "#pragma once\n\n/**\n * @brief Tree Decomposition Width 2(\u6728\u5E452\u306E\
    \u6728\u5206\u89E3)\n * @see https://ei1333.hateblo.jp/entry/2020/02/12/150319\n\
    \ * @docs docs/tree-decomposition-width-2.md\n */\nstruct DecompNode {\n  vector<\
    \ int > bag, child;\n\n  DecompNode() = default;\n};\n\nstruct TreeDecompositionWidth2\
    \ {\n\n  vector< vector< int > > g;\n\n  explicit TreeDecompositionWidth2(int\
    \ V) : g(V) {}\n\n  void add_edge(int a, int b) {\n    g[a].emplace_back(b);\n\
    \    g[b].emplace_back(a);\n  }\n\n  vector< DecompNode > build() {\n    const\
    \ int N = (int) g.size();\n\n    vector< int > used(N, -1), deg(N);\n    queue<\
    \ int > que;\n    for(int i = 0; i < N; i++) {\n      deg[i] = (int) g[i].size();\n\
    \      if(deg[i] <= 2) que.emplace(i);\n    }\n\n    vector< set< int > > exists(N);\n\
    \    for(int i = 0; i < N; i++) {\n      for(auto &j : g[i]) {\n        if(i <\
    \ j) exists[i].emplace(j);\n      }\n    }\n\n    vector< DecompNode > ret;\n\
    \    ret.emplace_back();\n    while(!que.empty()) {\n      int idx = que.front();\n\
    \      que.pop();\n      if(deg[idx] > 2 || used[idx] != -1) continue;\n\n   \
    \   DecompNode r;\n      r.bag.emplace_back(idx);\n      int u = -1, v = -1;\n\
    \      for(auto &to : g[idx]) {\n        if(used[to] == -1) {\n          (u ==\
    \ -1 ? u : v) = to;\n          r.bag.emplace_back(to);\n        } else if(used[to]\
    \ >= 0) {\n          r.child.emplace_back(used[to]);\n          used[to] = -2;\n\
    \        }\n      }\n\n      if(u == -1) {\n\n      } else if(v == -1) {\n   \
    \     --deg[u];\n      } else {\n        if(u > v) swap(u, v);\n        if(!exists[u].count(v))\
    \ {\n          g[u].emplace_back(v);\n          g[v].emplace_back(u);\n      \
    \    exists[u].emplace(v);\n        } else {\n          --deg[u];\n          --deg[v];\n\
    \        }\n      }\n\n      for(auto &to : g[idx]) {\n        if(deg[to] <= 2)\
    \ que.emplace(to);\n      }\n\n      used[idx] = (int) ret.size();\n      deg[idx]\
    \ = 0;\n      ret.emplace_back(r);\n    }\n    for(int i = 0; i < N; i++) {\n\
    \      if(deg[i] > 0) return {};\n    }\n    ret.front() = ret.back();\n    ret.pop_back();\n\
    \    return ret;\n  }\n};\n\n\nvoid to_nice(vector< DecompNode > &g, int root\
    \ = 0) {\n\n  for(auto &p : g) {\n    sort(p.bag.begin(), p.bag.end());\n  }\n\
    \n  stack< int > st;\n  st.emplace(root);\n\n  while(!st.empty()) {\n    int idx\
    \ = st.top();\n    st.pop();\n\n    // join\n    while(g[idx].child.size() > 2)\
    \ {\n      DecompNode r;\n      r.child.resize(2);\n      r.child[0] = g[idx].child.back();\n\
    \      g[idx].child.pop_back();\n      r.child[1] = g[idx].child.back();\n   \
    \   g[idx].child.pop_back();\n      r.bag = g[idx].bag;\n      g[idx].child.emplace_back((int)\
    \ g.size());\n      g.emplace_back(r);\n    }\n\n    if(g[idx].child.size() ==\
    \ 2) {\n      for(auto &ch : g[idx].child) {\n        if(g[ch].bag != g[idx].bag)\
    \ {\n          DecompNode r;\n          r.child = {ch};\n          r.bag = g[idx].bag;\n\
    \          ch = (int) g.size();\n          g.emplace_back(r);\n        }\n   \
    \   }\n    }\n\n    // introduce / forget\n    if(g[idx].child.size() == 1) {\n\
    \      int &ch = g[idx].child[0];\n\n      vector< int > latte, malta;\n     \
    \ set_difference(g[idx].bag.begin(), g[idx].bag.end(),\n                     g[ch].bag.begin(),\
    \ g[ch].bag.end(),\n                     back_inserter(latte));\n      set_difference(g[ch].bag.begin(),\
    \ g[ch].bag.end(),\n                     g[idx].bag.begin(), g[idx].bag.end(),\n\
    \                     back_inserter(malta));\n      if(latte.size() + malta.size()\
    \ > 1) {\n        DecompNode r;\n        r.child = {ch};\n        r.bag = g[idx].bag;\n\
    \        if(!latte.empty()) {\n          r.bag.erase(find(r.bag.begin(), r.bag.end(),\
    \ latte.back()));\n        } else {\n          r.bag.emplace_back(malta.back());\n\
    \        }\n        ch = (int) g.size();\n        g.emplace_back(r);\n      }\n\
    \    }\n\n    // leaf\n    if(g[idx].child.empty()) {\n      if(g[idx].bag.size()\
    \ > 1) {\n        DecompNode r;\n        r.bag = g[idx].bag;\n        r.bag.pop_back();\n\
    \        g[idx].child.emplace_back((int) g.size());\n        g.emplace_back(r);\n\
    \      }\n    }\n\n    for(auto &ch : g[idx].child) {\n      st.emplace(ch);\n\
    \    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/others/tree-decomposition-width-2.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-tree-decomposition-width-2.test.cpp
  - test/verify/aoj-2405.test.cpp
documentation_of: graph/others/tree-decomposition-width-2.hpp
layout: document
redirect_from:
- /library/graph/others/tree-decomposition-width-2.hpp
- /library/graph/others/tree-decomposition-width-2.hpp.html
title: "Tree Decomposition Width 2(\u6728\u5E452\u306E\u6728\u5206\u89E3)"
---
## 概要

無向グラフが与えられたとき, 木幅が $2$ 以下か判定し, $2$ 以下の場合は木幅 $2$ 以下の木分解を構成する.

非連結だとバグります！(適当にダミー辺を加えて連結にしてね)

## 使い方

* `add_edge(a, b)`: 頂点 `a`, `b` 間に辺を張る.
* `build()`: 木幅が $2$ 以下か判定し, $2$ 以下の場合はノード `0` を根とする木幅 $2$ 以下の木分解を返す. `bag` はそのノードに対応する頂点, `child` にはそのノードの子が格納される. $2$ より大きい場合は空列を返す.
* `to_nice(g, root)`: 木分解 `g` を Nice Tree-decomposition に変形する. これによりすべてのノードは, leaf(`bag` のサイズが $1$), introduce($1$ つの子を持ち, 子の `bag` に $1$ つの頂点を加えたもの), forget($1$ つの子を持ち,  子の`bag` から $1$ つの頂点を取り除いたもの), join($2$ つの子を持ち, 自身と $2$ つの子の `bag` はすべて同じ) のいずれかに属するようになる.

## 計算量

$O(E + V)$
