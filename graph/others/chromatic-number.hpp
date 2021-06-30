#pragma once
/**
 * @brief Chromatic-Number(彩色数)
 * @docs docs/chromatic-number.md
 * @see https://www.slideshare.net/wata_orz/ss-12131479
 */
template< typename Matrix >
int chromatic_number(Matrix &g) {
  int N = (int) g.size();
  vector< int > es(N);
  for(int i = 0; i < (int)g.size(); i++) {
    for(int j = 0; j < (int)g.size(); j++) {
      if(g[i][j] != 0) es[i] |= 1 << j;
    }
  }
  int ret = N;
  for(int d : {7, 11, 21}) {
    int mod = 1e9 + d;
    vector< int > ind(1 << N), aux(1 << N, 1);
    ind[0] = 1;
    for(int S = 1; S < 1 << N; S++) {
      int u = __builtin_ctz(S);
      ind[S] = ind[S ^ (1 << u)] + ind[(S ^ (1 << u)) & ~es[u]];
    }
    for(int i = 1; i < ret; i++) {
      int64_t all = 0;
      for(int j = 0; j < 1 << N; j++) {
        int S = j ^(j >> 1);
        aux[S] = (1LL * aux[S] * ind[S]) % mod;
        all += j & 1 ? aux[S] : mod - aux[S];
      }
      if(all % mod) ret = i;
    }
  }
  return ret;
}
