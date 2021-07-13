/**
 * @brief Count Subset Sum
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > count_subset_sum(vector< Mint > &c) {
  const int n = (int) c.size();
  vector< Mint > inv(n);
  inv[0] = Mint(0);
  inv[1] = Mint(1);
  auto mod = Mint::get_mod();
  for(int i = 2; i < n; i++) {
    inv[i] = -inv[mod % i] * (mod / i);
  }
  FPS< Mint > f(n);
  for(int i = 1; i < n; i++) {
    for(int j = 1, d = i; d < n; j++, d += i) {
      if(j & 1) f[d] += c[i] * inv[j];
      else f[d] -= c[i] * inv[j];
    }
  }
  return f.exp();
}
