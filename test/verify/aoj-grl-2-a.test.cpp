// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "../../template/template.hpp"

#include "../../graph/mst/prim.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  Graph<> g(V);
  g.read(E, 0, true);
  cout << prim(g).cost << "\n";
}
