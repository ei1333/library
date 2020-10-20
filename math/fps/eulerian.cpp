#pragma once
#include "formal-power-series.cpp"

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
