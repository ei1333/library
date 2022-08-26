#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../graph/graph-template.hpp"
#include "../../graph/tree/pmormq-lowest-common-ancestor.hpp"
#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"
#include "../../template/template.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  PMORMQLowestCommonAncestor< int > g(N);
  for (int i = 1; i < N; i++) {
    int x;
    in.read(x);
    g.add_directed_edge(x, i);
  }
  g.build();
  for (int i = 0; i < Q; i++) {
    int u, v;
    in.read(u, v);
    out.writeln(g.lca(u, v));
  }
}
