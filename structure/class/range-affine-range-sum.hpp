#include "affine.hpp"

template <typename T>
struct RangeAffineRangeSum {
  using S = pair<T, T>;
  using F = Affine<T>;
  static constexpr S op(const S &a, const S &b) {
    return {a.first + b.first, a.second + b.second};
  }
  static constexpr S e() { return {0, 0}; }
  static constexpr S mapping(const S &x, const F &f) {
    return {x.first * f.a + x.second * f.b, x.second};
  }
  static constexpr F composition(const F &f, const F &g) { return F::op(f, g); }
  static constexpr F id() { return F(); }
};
