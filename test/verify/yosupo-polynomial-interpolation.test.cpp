// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_interpolation

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/polynomial-interpolation.hpp"

using mint = modint998244353;

int main() {
  int N, M;
  cin >> N;
  FPS< mint > xs(N), ys(N);
  cin >> xs >> ys;
  cout << polynomial_interpolation(xs, ys) << endl;
}
