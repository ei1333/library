// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_taylor_shift

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

using mint = modint998244353;

int main() {
  int N, C;
  cin >> N >> C;
  FPS< mint > F(N);
  cin >> F;
  cout << F.taylor_shift(mint(C)) << "\n";
}
