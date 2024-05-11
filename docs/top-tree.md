---
documentation_of: //structure/dynamic-tree/top-tree.hpp
---

Top Tree とは動的木の一つで, 辺の追加や削除などの木構造の動的な変化がある場合でも効率的にクエリを処理できます。

Light edge に繋がる情報もマージできるため Link Cut Tree よりも強いクエリを処理できます。


# コンストラクタ

```
TopTree< TreeDPInfo >()
```

## TreeDPInfo について

`TreeDPInfo` は、次の構造体と関数を持つ構造体です。

```cpp
struct TreeDPInfo {
  struct Point {};
  struct Path {};
  struct Info {};
  static Path vertex(const Info& u) {}
  static Path add_vertex(const Point& d, const Info& u) {}
  static Point add_edge(const Path& d) {}
  static Point rake(const Point& l, const Point& r) {}
  static Path compress(const Path& p, const Path& c) {}
};
```

* `Point`: Light edge で繋がる頂点をまとめた結果 (Point cluster) を表す構造体
* `Path`: Heavy edge で繋がる頂点をまとめた結果 (Path cluster) を表す構造体
* `Info`: 頂点を表す構造体
* `vertex(u)`: 頂点 `u` のみからなる Path cluster を生成する関数
* `add_vertex(d, u)`: Point cluster `d` の根に頂点 `u` を代入して Path cluster にする関数
* `add_edge(d)`: Path cluster `d` に virtual な根を生やして Point cluster にする関数
* `rake(l, r)`: Point cluster `l` と `r` をマージする関数
* `compress(p, c)`: Path cluster `p` と `c` (`p` が根に近い側にある) をマージする関数

以下のコードを Splay Tree により高速化したデータ構造とみなすことができます。

```cpp
Point calc_light(int r) {
  vector< Point > points;
  // g[r][0] は heavy_edge なので skip
  for(int i = 1; i < (int) g[r].size(); i++) {
    Path res = calc_heavy(g[r][i]);
    points.push_back(add_edge(res));
  }
  for(int i = 1; i < (int) points.size(); i++) {
    points[0] = rake(points[0], points[i]);
  }
  return points[0];
}

Path calc_heavy(int r) {
  vector< Path > paths;
  while(not g[r].empty()) {
    if(g[r].size() == 1) {
      // light_edge を持っていない
      paths.push_back(vertex(info[r]));
    } else {
      // light_edge を持っている
      Point res = calc_light(r);
      paths.push_back(add_vertex(res, info[r]));
    }
    r = g[r][0]; // (r, g[r][0]) は Heavy edge
  }
  for(int i = 1; i < (int) paths.size(); i++) {
    paths[0] = compress(paths[0], paths[i]);
  }
  return paths[0];
}
```

`Point` に逆元と単位元が存在する場合は [Link Cut Tree For Subtree]({{ site.baseurl }}/structure/dynamic-tree/link-cut-tree-for-subtree.hpp) で十分です。

`Point` と `Path` に対し遅延伝搬が必要な場合は [Lazy Top Tree]({{ site.baseurl }}/structure/dynamic-tree/lazy-top-tree.hpp) が必要です。

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

# query_subtree

```
(1) Path query_subtree(NP u)
(2) Path query_subtree(NP r, NP u)
```

1. 頂点 `u` を根とする部分木を `compress` でマージした結果を返します。
2. 根を頂点 `r` に変更し、頂点 `u` を根とする部分木を `compress` でマージした結果を返します。

## 計算量

- amortized $O(\log n)$
