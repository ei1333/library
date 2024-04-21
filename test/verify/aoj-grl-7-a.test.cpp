// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A

#include "../../template/template.hpp"

#include "../../graph/flow/bipartite-matching.hpp"

int main() {
  int X, Y, E;
  scanf("%d %d %d", &X, &Y, &E);
  BipartiteMatching bm(X + Y);
  for(int i = 0; i < E; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    bm.add_edge(a, X + b);
  }
  printf("%d\n", bm.bipartite_matching());
}
