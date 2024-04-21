// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/three_edge_connected_components

#include "../../template/template.hpp"

#include "../../graph/connected-components/three-edge-connected-components.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  ThreeEdgeConnectedComponents<> g(N);
  g.read(M, 0);
  g.build();
  cout << g.group.size() << "\n";
  for(auto &p : g.group) {
    cout << p.size() << " " << p << "\n";
  }
}
