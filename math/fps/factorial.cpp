#include "sample-point-shift.cpp"

/**
 * @brief Factorial(階乗)
 */
template< template< typename > class FPS, typename Mint >
Mint factorial(int n) {
  if(n <= 1) return 1;
  if(n >= Mint::get_mod()) return 0;
  long long v = 1;
  while(v * v < n) v *= 2;
  Mint iv = Mint(1) / v;
  FPS< Mint > G{1, v + 1};
  for(long long d = 1; d != v; d <<= 1) {
    FPS< Mint > G1 = sample_point_shift(G, Mint(d) * iv);
    FPS< Mint > G2 = sample_point_shift(G, Mint(d * v + v) * iv);
    FPS< Mint > G3 = sample_point_shift(G, Mint(d * v + d + v) * iv);
    for(int i = 0; i <= d; i++) G[i] *= G1[i], G2[i] *= G3[i];
    copy(begin(G2), end(G2) - 1, back_inserter(G));
  }
  Mint res = 1;
  long long i = 0;
  while(i + v <= n) res *= G[i / v], i += v;
  while(i < n) res *= ++i;
  return res;
}
