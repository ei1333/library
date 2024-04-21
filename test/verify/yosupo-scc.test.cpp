// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/scc

#include "../../template/template.hpp"

#include "../../graph/connected-components/strongly-connected-components.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  StronglyConnectedComponents<> g(N);
  g.read(M, 0, false, true);
  g.build();
  cout << g.group.size() << "\n";
  for(auto &p : g.group) {
    cout << p.size() << " " << p << "\n";
  }
}
