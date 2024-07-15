// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/global_minimum_cut_of_dynamic_star_augmented_graph

#include "../../template/template.hpp"

#include "../../graph/flow/global-minimum-cut-of-dynamic-star-augmented-graph.hpp"

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<int> A(N);
  for (auto &a : A) cin >> a;
  Edges<int64> es(M);
  for (auto &e : es) {
    cin >> e.from >> e.to >> e.cost;
  }
  GlobalMinimumCutofDynamicStarAugmentedGraph<int64> g(N, es);
  for (int i = 0; i < N; i++) {
    g.update(i, A[i]);
  }
  while (Q--) {
    int x, y;
    cin >> x >> y;
    cout << g.update(x, y) << "\n";
  }
}
