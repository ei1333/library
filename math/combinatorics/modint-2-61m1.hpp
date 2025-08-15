struct ModInt_2_61m1 {
 private:
  using mint = ModInt_2_61m1;
  using u64 = uint64_t;
  using u128 = __uint128_t;

  u64 x;

 public:
  ModInt_2_61m1() : x{} {}

  explicit ModInt_2_61m1(u64 a) : x{a} {}

  mint& operator+=(const mint& p) {
    if ((x += p.x) >= mod()) x -= mod();
    return *this;
  }

  mint& operator-=(const mint& p) {
    if ((x += mod() - p.x) >= mod()) x -= mod();
    return *this;
  }

  mint& operator*=(const mint& p) {
    u128 c = (u128)x * p.x;
    x = u64(c >> 61) + u64(c & mod());
    if (x >= mod()) x -= mod();
    return *this;
  }

  mint& operator/=(const mint& p) {
    *this *= p.inv();
    return *this;
  }

  mint operator-() const { return mint() - *this; }

  mint operator+(const mint& p) const { return mint(*this) += p; }

  mint operator-(const mint& p) const { return mint(*this) -= p; }

  mint operator*(const mint& p) const { return mint(*this) *= p; }

  mint operator/(const mint& p) const { return mint(*this) /= p; }

  bool operator==(const mint& p) const { return x == p.x; }

  bool operator!=(const mint& p) const { return x != p.x; }

  u64 val() const { return x; }

  mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  mint inv() const { return pow(mod() - 2); }

  friend ostream& operator<<(ostream& os, const mint& p) {
    return os << p.val();
  }

  friend istream& operator>>(istream& is, mint& a) {
    u64 t;
    is >> t;
    a = mint(t);
    return is;
  }

  static constexpr u64 mod() { return (1ull << 61) - 1; }
};
