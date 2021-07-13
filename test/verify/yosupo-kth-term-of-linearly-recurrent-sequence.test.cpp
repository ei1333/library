#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fps/formal-power-series-friendly-ntt.cpp"
#include "../../math/fps/kth-term-of-linearly-recurrent-sequence.cpp"

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
