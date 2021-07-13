/**
 * @brief Maximum Independent Set(最大独立集合)
 */
template< typename Matrix >
vector< int > maximum_independent_set(const Matrix &g, int trial = 1000000) {
  int N = (int) g.size();
  vector< uint64_t > bit(N);
  assert(N <= 64);
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(i != j) {
        assert(g[i][j] == g[j][i]);
        if(g[i][j]) bit[i] |= uint64_t(1) << j;
      }
    }
  }

  vector< int > ord(N);
  iota(begin(ord), end(ord), 0);
  mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
  int ret = 0;
  uint64_t ver = 0;
  for(int i = 0; i < trial; i++) {
    shuffle(begin(ord), end(ord), mt);
    uint64_t used = 0;
    int add = 0;
    for(int j : ord) {
      if(used & bit[j]) continue;
      used |= uint64_t(1) << j;
      ++add;
    }
    if(ret < add) {
      ret = add;
      ver = used;
    }
  }
  vector< int > ans;
  for(int i = 0; i < N; i++) {
    if((ver >> i) & 1) ans.emplace_back(i);
  }
  return ans;
}
