/**
 * @brief Euler's Phi(オイラーのφ関数)
 * 
 */
template< typename T >
T euler_phi(T n) {
  T ret = n;
  for(T i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      ret -= ret / i;
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) ret -= ret / n;
  return ret;
}
