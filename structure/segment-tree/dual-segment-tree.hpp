/**
 * @brief Dual-Segment-Tree(双対セグメント木)
 * 
 */
template< typename E, typename H >
struct DualSegmentTree {
  int sz, height;
  vector< E > lazy;
  const H h;
  const E ei;

  DualSegmentTree(int n, const H h, const E &ei) : h(h), ei(ei) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    lazy.assign(2 * sz, ei);
  }

  inline void propagate(int k) {
    if(lazy[k] != ei) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      lazy[k] = ei;
    }
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const E &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
  }

  E operator[](int k) {
    thrust(k += sz);
    return lazy[k];
  }
};

template< typename E, typename H >
DualSegmentTree< E, H > get_dual_segment_tree(int N, const H& h, const E& ei) {
  return {N, h, ei};
}
