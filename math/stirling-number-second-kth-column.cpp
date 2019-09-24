template< typename T >
FormalPowerSeries< T > stirling_number_second_kth_column(int N, int K) {
  FormalPowerSeries< T > po(N + 1), ret(N + 1);
  po[1] = 1;
  po = po.exp();
  po[0] -= 1;
  po = po.pow(K);
  T rev = 1, mul = 1;
  for(int i = 2; i <= K; i++) rev *= i;
  rev = T(1) / rev;
  po *= rev;
  for(int i = 0; i <= N; i++) {
    ret[i] = po[i] * mul;
    mul *= i + 1;
  }
  return ret;
}
