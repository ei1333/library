// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/kth-term-of-linearly-recurrent-sequence.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int D;
  int64_t K;
  cin >> D >> K;
  FPS< mint > a(D), c(D);
  cin >> a >> c;
  cout << kth_term_of_linearly_recurrent_sequence(a, c, K) << "\n";
}
