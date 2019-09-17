template< typename T >
struct UnionRectangle {
  map< T, T > data;
  int64 sum;

  UnionRectangle() : sum(0) {
    const T INF = numeric_limits< T >::max();
    data[0] = INF;
    data[INF] = 0;
  }
  void add_point(T x, T y) {
    auto p = data.lower_bound(x);
    if(p->second >= y) return;
    const T nxtY = p->second;
    --p;
    while(p->second <= y) {
      auto it = *p;
      p = --data.erase(p);
      sum -= (it.first - p->first) * (it.second - nxtY);
    }
    sum += (x - p->first) * (y - nxtY);
    data[x] = y;
  }

  int64 get() {
    return sum;
  }
};
