/**
 * @brief Knapsack Limitations(個数制限つきナップサック問題) $O(NW)$
 * @docs docs/knapsack-limitations.md
 */
template< typename T, typename Compare = greater< T > >
vector< T > knapsack_limitations(const vector< int > &w, const vector< int > &m, const vector< T > &v,
                                 const int &W, const T &NG, const Compare &comp = Compare()) {
  const int N = (int) w.size();
  vector< T > dp(W + 1, NG), deqv(W + 1);
  dp[0] = T();
  vector< int > deq(W + 1);
  for(int i = 0; i < N; i++) {
    if(w[i] == 0) {
      for(int j = 0; j <= W; j++) {
        if(dp[j] != NG && comp(dp[j] + v[i] * m[i], dp[j])) {
          dp[j] = dp[j] + v[i] * m[i];
        }
      }
    } else {
      for(int a = 0; a < w[i]; a++) {
        int s = 0, t = 0;
        for(int j = 0; w[i] * j + a <= W; j++) {
          if(dp[w[i] * j + a] != NG) {
            auto val = dp[w[i] * j + a] - j * v[i];
            while(s < t && comp(val, deqv[t - 1])) --t;
            deq[t] = j;
            deqv[t++] = val;
          }
          if(s < t) {
            dp[j * w[i] + a] = deqv[s] + j * v[i];
            if(deq[s] == j - m[i]) ++s;
          }
        }
      }
    }
  }
  return dp;
}
