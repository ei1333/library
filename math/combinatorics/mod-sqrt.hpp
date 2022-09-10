/**
 * @brief Mod Sqrt
 */
template< typename T >
T mod_sqrt(const T &a, const T &p) {
  if(a == 0) return 0;
  if(p == 2) return a;
  if(mod_pow(a, (p - 1) >> 1, p) != 1) return -1;
  T b = 1;
  while(mod_pow(b, (p - 1) >> 1, p) == 1) ++b;
  T e = 0, m = p - 1;
  while(m % 2 == 0) m >>= 1, ++e;
  T x = mod_pow(a, (m - 1) >> 1, p);
  T y = a * (x * x % p) % p;
  (x *= a) %= p;
  T z = mod_pow(b, m, p);
  while(y != 1) {
    T j = 0, t = y;
    while(t != 1) {
      j += 1;
      (t *= t) %= p;
    }
    z = mod_pow(z, T(1) << (e - j - 1), p);
    (x *= z) %= p;
    (z *= z) %= p;
    (y *= z) %= p;
    e = j;
  }
  return x;
}
