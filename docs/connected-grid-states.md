---
title: Connected Grid States(グリッドの連結性を持つDPの状態遷移)
documentation_of: //other/connected-grid-states.hpp
---

グリッドの連結性を持つDPの状態遷移を計算します。

それぞれの Union Find の状態に番号付けして、そのマスに '#'、'.' を置くそれぞれの場合の遷移先の番号を $O(1)$ で求められるようにします。

# コンストラクタ

```
ConnectedGridStates(int n)
```

横幅が `n` のグリッドの各連結状態について、状態遷移を前計算します。

## 制約

- $1 \leq n$

## 計算量

$n$ に対して指数オーダーです。状態数の合計を $s$ として $O(ns \log s)$ です。
 
$n \leq 11$ くらいが限度だと思います。

参考: 状態数の合計
```
1: 3
2: 11
3: 34
4: 102
5: 306
6: 914
7: 2722
8: 8080
9: 23929
10: 70747
11: 208944
12: 616706
13: 1819663
```

何も存在しない状態の番号は $0$ または $states\[k\].size - 1$ であることを保証します。

前者は過去に壁が存在したことがない、後者は過去に壁が存在したことがある状態を意味します。

# set_wall

```
int set_wall(int k, int state)
```

$k$ 列目で状態 $state$ にいるときに、$k$ 列目のマスに壁を置いた場合の遷移先を返します。

## 制約

- $0 \leq k \lt n$
- $0 \leq state \lt states\[k\].size$

## 計算量

- $O(1)$

# set_ground

```
int set_ground(int k, int state)
```

$k$ 列目で状態 $state$ にいるときに、$k$ 列目のマスに壁を置いた場合の遷移先を返します。

## 制約

- $0 \leq k \lt n$
- $0 \leq state \lt states\[k\].size$

## 計算量

- $O(1)$

# operator []

```
operator [k]
```

$k$ 列目のすべての状態を返します。

$\[k\]\[state\]$ とすることで、$k$ 列目の状態 $state$ の Union Find の状態を確認できます。

便宜的に $n \leq k \lt 2n$ を与えたとき、$k - n$ 列目のすべての状態を返します。

## 制約

- $0 \leq k \lt 2n$

## 計算量

- $O(1)$
