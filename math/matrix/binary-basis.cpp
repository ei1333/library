template< typename T >
struct BinaryBasis {
  vector< T > basis;
  bool update;

  BinaryBasis() : update(false) {}

  bool add(T bit) {
    for(auto &p : basis) {
      bit = min(bit, bit ^ p);
    }
    if(bit) {
      basis.emplace_back(bit);
      return update = true;
    } else {
      return false;
    }
  }

  bool check(T bit) const {
    for(auto &p : basis) {
      bit = min(bit, bit ^ p);
    }
    return bit == 0;
  }

  void normalize() {
    sweep();
    for(int i = (int) basis.size() - 1; i >= 0; i--) {
      for(int j = i - 1; j >= 0; j--) chmin(basis[i], basis[i] ^ basis[j]);
    }
  }

  void sweep() {
    if(exchange(update, false)) {
      sort(begin(basis), end(basis));
    }
  }

  bool operator==(BinaryBasis< T > &a) {
    normalize(), a.normalize();
    return basis == a.basis;
  }

  T get_kth(int64_t k) { /* 0-indexed */
    if((1LL << basis.size()) <= k) {
      return -1;
    }
    T ret = T();
    sweep();
    for(int i = (int) basis.size() - 1; i >= 0; i--) {
      if(k < (1LL << i)) {
        ret = min(ret, ret ^ basis[i]);
      } else {
        k -= 1LL << i;
        ret = max(ret, ret ^ basis[i]);
      }
    }
    return ret;
  }

  size_t size() const {
    return basis.size();
  }
};
