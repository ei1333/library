---
title: Persistent Array
documentation_of: //structure/others/persistent-array.hpp
---

木構造で配列を表現する永続配列です。

オブジェクトをコピーしてから `mutable_get` で更新することで、更新前の状態を保持したまま新しい状態を作れます。

# コンストラクタ

```cpp
PersistentArray()
```

空の永続配列を作成します。

# get

```cpp
T get(const int& k)
```

添字 `k` の値を返します。

## 制約

- $0 \leq k$
- `k` に対応する要素が構築済み

## 計算量

- $O(\log k)$

# mutable_get

```cpp
T* mutable_get(const int& k)
```

添字 `k` に対応する値へのポインタを返します。  
この呼び出しは内部ノードを必要な分だけコピーし、`root` を更新します。

返されたポインタに値を書き込むことで `k` 番目要素を更新できます。

## 制約

- $0 \leq k$

## 計算量

- $O(\log k)$

# build

```cpp
void build(const vector<T>& v)
```

配列 `v` から永続配列を構築します。

## 計算量

- $O(|v| \log |v|)$
