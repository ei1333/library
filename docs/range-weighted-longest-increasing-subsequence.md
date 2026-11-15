---
title: Range Weighted Longest Increasing Subsequence (区間重み付き最長増加部分列)
documentation_of: //dp/range-weighted-longest-increasing-subsequence.hpp
---

静的な数列に対して、指定した区間内の狭義単調増加部分列の重みの総和の最大値を求める。最大値だけでなく、それを達成する部分列の添字も復元できる。

各要素の重みは正でなければならない。すべての重みを $1$ にすると、区間最長増加部分列の長さと、その部分列を求められる。同じ値を持つ要素が複数あってもよいが、同じ部分列には同じ値を $2$ 回以上含められない。

## テンプレート引数

- `T`: 数列の要素の型。`operator<` による大小比較ができ、その比較が狭義弱順序を定めること。
- `Weight`: 重みとその総和の型。デフォルトは `long long`。`Weight{}` が零であり、正の重み、`operator+` による加算、`operator<` による大小比較を正確に扱えること。重みを省略するコンストラクタでは `Weight{1}` が $1$ を表すこと。

## 記法

- $n$: 数列の長さ
- $k$: 復元する部分列の長さ
- 添字は $0$-indexed とし、区間は半開区間 $[l, r)$ で表す。
- 計算量は、値の比較と重みの加算・比較を $O(1)$ として数える。

# コンストラクタ

```cpp
RangeWeightedLongestIncreasingSubsequence(const std::vector<T>& a,
                                         const std::vector<Weight>& w)
explicit RangeWeightedLongestIncreasingSubsequence(const std::vector<T>& a)
```

数列 `a` と重み `w` を前処理する。`w` を省略した場合は、すべての重みを $1$ とする。構築後に数列や重みを更新する操作は持たない。クエリ区間を構築時に指定する必要はない。

## 引数

- `a`: 数列
- `w`: 各要素の重み

## 制約

- `a.size() == w.size()`
- すべての $i$ について $0 < w_i$
- 空の数列を構築できる。
- 要素の添字と内部ノードの番号が `int` に収まること。
- 前処理中の加算結果を含め、扱う重みの総和が `Weight` に収まること。

## 計算量

- 前処理時間: $O(n \log^2(n+1))$
- 使用空間: $O(n \log^2(n+1))$
- 空の数列の場合はいずれも $O(1)$。

## 注意事項

重みの加算と比較が正確であることを前提とする。整数を使う場合は、オーバーフローしない型を選ぶこと。浮動小数点数の丸め誤差によって比較結果が変わると、後述の単一交差性が成立しなくなり、正しい結果を保証できない。

# prod

```cpp
Weight prod(int l, int r) const
```

区間 $[l, r)$ に含まれる狭義単調増加部分列について、重みの総和の最大値を返す。空区間では零を返す。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- 時間: $O(\log(n+1))$
- 空区間の場合は $O(1)$。

# restore

```cpp
std::vector<int> restore(int l, int r) const
```

区間 $[l, r)$ の重みの総和が最大になる狭義単調増加部分列を $1$ つ復元する。返り値は元の数列における添字の列であり、区間内の相対的な添字ではない。

返された添字を $i_0, \ldots, i_{k-1}$ とすると、添字と対応する値はともに狭義単調増加であり、重みの総和は `prod(l, r)` に等しい。最適な部分列が複数ある場合、どれを返すかは規定しない。空区間では空の配列を返す。

`prod` と `restore` は前処理済みのデータを変更しない。クエリは任意の順番で繰り返し実行できる。

## 制約

- $0 \leq l \leq r \leq n$

## 計算量

- 時間: $O(k+\log(n+1))$
- 返り値と作業領域を含む追加空間: $O(k+\log(n+1))$
- 空区間の場合はいずれも $O(1)$。

# 使用例

```cpp
#include <cassert>
#include <vector>

#include "dp/range-weighted-longest-increasing-subsequence.hpp"

int main() {
  std::vector<int> a = {3, 1, 2, 2, 4};
  std::vector<long long> w = {4, 2, 3, 8, 1};
  RangeWeightedLongestIncreasingSubsequence<int> lis(a, w);

  assert(lis.prod(0, 5) == 11);
  assert((lis.restore(0, 5) == std::vector<int>{1, 3, 4}));
  assert(lis.prod(2, 4) == 8);
  assert(lis.prod(3, 3) == 0);
  assert(lis.restore(3, 3).empty());

  RangeWeightedLongestIncreasingSubsequence<int> unweighted(a);
  assert(unweighted.prod(0, 5) == 3);
}
```

# アルゴリズム

まず、値の昇順、同じ値の中では添字の降順で順位を付け、数列を相異なる整数からなる列に変換する。同じ値の要素が元の添字順では降順の順位を持つため、狭義単調増加部分列が保存される。

末尾の添字を $p$、左端を $l$ としたときの最適値を $D_p(l)$ とする。末尾の候補を集合 $E$ に制限した最適値の関数 $H_E(l)$ は、$E$ に属する各 $D_p(l)$ と零の最大値である。

末尾の値が小さい集合 $L$ と大きい集合 $R$ に対して、$H_R(l) > H_L(l)$ となる左端 $l$ はある接頭辞に限られる。この単一交差性により、$H_{L \cup R}$ は $H_R$ の接頭辞と $H_L$ の接尾辞をつなげて表せる。同点では $H_L$ を選ぶことが重要である。

左端を添字とする永続セグメント木でこれらの関数を保持し、各ノードに区間の右端の値を保存する。マージでは各段の片側だけを再帰的に処理し、$O(\log n)$ 時間で新しい関数を作る。値を添字とする外側のセグメント木では、値が小さい側、大きい側の順序を保ってマージする。各要素につき $O(\log n)$ 回のマージと重みを加える接頭辞更新を行うため、前処理は $O(n\log^2 n)$ となる。

各右端 $r$ まで処理した関数の根を保存すると、区間クエリはその関数を $l$ で評価する操作になる。復元用の部分列は、共有可能な二分連結の形で接尾辞タグに保持する。クエリで通る経路のタグを葉から根の順に並べ、それぞれを展開することで、出力長に比例する時間で最適な部分列を復元できる。

# 参考文献

- Keisuke Korogi, [Near-Linear Preprocessing for Range Weighted Longest Increasing Subsequence Queries](https://arxiv.org/html/2610.20983v1), 2026.
