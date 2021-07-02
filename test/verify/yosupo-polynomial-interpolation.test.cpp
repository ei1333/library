#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fps/formal-power-series-friendly-ntt.cpp"
#include "../../math/fps/polynomial-interpolation.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, M;
  cin >> N;
  FPS< mint > xs(N), ys(N);
  cin >> xs >> ys;
  cout << polynomial_interpolation(xs, ys) << endl;
}
