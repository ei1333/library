---
title: Queue Operate Aggregation
documentation_of: //structure/others/queue-operate-aggregation.hpp
---

半群の要素列 $A$ に対して以下の操作を効率的に行います。

* push: $A$ の末尾に要素を追加する
* pop: $A$ の先頭の要素を削除する
* all_prod: $A$ 全体の集約値の取得する

# コンストラクタ

```cpp
QueueOperateAggregation< T, F >(F f)
```

二項演算 $f$ で定義される型 `T` の半群の要素列 $A$ を、空の列で初期化します。

## 計算量

- $O(1)$

# empty

```cpp
bool empty() const
```

$A$ が空のとき `true`、空でないとき `false` を返します。

## 計算量

- $O(1)$

# size

```cpp
size_t size() const
```

$A$ の要素数を返します。

## 計算量

- $O(1)$

# all_prod

```cpp
T all_prod() const
```

$A$ 全体を $f$ で集約した値を返します。

## 制約

- $A$ が空ではない

## 計算量

- $O(1)$

# push

```cpp
void push(const T &x)
```

$A$ の末尾に $x$ を追加します。

## 計算量

- $O(1)$

# pop

```cpp
void pop()
```

$A$ の先頭の要素を削除します。

## 制約

- $A$ が空ではない

## 計算量

- amortized $O(1)$

# get_deque_operate_aggregation

```cpp
template<typename T, typename F>
QueueOperateAggregation<T, F> get_queue_operate_aggregation(const F &f)
```

型 `T`、二項演算 `f` の半群に対応する `QueueOperateAggregation` を返すヘルパー関数です。

## 計算量

- $O(1)$

## 使用例

```cpp
auto que = get_queue_operate_aggregation< T >(f);
```
