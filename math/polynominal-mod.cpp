template< typename T >
struct PolynominalMod : vector< T > {
  using vector< T >::vector;
  using P = PolynominalMod;
  static ArbitraryModConvolution< T > fft;


  P operator+(const P &r) const { return P(*this) += r; }

  P operator-(const P &r) const { return P(*this) -= r; }

  P operator*(const P &r) const { return P(*this) *= r; }

  P operator/(const P &r) const { return P(*this) /= r; }

  P &operator+=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  P &operator-=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  P &operator*=(const P &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    auto ret = fft.multiply(*this, r);
    this->resize(ret.size());
    for(int k = 0; k < ret.size(); k++) (*this)[k] = ret[k];
    return *this;
  }

  P operator-() const {
    P ret(this->size());
    for(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  P &operator/=(const P &r) {
    return *this *= r.inverse();
  }

  P inverse() const {
    const int n = (int) this->size();
    assert(n);
    P ret({T(1) / (*this)[0]});
    for(int k = 2; (k >> 1) < n; k <<= 1) {
      P ff(min(n, k));
      for(int i = 0; i < ff.size(); i++) ff[i] = (*this)[i];
      P nr = ret * ret;
      nr.resize(ff.size());
      nr = nr * ff;
      nr.resize(ff.size());
      for(int i = 0; i < (k >> 1); i++) nr[i] -= ret[i] + ret[i];
      ret = -nr;
    }
    return ret;
  }

  P sqrt() const {
    const int n = (int) this->size();
    assert(n);
    P ret({T(1)});
    const T inv2 = T(1) / 2;
    for(int k = 2; (k >> 1) < n; k <<= 1) {
      P ff(min(n, k));
      for(int i = 0; i < ff.size(); i++) ff[i] = (*this)[i];
      ret.resize(ff.size());
      P ns = ret.inverse() * ff;
      for(int i = 0; i < ff.size(); i++) ret[i] = (ret[i] + ns[i]) * inv2;
    }
    return ret;
  }
};
