// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/find_linear_recurrence

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/berlekamp-massey.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  FPS< mint > a(N);
  cin >> a;
  auto c = berlekamp_massey(a);
  c.pop_back();
  reverse(begin(c), end(c));
  cout << c.size() << "\n";
  cout << c << "\n";
}
