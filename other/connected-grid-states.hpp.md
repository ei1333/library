---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/connected-grid-states.hpp\"\nstruct ConnectedGridStates\
    \ {\nprivate:\n  vector< vector< vector< int > > > states;\n  vector< vector<\
    \ int > > nxt_wall, nxt_ground;\n  int width;\n\npublic:\n\n  explicit ConnectedGridStates(int\
    \ width):\n      width(width), states(width), nxt_wall(width), nxt_ground(width)\
    \ {\n    assert(width > 0);\n\n    auto modify = [&](vector< int > B) {\n    \
    \  vector< int > id(width, -1);\n      int now = 0;\n      for (int i = 0; i <\
    \ width; i++) {\n        if (B[i] != -1) {\n          if (id[B[i]] == -1) {\n\
    \            id[B[i]] = now++;\n          }\n          B[i] = id[B[i]];\n    \
    \    }\n      }\n      return B;\n    };\n\n    vector< map< vector< int >, int\
    \ > > ids(width);\n    queue< pair< int, int > > que; // {col, state_id}\n\n \
    \   {\n      vector< int > state(width, -1);\n      states[0].emplace_back(state);\n\
    \      ids[0].emplace(state, 0);\n      nxt_wall[0].emplace_back(-1);\n      nxt_ground[0].emplace_back(-1);\n\
    \      que.emplace(0, 0);\n    }\n\n    auto push = [&](int nxt, const vector<\
    \ int > &state) -> int {\n      auto it = ids[nxt].emplace(state, states[nxt].size());\n\
    \      if (it.second) {\n        states[nxt].emplace_back(state);\n        nxt_wall[nxt].emplace_back(-1);\n\
    \        nxt_ground[nxt].emplace_back(-1);\n        que.emplace(nxt,it.first->second);\n\
    \      }\n      return it.first->second;\n    };\n\n    while (not que.empty())\
    \ {\n      auto [i, id] = que.front();\n      que.pop();\n      int j = i + 1\
    \ == width ? 0 : i + 1;\n      auto& state = states[i][id];\n      int mx = *max_element(state.begin(),\
    \ state.end());\n      { // '.'\n        if (state[i] == -1) {\n          nxt_ground[i][id]\
    \ = push(j, state);\n        } else {\n          bool ok = false;\n          for\
    \ (int k = 0; k < width; k++) {\n            ok |= i != k and state[k] == state[i];\n\
    \          }\n          if (ok) {\n            auto to = state;\n            to[i]\
    \ = -1;\n            nxt_ground[i][id] = push(j, modify(to));\n          } else\
    \ if (mx >= 1) { // disconnected\n            nxt_ground[i][id] = -1;\n      \
    \    } else { // disappeared\n            nxt_ground[i][id] = -2;\n          }\n\
    \        }\n      }\n      { // '#'\n        auto to = state;\n        if (i ==\
    \ 0) {\n          if (state[i] == -1) {\n            to[i] = mx + 1;\n       \
    \   }\n        } else {\n          if (state[i] == -1) {\n            if (state[i\
    \ - 1] == -1) {\n              to[i] = mx + 1;\n            } else {\n       \
    \       to[i] = state[i - 1];\n            }\n          } else if (state[i - 1]\
    \ != -1) {\n            for (int k = 0; k < width; k++) {\n              if (state[k]\
    \ == state[i]) {\n                to[k] = state[i - 1];\n              }\n   \
    \         }\n          }\n        }\n        nxt_wall[i][id] = push(j, modify(to));\n\
    \      }\n    }\n    for (int i = 0; i < width; i++) {\n      int j = i + 1 ==\
    \ width ? 0 : i + 1;\n      int sz = (int) states[j].size();\n      for (auto\
    \ &k: nxt_ground[i]) {\n        if (k == -2) k = sz;\n      }\n      for (auto\
    \ &k: nxt_wall[i]) {\n        if (k == -2) k = sz;\n      }\n      nxt_ground[i].emplace_back(sz);\n\
    \      nxt_wall[i].emplace_back(-1);\n    }\n    for (int i = 0; i < width; i++)\
    \ {\n      states[i].emplace_back(width, -1);\n    }\n  }\n\n  inline int set_wall(int\
    \ k, int state) const {\n    return nxt_wall[k][state];\n  }\n\n  inline int set_ground(int\
    \ k, int state) const {\n    return nxt_ground[k][state];\n  }\n\n  inline const\
    \ vector< vector< int > > &operator[](int k) const {\n    return states[k >= width\
    \ ? k - width : k];\n  }\n};\n"
  code: "struct ConnectedGridStates {\nprivate:\n  vector< vector< vector< int > >\
    \ > states;\n  vector< vector< int > > nxt_wall, nxt_ground;\n  int width;\n\n\
    public:\n\n  explicit ConnectedGridStates(int width):\n      width(width), states(width),\
    \ nxt_wall(width), nxt_ground(width) {\n    assert(width > 0);\n\n    auto modify\
    \ = [&](vector< int > B) {\n      vector< int > id(width, -1);\n      int now\
    \ = 0;\n      for (int i = 0; i < width; i++) {\n        if (B[i] != -1) {\n \
    \         if (id[B[i]] == -1) {\n            id[B[i]] = now++;\n          }\n\
    \          B[i] = id[B[i]];\n        }\n      }\n      return B;\n    };\n\n \
    \   vector< map< vector< int >, int > > ids(width);\n    queue< pair< int, int\
    \ > > que; // {col, state_id}\n\n    {\n      vector< int > state(width, -1);\n\
    \      states[0].emplace_back(state);\n      ids[0].emplace(state, 0);\n     \
    \ nxt_wall[0].emplace_back(-1);\n      nxt_ground[0].emplace_back(-1);\n     \
    \ que.emplace(0, 0);\n    }\n\n    auto push = [&](int nxt, const vector< int\
    \ > &state) -> int {\n      auto it = ids[nxt].emplace(state, states[nxt].size());\n\
    \      if (it.second) {\n        states[nxt].emplace_back(state);\n        nxt_wall[nxt].emplace_back(-1);\n\
    \        nxt_ground[nxt].emplace_back(-1);\n        que.emplace(nxt,it.first->second);\n\
    \      }\n      return it.first->second;\n    };\n\n    while (not que.empty())\
    \ {\n      auto [i, id] = que.front();\n      que.pop();\n      int j = i + 1\
    \ == width ? 0 : i + 1;\n      auto& state = states[i][id];\n      int mx = *max_element(state.begin(),\
    \ state.end());\n      { // '.'\n        if (state[i] == -1) {\n          nxt_ground[i][id]\
    \ = push(j, state);\n        } else {\n          bool ok = false;\n          for\
    \ (int k = 0; k < width; k++) {\n            ok |= i != k and state[k] == state[i];\n\
    \          }\n          if (ok) {\n            auto to = state;\n            to[i]\
    \ = -1;\n            nxt_ground[i][id] = push(j, modify(to));\n          } else\
    \ if (mx >= 1) { // disconnected\n            nxt_ground[i][id] = -1;\n      \
    \    } else { // disappeared\n            nxt_ground[i][id] = -2;\n          }\n\
    \        }\n      }\n      { // '#'\n        auto to = state;\n        if (i ==\
    \ 0) {\n          if (state[i] == -1) {\n            to[i] = mx + 1;\n       \
    \   }\n        } else {\n          if (state[i] == -1) {\n            if (state[i\
    \ - 1] == -1) {\n              to[i] = mx + 1;\n            } else {\n       \
    \       to[i] = state[i - 1];\n            }\n          } else if (state[i - 1]\
    \ != -1) {\n            for (int k = 0; k < width; k++) {\n              if (state[k]\
    \ == state[i]) {\n                to[k] = state[i - 1];\n              }\n   \
    \         }\n          }\n        }\n        nxt_wall[i][id] = push(j, modify(to));\n\
    \      }\n    }\n    for (int i = 0; i < width; i++) {\n      int j = i + 1 ==\
    \ width ? 0 : i + 1;\n      int sz = (int) states[j].size();\n      for (auto\
    \ &k: nxt_ground[i]) {\n        if (k == -2) k = sz;\n      }\n      for (auto\
    \ &k: nxt_wall[i]) {\n        if (k == -2) k = sz;\n      }\n      nxt_ground[i].emplace_back(sz);\n\
    \      nxt_wall[i].emplace_back(-1);\n    }\n    for (int i = 0; i < width; i++)\
    \ {\n      states[i].emplace_back(width, -1);\n    }\n  }\n\n  inline int set_wall(int\
    \ k, int state) const {\n    return nxt_wall[k][state];\n  }\n\n  inline int set_ground(int\
    \ k, int state) const {\n    return nxt_ground[k][state];\n  }\n\n  inline const\
    \ vector< vector< int > > &operator[](int k) const {\n    return states[k >= width\
    \ ? k - width : k];\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other/connected-grid-states.hpp
  requiredBy: []
  timestamp: '2023-04-03 03:42:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/connected-grid-states.hpp
layout: document
title: "Connected Grid States(\u30B0\u30EA\u30C3\u30C9\u306E\u9023\u7D50\u6027\u3092\
  \u6301\u3064DP\u306E\u72B6\u614B\u9077\u79FB)"
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
