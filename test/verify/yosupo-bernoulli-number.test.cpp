// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bernoulli_number

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/bernoulli.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << bernoulli< FPS, mint >(N) << endl;
}

