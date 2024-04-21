// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A

#include "../../template/template.hpp"

#include "../../graph/others/low-link.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  LowLink<> g(V);
  g.read(E, 0);
  g.build();
  auto &art = g.articulation;
  sort(art.begin(), art.end());
  for(auto &v : art) cout << v << "\n";
}

