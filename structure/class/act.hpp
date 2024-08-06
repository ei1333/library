#pragma once

template <typename F2, typename Composition, typename Id>
struct LambdaAct {
  using F = F2;

  F composition(const F &f, const F &g) const { return _composition(f, g); }

  F id() const { return _id(); }

  LambdaAct(Composition _composition, Id _id)
      : _composition(_composition), _id(_id) {}

 private:
  Composition _composition;
  Id _id;
};

template <typename Composition, typename Id>
LambdaAct(Composition _composition,
          Id _id) -> LambdaAct<decltype(_id()), Composition, Id>;

/*
struct Act {
  using F = ?;
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() const {}
};
*/
