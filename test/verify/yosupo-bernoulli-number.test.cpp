#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fps/formal-power-series-friendly-ntt.cpp"
#include "../../math/fps/bernoulli.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << bernoulli< FPS, mint >(N) << endl;
}

