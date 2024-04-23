// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/partition_function

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/partition.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  cout << partition< FPS, mint >(N) << endl;
}

