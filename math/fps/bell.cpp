#pragma once
#include "formal-power-series.cpp"
#include "exp.cpp"

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
