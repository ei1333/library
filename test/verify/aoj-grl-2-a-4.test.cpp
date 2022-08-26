#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include "../../graph/mst/prim-fibonacchi-heap.hpp"
#include "../../template/template.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  Graph<> g(V);
  g.read(E, 0, true);
  cout << prim_fibonacchi_heap(g).cost << "\n";
}
