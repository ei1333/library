#pragma once
#include "formal-power-series.cpp"

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
