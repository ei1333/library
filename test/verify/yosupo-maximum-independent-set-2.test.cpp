// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/maximum_independent_set

#include "../../template/template.hpp"

#include "../../graph/others/maximum-clique.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  auto D = make_v< int >(V, V);
  for(int i = 0; i < E; i++) {
    int a, b;
    cin >> a >> b;
    D[a][b] = D[b][a] = true;
  }
  MaximumClique< 40 > mc(V);
  for(int i = 0; i < V; i++) {
    for(int j = 0; j < i; j++) {
      if(!D[i][j]) mc.add_edge(i, j);
    }
  }
  auto ret = mc.solve();
  cout << ret.size() << "\n";
  cout << ret << "\n";
}
