#include "../class/monoid.hpp"

template <typename Monoid>
struct SegmentTree {
  using S = typename Monoid::S;

 private:
  int n, sz;

  vector<S> seg;

  Monoid m;

 public:
  SegmentTree() = default;

  explicit SegmentTree(Monoid m, int n) : m(m), n(n) {
    sz = 1;
    while (sz < n) sz <<= 1;
    seg.assign(2 * sz, m.e());
  }

  explicit SegmentTree(Monoid m, const vector<S>& v)
      : SegmentTree(m, (int)v.size()) {
    build(v);
  }

  void build(const vector<S>& v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) seg[k + sz] = v[k];
    for (int k = sz - 1; k > 0; k--) {
      seg[k] = m.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  void set(int k, const S& x) {
    k += sz;
    seg[k] = x;
    while (k >>= 1) {
      seg[k] = m.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  S get(int k) const { return seg[k + sz]; }

  S operator[](int k) const { return get(k); }

  void apply(int k, const S& x) {
    k += sz;
    seg[k] = m.op(seg[k], x);
    while (k >>= 1) {
      seg[k] = m.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  S prod(int l, int r) const {
    if (l >= r) return m.e();
    S L = m.e(), R = m.e();
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = m.op(L, seg[l++]);
      if (r & 1) R = m.op(seg[--r], R);
    }
    return m.op(L, R);
  }

  S all_prod() const { return seg[1]; }

  template <typename C>
  int find_first(int l, const C& check) const {
    if (l >= n) return n;
    l += sz;
    S sum = m.e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(m.op(sum, seg[l]))) {
        while (l < sz) {
          l <<= 1;
          auto nxt = m.op(sum, seg[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = m.op(sum, seg[l++]);
    } while ((l & -l) != l);
    return n;
  }

  template <typename C>
  int find_last(int r, const C& check) const {
    if (r <= 0) return -1;
    r += sz;
    S sum = m.e();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(m.op(seg[r], sum))) {
        while (r < sz) {
          r = (r << 1) + 1;
          auto nxt = m.op(seg[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = m.op(seg[r], sum);
    } while ((r & -r) != r);
    return -1;
  }
};
