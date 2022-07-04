/**
 * @brief Knapsack 01(0-1ナップサック問題) $O(N \sum {v_i})$
 * @docs docs/knapsack-01-2.md
 */
template< typename T >
T knapsack_01_2(const vector< T > &w, const vector< int > &v, const T &W) {
  const int N = (int) w.size();
  const int sum = accumulate(begin(v), end(v), 0);
  vector< T > dp(sum + 1, W + 1);
  dp[0] = T();
  for(int i = 0; i < N; i++) {
    for(int j = sum; j >= v[i]; j--) {
      dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
    }
  }
  int ret = 0;
  for(int i = 0; i <= sum; i++) {
    if(dp[i] <= W) ret = i;
  }
  return ret;
}
