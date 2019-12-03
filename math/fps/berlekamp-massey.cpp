template< class T >
FormalPowerSeries< T > berlekamp_massey(const FormalPowerSeries< T > &s) {
  const int N = (int) s.size();
  FormalPowerSeries< T > b = {T(-1)}, c = {T(-1)};
  T y = T(1);
  for(int ed = 1; ed <= N; ed++) {
    int l = int(c.size()), m = int(b.size());
    T x = 0;
    for(int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
    b.emplace_back(0);
    m++;
    if(x == T(0)) continue;
    T freq = x / y;
    if(l < m) {
      auto tmp = c;
      c.insert(begin(c), m - l, T(0));
      for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
      b = tmp;
      y = x;
    } else {
      for(int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
    }
  }
  return c;
}
