#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/taylor-shift.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  using FPS = FormalPowerSeries< mint >;

  int N, C;
  cin >> N >> C;
  FPS F(N);
  cin >> F;
  cout << F.taylor_shift(mint(C)) << "\n";
}
