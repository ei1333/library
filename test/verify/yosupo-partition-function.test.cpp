#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/partition.hpp"
#include "../../template/template.hpp"

const int MOD = 998244353;
using mint    = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << partition< FPS, mint >(N) << endl;
}
