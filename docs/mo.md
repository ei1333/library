---
title: Mo's algorithm
documentation_of: //other/mo.hpp
---

# コンストラクタ

```cpp
Mo(int n, int q)
```

区間の長さ $n$、クエリの個数 $q$ で初期化します。

## 計算量

- $O(q)$

# add_query

```cpp
void add_query(int l, int r)
```

クエリ $[l, r)$ を追加します。

## 制約

- $0 \leq l \lt r \leq n$

## 計算量

- $O(1)$

# calclate_queries

```cpp
(1) template <typename AL, typename AR, typename EL, typename ER, typename Q>
    void calclate_queries(const AL &add_left, const AR &add_right, const EL &erase_left,
                          const ER &erase_right, const Q &query)
(2) template <typename A, typename E, typename Q>
    void calclate_queries(const A &add, const E &erase, const Q &query)
```

追加したすべてのクエリを処理します。

(1) では、それぞれの引数は次に対応します。

- $add\_left(x)$: $x$ 番目の要素を左から追加します。
- $add\_right(x)$: $x$ 番目の要素を右から追加化します。
- $erase\_left(x)$: $x$ 番目の要素を左から削除します。
- $erase\_right(x)$: $x$ 番目の要素を右から削除します。
- $query(x)$: $x$ 番目のクエリを処理します。

(2) では、それぞれの引数は次に対応します。左右の区別が必要ない場合に使用します。

- $add(x)$: $x$ 番目の要素を追加します。
- $erase(x)$: $x$ 番目の要素を削除します。
- $query(x)$: $x$ 番目のクエリを処理します。

## 制約

- 追加したクエリの個数が $q$ と一致する

## 計算量

- $O(\alpha N \sqrt Q)$

区間を $1$ 伸縮させる計算量を $O(a)$ とします。
