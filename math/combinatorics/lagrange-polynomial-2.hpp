/**
 * @brief Lagrange Polynomial(多項式補間, 係数)
 */
template< typename Mint >
vector< Mint > lagrange_polynomial(const vector< Mint > &x, const vector< Mint > &y) {
  int k = (int) x.size() - 1;

  vector< Mint > f(k + 1), dp(k + 2);
  dp[0] = 1;
  for(int j = 0; j <= k; j++) {
    for(int l = k + 1; l > 0; l--) {
      dp[l] = dp[l] * -x[j] + dp[l - 1];
    }
    dp[0] *= -x[j];
  }

  for(int i = 0; i <= k; i++) {
    Mint d = 1;
    for(int j = 0; j <= k; j++) {
      if(i != j) {
        d *= x[i] - x[j];
      }
    }
    Mint mul = y[i] / d;
    if(x[i] == 0) {
      for(int j = 0; j <= k; j++) {
        f[j] += dp[j + 1] * mul;
      }
    } else {
      Mint inv = Mint(1) / (-x[i]), pre = 0;
      for(int j = 0; j <= k; j++) {
        Mint cur = (dp[j] - pre) * inv;
        f[j] += cur * mul;
        pre = cur;
      }
    }
  }
  return f;
}
