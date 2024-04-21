// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B

#include "../../template/template.hpp"

#include "../../graph/mst/directed-mst.hpp"

int main() {
  int V, E, R;
  cin >> V >> E >> R;
  Edges< int > edges;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges.emplace_back(a, b, c);
  }
  cout << directed_mst(V, R, edges).cost << "\n";
}
