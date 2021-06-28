#include "sample-point-shift.cpp"

/**
 * @brief Factorial(階乗)
 */
template< typename Mint, typename F >
Mint factorial(int64_t n, const F& multiply) {
  if(n <= 1) return 1;
  if(n >= Mint::get_mod()) return 0;
  int64_t v = 1;
  while(v * v < n) v *= 2;
  Mint iv = Mint(1) / v;
  vector< Mint > G{1, v + 1};
  for(int64_t d = 1; d != v; d <<= 1) {
    vector< Mint > G1 = sample_point_shift(G, Mint(d) * iv, multiply);
    vector< Mint > G2 = sample_point_shift(G, Mint(d * v + v) * iv, multiply);
    vector< Mint > G3 = sample_point_shift(G, Mint(d * v + d + v) * iv, multiply);
    for(int i = 0; i <= d; i++) G[i] *= G1[i], G2[i] *= G3[i];
    copy(begin(G2), end(G2) - 1, back_inserter(G));
  }
  Mint res = 1;
  int64_t i = 0;
  while(i + v <= n) res *= G[i / v], i += v;
  while(i < n) res *= ++i;
  return res;
}
