#pragma once
#include "formal-power-series.cpp"
#include "inv.cpp"

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
