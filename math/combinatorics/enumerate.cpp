template< typename T >
struct Enumerate {
private:
  vector< T > _fact, _rfact, _inv;

  inline void expand(size_t sz) {
    if(_fact.size() < sz + 1) {
      int pre_sz = (int) _fact.size();
      _fact.resize(sz + 1);
      _rfact.resize(sz + 1);
      _inv.resize(sz + 1);
      for(int i = pre_sz; i <= sz; i++) {
        _fact[i] = _fact[i - 1] * T(i);
      }
      _rfact[sz] = T(1) / _fact[sz];
      for(int i = (int) sz - 1; i >= pre_sz; i--) {
        _rfact[i] = _rfact[i + 1] * T(i + 1);
      }
      for(int i = pre_sz; i <= sz; i++) {
        _inv[i] = _rfact[i] * _fact[i - 1];
      }
    }
  }

public:
  explicit Enumerate(size_t sz = 0) : _fact{T(1)}, _rfact{T(1)}, _inv{T(1)} {
    expand(sz);
  }

  inline T fact(int k) {
    expand(k);
    return _fact[k];
  }

  inline T rfact(int k) {
    expand(k);
    return _rfact[k];
  }

  inline T inv(int k) {
    expand(k);
    return _inv[k];
  }

  T P(int n, int r) {
    if(r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }

  T C(int p, int q) {
    if(q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }

  T H(int n, int r) {
    if(n < 0 || r < 0) return 0;
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};
