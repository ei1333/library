#pragma once
#include "formal-power-series.cpp"
#include "exp.cpp"

/**
 * @brief Pow ($f(x)^k$)
 */
P pow(int64_t k, int deg = -1) const {
  const int n = (int) this->size();
  if(deg == -1) deg = n;
  for(int i = 0; i < n; i++) {
    if((*this)[i] != T(0)) {
      T rev = T(1) / (*this)[i];
      P ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
      if(i * k > deg) return P(deg, T(0));
      ret = (ret << (i * k)).pre(deg);
      if(ret.size() < deg) ret.resize(deg, T(0));
      return ret;
    }
  }
  return *this;
}
