#pragma once
#include "formal-power-series.cpp"
#include "diff.cpp"
#include "log.cpp"

/**
 * @brief Exp ($e^{f(x)}$)
 * @docs docs/exp.md
 */
template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::exp_fast(int deg) const {
  if(deg == -1) deg = this->size();
  assert((*this)[0] == T(0));

  P inv;
  inv.reserve(deg + 1);
  inv.push_back(T(0));
  inv.push_back(T(1));

  auto inplace_integral = [&](P &F) -> void {
    const int n = (int) F.size();
    auto mod = T::get_mod();
    while((int) inv.size() <= n) {
      int i = inv.size();
      inv.push_back((-inv[mod % i]) * (mod / i));
    }
    F.insert(begin(F), T(0));
    for(int i = 1; i <= n; i++) F[i] *= inv[i];
  };

  auto inplace_diff = [](P &F) -> void {
    if(F.empty()) return;
    F.erase(begin(F));
    T coeff = 1, one = 1;
    for(int i = 0; i < (int) F.size(); i++) {
      F[i] *= coeff;
      coeff += one;
    }
  };

  P b{1, 1 < (int) this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
  for(int m = 2; m < deg; m *= 2) {
    auto y = b;
    y.resize(2 * m);
    get_fft()(y);
    z1 = z2;
    P z(m);
    for(int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
    get_ifft()(z);
    fill(begin(z), begin(z) + m / 2, T(0));
    get_fft()(z);
    for(int i = 0; i < m; ++i) z[i] *= -z1[i];
    get_ifft()(z);
    c.insert(end(c), begin(z) + m / 2, end(z));
    z2 = c;
    z2.resize(2 * m);
    get_fft()(z2);
    P x(begin(*this), begin(*this) + min< int >(this->size(), m));
    inplace_diff(x);
    x.push_back(T(0));
    get_fft()(x);
    for(int i = 0; i < m; ++i) x[i] *= y[i];
    get_ifft()(x);
    x -= b.diff();
    x.resize(2 * m);
    for(int i = 0; i < m - 1; ++i) x[m + i] = x[i], x[i] = T(0);
    get_fft()(x);
    for(int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
    get_ifft()(x);
    x.pop_back();
    inplace_integral(x);
    for(int i = m; i < min< int >(this->size(), 2 * m); ++i) x[i] += (*this)[i];
    fill(begin(x), begin(x) + m, T(0));
    get_fft()(x);
    for(int i = 0; i < 2 * m; ++i) x[i] *= y[i];
    get_ifft()(x);
    b.insert(end(b), begin(x) + m, end(x));
  }
  return P{begin(b), begin(b) + deg};
}

template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::exp(int deg) const {
  assert((*this)[0] == T(0));
  const int n = (int) this->size();
  if(deg == -1) deg = n;
  if(get_fft() != nullptr) {
    P ret(*this);
    ret.resize(deg, T(0));
    return ret.exp_fast(deg);
  }
  P ret({T(1)});
  for(int i = 1; i < deg; i <<= 1) {
    ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
  }
  return ret.pre(deg);
}
