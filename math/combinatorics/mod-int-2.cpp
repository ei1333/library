static constexpr uint32_t mul_inv(uint32_t n, int e = 5, uint32_t x = 1) {
  return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
}

template< uint32_t mod, bool fast = false >
struct ModInt2 {
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 inv = mul_inv(mod);
  static constexpr u32 r2 = -uint64_t(mod) % mod;

  uint32_t x;

  ModInt2() : x(0) {}

  ModInt2(const int64_t &y)
      : x(reduce(u64(fast ? y : (y >= 0 ? y % mod : (mod - (-y) % mod) % mod)) * r2)) {}

  u32 reduce(const u64 &w) const {
    return u32(w >> 32) + mod - u32((u64(u32(w) * inv) * mod) >> 32);
  }

  ModInt2 &operator+=(const ModInt2 &p) {
    if(int(x += p.x - 2 * mod) < 0) x += 2 * mod;
    return *this;
  }

  ModInt2 &operator-=(const ModInt2 &p) {
    if(int(x -= p.x) < 0) x += 2 * mod;
    return *this;
  }

  ModInt2 &operator*=(const ModInt2 &p) {
    x = reduce(uint64_t(x) * p.x);
    return *this;
  }

  ModInt2 &operator/=(const ModInt2 &p) {
    *this *= p.inverse();
    return *this;
  }

  ModInt2 operator-() const { return ModInt2() - *this; }

  ModInt2 operator+(const ModInt2 &p) const { return ModInt2(*this) += p; }

  ModInt2 operator-(const ModInt2 &p) const { return ModInt2(*this) -= p; }

  ModInt2 operator*(const ModInt2 &p) const { return ModInt2(*this) *= p; }

  ModInt2 operator/(const ModInt2 &p) const { return ModInt2(*this) /= p; }

  bool operator==(const ModInt2 &p) const { return get() == p.get(); }

  bool operator!=(const ModInt2 &p) const { return get() != p.get(); }

  int get() const { return reduce(x) % mod; }

  ModInt2 pow(int64_t n) const {
    ModInt2 ret(1), mul(*this);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  ModInt2 inverse() const {
    return pow(mod - 2);
  }

  friend ostream &operator<<(ostream &os, const ModInt2 &p) {
    return os << p.get();
  }

  friend istream &operator>>(istream &is, ModInt2 &a) {
    int64_t t;
    is >> t;
    a = ModInt2< mod, fast >(t);
    return (is);
  }

  static int get_mod() { return mod; }
};

using modint = ModInt2< mod >;
