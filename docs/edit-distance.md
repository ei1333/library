---
title: Edit Distance(編集距離)
documentation_of: //dp/edit-distance.hpp
---

## 概要

レーベルシュタイン距離とも呼ばれる. $2$ つの文字列がどの程度異なっているかを示す距離の一種である.

$1$ 文字の挿入・削除・置換によって, 一方の文字列をもう一方の文字列に変形するのに必要な手順の最小値として定義される.

* `edit_distance(S, T)`: 文字列 `S, T` の編集距離を返す.

## 計算量

* $O(nm)$
