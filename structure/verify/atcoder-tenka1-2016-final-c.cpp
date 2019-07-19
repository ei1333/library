int main() {
  Trie< 26, 'a' > trie;
  string S, P[5000];
  int M, W[5000];

  cin >> S;
  cin >> M;
  for(int i = 0; i < M; i++) {
    cin >> P[i];
    trie.add(P[i]);
  }
  for(int i = 0; i < M; i++) {
    cin >> W[i];
  }
  vector< int > dp(S.size() + 1);
  for(int i = 0; i < S.size(); i++) {
    auto update = [&](int idx) {
      dp[i + P[idx].size()] = max(dp[i + P[idx].size()], dp[i] + W[idx]);
    };
    trie.query(S, update, i, 0);
    dp[i + 1] = max(dp[i + 1], dp[i]);
  }
  cout << dp.back() << endl;
}
