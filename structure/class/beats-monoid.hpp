#pragma once

template< typename S2, typename Op, typename Fail, typename E, typename F2, typename Mapping, typename Composition, typename Id >
struct LambdaBeatsMonoid {
  using S = S2;
  using F = F2;

  S op(const S &a, const S &b) const { return _op(a, b); }

  bool fail(const S &a) const { return _fail(a); }

  S e() const { return _e(); }

  S mapping(const S &x, const F &f) const { return _mapping(x, f); }

  F composition(const F &f, const F &g) const { return _composition(f, g); }

  F id() const { return _id(); }

  LambdaBeatsMonoid(Op _op, Fail _fail, E _e, Mapping _mapping, Composition _composition,
                    Id _id)
      : _op(_op),
        _fail(_fail),
        _e(_e),
        _mapping(_mapping),
        _composition(_composition),
        _id(_id) {}

private:
  Op _op;
  Fail _fail;
  E _e;
  Mapping _mapping;
  Composition _composition;
  Id _id;
};

template< typename Op, typename Fail, typename E, typename Mapping, typename Composition,
    typename Id >
LambdaBeatsMonoid(Op _op, Fail _fail, E _e, Mapping _mapping, Composition _composition, Id _id)
-> LambdaBeatsMonoid< decltype(_e()), Op, Fail, E, decltype(_id()), Mapping, Composition, Id >;

/*
struct BeatsMonoid {
  using S = ?;
  using F = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr bool fail(const S& a) {}
  static constexpr S e() {}
  static constexpr S mapping(const S &x, const F &f) {}
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
*/
