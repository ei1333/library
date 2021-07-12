/**
 * @brief Multipoint-Evaluation
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > multipoint_evaluation(const FPS< Mint > &f, const FPS< Mint > &xs) {
  int n = (int) f.size(), m = (int) xs.size();
  int k = 1;
  while(k < m) k <<= 1;
  vector< FPS< Mint > > g(2 * k, {1});
  for(int i = 0; i < m; i++) g[k + i] = {-xs[i], Mint(1)};
  for(int i = k; i-- > 1;) g[i] = g[i << 1] * g[i << 1 | 1];
  g[1] = f % g[1];
  for(int i = 2; i < k + m; i++) g[i] = g[i >> 1] % g[i];
  FPS< Mint > ys(m);
  for(int i = 0; i < m; i++) ys[i] = g[k + i][0];
  return ys;
}
