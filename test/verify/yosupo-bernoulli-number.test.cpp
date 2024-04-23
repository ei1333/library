// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bernoulli_number

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/bernoulli.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  cout << bernoulli< FPS, mint >(N) << endl;
}

