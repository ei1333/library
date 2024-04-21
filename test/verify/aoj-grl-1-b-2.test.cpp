// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

#include "../../template/template.hpp"

#include "../../graph/shortest-path/shortest-path-faster-algorithm.hpp"

int main() {
  int V, E, R;
  cin >> V >> E >> R;
  Graph< int > g(V);
  g.read(E, 0, true, true);
  auto dists = shortest_path_faster_algorithm(g, R);
  if(dists.empty()) cout << "NEGATIVE CYCLE\n";
  for(auto &dist : dists) {
    if(dist == numeric_limits< int >::max()) cout << "INF\n";
    else cout << dist << "\n";
  }
}
