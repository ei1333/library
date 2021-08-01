#include "fast-walsh-hadamard-transform.cpp"

/**
 * @brief Bitwise Xor Convolution (Bitwise-XOR畳み込み)
 */
template< typename T >
vector< T > bitwise_xor_convolution(vector< T > f, vector< T > g) {
  const int n = (int) f.size();
  assert(f.size() == g.size());
  assert((n & (n - 1)) == 0);
  fast_walsh_hadamard_transform(f, false);
  fast_walsh_hadamard_transform(g, false);
  for(int i = 0; i < n; i++) f[i] *= g[i];
  fast_walsh_hadamard_transform(f, true);
  return f;
}
