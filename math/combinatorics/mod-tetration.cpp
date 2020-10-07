/**
 * @brief Mod-Tetration(テトレーション)
 * @docs docs/mod-tetration.md
 */
template< typename T >
T mod_tetration(const T &a, const T &b, const T &m) {
  if(m == 1) return 0;
  if(a == 0) return !(b & 1);
  if(b == 0) return 1;
  if(b == 1) return a % m;
  if(b == 2) return mod_pow(a % m, a, m);
  auto phi = euler_phi(m);
  return mod_pow(a % m, mod_tetration(a, b - 1, phi) + phi, m);
}
