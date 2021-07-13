/**
 * @brief Subproduct Tree
 */
template< template< typename > class FPS, typename Mint >
vector< FPS< Mint > > subproduct_tree(const FPS< Mint > &xs) {
  int n = (int) xs.size();
  int k = 1;
  while(k < n) k <<= 1;
  vector< FPS< Mint > > g(2 * k, {1});
  for(int i = 0; i < n; i++) g[k + i] = {-xs[i], Mint(1)};
  for(int i = k; i-- > 1;) g[i] = g[i << 1] * g[i << 1 | 1];
  return g;
}
