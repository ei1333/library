#include "subset-zeta-moebius-transform.cpp"

/**
 * @brief Bitwise Or Convolution (Bitwise-OR畳み込み)
 */
template< typename T >
vector< T > bitwise_or_convolution(vector< T > f, vector< T > g) {
  const int n = (int) f.size();
  assert(f.size() == g.size());
  assert((n & (n - 1)) == 0);
  subset_zeta_transform(f);
  subset_zeta_transform(g);
  for(int i = 0; i < n; i++) f[i] *= g[i];
  subset_moebius_transform(f);
  return f;
}
