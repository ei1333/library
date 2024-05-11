---
documentation_of: //structure/dynamic-tree/link-cut-tree.hpp
---

Link Cut Tree とは動的木の一つで, 辺の追加や削除などの木構造の動的な変化がある場合でも効率的にクエリを処理できます。

# コンストラクタ

```
LinkCutTree< TreeDPInfo >()
```

## TreeDPInfo について

`TreeDPInfo` は、次の構造体と関数を持つ構造体です。

```cpp
struct TreeDPInfo {
  struct Path {};
  struct Info {};
  static Path vertex(const Info& u) {}
  static Path compress(const Path& p, const Path& c) {}
};
```

* `Path`: Heavy edge で繋がる頂点をまとめた結果 (Path cluster) を表す構造体
* `Info`: 頂点を表す構造体
* `vertex(u)`: 頂点 `u` のみからなる Path cluster を生成する関数
* `compress(p, c)`: Path cluster `p` と `c` (`p` が根に近い側にある) をマージする関数

以下のコードを Splay Tree により高速化したデータ構造とみなすことができます。

```cpp
Path calc_heavy(int r) {
  vector< Path > paths;
  while(not g[r].empty()) {
    paths.push_back(vertex(info[r]));
    r = g[r][0]; // (r, g[r][0]) は Heavy edge
  }
  for(int i = 1; i < (int) paths.size(); i++) {
    paths[0] = compress(paths[0], paths[i]);
  }
  return paths[0];
}
```

# expose

```
NP expose(NP t)
```

頂点 `t` から根までのパスを Heavy edge で繋げます。`t` を Splay tree の根にして、`t` 自身を返します。

## 計算量

- amortized $O(\log n)$

# link

```
void link(NP child, NP parent)
```

頂点　`child` と `parent` との間に辺を追加します。

## 制約

- `child` と `parent` は異なる連結成分
- `child` は根（根ではない場合は先に `evert(child)` を呼び出すこと）

## 計算量

- amortized $O(\log n)$

# cut

```
void cut(NP child)
```

頂点 `child` と親との間にある辺を削除します。

## 制約

- `child` は根ではない

## 計算量

- amortized $O(\log n)$

# evert

```
void evert(t)
```

頂点 `t` を根に変更します。

## 計算量

- amortized $O(\log n)$

# alloc

```
NP alloc(const Info &v)
```

Info が `v` の新しい頂点を作成します。

## 計算量

- O(1)

# is_connected

```
bool is_connected(NP u, NP v)
```

頂点 `u` と `v` が同じ連結成分に属する場合は `true`、そうではない場合は `false` を返します。

関数内部で `expose(u)`、`expose(v)` の順で呼び出すため、Splay tree の木の根が変更されます。

## 計算量

- amortized $O(\log n)$

# build

```
vector<NP> build(vector<Info> &vs)
```

各 Info の値が `vs[i]` の新しい頂点たちを作成します。


## 計算量

- $O(n)

# lca

```
NP lca(NP u, NP v)
```

頂点 `u` と `v` の最小共通祖先を返します。ただし、頂点 `u` と `v` が異なる連結成分に属する場合は `nullptr` を返します。

関数内部で `expose(u)`、`expose(v)` の順で呼び出すため、Splay tree の木の根が変更されます。

## 計算量

- amortized $O(\log n)$

# set_key

```
void set_key(NP t, const Info &v)
```

頂点 `t` の Info を `v` に変更します。

関数内部で `expose(t)` を呼び出すため、Splay tree の木の根が `t` に変更されます。

## 計算量

- amortized $O(\log n)$

# query_path

```
(1) const Path &query_path(NP u)
(2) const Path &query_path(NP u, NP v)
```

1. 根から頂点 `u` までのパス上の頂点を Heavy edge で繋げ、それらを `compress` でマージした結果を返します。
2. 頂点 `u` から頂点 `v` までのパス上の頂点を Heavy edge で繋げ、それらを `compress` でマージした結果を返します。副作用として、頂点 `u` を根に変更します。

## 計算量

- amortized $O(\log n)$

# find_first

```
pair<NP, Path> find_first(NP u, const C &check)
```

根から頂点 `u` までのパス上の頂点を Heavy edge で繋げます。

パス上の頂点から頂点 `u` までの頂点を `compress` した結果を `path` とします。`check(path)` が `true` となるパス上の頂点のうち、頂点 `u` に最も近い頂点をその `path` とともに返します。`true` となる頂点が存在しない場合は `nullptr` を返します。

## 制約

- `check` は、第一引数に `Path`、返り値が `bool` の関数
- `check` の結果は単調（根からある頂点まで返り値が `true` で、それ以降の頂点に対しては `false`)

## 計算量

- amortized $O(\log n)$

## 使用例

頂点 `v` から `u` までのパス上に出現する頂点を並べたとき、`k` 番目に現れる頂点を見つける場合、以下のように書けます。

```cpp
struct TreeDPInfo {
  struct Path { int sz; };
  struct Info { int idx; };
  static Path vertex(const Info& u) { return {1}; }
  static Path compress(const Path& p, const Path& c) { return {p.sz + c.sz}; }
};

auto res = lct.find_first(vs[u], vs[v],
  [](const TreeDPInfo::Path& p) { return p.sz >= k; });
```
