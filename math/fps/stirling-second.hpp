/**
 * @brief Stirling Second(第二種スターリング数)
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > stirling_second(int N) {
  FPS< Mint > A(N + 1), B(N + 1);
  Mint tmp = 1;
  for(int i = 0; i <= N; i++) {
    Mint rev = Mint(1) / tmp;
    A[i] = Mint(i).pow(N) * rev;
    B[i] = Mint(1) * rev;
    if(i & 1) B[i] *= -1;
    tmp *= i + 1;
  }
  return (A * B).pre(N + 1);
}
