/**
 * @brief Edit Distance(編集距離)
 * @docs docs/edit-distance.md
 */
int edit_distance(const string &S, const string &T) {
  const int N = (int) S.size(), M = (int) T.size();
  vector< vector< int > > dp(N + 1, vector< int >(M + 1, N + M));
  for(int i = 0; i <= N; i++) dp[i][0] = i;
  for(int i = 0; i <= M; i++) dp[0][i] = i;
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= M; j++) {
      dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
      dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
      dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (S[i - 1] != T[j - 1]));
    }
  }
  return dp[N][M];
}
