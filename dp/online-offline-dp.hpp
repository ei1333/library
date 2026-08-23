#pragma once

#include <functional>
#include <vector>

#include "monotone-minima.hpp"

template <typename T, typename Compare = std::less<T> >
std::vector<T> online_offline_dp(int W, const std::function<T(int, int)>& f,
                                 const Compare& comp = Compare()) {
  std::vector<T> dp(W + 1);
  std::vector<int> isset(W + 1);
  int y_base = -1, x_base = -1;
  std::function<T(int, int)> get_cost =
      [&](int y, int x) {  // return dp[0, x+x_base)+f[x+x_base, y+y_base)
        return dp[x + x_base] + f(x + x_base, y + y_base);
      };
  std::function<void(int, int, int)> induce =
      [&](int l, int m,
          int r) {  // dp[l, m) -> dp[m, r)
        x_base = l, y_base = m;
        auto ret =
            monotone_minima(r - m, m - l, [&](int i, int old_j, int new_j) {
              return comp(get_cost(i, new_j), get_cost(i, old_j));
            });
        for (int i = 0; i < ret.size(); i++) {
          T cost = get_cost(i, ret[i]);
          if (!isset[m + i] || comp(cost, dp[m + i])) {
            isset[m + i] = true;
            dp[m + i] = cost;
          }
        }
      };
  std::function<void(int, int)> dfs = [&](int l, int r) {
    if (l + 1 == r) {
      x_base = l, y_base = l;
      T cst = l ? get_cost(0, -1) : 0;
      if (!isset[l] || comp(cst, dp[l])) {
        isset[l] = true;
        dp[l] = cst;
      }
    } else {
      int mid = (l + r) / 2;
      dfs(l, mid);
      induce(l, mid, r);
      dfs(mid, r);
    }
  };
  dfs(0, W + 1);
  return dp;
};
