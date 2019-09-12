template< typename T >
PolynominalMod< T > partition(int N) {
  PolynominalMod< T > po(N + 1);
  po[0] = 1;
  for(int k = 1; k <= N; k++) {
    if(1LL * k * (3 * k + 1) / 2 <= N) po[k * (3 * k + 1) / 2] += (k % 2 ? -1 : 1);
    if(1LL * k * (3 * k - 1) / 2 <= N) po[k * (3 * k - 1) / 2] += (k % 2 ? -1 : 1);
  }
  return po.inverse();
}
