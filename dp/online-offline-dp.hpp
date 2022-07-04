#include "monotone-minima.cpp"

/**
 * @brief  Online Offline DP(オンライン・オフライン変換)
 * @docs docs/online-offline-dp.md
 */
template< typename T, typename Compare = less< T > >
vector< T > online_offline_dp(int W, const function< T(int, int) > &f, const Compare &comp = Compare()) {
  vector< T > dp(W + 1);
  vector< int > isset(W + 1);
  int y_base = -1, x_base = -1;
  function< T(int, int) > get_cost = [&](int y, int x) { // return dp[0, x+x_base)+f[x+x_base, y+y_base)
    return dp[x + x_base] + f(x + x_base, y + y_base);
  };
  function< void(int, int, int) > induce = [&](int l, int m, int r) { // dp[l, m) -> dp[m, r)
    x_base = l, y_base = m;
    auto ret = monotone_minima(r - m, m - l, get_cost, comp);
    for(int i = 0; i < ret.size(); i++) {
      if(!isset[m + i] || comp(ret[i].second, dp[m + i])) {
        isset[m + i] = true;
        dp[m + i] = ret[i].second;
      }
    }
  };
  function< void(int, int) > dfs = [&](int l, int r) {
    if(l + 1 == r) {
      x_base = l, y_base = l;
      T cst = l ? get_cost(0, -1) : 0;
      if(!isset[l] || comp(cst, dp[l])) {
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
