int main() {
  int N, M, K, A[100000];
  cin >> N >> M >> K;
  for(int i = 0; i < N; i++) {
    cin >> A[i];
  }
  vector< int64 > dp(N);
  for(int i = 0; i < N; i++) {
    dp[i] = A[i];
  }
  for(int i = 1; i < K; i++) {
    vector< int64 > dp2(N);
    reverse(begin(dp), end(dp));
    dp.resize(N + M - 1);
    reverse(begin(dp), end(dp));
    auto p = slide_min(dp, M);
    for(int j = i; j < N; j++) {
      dp2[j] = max(dp2[j], p[j - 1] + 1LL * (i + 1) * A[j]);
    }
    dp.swap(dp2);
  }
  cout << *max_element(begin(dp), end(dp)) << endl;
}

