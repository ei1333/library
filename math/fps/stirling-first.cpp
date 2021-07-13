/**
 * @brief Stirling First(第一種スターリング数)
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > stirling_first(int N) {
  if(N == 0) return {Mint(1)};
  int M = 1;
  vector< Mint > fact(N + 1), rfact(N + 1);
  fact[0] = rfact[N] = Mint(1);
  for(int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i;
  rfact[N] /= fact[N];
  for(int i = N - 1; i >= 0; i--) rfact[i] = rfact[i + 1] * (i + 1);
  FPS< Mint > ret({Mint(0), Mint(1)});
  for(int k = 30 - __builtin_clz(N); k >= 0; k--) {
    FPS< Mint > as(M + 1), bs(M + 1);
    for(int i = 0; i <= M; i++) as[i] = ret[i] * fact[i];
    bs[M] = Mint(1);
    for(int i = 1; i <= M; i++) bs[M - i] = bs[M - (i - 1)] * Mint(-M);
    for(int i = 0; i <= M; i++) bs[M - i] *= rfact[i];
    auto cs = as * bs;
    FPS< Mint > ds(M + 1);
    for(int i = 0; i <= M; i++) ds[i] = rfact[i] * cs[M + i];
    ret *= ds;
    M <<= 1;
    if((N >> k) & 1) {
      FPS< Mint > ts(M + 1 + 1, Mint(0));
      for(int i = 0; i <= M; i++) {
        ts[i + 0] -= ret[i] * Mint(M);
        ts[i + 1] += ret[i];
      }
      ret = ts;
      M |= 1;
    }
  }
  return ret;
}
