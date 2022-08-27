#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/berlekamp-massey.hpp"
#include "../../math/fps/formal-power-series.hpp"
#include "../../math/fps/sparse-matrix.hpp"
#include "../../template/template.hpp"

const int MOD = 998244353;
using mint    = ModInt< MOD >;

int main() {
  int N, K;
  cin >> N >> K;
  FPSGraph< mint > g(N);
  for (int i = 0; i < K; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].emplace_back(b, c);
  }
  cout << sparse_determinant(g) << endl;
}
