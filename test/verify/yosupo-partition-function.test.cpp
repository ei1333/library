// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/partition_function

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/partition.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << partition< FPS, mint >(N) << endl;
}

