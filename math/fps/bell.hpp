/**
 * @brief Bell(ベル数)
 * 
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > bell(int N) {
  FPS< Mint > poly(N + 1), ret(N + 1);
  poly[1] = 1;
  poly = poly.exp();
  poly[0] -= 1;
  poly = poly.exp();
  Mint mul = 1;
  for(int i = 0; i <= N; i++) {
    ret[i] = poly[i] * mul;
    mul *= i + 1;
  }
  return ret;
}
