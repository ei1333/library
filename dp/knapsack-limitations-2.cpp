#include "knapsack-limitations.cpp"

/**
 * @brief Knapsack Limitations(個数制限つきナップサック問題) $O(N^2 \max(v_i)^2)$
 * @docs docs/knapsack-limitations-2.md
 */
template< typename T >
T knapsack_limitations(const vector< T > &w, const vector< T > &m, const vector< int > &v,
                       const T &W) {
  const int N = (int) w.size();
  auto v_max = *max_element(begin(v), end(v));
  if(v_max == 0) return 0;
  vector< int > ma(N);
  vector< T > mb(N);
  for(int i = 0; i < N; i++) {
    ma[i] = min< T >(m[i], v_max - 1);
    mb[i] = m[i] - ma[i];
  }
  T sum = 0;
  for(int i = 0; i < N; i++) sum += ma[i] * v[i];
  auto dp = knapsack_limitations(v, ma, w, sum, T(-1), less<>());
  vector< int > ord(N);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), [&](int a, int b) {
    return v[a] * w[b] > v[b] * w[a];
  });
  T ret = T();
  for(int i = 0; i < dp.size(); i++) {
    if(dp[i] > W || dp[i] == -1) continue;
    T rest = W - dp[i], cost = i;
    for(auto &p : ord) {
      auto get = min(mb[p], rest / w[p]);
      if(get == 0) break;
      cost += get * v[p];
      rest -= get * w[p];
    }
    ret = max(ret, cost);
  }
  return ret;
}
