#include "../others/binary-indexed-tree.hpp"

template <typename T>
struct PointAddRectangleSum {
  using S = T;
  using D = BinaryIndexedTree<T>;
  static constexpr S op(const S& a, const S& b) { return a + b; }
  static constexpr S e() { return 0; }
  static constexpr D init(int n) { return D{n}; }
  static constexpr void apply(D& d, int k, const S& v) { d.apply(k, v); }
  static constexpr S prod(D& d, int l, int r) { return d.prod(l, r); }
};
