template< typename T >
FormalPowerSeries< T > random_poly(int n) {
  mt19937 mt(1333333);
  FormalPowerSeries< T > res(n);
  uniform_int_distribution< int > rand(0, T::get_mod() - 1);
  for(int i = 0; i < n; i++) res[i] = rand(mt);
  return res;
}
 
template< typename T, typename F >
FormalPowerSeries< T > minimum_poly(int N, const F &nex) {
  auto dp = random_poly< T >(N);
  auto u = random_poly< T >(N);
  FormalPowerSeries< T > f(2 * N + 5);
  for(int i = 0; i < 2 * N + 5; i++) {
    for(int j = 0; j < N; j++) f[i] += u[j] * dp[j];
    dp = nex(dp);
  }
  return berlekamp_massey< T >(f);
}
 
 
template< typename T, typename F >
FormalPowerSeries< T > sparse_mat_pow(int N, int64_t Q, FormalPowerSeries< modint > dp, const F &nex) {
  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly< T >(N, nex));
  FormalPowerSeries< T > res(N);
  for(int i = 0; i < A.size(); i++) {
    res += dp * A[i];
    dp = nex(dp);
  }
  return res;
}
