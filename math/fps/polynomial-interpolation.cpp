#include "multipoint-evaluation.cpp"
#include "diff.cpp"

template< class T >
FormalPowerSeries< T > polynomial_interpolation(const FormalPowerSeries< T > &xs, const vector< T > &ys) {
  assert(xs.size() == ys.size());
  using FPS = FormalPowerSeries< T >;
  PolyBuf< T > buf(xs);
  FPS w = buf.query(0, xs.size()).diff();
  auto vs = multipoint_evaluation(w, xs, buf);
  function< FPS(int, int) > rec = [&](int l, int r) -> FPS {
    if(r - l == 1) return {ys[l] / vs[l]};
    int m = (l + r) >> 1;
    return rec(l, m) * buf.query(m, r) + rec(m, r) * buf.query(l, m);
  };
  return rec(0, xs.size());
}
