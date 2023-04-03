---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: dp/divide-and-conquer-optimization.hpp
    title: Divide And Conquer Optimization
  - icon: ':heavy_check_mark:'
    path: dp/online-offline-dp.hpp
    title: "Online Offline DP(\u30AA\u30F3\u30E9\u30A4\u30F3\u30FB\u30AA\u30D5\u30E9\
      \u30A4\u30F3\u5909\u63DB)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2603.test.cpp
    title: test/verify/aoj-2603.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-703.test.cpp
    title: test/verify/yukicoder-703.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-704.test.cpp
    title: test/verify/yukicoder-704.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-705.test.cpp
    title: test/verify/yukicoder-705.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"dp/monotone-minima.hpp\"\ntemplate< typename T, typename\
    \ Compare = less< T > >\nvector< pair< int, T > > monotone_minima(int H, int W,\
    \ const function< T(int, int) > &f, const Compare &comp = Compare()) {\n  vector<\
    \ pair< int, T > > dp(H);\n  function< void(int, int, int, int) > dfs = [&](int\
    \ top, int bottom, int left, int right) {\n    if(top > bottom) return;\n    int\
    \ line = (top + bottom) / 2;\n    T ma;\n    int mi = -1;\n    for(int i = left;\
    \ i <= right; i++) {\n      T cst = f(line, i);\n      if(mi == -1 || comp(cst,\
    \ ma)) {\n        ma = cst;\n        mi = i;\n      }\n    }\n    dp[line] = make_pair(mi,\
    \ ma);\n    dfs(top, line - 1, left, mi);\n    dfs(line + 1, bottom, mi, right);\n\
    \  };\n  dfs(0, H - 1, 0, W - 1);\n  return dp;\n}\n"
  code: "template< typename T, typename Compare = less< T > >\nvector< pair< int,\
    \ T > > monotone_minima(int H, int W, const function< T(int, int) > &f, const\
    \ Compare &comp = Compare()) {\n  vector< pair< int, T > > dp(H);\n  function<\
    \ void(int, int, int, int) > dfs = [&](int top, int bottom, int left, int right)\
    \ {\n    if(top > bottom) return;\n    int line = (top + bottom) / 2;\n    T ma;\n\
    \    int mi = -1;\n    for(int i = left; i <= right; i++) {\n      T cst = f(line,\
    \ i);\n      if(mi == -1 || comp(cst, ma)) {\n        ma = cst;\n        mi =\
    \ i;\n      }\n    }\n    dp[line] = make_pair(mi, ma);\n    dfs(top, line - 1,\
    \ left, mi);\n    dfs(line + 1, bottom, mi, right);\n  };\n  dfs(0, H - 1, 0,\
    \ W - 1);\n  return dp;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: dp/monotone-minima.hpp
  requiredBy:
  - dp/online-offline-dp.hpp
  - dp/divide-and-conquer-optimization.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-704.test.cpp
  - test/verify/aoj-2603.test.cpp
  - test/verify/yukicoder-703.test.cpp
  - test/verify/yukicoder-705.test.cpp
documentation_of: dp/monotone-minima.hpp
layout: document
title: Monotone Minima
---

## 概要

$2$ 変数関数 $f(i, j) (0 \leq i \lt H, 0 \leq j \lt W)$ が Monotone であるとは, すべての $k$ に対して $\mathrm{argmin} f(k, *) \leq \mathrm{argmin} f(k + 1, *)$ を満たすことをいう. つまり各行の最小値をとる位置が右下に単調に下がっていることを意味する.

Monge $\Rightarrow$ Totally Monotone(TM) $\Rightarrow$ Monotone なので, Monotone は弱い条件である.

* `monotone_minima(H, W, f, comp)`: 各行について, 最小値をとる位置と最小値をペアで返す. `f` は $2$ 変数関数, `comp` は比較関数.

## 計算量

* $O(N \log N)$
