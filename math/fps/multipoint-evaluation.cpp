#include "formal-power-series.cpp"
#include "inv.cpp"

template< typename T >
struct PolyBuf {
  using FPS = FormalPowerSeries< T >;
  const FPS xs;
  using pi = pair< int, int >;
  map< pi, FPS > buf;

  PolyBuf(const FPS &xs) : xs(xs) {}

  const FPS &query(int l, int r) {
    if(buf.count({l, r})) return buf[{l, r}];
    if(l + 1 == r) return buf[{l, r}] = {-xs[l], 1};
    return buf[{l, r}] = query(l, (l + r) >> 1) * query((l + r) >> 1, r);
  }
};


template< typename T >
FormalPowerSeries< T > multipoint_evaluation(const FormalPowerSeries< T > &as, const FormalPowerSeries< T > &xs, PolyBuf< T > &buf) {
  using FPS = FormalPowerSeries< T >;
  FPS ret;
  const int B = 64;
  function< void(FPS, int, int) > rec = [&](FPS a, int l, int r) -> void {
    a %= buf.query(l, r);
    if(a.size() <= B) {
      for(int i = l; i < r; i++) ret.emplace_back(a.eval(xs[i]));
      return;
    }
    rec(a, l, (l + r) >> 1);
    rec(a, (l + r) >> 1, r);
  };
  rec(as, 0, xs.size());
  return ret;
};

template< typename T >
FormalPowerSeries< T > multipoint_evaluation(const FormalPowerSeries< T > &as, const FormalPowerSeries< T > &xs) {
  PolyBuf< T > buff(xs);
  return multipoint_evaluation(as, xs, buff);
}

