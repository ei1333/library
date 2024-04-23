// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_formal_power_series

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

using mint = modint998244353;

int main() {
  int N;
  int64_t M;
  cin >> N >> M;
  FPS< mint > f(N);
  cin >> f;
  cout << f.pow(M) << "\n";
}
