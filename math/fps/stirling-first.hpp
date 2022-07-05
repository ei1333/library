/**
 * @brief Stirling First(第一種スターリング数)
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > stirling_first(int N) {
  if(N <= 0) return {Mint(1)};
  auto f = stirling_first< FPS, Mint >(N >> 1);
  f *= f.taylor_shift(-(N >> 1));
  if(N & 1) f = (f << 1) - f * (N - 1);
  return f;
}
