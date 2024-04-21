/**
 * @brief Euler’s Phi Table(オイラーのφ関数テーブル)
 * 
 */
vector< int > euler_phi_table(int n) {
  vector< int > euler(n + 1);
  for(int i = 0; i <= n; i++) {
    euler[i] = i;
  }
  for(int i = 2; i <= n; i++) {
    if(euler[i] == i) {
      for(int j = i; j <= n; j += i) {
        euler[j] = euler[j] / i * (i - 1);
      }
    }
  }
  return euler;
}
