/**
 * @brief Montmort-Number(モンモール数)
 * 
 */
template< typename T >
vector< T > montmort(int N) {
  vector< T > dp(N + 1);
  for(int k = 2; k <= N; k++) {
    dp[k] = dp[k - 1] * k;
    if(k & 1) dp[k] -= 1;
    else dp[k] += 1;
  }
  return dp;
}
