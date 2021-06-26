#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/formal-power-series-friendly-ntt.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  FPS< mint > F(N);
  cin >> F;
  cout << F.log() << endl;
}
