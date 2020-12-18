#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B"

#include "../../template/template.cpp"

#include "../../graph/mst/directed-minimum-spanning-tree.cpp"

int main() {
  int V, E, R;
  cin >> V >> E >> R;
  Edges< int > edges;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges.emplace_back(a, b, c);
  }
  cout << directed_minimum_spanning_tree(V, R, edges).cost << "\n";
}
