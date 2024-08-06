template <typename T>
struct RangeAddRangeMin {
  using S = T;
  using F = T;
  static constexpr S op(const S &a, const S &b) { return min(a, b); }
  static constexpr S e() { return numeric_limits<T>::max(); }
  static constexpr F mapping(const S &x, const F &f) { return x + f; }
  static constexpr F composition(const F &f, const F &g) { return f + g; }
  static constexpr F id() { return {0}; }
};
