/**
 * @brief Sample-Point-Shift
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > sample_point_shift(const FPS< Mint > &ys, const Mint &m) {
  Enumeration< Mint > comb;
  int d = (int) ys.size() - 1;
  FPS< Mint > f(d + 1), g(d * 2 + 1);
  for(int i = 0; i <= d; i++) {
    f[i] = ys[i] * comb.finv(i) * comb.finv(d - i);
    if((d - i) & 1) f[i] = -f[i];
  }
  for(int i = 0; i <= 2 * d; i++) {
    g[i] = modint(1) / (m - d + i);
  }
  auto h = f * g;
  Mint coef = 1;
  for(int i = 0; i <= d; i++) {
    coef *= (m - d + i);
  }
  for(int i = 0; i <= d; i++) {
    h[i + d] *= coef;
    coef *= (m + i + 1) * g[i];
  }
  return FPS< Mint >{begin(h) + d, begin(h) + 2 * d + 1};
}
