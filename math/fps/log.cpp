#pragma once
#include "formal-power-series.cpp"
#include "diff.cpp"
#include "inv.cpp"
#include "integral.cpp"

/**
 * @brief Log ($\log {f(x)}$)
 */
template< typename T >
typename FormalPowerSeries< T > FormalPowerSeries< T >::log(int deg) const {
  assert((*this)[0] == 1);
  const int n = (int) this->size();
  if(deg == -1) deg = n;
  return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
}
