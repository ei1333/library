#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

#include "../../graph/shortest-path/dijkstra-fibonacchi-heap.hpp"
#include "../../template/template.hpp"

int main() {
  int V, E, R;
  cin >> V >> E >> R;
  Graph< int > g(V);
  g.read(E, 0, true, true);
  for (auto &dist: dijkstra_fibonacchi_heap(g, R)) {
    if (dist == numeric_limits< int >::max())
      cout << "INF\n";
    else
      cout << dist << "\n";
  }
}
