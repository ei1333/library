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
  static constexpr S mapping(const S &x, const F &f) {}
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
*/
