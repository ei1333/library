// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/manhattanmst

#include "../../template/template.hpp"

#include "../../graph/mst/manhattan-mst.hpp"
#include "../../graph/mst/kruskal.hpp"

int main() {
  int N;
  cin >> N;
  vector< int64_t > X(N), Y(N);
  for(int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }
  auto es = manhattan_mst(X, Y);
  auto ret = kruskal(es, N);
  cout << ret.cost << "\n";
  for(auto &e : ret.edges) cout << e.from << " " << e.to << "\n";
}
