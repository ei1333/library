#pragma once
#include "formal-power-series.cpp"

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
