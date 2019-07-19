int64_t power(int64_t x, int64_t n, int64_t mod) {
  int64_t ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= mod;
    (x *= x) %= mod;
    n >>= 1;
  }
  return ret;
}
