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

/* 行列累乗: nexの計算量をO(S)として O(N(N+S) + N log N log Q) */
template< typename T, typename F >
FormalPowerSeries< T > sparse_pow(int64_t Q, FormalPowerSeries< modint > dp, const F &nex) {
  const int N = (int)dp.size();
  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly< T >(N, nex));
  FormalPowerSeries< T > res(N);
  for(int i = 0; i < A.size(); i++) {
    res += dp * A[i];
    dp = nex(dp);
  }
  return res;
}

/* 行列式: 非0の要素をS個として O(N(N+S)) */
template< typename T >
T sparse_determinant(const vector< vector< pair< int, T > > > &g) {
  using FPS = FormalPowerSeries< T >;
  int N = (int) g.size();
  auto C = random_poly< T >(N), L = random_poly< T >(N), R = random_poly< T >(N);
  auto nex = [&](FPS dp) {
    for(int i = 0; i < N; i++) dp[i] *= C[i];
    FPS nxt(N);
    for(int i = 0; i < N; i++) {
      for(auto &e : g[i]) nxt[i] += dp[e.first] * e.second;
    }
    return nxt;
  };
  auto u = minimum_poly< T >(N, nex);
  T acdet = u[0];
  if(N % 2 == 0) acdet *= -1;
  T cdet = 1;
  for(int i = 0; i < N; i++) cdet *= C[i];
  return acdet / cdet;
}
