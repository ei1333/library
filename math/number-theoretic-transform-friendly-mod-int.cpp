template< typename Mint >
struct NumberTheoreticTransformFriendlyModInt {

  vector< int > rev;
  vector< Mint > rts;
  int base, max_base;
  Mint root;

  NumberTheoreticTransformFriendlyModInt() : base(1), rev{0, 1}, rts{0, 1} {
    const int mod = Mint::get_mod();
    assert(mod >= 3 && mod % 2 == 1);
    auto tmp = mod - 1;
    max_base = 0;
    while(tmp % 2 == 0) tmp >>= 1, max_base++;
    root = 2;
    while(root.pow((mod - 1) >> 1) == 1) root += 1;
    assert(root.pow(mod - 1) == 1);
    root = root.pow((mod - 1) >> max_base);
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
      Mint z = root.pow(1 << (max_base - 1 - base));
      for(int i = 1 << (base - 1); i < (1 << base); i++) {
        rts[i << 1] = rts[i];
        rts[(i << 1) + 1] = rts[i] * z;
      }
      ++base;
    }
  }


  void ntt(vector< Mint > &a) {
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
          Mint z = a[i + j + k] * rts[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
  }


  void intt(vector< Mint > &a) {
    reverse(a.begin() + 1, a.end());
    ntt(a);
  }

  vector< Mint > multiply(vector< Mint > a, vector< Mint > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    Mint inv_sz = Mint(1) / sz;
    for(int i = 0; i < sz; i++) {
      a[i] *= b[i] * inv_sz;
    }
    intt(a);
    a.resize(need);
    return a;
  }
};
