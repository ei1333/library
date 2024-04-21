// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/952

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp"

int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  cin >> A;
  vector< int64 > S(N + 2);
  for(int i = 0; i < N; i++) {
    S[i + 1] = S[i] + A[i];
  }

  auto dp = make_v< int64 >(N + 2, N + 1);
  auto dp2 = make_v< int64 >(N + 2, N + 1);
  fill_v(dp, infll);
  fill_v(dp2, infll);
  dp[0][0] = 0;

  vector< ConvexHullTrickAddMonotone< int64, true > > chts(2 * N + 10);
  const int Shift = N + 5;

  for(int i = 0; i <= N + 1; i++) {
    if(i <= N) {
      for(int j = 0; j <= N; j++) {
        int Q = j - i + Shift;
        if(!chts[Q].empty()) chmin(dp2[i + 1][j], S[i] * S[i] + chts[Q].query_monotone_dec(-2 * S[i]));
      }
    }
    for(int j = 0; j <= N; j++) {
      if(i) dp[i][j] = min(dp[i - 1][j], dp2[i][j]);
      if(dp[i][j] != infll) chts[j - i + Shift].add(S[i], dp[i][j] + S[i] * S[i]);
    }
  }

  for(int i = 1; i <= N; i++) {
    cout << dp[N + 1][i] << endl;
  }
}
