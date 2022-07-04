#include "../fft/number-theoretic-transform-friendly-mod-int.cpp"

/**
 * @brief Formal Power Series Friendly NTT(NTTmod用形式的冪級数)
 * @docs docs/formal-power-series-friendly-ntt.md
 */
template< typename T >
struct FormalPowerSeriesFriendlyNTT : vector< T > {
  using vector< T >::vector;
  using P = FormalPowerSeriesFriendlyNTT;
  using NTT = NumberTheoreticTransformFriendlyModInt< T >;

  P pre(int deg) const {
    return P(begin(*this), begin(*this) + min((int) this->size(), deg));
  }

  P rev(int deg = -1) const {
    P ret(*this);
    if(deg != -1) ret.resize(deg, T(0));
    reverse(begin(ret), end(ret));
    return ret;
  }

  void shrink() {
    while(this->size() && this->back() == T(0)) this->pop_back();
  }

  P operator+(const P &r) const { return P(*this) += r; }

  P operator+(const T &v) const { return P(*this) += v; }

  P operator-(const P &r) const { return P(*this) -= r; }

  P operator-(const T &v) const { return P(*this) -= v; }

  P operator*(const P &r) const { return P(*this) *= r; }

  P operator*(const T &v) const { return P(*this) *= v; }

  P operator/(const P &r) const { return P(*this) /= r; }

  P operator%(const P &r) const { return P(*this) %= r; }

  P &operator+=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < (int) r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  P &operator-=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < (int) r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  // https://judge.yosupo.jp/problem/convolution_mod
  P &operator*=(const P &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    auto ret = NTT::multiply(*this, r);
    return *this = {begin(ret), end(ret)};
  }

  P &operator/=(const P &r) {
    if(this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }

  P &operator%=(const P &r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }

  // https://judge.yosupo.jp/problem/division_of_polynomials
  pair< P, P > div_mod(const P &r) {
    P q = *this / r;
    P x = *this - q * r;
    x.shrink();
    return make_pair(q, x);
  }

  P operator-() const {
    P ret(this->size());
    for(int i = 0; i < (int) this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  P &operator+=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  P &operator-=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] -= r;
    return *this;
  }

  P &operator*=(const T &v) {
    for(int i = 0; i < (int) this->size(); i++) (*this)[i] *= v;
    return *this;
  }

  P dot(P r) const {
    P ret(min(this->size(), r.size()));
    for(int i = 0; i < (int) ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  P operator>>(int sz) const {
    if((int) this->size() <= sz) return {};
    P ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  P operator<<(int sz) const {
    P ret(*this);
    ret.insert(ret.begin(), sz, T(0));
    return ret;
  }

  T operator()(T x) const {
    T r = 0, w = 1;
    for(auto &v : *this) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  P diff() const {
    const int n = (int) this->size();
    P ret(max(0, n - 1));
    for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
    return ret;
  }

  P integral() const {
    const int n = (int) this->size();
    P ret(n + 1);
    ret[0] = T(0);
    for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
    return ret;
  }

  // https://judge.yosupo.jp/problem/inv_of_formal_power_series
  // F(0) must not be 0
  P inv(int deg = -1) const {
    assert(((*this)[0]) != T(0));
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    P res(deg);
    res[0] = {T(1) / (*this)[0]};
    for(int d = 1; d < deg; d <<= 1) {
      P f(2 * d), g(2 * d);
      for(int j = 0; j < min(n, 2 * d); j++) f[j] = (*this)[j];
      for(int j = 0; j < d; j++) g[j] = res[j];
      NTT::ntt(f);
      NTT::ntt(g);
      f = f.dot(g);
      NTT::intt(f);
      for(int j = 0; j < d; j++) f[j] = 0;
      NTT::ntt(f);
      for(int j = 0; j < 2 * d; j++) f[j] *= g[j];
      NTT::intt(f);
      for(int j = d; j < min(2 * d, deg); j++) res[j] = -f[j];
    }
    return res;
  }

  // https://judge.yosupo.jp/problem/log_of_formal_power_series
  // F(0) must be 1
  P log(int deg = -1) const {
    assert((*this)[0] == T(1));
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
  P sqrt(int deg = -1, const function< T(T) > &get_sqrt = [](T) { return T(1); }) const {
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    if((*this)[0] == T(0)) {
      for(int i = 1; i < n; i++) {
        if((*this)[i] != T(0)) {
          if(i & 1) return {};
          if(deg - i / 2 <= 0) break;
          auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);
          if(ret.empty()) return {};
          ret = ret << (i / 2);
          if((int) ret.size() < deg) ret.resize(deg, T(0));
          return ret;
        }
      }
      return P(deg, 0);
    }
    auto sqr = T(get_sqrt((*this)[0]));
    if(sqr * sqr != (*this)[0]) return {};
    P ret{sqr};
    T inv2 = T(1) / T(2);
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
    }
    return ret.pre(deg);
  }

  P sqrt(const function< T(T) > &get_sqrt, int deg = -1) const {
    return sqrt(deg, get_sqrt);
  }

  // https://judge.yosupo.jp/problem/exp_of_formal_power_series
  // F(0) must be 0
  P exp(int deg = -1) const {
    if(deg == -1) deg = this->size();
    assert((*this)[0] == T(0));

    P inv;
    inv.reserve(deg + 1);
    inv.push_back(T(0));
    inv.push_back(T(1));

    auto inplace_integral = [&](P &F) -> void {
      const int n = (int) F.size();
      auto mod = T::get_mod();
      while((int) inv.size() <= n) {
        int i = inv.size();
        inv.push_back((-inv[mod % i]) * (mod / i));
      }
      F.insert(begin(F), T(0));
      for(int i = 1; i <= n; i++) F[i] *= inv[i];
    };

    auto inplace_diff = [](P &F) -> void {
      if(F.empty()) return;
      F.erase(begin(F));
      T coeff = 1, one = 1;
      for(int i = 0; i < (int) F.size(); i++) {
        F[i] *= coeff;
        coeff += one;
      }
    };

    P b{1, 1 < (int) this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
    for(int m = 2; m < deg; m *= 2) {
      auto y = b;
      y.resize(2 * m);
      NTT::ntt(y);
      z1 = z2;
      P z(m);
      for(int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
      NTT::intt(z);
      fill(begin(z), begin(z) + m / 2, T(0));
      NTT::ntt(z);
      for(int i = 0; i < m; ++i) z[i] *= -z1[i];
      NTT::intt(z);
      c.insert(end(c), begin(z) + m / 2, end(z));
      z2 = c;
      z2.resize(2 * m);
      NTT::ntt(z2);
      P x(begin(*this), begin(*this) + min< int >(this->size(), m));
      inplace_diff(x);
      x.push_back(T(0));
      NTT::ntt(x);
      for(int i = 0; i < m; ++i) x[i] *= y[i];
      NTT::intt(x);
      x -= b.diff();
      x.resize(2 * m);
      for(int i = 0; i < m - 1; ++i) x[m + i] = x[i], x[i] = T(0);
      NTT::ntt(x);
      for(int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
      NTT::intt(x);
      x.pop_back();
      inplace_integral(x);
      for(int i = m; i < min< int >(this->size(), 2 * m); ++i) x[i] += (*this)[i];
      fill(begin(x), begin(x) + m, T(0));
      NTT::ntt(x);
      for(int i = 0; i < 2 * m; ++i) x[i] *= y[i];
      NTT::intt(x);
      b.insert(end(b), begin(x) + m, end(x));
    }
    return P{begin(b), begin(b) + deg};
  }

  // https://judge.yosupo.jp/problem/pow_of_formal_power_series
  P pow(int64_t k, int deg = -1) const {
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    for(int i = 0; i < n; i++) {
      if((*this)[i] != T(0)) {
        T rev = T(1) / (*this)[i];
        P ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
        if(i * k > deg) return P(deg, T(0));
        ret = (ret << (i * k)).pre(deg);
        if((int) ret.size() < deg) ret.resize(deg, T(0));
        return ret;
      }
    }
    return *this;
  }

  P mod_pow(int64_t k, P g) const {
    P modinv = g.rev().inv();
    auto get_div = [&](P base) {
      if(base.size() < g.size()) {
        base.clear();
        return base;
      }
      int n = base.size() - g.size() + 1;
      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
    };
    P x(*this), ret{1};
    while(k > 0) {
      if(k & 1) {
        ret *= x;
        ret -= get_div(ret) * g;
        ret.shrink();
      }
      x *= x;
      x -= get_div(x) * g;
      x.shrink();
      k >>= 1;
    }
    return ret;
  }

  // https://judge.yosupo.jp/problem/polynomial_taylor_shift
  P taylor_shift(T c) const {
    int n = (int) this->size();
    vector< T > fact(n), rfact(n);
    fact[0] = rfact[0] = T(1);
    for(int i = 1; i < n; i++) fact[i] = fact[i - 1] * T(i);
    rfact[n - 1] = T(1) / fact[n - 1];
    for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);
    P p(*this);
    for(int i = 0; i < n; i++) p[i] *= fact[i];
    p = p.rev();
    P bs(n, T(1));
    for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];
    p = (p * bs).pre(n);
    p = p.rev();
    for(int i = 0; i < n; i++) p[i] *= rfact[i];
    return p;
  }
};

template< typename Mint >
using FPS = FormalPowerSeriesFriendlyNTT< Mint >;
