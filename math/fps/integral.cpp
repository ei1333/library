#pragma once
#include "formal-power-series.cpp"

/**
 * @brief Integral $\int f(x) dx$
 */
template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::integral() const {
  const int n = (int) this->size();
  P ret(n + 1);
  ret[0] = T(0);
  for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
  return ret;
}
