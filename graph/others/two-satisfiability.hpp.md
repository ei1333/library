---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/connected-components/strongly-connected-components.hpp
    title: "Strongly Connected Components(\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\
      )"
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "Graph Template(\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-two-sat.test.cpp
    title: test/verify/yosupo-two-sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/two-satisfiability.md
    document_title: Two Satisfiability(2-SAT)
    links: []
  bundledCode: "#line 2 \"graph/others/two-satisfiability.hpp\"\n\n#line 2 \"graph/connected-components/strongly-connected-components.hpp\"\
    \n\n#line 2 \"graph/graph-template.hpp\"\n\n/**\n * @brief Graph Template(\u30B0\
    \u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8)\n */\ntemplate< typename T =\
    \ int >\nstruct Edge {\n  int from, to;\n  T cost;\n  int idx;\n\n  Edge() = default;\n\
    \n  Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost),\
    \ idx(idx) {}\n\n  operator int() const { return to; }\n};\n\ntemplate< typename\
    \ T = int >\nstruct Graph {\n  vector< vector< Edge< T > > > g;\n  int es;\n\n\
    \  Graph() = default;\n\n  explicit Graph(int n) : g(n), es(0) {}\n\n  size_t\
    \ size() const {\n    return g.size();\n  }\n\n  void add_directed_edge(int from,\
    \ int to, T cost = 1) {\n    g[from].emplace_back(from, to, cost, es++);\n  }\n\
    \n  void add_edge(int from, int to, T cost = 1) {\n    g[from].emplace_back(from,\
    \ to, cost, es);\n    g[to].emplace_back(to, from, cost, es++);\n  }\n\n  void\
    \ read(int M, int padding = -1, bool weighted = false, bool directed = false)\
    \ {\n    for(int i = 0; i < M; i++) {\n      int a, b;\n      cin >> a >> b;\n\
    \      a += padding;\n      b += padding;\n      T c = T(1);\n      if(weighted)\
    \ cin >> c;\n      if(directed) add_directed_edge(a, b, c);\n      else add_edge(a,\
    \ b, c);\n    }\n  }\n\n  inline vector< Edge< T > > &operator[](const int &k)\
    \ {\n    return g[k];\n  }\n\n  inline const vector< Edge< T > > &operator[](const\
    \ int &k) const {\n    return g[k];\n  }\n};\n\ntemplate< typename T = int >\n\
    using Edges = vector< Edge< T > >;\n#line 4 \"graph/connected-components/strongly-connected-components.hpp\"\
    \n\ntemplate< typename T = int >\nstruct StronglyConnectedComponents : Graph<\
    \ T > {\npublic:\n  using Graph< T >::Graph;\n  using Graph< T >::g;\n  vector<\
    \ int > comp;\n  Graph< T > dag;\n  vector< vector< int > > group;\n\n  void build()\
    \ {\n    rg = Graph< T >(g.size());\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      for(auto &e : g[i]) {\n        rg.add_directed_edge(e.to, e.from, e.cost);\n\
    \      }\n    }\n    comp.assign(g.size(), -1);\n    used.assign(g.size(), 0);\n\
    \    for(size_t i = 0; i < g.size(); i++) dfs(i);\n    reverse(begin(order), end(order));\n\
    \    int ptr = 0;\n    for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;\n\
    \    dag = Graph< T >(ptr);\n    for(size_t i = 0; i < g.size(); i++) {\n    \
    \  for(auto &e : g[i]) {\n        int x = comp[e.from], y = comp[e.to];\n    \
    \    if(x == y) continue;\n        dag.add_directed_edge(x, y, e.cost);\n    \
    \  }\n    }\n    group.resize(ptr);\n    for(size_t i = 0; i < g.size(); i++)\
    \ {\n      group[comp[i]].emplace_back(i);\n    }\n  }\n\n  int operator[](int\
    \ k) const {\n    return comp[k];\n  }\n\nprivate:\n  vector< int > order, used;\n\
    \  Graph< T > rg;\n\n  void dfs(int idx) {\n    if(exchange(used[idx], true))\
    \ return;\n    for(auto &to : g[idx]) dfs(to);\n    order.push_back(idx);\n  }\n\
    \n  void rdfs(int idx, int cnt) {\n    if(comp[idx] != -1) return;\n    comp[idx]\
    \ = cnt;\n    for(auto &to : rg.g[idx]) rdfs(to, cnt);\n  }\n};\n#line 4 \"graph/others/two-satisfiability.hpp\"\
    \n\n/**\n * @brief Two Satisfiability(2-SAT)\n * @docs docs/two-satisfiability.md\n\
    \ */\nstruct TwoSatisfiability : StronglyConnectedComponents< bool > {\npublic:\n\
    \  using StronglyConnectedComponents< bool >::g;\n  using StronglyConnectedComponents<\
    \ bool >::comp;\n  using StronglyConnectedComponents< bool >::add_edge;\n  size_t\
    \ sz;\n\n  explicit TwoSatisfiability(size_t v) : StronglyConnectedComponents<\
    \ bool >(v + v), sz(v) {}\n\n  void add_if(int u, int v) {\n    // u -> v <=>\
    \ !v -> !u\n    add_directed_edge(u, v);\n    add_directed_edge(rev(v), rev(u));\n\
    \  }\n\n  void add_or(int u, int v) {\n    // u or v <=> !u -> v\n    add_if(rev(u),\
    \ v);\n  }\n\n  void add_nand(int u, int v) {\n    // u nand v <=> u -> !v\n \
    \   add_if(u, rev(v));\n  }\n\n  void set_true(int u) {\n    // u <=> !u -> u\n\
    \    add_directed_edge(rev(u), u);\n  }\n\n  void set_false(int u) {\n    // !u\
    \ <=> u -> !u\n    add_directed_edge(u, rev(u));\n  }\n\n  inline int rev(int\
    \ x) {\n    if(x >= (int)sz) return x - sz;\n    return x + sz;\n  }\n\n  vector<\
    \ int > solve() {\n    StronglyConnectedComponents< bool >::build();\n    vector<\
    \ int > ret(sz);\n    for(size_t i = 0; i < sz; i++) {\n      if(comp[i] == comp[rev(i)])\
    \ return {};\n      ret[i] = comp[i] > comp[rev(i)];\n    }\n    return ret;\n\
    \  }\n};\n"
  code: "#pragma once\n\n#include \"../connected-components/strongly-connected-components.hpp\"\
    \n\n/**\n * @brief Two Satisfiability(2-SAT)\n * @docs docs/two-satisfiability.md\n\
    \ */\nstruct TwoSatisfiability : StronglyConnectedComponents< bool > {\npublic:\n\
    \  using StronglyConnectedComponents< bool >::g;\n  using StronglyConnectedComponents<\
    \ bool >::comp;\n  using StronglyConnectedComponents< bool >::add_edge;\n  size_t\
    \ sz;\n\n  explicit TwoSatisfiability(size_t v) : StronglyConnectedComponents<\
    \ bool >(v + v), sz(v) {}\n\n  void add_if(int u, int v) {\n    // u -> v <=>\
    \ !v -> !u\n    add_directed_edge(u, v);\n    add_directed_edge(rev(v), rev(u));\n\
    \  }\n\n  void add_or(int u, int v) {\n    // u or v <=> !u -> v\n    add_if(rev(u),\
    \ v);\n  }\n\n  void add_nand(int u, int v) {\n    // u nand v <=> u -> !v\n \
    \   add_if(u, rev(v));\n  }\n\n  void set_true(int u) {\n    // u <=> !u -> u\n\
    \    add_directed_edge(rev(u), u);\n  }\n\n  void set_false(int u) {\n    // !u\
    \ <=> u -> !u\n    add_directed_edge(u, rev(u));\n  }\n\n  inline int rev(int\
    \ x) {\n    if(x >= (int)sz) return x - sz;\n    return x + sz;\n  }\n\n  vector<\
    \ int > solve() {\n    StronglyConnectedComponents< bool >::build();\n    vector<\
    \ int > ret(sz);\n    for(size_t i = 0; i < sz; i++) {\n      if(comp[i] == comp[rev(i)])\
    \ return {};\n      ret[i] = comp[i] > comp[rev(i)];\n    }\n    return ret;\n\
    \  }\n};\n"
  dependsOn:
  - graph/connected-components/strongly-connected-components.hpp
  - graph/graph-template.hpp
  isVerificationFile: false
  path: graph/others/two-satisfiability.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-two-sat.test.cpp
documentation_of: graph/others/two-satisfiability.hpp
layout: document
redirect_from:
- /library/graph/others/two-satisfiability.hpp
- /library/graph/others/two-satisfiability.hpp.html
title: Two Satisfiability(2-SAT)
---
## 概要

SAT(充足可能性問題) とは, いくつかの論理変数及びその否定からなる論理式が与えられたときに, 各変数に `true` または `false` を割り当てることによって論理式を `true` にできるかを判定する問題である.

次のような形の論理式を乗法標準形とよぶ.

$(a \lor b \lor \dots) \land (c \lor d \lor \dots) \land \dots$

$a, b, \cdots$ をリテラルと呼び, 論理変数かその否定が入る. $(a \lor b \lor \dots)$ のように $\lor$ で繋がれた部分をクロージャと呼び, 全てのクロージャ内のリテラル数が高々 $2$ である乗法標準形の論理式に対する SAT を 2-SAT と呼ぶ.

クロージャ ($a \lor b)$ を $\Rightarrow$ (含意) を用いて $(\lnot a \Rightarrow b \land \lnot b \Rightarrow a)$ に変換する. すると乗法標準形は $(a \Rightarrow b) \land (c \Rightarrow d) \land \dots$ のようにすべて $\land$ で結ばれた論理式で表すことができる. ここで $x$ と $\lnot x$ に対応する頂点をつくって, $\Rightarrow$ を辺とした有向グラフを作成する。このグラフを強連結成分分解して $x$ と $\lnot x$ が同じ強連結成分に含まれるものが存在するとき充足不能, 逆に存在しないときは $x$ の強連結成分のトポロジカル順序が $\lnot x$ を含む強連結成分より後ろかどうかを真偽値として充足可能となる解を求めることが出来る.

## 等価なグラフへの変形

全ての条件を愚直に追加して 2-SAT を解く問題はつまらないので, 等価なグラフに変形して条件の個数を削減することによって効率的に解ける問題が度々出題されている.

以下の説明では $N$ 個のリテラルがあって, $i(0 \leq i \lt N)$ 番目のリテラルを $v_i$, その否定を $\lnot v_i$ で表すことにする.

### 高々1個がtrue

2-SAT では, あるリテラルの集合 $(k_1, k_2, \cdots, k_K)$ があって, そのうち高々 $1$ つのリテラルが `true` という条件を記述することが可能である. この条件は, 同時に異なる $2$ つのリテラルが `true` にならないことと等価である.

つまり, 条件 $(\lnot v_{k_i} \lor \lnot v_{k_j})$ を各 $(i, j) (i \neq j)$ に対して追加すればよい. このとき追加するべき条件の個数は $O(K^2)$ となるが, 工夫すると $O(K)$ にできる.

新しい $K-1$ 個のリテラル $(e_2, e_3, \cdots, e_K)$ を用意する. このうち $i$ 番目のリテラル $e_i$ は区間 $[1, k)$ のリテラルが全て `false` の場合に限って `false` に設定できることを目標とする.

このためにまず, 各 $i$ に対して条件 $(\lnot e_i \lor e_{i+1})$ を追加する. これは $e_i$ が `true` のとき $e_{i+1}$ を `true` とすることを表している. さらに, 条件 $(\lnot v_{k_i} \lor \lnot e_i)$ と $(\lnot v_{k_i} \lor e_{i+1})$ を追加すると良い. 前者の条件は $e_i$ が `true` のとき, 既に区間 $[1, i)$ のリテラルで `true` が存在するので $v_{k_i}$ を `false` にする必要があることを表している. 後者の条件は, $v_{k_i}$ を `true` に設定したときに $e_{i+1}$ を `true` にする必要があることを表している. (正確には対偶辺も考える必要があるが, 矛盾がないことを確認できる. 境界部分は適切に場合分けすること.)

この変形によって条件の個数が $O(K^2)$ から $O(K)$ に削減できていることは容易に確認できる.

これをグラフベースで考える方法もここで説明する(個人的にはこちらの考え方のほうがやりやすい気がしている). 条件 $(\lnot v_{k_i} \lor \lnot v_{k_j})$ はグラフに有向辺 $v_{k_i} \Rightarrow \lnot v_{k_j}$ と $v_{k_j} \Rightarrow \lnot v_{k_i}$ を張ることに対応している. 各 $(i, j) (i \neq j)$ について, 頂点 $v_{k_i}$ から $\lnot v_{k_j}$ に到達できる等価なグラフを構成できれば良い. これは $v_{k_i}$ ($i$ は任意) を始点として, $\lnot v_{k_j}$ ($j$ は任意) から $\lnot v_{k_i}$ を取り除いた頂点たちに到達できるようなグラフを意味している. 長さ $K$ のパスグラフを新たに $2$ つ生やして適当な頂点と結ぶことで, ある頂点から, 頂点 $[\lnot v_{k_1}, \cdots, \lnot v_{k_r}]$ や $[\lnot v_{k_l}, \cdots, \lnot v_{k_K}]$ に到達できるようなグラフを構成できる. $v_{k_i}$ からは, 頂点 $[\lnot v_{k_1}, \cdots, \lnot v_{k_{i-1}}]$ と $[\lnot v_{k_{i+1}}, \cdots, \lnot v_{k_K}]$ に到達できるように辺を張ればよい. このようなグラフを構成しても辺の個数が $O(K)$ に削減できていることが確認できる.

### 区間

$l \leq j \lt r$ を満たす全ての $j$ に対して, 条件 $(v_i \lor v_j)$ を追加したい場合がある. このとき追加するべき条件の個数は $r - l$ 個となるが, 工夫すると $1$ クエリあたり $O(\log N)$ に改善できる.

条件 $(v_i \lor v_j)$ はグラフに有向辺 $\lnot v_i \Rightarrow v_j$ と $\lnot v_j \Rightarrow v_i$ を張ることに対応している. 各 $j(l \leq j \lt r)$ について, 頂点 $\lnot v_i$ から $v_j$, $\lnot v_j$ から $v_i$ に到達できるグラフを構成できればよい. 前者の条件を考える. 葉の数が $N$ の完全平衡二分木を生やし, $j$ 番目の葉から頂点 $v_j$ に結ぶ. また, 葉以外のノードからは, $2$ つの子と辺で結ぶ. セグメント木をイメージすると, 全ての区間は $O(\log N)$ 個のノードで表されて, $\lnot v_i$ からそれらのノードに繋ぐことで等価なグラフを構成できる. 後者の条件も同様に, 平衡二分木を生やせばよい. ただし, 辺の向きは全て反転させる.

特に $l=0$ や $r=N$ を満たすことが分かっている場合は, 先頭から末尾, あるいは末尾から先頭に向かう長さ $N$ のパスグラフを生やして, $1$ クエリあたり $O(1)$ に改善する方法も考えられる. 本質的には先述した高々 $1$ 個が `true` と同じ方法である.

## 使い方

* `TwoSatisfiability(N)`: `N` 個のリテラルで初期化する.
* `add_if(u, v)`: 条件 `u` ならば `v` を追加する.
* `add_or(u, v)`: 条件 `u` または `v` が `true` を追加する.
* `add_nand(u, v)`: 条件 `u` または `v` が `false` を追加する.
* `set_true(u)`: 条件 `u` が `true` を追加する.
* `set_false(u)`: 条件 `u` が `false` を追加する.
* `rev(u)`: 変数 `u` の否定を返す.
* `solve()`: 充足可能か判定し, 可能なら各リテラルの割り当ての例を格納した配列, 不能なら空配列を返す.

## 計算量

$O(V+E)$
