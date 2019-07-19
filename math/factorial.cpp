template< typename T >
T factorial(int64_t n) {
  if(n >= T::get_mod()) return 0;
  if(n == 0) return 1;
 
  const int64_t sn = sqrt(n);
  const T sn_inv = T(1) / sn;
 
  Combination< modint > comb(sn);
  using P = vector< T >;
  ArbitraryModConvolution< modint > fft;
 
  auto shift = [&](const P &f, T dx) {
    int n = (int) f.size();
    T a = dx * sn_inv;
    auto p1 = P(f);
    for(int i = 0; i < n; i++) {
      T d = comb.rfact(i) * comb.rfact((n - 1) - i);
      if(((n - 1 - i) & 1)) d = -d;
      p1[i] *= d;
    }
    auto p2 = P(2 * n);
    for(int i = 0; i < p2.size(); i++) {
      p2[i] = (a.x + i - n) <= 0 ? 1 : a + i - n;
    }
    for(int i = 1; i < p2.size(); i++) {
      p2[i] *= p2[i - 1];
    }
    T prod = p2[2 * n - 1];
    T prod_inv = T(1) / prod;
    for(int i = 2 * n - 1; i > 0; --i) {
      p2[i] = prod_inv * p2[i - 1];
      prod_inv *= a + i - n;
    }
    p2[0] = prod_inv;
    auto p3 = fft.multiply(p1, p2, (int) p2.size());
    p1 = P(p3.begin() + p1.size(), p3.begin() + p2.size());
    prod = 1;
    for(int i = 0; i < n; i++) {
      prod *= a + n - 1 - i;
    }
    for(int i = n - 1; i >= 0; --i) {
      p1[i] *= prod;
      prod *= p2[n + i] * (a + i - n);
    }
    return p1;
  };
  function< P(int) > rec = [&](int64_t n) {
    if(n == 1) return P({1, 1 + sn});
    int64_t nh = n >> 1;
    auto a1 = rec(nh);
    auto a2 = shift(a1, nh);
    auto b1 = shift(a1, sn * nh);
    auto b2 = shift(a1, sn * nh + nh);
    for(int i = 0; i <= nh; i++) a1[i] *= a2[i];
    for(int i = 1; i <= nh; i++) a1.emplace_back(b1[i] * b2[i]);
    if(n & 1) {
      for(int64_t i = 0; i < n; i++) {
        a1[i] *= n + 1LL * sn * i;
      }
      T prod = 1;
      for(int64_t i = 1LL * n * sn; i < 1LL * n * sn + n; i++) {
        prod *= (i + 1);
      }
      a1.push_back(prod);
    }
    return a1;
  };
  auto vs = rec(sn);
  T ret = 1;
  for(int64_t i = 0; i < sn; i++) ret *= vs[i];
  for(int64_t i = 1LL * sn * sn + 1; i <= n; i++) ret *= i;
  return ret;
}
