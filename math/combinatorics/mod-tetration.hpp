#include "mod-pow.hpp"
#include "../number-theory/euler-phi.hpp"

/**
 * @brief Mod Tetration(テトレーション)
 * 
 */
template< typename T >
T mod_tetration(const T &a, const T &b, const T &m) {
  if(m == 1) return 0;
  if(a == 0) return !(b & 1);
  if(b == 0) return 1;
  if(b == 1) return a % m;
  if(b == 2) return mod_pow(a, a, m);
  auto phi = euler_phi(m);
  auto tmp = mod_tetration(a, b - 1, phi);
  if(tmp == 0) tmp += phi;
  return mod_pow(a, tmp, m);
}
