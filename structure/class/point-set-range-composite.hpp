#include "affine.hpp"

template <typename T>
struct PointSetRangeComposite {
  using S = Affine<T>;
  static constexpr S op(const S& a, const S& b) { return S::op(a, b); }
  static constexpr S e() { return S(); }
};
