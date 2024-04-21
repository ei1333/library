// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include "../../template/template.hpp"

#include "../../graph/tree/offline-lca.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  Graph< int > g(N);
  for(int i = 1; i < N; i++) {
    int x;
    in.read(x);
    g.add_directed_edge(x, i);
  }
  vector< pair< int, int > > qs(Q);
  for(auto&[l, r]: qs) in.read(l, r);
  auto ans = offline_lca(g, qs);
  for(auto &p: ans) out.writeln(p);
}
