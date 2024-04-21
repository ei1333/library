// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1720

#include "../../template/template.hpp"

#include "../../structure/others/permutation-tree.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

const int MOD = 998244353;
using mint = MontgomeryModInt< MOD >;

int main() {
  int N, K;
  cin >> N >> K;
  vector< int > A(N);
  cin >> A;
  for(auto &a: A) --a;
  using NP = PermutationTree::Node *;
  auto dp = make_v< mint >(K + 1, N + 1);
  dp[0][0] = 1;
  MFP([&](auto rec, NP r) -> void {
    if(r->is_cut() or r->is_leaf()) {
      for(int k = 0; k < K; k++) {
        dp[k + 1][r->r] += dp[k][r->l];
      }
    }
    vector< mint > sum(K);
    for(auto &c: r->ch) {
      rec(c);
      if(r->is_join()) {
        for(int k = 0; k < K; k++) {
          dp[k + 1][c->r] += sum[k];
          sum[k] += dp[k][c->l];
        }
      }
    }
  })(PermutationTree::build(A));
  for(int i = 1; i <= K; i++) {
    cout << dp[i][N] << "\n";
  }
}
