#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/formal-power-series-friendly-ntt.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, C;
  cin >> N >> C;
  FPS< mint > F(N);
  cin >> F;
  cout << F.taylor_shift(mint(C)) << "\n";
}
