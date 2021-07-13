/**
 * @brief Enumeration(組み合わせ)
 */
template< typename T >
struct Enumeration {
private:
  static vector< T > _fact, _finv, _inv;

  inline static void expand(size_t sz) {
    if(_fact.size() < sz + 1) {
      int pre_sz = max(1, (int) _fact.size());
      _fact.resize(sz + 1, T(1));
      _finv.resize(sz + 1, T(1));
      _inv.resize(sz + 1, T(1));
      for(int i = pre_sz; i <= (int) sz; i++) {
        _fact[i] = _fact[i - 1] * T(i);
      }
      _finv[sz] = T(1) / _fact[sz];
      for(int i = (int) sz - 1; i >= pre_sz; i--) {
        _finv[i] = _finv[i + 1] * T(i + 1);
      }
      for(int i = pre_sz; i <= (int) sz; i++) {
        _inv[i] = _finv[i] * _fact[i - 1];
      }
    }
  }

public:
  explicit Enumeration(size_t sz = 0) { expand(sz); }

  static inline T fact(int k) {
    expand(k);
    return _fact[k];
  }

  static inline T finv(int k) {
    expand(k);
    return _finv[k];
  }

  static inline T inv(int k) {
    expand(k);
    return _inv[k];
  }

  static T P(int n, int r) {
    if(r < 0 || n < r) return 0;
    return fact(n) * finv(n - r);
  }

  static T C(int p, int q) {
    if(q < 0 || p < q) return 0;
    return fact(p) * finv(q) * finv(p - q);
  }

  static T H(int n, int r) {
    if(n < 0 || r < 0) return 0;
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};

template< typename T >
vector< T > Enumeration< T >::_fact = vector< T >();
template< typename T >
vector< T > Enumeration< T >::_finv = vector< T >();
template< typename T >
vector< T > Enumeration< T >::_inv = vector< T >();
