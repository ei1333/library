// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bipartitematching

#include "../../template/template.hpp"

#include "../../graph/flow/bipartite-flow.hpp"

int main() {
  int L, R, M;
  cin >> L >> R >> M;
  BipartiteFlow flow(L, R);
  for(int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    flow.add_edge(a, b);
  }
  auto es = flow.max_matching();
  cout << es.size() << "\n";
  for(auto &p : es) cout << p.first << " " << p.second << "\n";
}
