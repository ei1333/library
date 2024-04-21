/**
 * @brief Binomial(二項係数)
 * 
 */
template< typename T >
T binomial(int64_t N, int64_t K) {
  if(K < 0 || N < K) return 0;
  static vector< T > invs;
  if(invs.size() < K + 1) {
    int pre_sz = max(1, (int) invs.size());
    invs.resize(K + 1);
    for(int i = pre_sz; i <= K; i++) {
      invs[i] = T(1) / i;
    }
  }
  T ret = 1;
  for(int64_t i = 1; i <= K; ++i) {
    ret *= N;
    N--;
    ret *= invs[i];
  }
  return ret;
}
