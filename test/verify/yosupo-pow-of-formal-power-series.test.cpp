#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/formal-power-series-friendly-ntt.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, M;
  cin >> N >> M;
  FPS< mint > f(N);
  cin >> f;
  cout << f.pow(M) << "\n";
}
