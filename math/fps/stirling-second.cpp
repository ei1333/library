#pragma once
#include "formal-power-series.cpp"

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
