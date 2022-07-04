#include "enumeration.cpp"

/**
 * @brief Sample Point Shift(標本点シフト)
 */
template< typename Mint, typename F >
vector< Mint > sample_point_shift(const vector< Mint > &ys, const Mint &m, const F &multiply) {
  Enumeration< Mint > comb;
  int d = (int) ys.size() - 1;
  vector< Mint > f(d + 1), g(d * 2 + 1);
  for(int i = 0; i <= d; i++) {
    f[i] = ys[i] * comb.finv(i) * comb.finv(d - i);
    if((d - i) & 1) f[i] = -f[i];
  }
  for(int i = 0; i <= 2 * d; i++) {
    g[i] = Mint(1) / (m - d + i);
  }
  auto h = multiply(f, g);
  Mint coef = 1;
  for(int i = 0; i <= d; i++) {
    coef *= (m - d + i);
  }
  for(int i = 0; i <= d; i++) {
    h[i + d] *= coef;
    coef *= (m + i + 1) * g[i];
  }
  return vector< Mint >{begin(h) + d, begin(h) + 2 * d + 1};
}
