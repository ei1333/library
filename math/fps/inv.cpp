#pragma once
#include "formal-power-series.cpp"

/**
 * @brief Inv ($\frac {1} {f(x)}$)
 */
template< typename T >
typename FormalPowerSeries< T > FormalPowerSeries< T >::inv_fast() const {
  assert(((*this)[0]) != T(0));

  const int n = (int) this->size();
  P res{T(1) / (*this)[0]};

  for(int d = 1; d < n; d <<= 1) {
    P f(2 * d), g(2 * d);
    for(int j = 0; j < min(n, 2 * d); j++) f[j] = (*this)[j];
    for(int j = 0; j < d; j++) g[j] = res[j];
    get_fft()(f);
    get_fft()(g);
    for(int j = 0; j < 2 * d; j++) f[j] *= g[j];
    get_ifft()(f);
    for(int j = 0; j < d; j++) {
      f[j] = 0;
      f[j + d] = -f[j + d];
    }
    get_fft()(f);
    for(int j = 0; j < 2 * d; j++) f[j] *= g[j];
    get_ifft()(f);
    for(int j = 0; j < d; j++) f[j] = res[j];
    res = f;
  }
  return res.pre(n);
}

template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::inv(int deg) const {
  assert(((*this)[0]) != T(0));
  const int n = (int) this->size();
  if(deg == -1) deg = n;
  if(get_fft() != nullptr) {
    P ret(*this);
    ret.resize(deg, T(0));
    return ret.inv_fast();
  }
  P ret({T(1) / (*this)[0]});
  for(int i = 1; i < deg; i <<= 1) {
    ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);
  }
  return ret.pre(deg);
}
