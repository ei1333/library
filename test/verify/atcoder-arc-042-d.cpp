int64_t mod_pow(int64_t x, int64_t n, int64_t mod) {
  int64_t ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= mod;
    (x *= x) %= mod;
    n >>= 1;
  }
  return ret;
}

int main() {
  int x, p, a, b;
  cin >> x >> p >> a >> b;

  if(p <= a) {
    int k = a / p;
    a -= k * p;
    b -= k * p;
  }

  if((b - a + 1) <= 10000000) {
    int64_t ret = infll;
    auto tmp = mod_pow(x, a, p);
    for(int i = a; i <= b; i++) {
      ret = min(ret, tmp);
      tmp = tmp * x % p;
    }
    cout << ret << endl;
  } else {
    for(int i = 1;; i++) {
      int tmp = mod_log(x, i, p);
      if((a <= tmp && tmp <= b) || (a <= tmp + p && tmp + p <= b)) {
        cout << i << endl;
        break;
      }
    }
  }
}

