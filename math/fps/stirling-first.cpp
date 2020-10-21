#include "formal-power-series.cpp"

/**
 * @brief Stirling-First(第一種スターリング数)
 */
template< typename T >
FormalPowerSeries< T > stirling_first(int N) {
  if(N == 0) return {1};
  int M = 1;
  vector< T > fact(N + 1), rfact(N + 1);
  fact[0] = rfact[N] = T(1);
  for(int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i;
  rfact[N] /= fact[N];
  for(int i = N - 1; i >= 0; i--) rfact[i] = rfact[i + 1] * (i + 1);
  FormalPowerSeries< T > ret({T(0), T(1)});
  for(int k = 30 - __builtin_clz(N); k >= 0; k--) {
    FormalPowerSeries< T > as(M + 1), bs(M + 1);
    for(int i = 0; i <= M; i++) as[i] = ret[i] * fact[i];
    bs[M] = T(1);
    for(int i = 1; i <= M; i++) bs[M - i] = bs[M - (i - 1)] * -T(M);
    for(int i = 0; i <= M; i++) bs[M - i] *= rfact[i];
    auto cs = as * bs;
    FormalPowerSeries< T > ds(M + 1);
    for(int i = 0; i <= M; i++) ds[i] = rfact[i] * cs[M + i];
    ret *= ds;
    M <<= 1;
    if((N >> k) & 1) {
      FormalPowerSeries< T > ts(M + 1 + 1, T(0));
      for(int i = 0; i <= M; i++) {
        ts[i + 0] += ret[i] * -T(M);
        ts[i + 1] += ret[i];
      }
      ret = ts;
      M |= 1;
    }
  }
  return ret;
}
