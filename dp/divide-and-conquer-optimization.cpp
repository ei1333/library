#include "monotone-minima.cpp"

/**
 * @brief Divide And Conquer Optimization
 * @docs docs/divide-and-conquer-optimization.md
 */
template< typename T, typename Compare = less< T > >
vector< vector< T > > divide_and_conquer_optimization(int H, int W, T INF, const function< T(int, int) > &f, const Compare &comp = Compare()) {
  vector< vector< T > > dp(H + 1, vector< T >(W + 1, INF));
  dp[0][0] = 0;
  for(int i = 1; i <= H; i++) {
    function< T(int, int) > get_cost = [&](int y, int x) {
      if(x >= y) return INF;
      return dp[i - 1][x] + f(x, y);
    };
    auto ret = monotone_minima(W + 1, W + 1, get_cost, comp);
    for(int j = 0; j <= W; j++) dp[i][j] = ret[j].second;
  }
  return dp;
}
