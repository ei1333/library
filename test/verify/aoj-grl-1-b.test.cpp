// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

#include "../../template/template.hpp"

#include "../../graph/shortest-path/bellman-ford.hpp"

int main() {
  int V, E, R;
  cin >> V >> E >> R;
  Edges< > es;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    es.emplace_back(a, b, c);
  }
  auto dists = bellman_ford(es, V, R);
  for(auto& dist : dists) {
    if(dist == numeric_limits< int >::min()) {
      cout << "NEGATIVE CYCLE\n";
      return 0;
    }
  }
  for(auto &dist : dists) {
    if(dist == numeric_limits< int >::max()) cout << "INF\n";
    else cout << dist << "\n";
  }
}
