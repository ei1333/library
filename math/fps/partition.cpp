/**
 * @brief Partition(分割数)
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > partition(int N) {
  FPS< Mint > poly(N + 1);
  poly[0] = 1;
  for(int k = 1; k <= N; k++) {
    if(1LL * k * (3 * k + 1) / 2 <= N) poly[k * (3 * k + 1) / 2] += (k % 2 ? -1 : 1);
    if(1LL * k * (3 * k - 1) / 2 <= N) poly[k * (3 * k - 1) / 2] += (k % 2 ? -1 : 1);
  }
  return poly.inv();
}
