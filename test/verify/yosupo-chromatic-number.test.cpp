#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../graph/others/chromatic-number.hpp"
#include "../../math/matrix/square-matrix.hpp"
#include "../../template/template.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  SquareMatrix< bool, 20 > g;
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    g[u][v] = g[v][u] = true;
  }
  cout << chromatic_number(g) << "\n";
}
