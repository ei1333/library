#pragma once
#include "formal-power-series.cpp"
#include "inv.cpp"

template< typename T >
FormalPowerSeries< T > bellnoulli(int N) {
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
