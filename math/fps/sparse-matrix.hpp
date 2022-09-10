template< typename T >
using FPSGraph = vector< vector< pair< int, T > > >;

template< typename T >
FormalPowerSeries< T > random_poly(int n) {
  mt19937 mt(1333333);
  FormalPowerSeries< T > res(n);
  uniform_int_distribution< int > rand(0, T::get_mod() - 1);
  for(int i = 0; i < n; i++) res[i] = rand(mt);
  return res;
}

template< typename T >
FormalPowerSeries< T > next_poly(const FormalPowerSeries< T > &dp, const FPSGraph< T > &g) {
  const int N = (int) dp.size();
  FormalPowerSeries< T > nxt(N);
  for(int i = 0; i < N; i++) {
    for(auto &p : g[i]) nxt[p.first] += p.second * dp[i];
  }
  return nxt;
}

template< typename T >
FormalPowerSeries< T > minimum_poly(const FPSGraph< T > &g) {
  const int N = (int) g.size();
  auto dp = random_poly< T >(N), u = random_poly< T >(N);
  FormalPowerSeries< T > f(2 * N);
  for(int i = 0; i < 2 * N; i++) {
    for(auto &p : u.dot(dp)) f[i] += p;
    dp = next_poly(dp, g);
  }
  return berlekamp_massey(f);
}

/* O(N(N+S) + N log N log Q) (O(S): time complexity of nex) */
template< typename T >
FormalPowerSeries< T > sparse_pow(int64_t Q, FormalPowerSeries< T > dp, const FPSGraph< T > &g) {
  const int N = (int) dp.size();
  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly(g));
  FormalPowerSeries< T > res(N);
  for(int i = 0; i < A.size(); i++) {
    res += dp * A[i];
    dp = next_poly(dp, g);
  }
  return res;
}

/* O(N(N+S)) (S: none-zero elements)*/
template< typename T >
T sparse_determinant(FPSGraph< T > g) {
  using FPS = FormalPowerSeries< T >;
  int N = (int) g.size();
  auto C = random_poly< T >(N);
  for(int i = 0; i < N; i++) for(auto &p : g[i]) p.second *= C[i];
  auto u = minimum_poly(g);
  T acdet = u[0];
  if(N % 2 == 0) acdet *= -1;
  T cdet = 1;
  for(int i = 0; i < N; i++) cdet *= C[i];
  return acdet / cdet;
}
