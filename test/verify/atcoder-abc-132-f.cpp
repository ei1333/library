#define IGNORE

int main() {
  int N, K;
  cin >> N >> K;
  auto range = quotient_range(N);

  vector< modint > dp(range.size());
  dp[0] = 1;
  for(int i = 0; i < K; i++) {
    reverse(begin(dp), end(dp));
    vector< modint > dp2(range.size());
    modint add = 0;
    for(int j = range.size() - 1; j >= 0; j--) {
      add += dp[j];
      dp2[j] = add * (range[j].first.second - range[j].first.first + 1);
    }
    dp.swap(dp2);
  }
  modint ret;
  for(auto &t : dp) ret += t;
  cout << ret << endl;
}

