#pragma once
#include "formal-power-series.cpp"
#include "inv.cpp"

/**
 * @brief Sqrt ($\sqrt {f(x)}$)
 */
template< typename T >
typename FormalPowerSeries< T > FormalPowerSeries< T >::sqrt(int deg) const {
  const int n = (int) this->size();
  if(deg == -1) deg = n;
  if((*this)[0] == T(0)) {
    for(int i = 1; i < n; i++) {
      if((*this)[i] != T(0)) {
        if(i & 1) return {};
        if(deg - i / 2 <= 0) break;
        auto ret = (*this >> i).sqrt(deg - i / 2);
        if(ret.empty()) return {};
        ret = ret << (i / 2);
        if(ret.size() < deg) ret.resize(deg, T(0));
        return ret;
      }
    }
    return P(deg, 0);
  }

  P ret;
  if(get_sqrt() == nullptr) {
    assert((*this)[0] == T(1));
    ret = {T(1)};
  } else {
    auto sqr = get_sqrt()((*this)[0]);
    if(sqr * sqr != (*this)[0]) return {};
    ret = {T(sqr)};
  }

  T inv2 = T(1) / T(2);
  for(int i = 1; i < deg; i <<= 1) {
    ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
  }
  return ret.pre(deg);
}
