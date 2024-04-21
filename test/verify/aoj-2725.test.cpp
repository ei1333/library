// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2725

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp"

int main() {
  int N, T;
  cin >> N >> T;
  vector< tuple< int, int, int > > dd;
  dd.reserve(N);
  for(int i = 0; i < N; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if(a <= T) dd.emplace_back(c, a, b);
  }
  sort(begin(dd), end(dd));
  N = (int) dd.size();
  vector< int64 > t(N), p(N), f(N);
  for(int i = 0; i < N; i++) {
    tie(f[i], t[i], p[i]) = dd[i];
  }
  auto dp = make_v< int64 >(N, T + 1);
  fill_v(dp, -infll);
  vector< DynamicLiChaoTree< int64, 0, 10000, infll > > cht(T + 1, DynamicLiChaoTree< int64, 0, 10000, infll >());
  for(int i = 0; i < N; i++) {
    dp[i][t[i]] = p[i];
    for(int j = T; j >= t[i]; j--) {
      dp[i][j] = max(dp[i][j], -cht[j - t[i]].query(f[i]) + p[i] - f[i] * f[i]);
    }
    for(int j = T; j >= 0; j--) {
      if(dp[i][j] == -infll) continue;
      cht[j].add_line(-2 * f[i], -(dp[i][j] - f[i] * f[i]));
    }
  }
  int64 ret = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= T; j++) {
      ret = max(ret, dp[i][j]);
    }
  }
  cout << ret << "\n";
}

