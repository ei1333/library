#define PROBLEM \
  "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../template/template.hpp"

const int MOD = 998244353;
using mint    = ModInt< MOD >;

int main() {
  int N, C;
  cin >> N >> C;
  FPS< mint > F(N);
  cin >> F;
  cout << F.taylor_shift(mint(C)) << "\n";
}
