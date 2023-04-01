---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: dp/monotone-minima.hpp
    title: Monotone Minima
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/verify/yukicoder-703.test.cpp
    title: test/verify/yukicoder-703.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-704.test.cpp
    title: test/verify/yukicoder-704.test.cpp
  - icon: ':x:'
    path: test/verify/yukicoder-705.test.cpp
    title: test/verify/yukicoder-705.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
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
    \  };\n  dfs(0, H - 1, 0, W - 1);\n  return dp;\n}\n#line 2 \"dp/online-offline-dp.hpp\"\
    \n\ntemplate< typename T, typename Compare = less< T > >\nvector< T > online_offline_dp(int\
    \ W, const function< T(int, int) > &f, const Compare &comp = Compare()) {\n  vector<\
    \ T > dp(W + 1);\n  vector< int > isset(W + 1);\n  int y_base = -1, x_base = -1;\n\
    \  function< T(int, int) > get_cost = [&](int y, int x) { // return dp[0, x+x_base)+f[x+x_base,\
    \ y+y_base)\n    return dp[x + x_base] + f(x + x_base, y + y_base);\n  };\n  function<\
    \ void(int, int, int) > induce = [&](int l, int m, int r) { // dp[l, m) -> dp[m,\
    \ r)\n    x_base = l, y_base = m;\n    auto ret = monotone_minima(r - m, m - l,\
    \ get_cost, comp);\n    for(int i = 0; i < ret.size(); i++) {\n      if(!isset[m\
    \ + i] || comp(ret[i].second, dp[m + i])) {\n        isset[m + i] = true;\n  \
    \      dp[m + i] = ret[i].second;\n      }\n    }\n  };\n  function< void(int,\
    \ int) > dfs = [&](int l, int r) {\n    if(l + 1 == r) {\n      x_base = l, y_base\
    \ = l;\n      T cst = l ? get_cost(0, -1) : 0;\n      if(!isset[l] || comp(cst,\
    \ dp[l])) {\n        isset[l] = true;\n        dp[l] = cst;\n      }\n    } else\
    \ {\n      int mid = (l + r) / 2;\n      dfs(l, mid);\n      induce(l, mid, r);\n\
    \      dfs(mid, r);\n    }\n  };\n  dfs(0, W + 1);\n  return dp;\n};\n"
  code: "#include \"monotone-minima.hpp\"\n\ntemplate< typename T, typename Compare\
    \ = less< T > >\nvector< T > online_offline_dp(int W, const function< T(int, int)\
    \ > &f, const Compare &comp = Compare()) {\n  vector< T > dp(W + 1);\n  vector<\
    \ int > isset(W + 1);\n  int y_base = -1, x_base = -1;\n  function< T(int, int)\
    \ > get_cost = [&](int y, int x) { // return dp[0, x+x_base)+f[x+x_base, y+y_base)\n\
    \    return dp[x + x_base] + f(x + x_base, y + y_base);\n  };\n  function< void(int,\
    \ int, int) > induce = [&](int l, int m, int r) { // dp[l, m) -> dp[m, r)\n  \
    \  x_base = l, y_base = m;\n    auto ret = monotone_minima(r - m, m - l, get_cost,\
    \ comp);\n    for(int i = 0; i < ret.size(); i++) {\n      if(!isset[m + i] ||\
    \ comp(ret[i].second, dp[m + i])) {\n        isset[m + i] = true;\n        dp[m\
    \ + i] = ret[i].second;\n      }\n    }\n  };\n  function< void(int, int) > dfs\
    \ = [&](int l, int r) {\n    if(l + 1 == r) {\n      x_base = l, y_base = l;\n\
    \      T cst = l ? get_cost(0, -1) : 0;\n      if(!isset[l] || comp(cst, dp[l]))\
    \ {\n        isset[l] = true;\n        dp[l] = cst;\n      }\n    } else {\n \
    \     int mid = (l + r) / 2;\n      dfs(l, mid);\n      induce(l, mid, r);\n \
    \     dfs(mid, r);\n    }\n  };\n  dfs(0, W + 1);\n  return dp;\n};\n"
  dependsOn:
  - dp/monotone-minima.hpp
  isVerificationFile: false
  path: dp/online-offline-dp.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/verify/yukicoder-704.test.cpp
  - test/verify/yukicoder-703.test.cpp
  - test/verify/yukicoder-705.test.cpp
documentation_of: dp/online-offline-dp.hpp
layout: document
title: "Online Offline DP(\u30AA\u30F3\u30E9\u30A4\u30F3\u30FB\u30AA\u30D5\u30E9\u30A4\
  \u30F3\u5909\u63DB)"
---

## 概要

$dp[j] = \min \\{ dp[i] + f(i,j) : i \in [0,j) \\}$ (例: $f(i,j)$ を区間 $[i,j)$ のコストとすると、区間[0, j) を任意個に分割するときの最小コスト) を考える.

愚直にDPをすると $O(N^2)$ かかるが, 最小値をとる位置 $i$ が $j$ の増加にしたがって単調増加する場合 $O(N \log^2 N)$ で解くことができる.

区間 $[l, r)$ の dp 配列を埋めたい. $m = \frac {l + r} 2$ とする.
遷移するときに $m$ をまたがないものは分割して再帰的に解くことにすると, $m$ をまたぐものだけを考えれば良い. $[l, m)$ の dp 配列の値はわかり, それ以前の dp の計算結果に依存しない形となる. つまり $2$ 変数関数 $g(j, i) = dp[i] + f(i, j) (l \le i \lt m, m \leq j \lt r)$ を定義できて, Monotone-Minima を用いて効率的に解くことができる. (日本語むずかしい　こまった）(分割統治FFTも同じ考え方なので下のコードのinduceの部分をFFTにするとできると思う)


* `online_offline_dp(N, f, comp)`: 長さ $N + 1$ の dp 配列($dp[j]:=$ 区間 $[0, j)$ を任意個に分割するときのコスト) を返す. $f(i, j)$ は区間 $[i, j)$ のコストを与える $2$ 変数関数($0 \leq i \lt j \leq N$ を満たす範囲で定義されていればよい).

## 計算量

* $O(N \log^2 N)$
