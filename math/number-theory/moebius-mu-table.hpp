/**
 * @brief Moebius Table(メビウス関数テーブル)
 */
vector< int > moebius_table(int n) {
  vector< int > mu(n + 1, 1), p(n + 1, 1);
  for(int i = 2; i <= n; i++) {
    if(p[i] == 1) {
      for(int j = i; j <= n; j += i) p[j] = i;
    }
    if((i / p[i]) % p[i] == 0) mu[i] = 0;
    else mu[i] = -mu[i / p[i]];
  }
  return mu;
}
