#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include "../../graph/mst/kruskal.hpp"
#include "../../template/template.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  Edges< int > edges;
  for (int i = 0; i < E; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges.emplace_back(a, b, c);
  }
  cout << kruskal(edges, V).cost << "\n";
}
