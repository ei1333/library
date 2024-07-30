template <typename Monoid>
struct SegmentTree {
  using S = typename Monoid::S;

 private:
  int n, sz;

  vector<S> seg;

  Monoid t;

 public:
  SegmentTree() = default;

  explicit SegmentTree(Monoid m, int n) : t(m), n(n) {
    sz = 1;
    while (sz < n) sz <<= 1;
    seg.assign(2 * sz, m.e());
  }

  explicit SegmentTree(Monoid m, const vector<S> &v)
      : SegmentTree(m, (int)v.size()) {
    build(v);
  }

  void build(const vector<S> &v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) seg[k + sz] = v[k];
    for (int k = sz - 1; k > 0; k--) {
      seg[k] = t.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  void set(int k, const S &x) {
    k += sz;
    seg[k] = x;
    while (k >>= 1) {
      seg[k] = t.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  S get(int k) const { return seg[k + sz]; }

  S operator[](const int &k) const { return get(k); }

  void apply(int k, const S &x) {
    k += sz;
    seg[k] = t.op(seg[k], x);
    while (k >>= 1) {
      seg[k] = t.op(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  S prod(int l, int r) const {
    S L = t.e(), R = t.e();
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = t.op(L, seg[l++]);
      if (r & 1) R = t.op(seg[--r], R);
    }
    return t.op(L, R);
  }

  S all_prod() const { return seg[1]; }

  template <typename C>
  int find_first(int l, const C &check) const {
    if (l >= n) return n;
    l += sz;
    S sum = t.e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(t.op(sum, seg[l]))) {
        while (l < sz) {
          l <<= 1;
          auto nxt = t.op(sum, seg[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = t.op(sum, seg[l++]);
    } while ((l & -l) != l);
    return n;
  }

  template <typename C>
  int find_last(int r, const C &check) const {
    if (r <= 0) return -1;
    r += sz;
    S sum = t.e();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(t.op(seg[r], sum))) {
        while (r < sz) {
          r = (r << 1) + 1;
          auto nxt = t.op(seg[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = t.op(seg[r], sum);
    } while ((r & -r) != r);
    return -1;
  }
};

template <class T, class OP, class E>
struct LambdaMonoid {
  using S = T;

  S op(const S &a, const S &b) const { return _op(a, b); }

  S e() const { return _e(); }

  LambdaMonoid(OP op, E e) : _op(op), _e(e) {}

 private:
  OP _op;

  E _e;
};

template <class OP, class E>
LambdaMonoid(OP op, E e) -> LambdaMonoid<decltype(e()), OP, E>;

/*
struct Monoid {
  using S = int;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
};
*/
