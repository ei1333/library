/**
 * @brief Segment Tree(セグメント木)
 * 
 */
template< typename T, typename F >
struct SegmentTree {
  int n, sz;
  vector< T > seg;

  const F f;
  const T ti;

  SegmentTree() = default;

  explicit SegmentTree(int n, const F f, const T &ti) : n(n), f(f), ti(ti) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz, ti);
  }

  explicit SegmentTree(const vector< T > &v, const F f, const T &ti) :
      SegmentTree((int) v.size(), f, ti) {
    build(v);
  }

  void build(const vector< T > &v) {
    assert(n == (int) v.size());
    for(int k = 0; k < n; k++) seg[k + sz] = v[k];
    for(int k = sz - 1; k > 0; k--) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  void set(int k, const T &x) {
    k += sz;
    seg[k] = x;
    while(k >>= 1) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  T get(int k) const {
    return seg[k + sz];
  }

  T operator[](const int &k) const {
    return get(k);
  }

  void apply(int k, const T &x) {
    k += sz;
    seg[k] = f(seg[k], x);
    while(k >>= 1) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  T prod(int l, int r) const {
    T L = ti, R = ti;
    for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, seg[l++]);
      if(r & 1) R = f(seg[--r], R);
    }
    return f(L, R);
  }

  T all_prod() const {
    return seg[1];
  }

  template< typename C >
  int find_first(int l, const C &check) const {
    if(l >= n) return n;
    l += sz;
    T sum = ti;
    do {
      while((l & 1) == 0) l >>= 1;
      if(check(f(sum, seg[l]))) {
        while(l < sz) {
          l <<= 1;
          auto nxt = f(sum, seg[l]);
          if(not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = f(sum, seg[l++]);
    } while((l & -l) != l);
    return n;
  }

  template< typename C >
  int find_last(int r, const C &check) const {
    if(r <= 0) return -1;
    r += sz;
    T sum = ti;
    do {
      r--;
      while(r > 1 and (r & 1)) r >>= 1;
      if(check(f(seg[r], sum))) {
        while(r < sz) {
          r = (r << 1) + 1;
          auto nxt = f(seg[r], sum);
          if(not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = f(seg[r], sum);
    } while((r & -r) != r);
    return -1;
  }
};

template< typename T, typename F >
SegmentTree< T, F > get_segment_tree(int N, const F &f, const T &ti) {
  return SegmentTree{N, f, ti};
}

template< typename T, typename F >
SegmentTree< T, F > get_segment_tree(const vector< T > &v, const F &f, const T &ti) {
  return SegmentTree{v, f, ti};
}
