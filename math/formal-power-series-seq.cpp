template< typename T >
FormalPowerSeries< T > bernoulli(int N) {
  FormalPowerSeries< T > poly(N + 1);
  poly[0] = T(1);
  for(int i = 1; i <= N; i++) {
    poly[i] = poly[i - 1] / T(i + 1);
  }
  poly = poly.inv();
  T tmp(1);
  for(int i = 1; i <= N; i++) {
    tmp *= T(i);
    poly[i] *= tmp;
  }
  return poly;
}

template< typename T >
FormalPowerSeries< T > partition(int N) {
  FormalPowerSeries< T > poly(N + 1);
  poly[0] = 1;
  for(int k = 1; k <= N; k++) {
    if(1LL * k * (3 * k + 1) / 2 <= N) poly[k * (3 * k + 1) / 2] += (k % 2 ? -1 : 1);
    if(1LL * k * (3 * k - 1) / 2 <= N) poly[k * (3 * k - 1) / 2] += (k % 2 ? -1 : 1);
  }
  return poly.inv();
}

template< typename T >
FormalPowerSeries< T > bell(int N) {
  FormalPowerSeries< T > poly(N + 1), ret(N + 1);
  poly[1] = 1;
  poly = poly.exp();
  poly[0] -= 1;
  poly = poly.exp();
  T mul = 1;
  for(int i = 0; i <= N; i++) {
    ret[i] = poly[i] * mul;
    mul *= i + 1;
  }
  return ret;
}

template< typename T >
FormalPowerSeries< T > stirling_first(int N) {
  if(N == 0) return {1};
  int M = N / 2;
  FormalPowerSeries< T > A = stirling_first< T >(M), B, C(N - M + 1);

  if(N % 2 == 0) {
    B = A;
  } else {
    B.resize(M + 2);
    B[M + 1] = 1;
    for(int i = 1; i < M + 1; i++) B[i] = A[i - 1] + A[i] * M;
  }

  T tmp = 1;
  for(int i = 0; i <= N - M; i++) {
    C[N - M - i] = T(M).pow(i) / tmp;
    B[i] *= tmp;
    tmp *= T(i + 1);
  }
  C *= B;
  tmp = 1;
  for(int i = 0; i <= N - M; i++) {
    B[i] = C[N - M + i] / tmp;
    tmp *= T(i + 1);
  }
  return A * B;
}

template< typename T >
FormalPowerSeries< T > stirling_second(int N) {
  FormalPowerSeries< T > A(N + 1), B(N + 1);
  modint tmp = 1;
  for(int i = 0; i <= N; i++) {
    T rev = T(1) / tmp;
    A[i] = T(i).pow(N) * rev;
    B[i] = T(1) * rev;
    if(i & 1) B[i] *= -1;
    tmp *= i + 1;
  }
  return (A * B).pre(N + 1);
}

template< typename T >
FormalPowerSeries< T > stirling_second_kth_column(int N, int K) {
  FormalPowerSeries< T > poly(N + 1), ret(N + 1);
  poly[1] = 1;
  poly = poly.exp();
  poly[0] -= 1;
  poly = poly.pow(K);
  T rev = 1, mul = 1;
  for(int i = 2; i <= K; i++) rev *= i;
  rev = T(1) / rev;
  poly *= rev;
  for(int i = 0; i <= N; i++) {
    ret[i] = poly[i] * mul;
    mul *= i + 1;
  }
  return ret;
}

template< typename T >
FormalPowerSeries< T > eulerian(int N) {
  vector< T > fact(N + 2), rfact(N + 2);
  fact[0] = rfact[N + 1] = 1;
  for(int i = 1; i <= N + 1; i++) fact[i] = fact[i - 1] * i;
  rfact[N + 1] /= fact[N + 1];
  for(int i = N; i >= 0; i--) rfact[i] = rfact[i + 1] * (i + 1);

  FormalPowerSeries< T > A(N + 1), B(N + 1);
  for(int i = 0; i <= N; i++) {
    A[i] = fact[N + 1] * rfact[i] * rfact[N + 1 - i];
    if(i & 1) A[i] *= -1;
    B[i] = T(i + 1).pow(N);
  }
  return (A * B).pre(N + 1);
}
