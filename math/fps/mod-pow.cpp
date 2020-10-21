#pragma once
#include "formal-power-series.cpp"
#include "inv.cpp"

/**
 * @brief Mod-Pow ($f(x)^k \bmod g$)
 */
template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::mod_pow(int64_t k, P g) const {
  P modinv = g.rev().inv();
  auto get_div = [&](P base) {
    if(base.size() < g.size()) {
      base.clear();
      return base;
    }
    int n = base.size() - g.size() + 1;
    return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
  };
  P x(*this), ret{1};
  while(k > 0) {
    if(k & 1) {
      ret *= x;
      ret -= get_div(ret) * g;
    }
    x *= x;
    x -= get_div(x) * g;
    k >>= 1;
  }
  return ret;
}
