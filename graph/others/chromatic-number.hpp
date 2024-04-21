#pragma once

/**
 * @brief Chromatic Number(彩色数)
 * 
 * @see https://www.slideshare.net/wata_orz/ss-12131479
 */
template< typename Matrix >
int chromatic_number(Matrix &g) {
  int N = (int) g.size();
  vector< int > es(N);
  for(int i = 0; i < (int) g.size(); i++) {
    for(int j = 0; j < (int) g.size(); j++) {
      if(g[i][j] != 0) es[i] |= 1 << j;
    }
  }
  vector< int > ind(1 << N);
  ind[0] = 1;
  for(int S = 1; S < (1 << N); S++) {
    int u = __builtin_ctz(S);
    ind[S] = ind[S ^ (1 << u)] + ind[(S ^ (1 << u)) & ~es[u]];
  }
  vector< int > cnt((1 << N) + 1);
  for(int i = 0; i < (1 << N); i++) {
    cnt[ind[i]] += __builtin_parity(i) ? -1 : 1;
  }
  vector< pair< unsigned, int > > hist;
  for(int i = 1; i <= (1 << N); i++) {
    if(cnt[i]) hist.emplace_back(i, cnt[i]);
  }
  constexpr int mods[] = {1000000007, 1000000011, 1000000021};
  int ret = N;
  for(int k = 0; k < 3; k++) {
    auto buf = hist;
    for(int c = 1; c < ret; c++) {
      int64_t sum = 0;
      for(auto&[i, x] : buf) {
        sum += (x = int64_t(x) * i % mods[k]);
      }
      if(sum % mods[k]) ret = c;
    }
  }
  return ret;
}
