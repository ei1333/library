#include "enumeration.hpp"

/**
 * @brief Bell Number(ベル数)
 * 
 */
template< typename T >
T bell_number(int n, int k) {
  if(n == 0) return 1;
  k = min(k, n);
  Enumeration< T > uku(k);
  T ret = 0;
  vector< T > pref(k + 1);
  pref[0] = 1;
  for(int i = 1; i <= k; i++) {
    if(i & 1) pref[i] = pref[i - 1] - uku.finv(i);
    else pref[i] = pref[i - 1] + uku.finv(i);
  }
  for(int i = 1; i <= k; i++) {
    ret += T(i).pow(n) * uku.finv(i) * pref[k - i];
  }
  return ret;
}
