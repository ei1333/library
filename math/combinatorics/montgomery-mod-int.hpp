/**
 * @brief Montgomery ModInt
 */
template< uint32_t mod, bool fast = false >
struct MontgomeryModInt {
  using mint = MontgomeryModInt;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for(i32 i = 0; i < 4; i++) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;

  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 x;

  MontgomeryModInt() : x{} {}

  MontgomeryModInt(const i64 &a)
      : x(reduce(u64(fast ? a : (a % mod + mod)) * n2)) {}

  static constexpr u32 reduce(const u64 &b) {
    return u32(b >> 32) + mod - u32((u64(u32(b) * r) * mod) >> 32);
  }

  mint &operator+=(const mint &p) {
    if(i32(x += p.x - 2 * mod) < 0) x += 2 * mod;
    return *this;
  }

  mint &operator-=(const mint &p) {
    if(i32(x -= p.x) < 0) x += 2 * mod;
    return *this;
  }

  mint &operator*=(const mint &p) {
    x = reduce(u64(x) * p.x);
    return *this;
  }

  mint &operator/=(const mint &p) {
    *this *= p.inverse();
    return *this;
  }

  mint operator-() const { return mint() - *this; }

  mint operator+(const mint &p) const { return mint(*this) += p; }

  mint operator-(const mint &p) const { return mint(*this) -= p; }

  mint operator*(const mint &p) const { return mint(*this) *= p; }

  mint operator/(const mint &p) const { return mint(*this) /= p; }

  bool operator==(const mint &p) const { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }

  bool operator!=(const mint &p) const { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x); }

  u32 get() const {
    u32 ret = reduce(x);
    return ret >= mod ? ret - mod : ret;
  }

  mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  mint inverse() const {
    return pow(mod - 2);
  }

  friend ostream &operator<<(ostream &os, const mint &p) {
    return os << p.get();
  }

  friend istream &operator>>(istream &is, mint &a) {
    i64 t;
    is >> t;
    a = mint(t);
    return is;
  }

  static u32 get_mod() { return mod; }
};

using modint = MontgomeryModInt< mod >;
