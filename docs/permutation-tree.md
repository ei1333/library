---
title: Permutation Tree (順列木)
documentation_of: //structure/others/permutation-tree.hpp
---

順列 $A$ に対応する順列木(Permutation Tree, 析合树) を構築します。

$ \max\limits_{l \leq i \leq r} A_i - \min\limits_{l \leq i \leq r} A_i = r-l$ が成立するような $[l, r]$ を良い連続部分列と定義する. この良い連続部分列を効率的に求めます。

順列木のそれぞれのノードはいくつかのタイプに分類されます。定義を以下に示します。

* `LEAF`: 葉ノード。数列のある 1 要素に対応する。
* `JOIN`: そのノードが持つ子の列から、連続する 2 つ以上の子を選んだときに全てが良い連続部分列となる。
* `CUT`: そのノードが持つ子の列から、どの連続する 2 つ以上の子を選んでも良い連続部分列にはならない。

# コンストラクタ

```cpp
PermutationTree()
```

順列木を初期化します。

# build

```cpp
static NP build(vector<int> &A)
```

順列 `A` に対応する順列木を返します。`Node` には、ノードのタイプ `type`, そのノードに対応する順列の index の区間 $[l, r)$, ノードに含まれる要素の値 `[min_v, max_v)`, 子 `ch` が格納されます。

## 制約

- `A` は $[0, n)$ からなる順列

## 計算量

- $O(n \log n)$
