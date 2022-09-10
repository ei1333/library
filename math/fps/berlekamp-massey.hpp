/**
 * @brief Berlekamp Massey
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > berlekamp_massey(const FPS< Mint > &s) {
  const int N = (int) s.size();
  FPS< Mint > b = {Mint(-1)}, c = {Mint(-1)};
  Mint y = Mint(1);
  for(int ed = 1; ed <= N; ed++) {
    int l = int(c.size()), m = int(b.size());
    Mint x = 0;
    for(int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
    b.emplace_back(0);
    m++;
    if(x == Mint(0)) continue;
    Mint freq = x / y;
    if(l < m) {
      auto tmp = c;
      c.insert(begin(c), m - l, Mint(0));
      for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
      b = tmp;
      y = x;
    } else {
      for(int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
    }
  }
  return c;
}
