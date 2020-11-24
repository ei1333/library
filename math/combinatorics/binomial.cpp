/**
 * @brief Binomial(二項係数)
 * @docs docs/binomial.md
 */
template< typename T >
T binomial(int64_t N, int64_t K) {
  if(K < 0 || N < K) return 0;
  T ret = 1;
  for(int64_t i = 1; i <= K; ++i) {
    ret *= N;
    N--;
    ret /= i;
  }
  return ret;
}
