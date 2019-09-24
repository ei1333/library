template< typename T >
FormalPowerSeries< T > bell_number(int N) {
  FormalPowerSeries< T > po(N + 1), ret(N + 1);
  po[1] = 1;
  po = po.exp();
  po[0] -= 1;
  po = po.exp();
  T mul = 1;
  for(int i = 0; i <= N; i++) {
    ret[i] = po[i] * mul;
    mul *= i + 1;
  }
  return ret;
}
