#include "../class/beats-monoid.hpp"

template <typename BeatsMonoid>
struct SegmentTreeBeats {
  using S = typename BeatsMonoid::S;
  using F = typename BeatsMonoid::F;

 private:
  BeatsMonoid m;

  int n{}, sz{}, height{};

  vector<S> data;

  vector<F> lazy;

  inline void update(int k) {
    data[k] = m.op(data[2 * k + 0], data[2 * k + 1]);
  }

  inline void apply_at(int k, const F& x) {
    data[k] = m.mapping(data[k], x);
    if (k < sz) {
      lazy[k] = m.composition(lazy[k], x);
      if (m.fail(data[k])) {
        propagate(k);
        update(k);
      }
    }
  }

  inline void propagate(int k) {
    if (lazy[k] != m.id()) {
      apply_at(2 * k + 0, lazy[k]);
      apply_at(2 * k + 1, lazy[k]);
      lazy[k] = m.id();
    }
  }

 public:
  SegmentTreeBeats() = default;

  explicit SegmentTreeBeats(BeatsMonoid m, int n) : m(m), n(n) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    data.assign(2 * sz, m.e());
    lazy.assign(2 * sz, m.id());
  }

  explicit SegmentTreeBeats(BeatsMonoid m, const vector<S>& v)
      : SegmentTreeBeats(m, v.size()) {
    build(v);
  }

  void build(const vector<S>& v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) data[k + sz] = v[k];
    for (int k = sz - 1; k > 0; k--) update(k);
  }

  void set(int k, const S& x) {
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

  void apply(int k, const F& f) {
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    data[k] = m.mapping(data[k], f);
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  void apply(int l, int r, const F& f) {
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
        if (l & 1) apply_at(l++, f);
        if (r & 1) apply_at(--r, f);
      }
      l = l2, r = r2;
    }
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }
};
