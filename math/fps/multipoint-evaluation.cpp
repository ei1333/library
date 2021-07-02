template< template< typename > class FPS, typename Mint >
struct PolyBuf {
  const FPS< Mint > xs;
  using pi = pair< int, int >;
  map< pi, FPS< Mint > > buf;

  PolyBuf(const FPS< Mint > &xs) : xs(xs) {}

  const FPS< Mint > &query(int l, int r) {
    if(buf.count({l, r})) return buf[{l, r}];
    if(l + 1 == r) return buf[{l, r}] = {-xs[l], 1};
    return buf[{l, r}] = query(l, (l + r) >> 1) * query((l + r) >> 1, r);
  }
};


template< template< typename > class FPS, typename Mint >
FPS< Mint > multipoint_evaluation(const FPS< Mint > &as, const FPS< Mint > &xs, PolyBuf< FPS, Mint > &buf) {
  FPS< Mint > ret;
  const int B = 64;
  function< void(FPS< Mint >, int, int) > rec = [&](FPS< Mint > a, int l, int r) -> void {
    a %= buf.query(l, r);
    if(a.size() <= B) {
      for(int i = l; i < r; i++) ret.emplace_back(a(xs[i]));
      return;
    }
    rec(a, l, (l + r) >> 1);
    rec(a, (l + r) >> 1, r);
  };
  rec(as, 0, xs.size());
  return ret;
};

template< template< typename > class FPS, typename Mint >
FPS< Mint > multipoint_evaluation(const FPS< Mint > &as, const FPS< Mint > &xs) {
  PolyBuf< FPS, Mint > buff(xs);
  return multipoint_evaluation(as, xs, buff);
}

