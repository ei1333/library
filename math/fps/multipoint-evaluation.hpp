#include "subproduct-tree.cpp"

/**
 * @brief Multipoint Evaluation
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > multipoint_evaluation(const FPS< Mint > &f, const FPS< Mint > &xs) {
  auto g = subproduct_tree(xs);
  int m = (int) xs.size(), k = (int) g.size() / 2;
  g[1] = f % g[1];
  for(int i = 2; i < k + m; i++) g[i] = g[i >> 1] % g[i];
  FPS< Mint > ys(m);
  for(int i = 0; i < m; i++) ys[i] = (g[k + i].empty() ? Mint(0) : g[k + i][0]);
  return ys;
}
