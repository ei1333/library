#define PROBLEM \
  "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../template/template.hpp"

const int MOD = 998244353;
using mint    = ModInt< MOD >;

int main() {
  int N;
  int64_t M;
  cin >> N >> M;
  FPS< mint > f(N);
  cin >> f;
  cout << f.pow(M) << "\n";
}
