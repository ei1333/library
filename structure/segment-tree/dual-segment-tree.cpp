/**
 * @brief Dual-Segment-Tree(双対セグメント木)
 * @docs docs/dual-segment-tree.md
 */
template< typename OperatorMonoid, typename H >
struct DualSegmentTree {
  int sz, height;
  vector< OperatorMonoid > lazy;
  const H h;
  const OperatorMonoid OM0;

  DualSegmentTree(int n, const H h, const OperatorMonoid &OM0) : h(h), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    lazy.assign(2 * sz, OM0);
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      lazy[k] = OM0;
    }
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
  }

  OperatorMonoid operator[](int k) {
    thrust(k += sz);
    return lazy[k];
  }
};

template< typename OperatorMonoid, typename H >
DualSegmentTree< OperatorMonoid, H > get_dual_segment_tree(int N, const H& h, const OperatorMonoid& OM0) {
  return {N, h, OM0};
}
