template< typename Monoid, typename OperatorMonoid = Monoid >
struct SegmentTreeBeats {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;


  SegmentTreeBeats(int n, const F f, const G g, const H h,
                   const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), M1(M1), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid &x) {
    data[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      data[k] = reflect(k);
      lazy[k] = OM0;
    }
  }

  inline Monoid reflect(int k) {
    return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
  }

  inline void recalc(int k) {
    while(k >>= 1) data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
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
    recalc(a);
    recalc(b);
  }

  Monoid query(int a, int b) {
    thrust(a += sz);
    thrust(b += sz - 1);
    Monoid L = M1, R = M1;
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, reflect(l++));
      if(r & 1) R = f(reflect(--r), R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) {
    return query(k, k + 1);
  }

  template< typename Uku, typename Check, typename Func, typename X >
  void update_beats_subtree(int k, const X &x, const Uku &uku, const Check &check, const Func &func) {
    if(k >= sz) {
      auto v = reflect(k);
      if(uku(v, x)) return;
      if(check(v)) lazy[k] = func(v, x);
      return;
    }
    propagate(k);
    if(uku(data[k], x)) return;
    if(check(data[k])) {
      lazy[k] = func(data[k], x);
      return;
    }
    update_beats_subtree(k * 2 + 0, x, uku, check, func);
    update_beats_subtree(k * 2 + 1, x, uku, check, func);
    data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  template< typename Uku, typename Check, typename Func, typename X >
  void update_beats(int a, int b, const X &x, const Uku &uku, const Check &check, const Func &func) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) update_beats_subtree(l++, x, uku, check, func);
      if(r & 1) update_beats_subtree(--r, x, uku, check, func);
    }
    recalc(a);
    recalc(b);
  }
};
