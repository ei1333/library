#include "subproduct-tree.cpp"

/**
 * @brief Polynomial Interpolation(多項式補間)
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > polynomial_interpolation(const FPS< Mint > &xs, const FPS< Mint > &ys) {
  assert(xs.size() == ys.size());
  auto mul = subproduct_tree(xs);
  int n = (int) xs.size(), k = (int) mul.size() / 2;
  vector< FPS< Mint > > g(2 * k);
  g[1] = mul[1].diff() % mul[1];
  for(int i = 2; i < k + n; i++) g[i] = g[i >> 1] % mul[i];
  for(int i = 0; i < n; i++) g[k + i] = {ys[i] / g[k + i][0]};
  for(int i = k; i-- > 1;) g[i] = g[i << 1] * mul[i << 1 | 1] + g[i << 1 | 1] * mul[i << 1];
  return g[1];
}
