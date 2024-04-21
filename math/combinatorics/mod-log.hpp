/**
 * @brief Mod Log(離散対数問題)
 * 
 */
int64_t mod_log(int64_t a, int64_t b, int64_t p) {
  int64_t g = 1;

  for(int64_t i = p; i; i /= 2) (g *= a) %= p;
  g = __gcd(g, p);

  int64_t t = 1, c = 0;
  for(; t % g; c++) {
    if(t == b) return c;
    (t *= a) %= p;
  }
  if(b % g) return -1;

  t /= g;
  b /= g;

  int64_t n = p / g, h = 0, gs = 1;

  for(; h * h < n; h++) (gs *= a) %= n;

  unordered_map< int64_t, int64_t > bs;
  for(int64_t s = 0, e = b; s < h; bs[e] = ++s) {
    (e *= a) %= n;
  }

  for(int64_t s = 0, e = t; s < n;) {
    (e *= gs) %= n;
    s += h;
    if(bs.count(e)) return c + s - bs[e];
  }
  return -1;
}
