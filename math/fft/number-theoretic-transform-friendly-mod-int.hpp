/**
 * @brief Number Theoretic Transform Friendly ModInt
 */
template< typename Mint >
struct NumberTheoreticTransformFriendlyModInt {

  static vector< Mint > roots, iroots, rate3, irate3;
  static int max_base;

  NumberTheoreticTransformFriendlyModInt() = default;

  static void init() {
    if(roots.empty()) {
      const unsigned mod = Mint::get_mod();
      assert(mod >= 3 && mod % 2 == 1);
      auto tmp = mod - 1;
      max_base = 0;
      while(tmp % 2 == 0) tmp >>= 1, max_base++;
      Mint root = 2;
      while(root.pow((mod - 1) >> 1) == 1) {
        root += 1;
      }
      assert(root.pow(mod - 1) == 1);

      roots.resize(max_base + 1);
      iroots.resize(max_base + 1);
      rate3.resize(max_base + 1);
      irate3.resize(max_base + 1);

      roots[max_base] = root.pow((mod - 1) >> max_base);
      iroots[max_base] = Mint(1) / roots[max_base];
      for(int i = max_base - 1; i >= 0; i--) {
        roots[i] = roots[i + 1] * roots[i + 1];
        iroots[i] = iroots[i + 1] * iroots[i + 1];
      }
      {
        Mint prod = 1, iprod = 1;
        for(int i = 0; i <= max_base - 3; i++) {
          rate3[i] = roots[i + 3] * prod;
          irate3[i] = iroots[i + 3] * iprod;
          prod *= iroots[i + 3];
          iprod *= roots[i + 3];
        }
      }
    }
  }

  static void ntt(vector< Mint > &a) {
    init();
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int h = __builtin_ctz(n);
    assert(h <= max_base);
    int len = 0;
    Mint imag = roots[2];
    if(h & 1) {
      int p = 1 << (h - 1);
      Mint rot = 1;
      for(int i = 0; i < p; i++) {
        auto r = a[i + p];
        a[i + p] = a[i] - r;
        a[i] += r;
      }
      len++;
    }
    for(; len + 1 < h; len += 2) {
      int p = 1 << (h - len - 2);
      { // s = 0
        for(int i = 0; i < p; i++) {
          auto a0 = a[i];
          auto a1 = a[i + p];
          auto a2 = a[i + 2 * p];
          auto a3 = a[i + 3 * p];
          auto a1na3imag = (a1 - a3) * imag;
          auto a0a2 = a0 + a2;
          auto a1a3 = a1 + a3;
          auto a0na2 = a0 - a2;
          a[i] = a0a2 + a1a3;
          a[i + 1 * p] = a0a2 - a1a3;
          a[i + 2 * p] = a0na2 + a1na3imag;
          a[i + 3 * p] = a0na2 - a1na3imag;
        }
      }
      Mint rot = rate3[0];
      for(int s = 1; s < (1 << len); s++) {
        int offset = s << (h - len);
        Mint rot2 = rot * rot;
        Mint rot3 = rot2 * rot;
        for(int i = 0; i < p; i++) {
          auto a0 = a[i + offset];
          auto a1 = a[i + offset + p] * rot;
          auto a2 = a[i + offset + 2 * p] * rot2;
          auto a3 = a[i + offset + 3 * p] * rot3;
          auto a1na3imag = (a1 - a3) * imag;
          auto a0a2 = a0 + a2;
          auto a1a3 = a1 + a3;
          auto a0na2 = a0 - a2;
          a[i + offset] = a0a2 + a1a3;
          a[i + offset + 1 * p] = a0a2 - a1a3;
          a[i + offset + 2 * p] = a0na2 + a1na3imag;
          a[i + offset + 3 * p] = a0na2 - a1na3imag;
        }
        rot *= rate3[__builtin_ctz(~s)];
      }
    }
  }

  static void intt(vector< Mint > &a, bool f = true) {
    init();
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int h = __builtin_ctz(n);
    assert(h <= max_base);
    int len = h;
    Mint iimag = iroots[2];
    for(; len > 1; len -= 2) {
      int p = 1 << (h - len);
      { // s = 0
        for(int i = 0; i < p; i++) {
          auto a0 = a[i];
          auto a1 = a[i + 1 * p];
          auto a2 = a[i + 2 * p];
          auto a3 = a[i + 3 * p];
          auto a2na3iimag = (a2 - a3) * iimag;
          auto a0na1 = a0 - a1;
          auto a0a1 = a0 + a1;
          auto a2a3 = a2 + a3;
          a[i] = a0a1 + a2a3;
          a[i + 1 * p] = (a0na1 + a2na3iimag);
          a[i + 2 * p] = (a0a1 - a2a3);
          a[i + 3 * p] = (a0na1 - a2na3iimag);
        }
      }
      Mint irot = irate3[0];
      for(int s = 1; s < (1 << (len - 2)); s++) {
        int offset = s << (h - len + 2);
        Mint irot2 = irot * irot;
        Mint irot3 = irot2 * irot;
        for(int i = 0; i < p; i++) {
          auto a0 = a[i + offset];
          auto a1 = a[i + offset + 1 * p];
          auto a2 = a[i + offset + 2 * p];
          auto a3 = a[i + offset + 3 * p];
          auto a2na3iimag = (a2 - a3) * iimag;
          auto a0na1 = a0 - a1;
          auto a0a1 = a0 + a1;
          auto a2a3 = a2 + a3;
          a[i + offset] = a0a1 + a2a3;
          a[i + offset + 1 * p] = (a0na1 + a2na3iimag) * irot;
          a[i + offset + 2 * p] = (a0a1 - a2a3) * irot2;
          a[i + offset + 3 * p] = (a0na1 - a2na3iimag) * irot3;
        }
        irot *= irate3[__builtin_ctz(~s)];
      }
    }
    if(len >= 1) {
      int p = 1 << (h - 1);
      for(int i = 0; i < p; i++) {
        auto ajp = a[i] - a[i + p];
        a[i] += a[i + p];
        a[i + p] = ajp;
      }
    }
    if(f) {
      Mint inv_sz = Mint(1) / n;
      for(int i = 0; i < n; i++) a[i] *= inv_sz;
    }
  }

  static vector< Mint > multiply(vector< Mint > a, vector< Mint > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    Mint inv_sz = Mint(1) / sz;
    for(int i = 0; i < sz; i++) a[i] *= b[i] * inv_sz;
    intt(a, false);
    a.resize(need);
    return a;
  }
};

template< typename Mint >
vector< Mint > NumberTheoreticTransformFriendlyModInt< Mint >::roots = vector< Mint >();
template< typename Mint >
vector< Mint > NumberTheoreticTransformFriendlyModInt< Mint >::iroots = vector< Mint >();
template< typename Mint >
vector< Mint > NumberTheoreticTransformFriendlyModInt< Mint >::rate3 = vector< Mint >();
template< typename Mint >
vector< Mint > NumberTheoreticTransformFriendlyModInt< Mint >::irate3 = vector< Mint >();
template< typename Mint >
int NumberTheoreticTransformFriendlyModInt< Mint >::max_base = 0;
