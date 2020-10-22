#include "formal-power-series.cpp"

/**
 * @brief Taylor-Shift ($f(x) \Rightarrow f(x + c)$)
 */
template< typename T >
typename FormalPowerSeries< T >::P FormalPowerSeries< T >::taylor_shift(T c) const {
  int n = (int) this->size();
  vector< T > fact(n), rfact(n);
  fact[0] = rfact[0] = T(1);
  for(int i = 1; i < n; i++) fact[i] = fact[i - 1] * T(i);
  rfact[n - 1] = T(1) / fact[n - 1];
  for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);
  P p(*this);
  for(int i = 0; i < n; i++) p[i] *= fact[i];
  p = p.rev();
  P bs(n, T(1));
  for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];
  p = (p * bs).pre(n);
  p = p.rev();
  for(int i = 0; i < n; i++) p[i] *= rfact[i];
  return p;
}
