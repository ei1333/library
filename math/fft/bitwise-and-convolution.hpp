#include "superset-zeta-moebius-transform.cpp"

/**
 * @brief Bitwise And Convolution (Bitwise-AND畳み込み)
 */
template< typename T >
vector< T > bitwise_and_convolution(vector< T > f, vector< T > g) {
  const int n = (int) f.size();
  assert(f.size() == g.size());
  assert((n & (n - 1)) == 0);
  superset_zeta_transform(f);
  superset_zeta_transform(g);
  for(int i = 0; i < n; i++) f[i] *= g[i];
  superset_moebius_transform(f);
  return f;
}
