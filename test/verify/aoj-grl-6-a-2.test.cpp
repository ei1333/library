// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A

#include "../../template/template.hpp"

#include "../../graph/flow/ford-fulkerson.hpp"

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  FordFulkerson< int > g(V);
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    g.add_edge(a, b, c);
  }
  printf("%d\n", g.max_flow(0, V - 1));
}
