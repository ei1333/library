#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/mst/prim.cpp"

int main() {
  int V, E;
  cin >> V >> E;
  WeightedGraph< int > g(V);
  for(int i = 0; i < E; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
  }
  cout << prim(g).cost << "\n";
}
