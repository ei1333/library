// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/log_of_formal_power_series

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"

#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  FPS< mint > F(N);
  cin >> F;
  cout << F.log() << endl;
}
