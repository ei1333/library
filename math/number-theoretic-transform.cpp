template< int mod, int primitiveroot >
struct NumberTheoreticTransform {
  vector< vector< int > > rts, rrts;

  void ensure_base(int N) {
    if(rts.size() >= N) return;
    rts.resize(N), rrts.resize(N);
    for(int i = 1; i < N; i <<= 1) {
      if(rts[i].size()) continue;
      int w = mod_pow(primitiveroot, (mod - 1) / (i * 2));
      int rw = inverse(w);
      rts[i].resize(i), rrts[i].resize(i);
      rts[i][0] = 1, rrts[i][0] = 1;
      for(int k = 1; k < i; k++) {
        rts[i][k] = mul(rts[i][k - 1], w);
        rrts[i][k] = mul(rrts[i][k - 1], rw);
      }
    }
  }

  inline int mod_pow(int x, int n) {
    int ret = 1;
    while(n > 0) {
      if(n & 1) ret = mul(ret, x);
      x = mul(x, x);
      n >>= 1;
    }
    return ret;
  }

  inline int inverse(int x) {
    return mod_pow(x, mod - 2);
  }

  inline unsigned add(unsigned x, unsigned y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
  }

  inline unsigned mul(unsigned a, unsigned b) {
    return 1ull * a * b % mod;
  }

  void ntt(vector< int > &a, bool rev) {
    const int N = (int) a.size();
    ensure_base(N);
    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(a[i], a[j]);
    }
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = a[j + k], t = mul(a[j + k + i], rev ? rrts[i][k] : rts[i][k]);
          a[j + k] = add(s, t), a[j + k + i] = add(s, mod - t);
        }
      }
    }
    if(rev) {
      int temp = inverse(N);
      for(int i = 0; i < N; i++) a[i] = mul(a[i], temp);
    }
  }

  vector< int > multiply(vector< int > a, vector< int > b) {
    int need = a.size() + b.size() - 1;
    int sz = 1;
    while(sz < need) sz <<= 1;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < sz; i++) a[i] = mul(a[i], b[i]);
    ntt(a, true);
    a.resize(need);
    return a;
  }
};
