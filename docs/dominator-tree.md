---
documentation_of: //graph/others/dominator-tree.hpp
---

## 概要

有向グラフが与えられたとき, 頂点 `root` を根とする Dominator tree を求める.

もとの有向グラフで, 頂点 `root` からある頂点 `i` へ向かうパスを考える. Dominator tree 上の頂点 `root` から `i` までのパス上にある頂点は, 頂点 `i` へ到達するために必ず通る必要のある頂点である(雰囲気的には関節点の有向グラフ版). 特に頂点 `i` の親は直接支配節 `idom(i)` と呼び, 必ず通る必要のある頂点のうち最も `w` に近い頂点を指す.

## 使い方

* `build(root)`: 頂点 `root` を根とする Dominator tree を返す. 各要素にはその要素の親の idx が格納される. ただし `root` には `root` が格納される. 頂点 `root` からその頂点に到達できない場合 `-1`.

## 計算量

$O(E \log V)$
