template< int mod >
struct NumberTheoreticTransform {

  vector< int > rev, rts;
  int base, max_base, root;

  NumberTheoreticTransform() : base(1), rev{0, 1}, rts{0, 1} {
    assert(mod >= 3 && mod % 2 == 1);
    auto tmp = mod - 1;
    max_base = 0;
    while(tmp % 2 == 0) tmp >>= 1, max_base++;
    root = 2;
    while(mod_pow(root, (mod - 1) >> 1) == 1) ++root;
    assert(mod_pow(root, mod - 1) == 1);
    root = mod_pow(root, (mod - 1) >> max_base);
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
    return 1ull * a * b % (unsigned long long) mod;
  }

  void ensure_base(int nbase) {
    if(nbase <= base) return;
    rev.resize(1 << nbase);
    rts.resize(1 << nbase);
    for(int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    assert(nbase <= max_base);
    while(base < nbase) {
      int z = mod_pow(root, 1 << (max_base - 1 - base));
      for(int i = 1 << (base - 1); i < (1 << base); i++) {
        rts[i << 1] = rts[i];
        rts[(i << 1) + 1] = mul(rts[i], z);
      }
      ++base;
    }
  }

  void ntt(vector< int > &a) {
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for(int i = 0; i < n; i++) {
      if(i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for(int k = 1; k < n; k <<= 1) {
      for(int i = 0; i < n; i += 2 * k) {
        for(int j = 0; j < k; j++) {
          int z = mul(a[i + j + k], rts[j + k]);
          a[i + j + k] = add(a[i + j], mod - z);
          a[i + j] = add(a[i + j], z);
        }
      }
    }
  }

  vector< int > multiply(vector< int > a, vector< int > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    int inv_sz = inverse(sz);
    for(int i = 0; i < sz; i++) {
      a[i] = mul(a[i], mul(b[i], inv_sz));
    }
    reverse(a.begin() + 1, a.end());
    ntt(a);
    a.resize(need);
    return a;
  }
};
