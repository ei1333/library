// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/stirling-first.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << stirling_first< FPS, mint >(N) << endl;
}
