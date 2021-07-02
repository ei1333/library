#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fps/formal-power-series-friendly-ntt.cpp"
#include "../../math/fps/berlekamp-massey.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

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
