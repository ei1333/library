#pragma once
#include "formal-power-series.cpp"

/**
 * @brief Diff ($f'(x)$)
 * @docs docs/diff.md
 */
template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::diff() const {
  const int n = (int) this->size();
  P ret(max(0, n - 1));
  for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
  return ret;
}
