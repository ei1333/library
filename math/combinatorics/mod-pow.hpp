/**
 * @brief Mod Pow(べき乗)
 * @docs docs/mod-pow.md
 */
template< typename T >
T mod_pow(T x, int64_t n, const T &p) {
  T ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= p;
    (x *= x) %= p;
    n >>= 1;
  }
  return ret % p;
}
