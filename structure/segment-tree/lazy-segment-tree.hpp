template <typename ActedMonoid>
struct LazySegmentTree {
  using S = typename ActedMonoid::S;
  using F = typename ActedMonoid::F;

 private:
  ActedMonoid m;

  int n{}, sz{}, height{};

  vector<S> data;

  vector<F> lazy;

  inline void update(int k) {
    data[k] = m.op(data[2 * k + 0], data[2 * k + 1]);
  }

  inline void all_apply(int k, const F &x) {
    data[k] = m.mapping(data[k], x);
    if (k < sz) lazy[k] = m.composition(lazy[k], x);
  }

  inline void propagate(int k) {
    if (lazy[k] != m.id()) {
      all_apply(2 * k + 0, lazy[k]);
      all_apply(2 * k + 1, lazy[k]);
      lazy[k] = m.id();
    }
  }

 public:
  LazySegmentTree() = default;

  explicit LazySegmentTree(ActedMonoid m, int n) : m(m), n(n) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    data.assign(2 * sz, m.e());
    lazy.assign(2 * sz, m.id());
  }

  explicit LazySegmentTree(ActedMonoid m, const vector<S> &v)
      : LazySegmentTree(m, v.size()) {
    build(v);
  }

  void build(const vector<S> &v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) data[k + sz] = v[k];
    for (int k = sz - 1; k > 0; k--) update(k);
  }

  void set(int k, const S &x) {
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    data[k] = x;
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  S get(int k) {
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    return data[k];
  }

  S operator[](int k) { return get(k); }

  S prod(int l, int r) {
    if (l >= r) return m.e();
    l += sz;
    r += sz;
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    S L = m.e(), R = m.e();
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = m.op(L, data[l++]);
      if (r & 1) R = m.op(data[--r], R);
    }
    return m.op(L, R);
  }

  S all_prod() const { return data[1]; }

  void apply(int k, const F &f) {
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    data[k] = m.mapping(data[k], f);
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  void apply(int l, int r, const F &f) {
    if (l >= r) return;
    l += sz;
    r += sz;
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
      }
      l = l2, r = r2;
    }
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <typename C>
  int find_first(int l, const C &check) {
    if (l >= n) return n;
    l += sz;
    for (int i = height; i > 0; i--) propagate(l >> i);
    S sum = m.e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(m.op(sum, data[l]))) {
        while (l < sz) {
          propagate(l);
          l <<= 1;
          auto nxt = m.op(sum, data[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = m.op(sum, data[l++]);
    } while ((l & -l) != l);
    return n;
  }

  template <typename C>
  int find_last(int r, const C &check) {
    if (r <= 0) return -1;
    r += sz;
    for (int i = height; i > 0; i--) propagate((r - 1) >> i);
    S sum = m.e();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(m.op(data[r], sum))) {
        while (r < sz) {
          propagate(r);
          r = (r << 1) + 1;
          auto nxt = m.op(data[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = m.op(data[r], sum);
    } while ((r & -r) != r);
    return -1;
  }
};

template <typename S2, typename Op, typename E, typename F2, typename Mapping,
          typename Composition, typename Id>
struct LambdaActedMonoid {
  using S = S2;
  using F = F2;

  S op(const S &a, const S &b) const { return _op(a, b); }

  S e() const { return _e(); }

  S mapping(const S &x, const F &f) const { return _mapping(x, f); }

  F composition(const F &f, const F &g) const { return _composition(f, g); }

  F id() const { return _id(); }

  LambdaActedMonoid(Op _op, E _e, Mapping _mapping, Composition _composition,
                    Id _id)
      : _op(_op),
        _e(_e),
        _mapping(_mapping),
        _composition(_composition),
        _id(_id) {}

 private:
  Op _op;

  E _e;

  Mapping _mapping;

  Composition _composition;

  Id _id;
};

template <typename Op, typename E, typename Mapping, typename Composition,
          typename Id>
LambdaActedMonoid(Op _op, E _e, Mapping _mapping, Composition _composition,
                  Id _id)
    -> LambdaActedMonoid<decltype(_e()), Op, E, decltype(_id()), Mapping,
                         Composition, Id>;

/*
struct ActedMonoid {
  using S = ?;
  using F = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr S e() {}
  static constexpr F mapping(const S &x, const F &f) {}
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
*/
