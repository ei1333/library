template< typename T >
FormalPowerSeries< T > berlekamp_massey(const FormalPowerSeries< T > &s) {
  const int N = (int) s.size();
  FormalPowerSeries< T > B(N), C(N);
  B[0] = C[0] = T(1);
  int L = 0, m = 1;
  T b{1};
  for(int n = 0; n < N; n++) {
    T d = s[n];
    for(int i = 1; i <= L; i++) d += C[i] * s[n - i];
    T inv_b = d / b;
    if(d == 0) {
      m++;
    } else if(2 * L <= n) {
      auto temp = C;
      for(int i = 0; i + m < N; i++) C[i + m] -= B[i] * inv_b;
      L = n + 1 - L;
      B = temp;
      b = d;
      m = 1;
    } else {
      for(int i = 0; i + m < N; i++) C[i + m] -= B[i] * inv_b;
      m++;
    }
  }
  C.resize(L + 1);
  reverse(C.begin(), C.end());
  assert(L < N - 1);
  return C;
}
