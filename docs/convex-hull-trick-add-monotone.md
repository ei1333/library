---
documentation_of: //structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
---

## 概要

直線 $ax+b$ の追加クエリ(ただし $a$ は単調増加または単調減少) と, ある点 $x$ での最小値クエリを効率的に処理する.

追加クエリは $a$ の単調性を考えながら, 上手く stack で管理することで効率的に処理できる(凸包を求めるアルゴリズムと似ている).

最小値クエリは $x$ が単調増加または単調減少のとき stack を端からみることで全体で $O(q + n)$, 単調性がない場合も二分探索することでクエリあたり $(\log n)$ で求められる.

## 使い方

`is_Min` を `true` にすると最小値, `false` にすると最大値を求める.

* `add(a, b)`: 直線 $ax + b$ を追加する. ただし $a$ は広義単調増加または広義単調減少.
* `query(x)`: $ax + b$ の最小値を求める.
* `query_monotone_inc(x)`: $ax + b$ の最小値を求める. ただし $x$ は広義単調増加.
* `query_monotone_dec(x)`: $ax + b$ の最小値を求める. ただし $x$ は広義単調減少.

## 計算量

* `add()`: 全体で $O(n)$
* `query()`: クエリあたり $O(\log n)$
* `query_monotone_inc(x)`, `query_monotone_dec(x)`: 全体で $O(n + q)$

$n$ は追加する直線の個数, $q$ はクエリ数. 
