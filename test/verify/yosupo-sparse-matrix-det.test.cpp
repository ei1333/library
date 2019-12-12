#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/formal-power-series.cpp"

#include "../../math/fps/berlekamp-massey.cpp"
#include "../../math/fps/sparse-matrix.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, K;
  cin >> N >> K;
  FPSGraph< mint > g(N);
  for(int i = 0; i < K; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].emplace_back(b, c);
  }
  cout << sparse_determinant(g) << endl;
}
