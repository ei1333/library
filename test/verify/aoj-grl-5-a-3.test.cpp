// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

#include "../../template/template.hpp"
#include "../../structure/dynamic-tree/diameter.hpp"
#include "../../structure/dynamic-tree/dynamic-tree-builder-for-edge.hpp"

int main() {
  int N;
  cin >> N;
  DynamicTreeBuilderForEdge< TopTree, Diameter< int64 > > g(N);
  for(int i = 0; i < N; i++) {
    g.set_vertex(i, {true, 0});
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    int64 w;
    cin >> a >> b >> w;
    g.add_edge(a, b, {false, w});
  }
  g.build();
  cout << g.query(g.vs[0]).dia << endl;
}
