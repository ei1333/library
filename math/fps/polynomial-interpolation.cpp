#include "multipoint-evaluation.cpp"

template< template< typename > class FPS, typename Mint >
FPS< Mint > polynomial_interpolation(const FPS< Mint > &xs, const vector< Mint > &ys) {
  assert(xs.size() == ys.size());
  PolyBuf< FPS, Mint > buf(xs);
  FPS< Mint > w = buf.query(0, xs.size()).diff();
  auto vs = multipoint_evaluation(w, xs, buf);
  function< FPS< Mint >(int, int) > rec = [&](int l, int r) -> FPS< Mint > {
    if(r - l == 1) return {ys[l] / vs[l]};
    int m = (l + r) >> 1;
    return rec(l, m) * buf.query(m, r) + rec(m, r) * buf.query(l, m);
  };
  return rec(0, xs.size());
}
