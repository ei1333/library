// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/215

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series.hpp"

const int MOD = (int) (1e9 + 7);
using mint = ModInt< MOD >;

int main() {
  int64 N;
  int P, C;
  cin >> N >> P >> C;
  vector< int > as{2, 3, 5, 7, 11, 13};
  vector< int > bs{4, 6, 8, 9, 10, 12};
  auto gen = [&](vector< int > &xs, int sum) {
    auto dp = make_v< mint >(sum + 1, xs.back() * sum + 1);
    dp[0][0] = 1;
    for(int x : xs) {
      for(int i = 1; i <= sum; i++) {
        for(int j = x; j < dp[i].size(); j++) {
          dp[i][j] += dp[i - 1][j - x];
        }
      }
    }
    return FPS< mint >{begin(dp[sum]), end(dp[sum])};
  };
  auto dp = gen(as, P) * gen(bs, C);
  dp[0] = -1;
  dp = dp.rev();
  FPS< mint > x{0, 1};
  auto cur = x.mod_pow(N + (int64) dp.size() - 2, dp);
  cout << accumulate(begin(cur), end(cur), mint(0)) << "\n";
}
