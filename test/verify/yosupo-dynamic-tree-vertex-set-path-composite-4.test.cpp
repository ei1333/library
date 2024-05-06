// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite

#include "../../template/template.hpp"

#include "../../structure/top-tree/top-tree.hpp"

#include "../../structure/top-tree/vertex-set-path-composite.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  TopTreeBuilderForVertex< VertexSetPathComposite > g(N);
  for(int i = 0; i < N; i++) {
    mint a, b;
    cin >> a >> b;
    g.set_vertex(i, {a, b});
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  g.build();
  while(Q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      g.evert(g.vs[u]);
      g.cut(g.vs[v]);
      g.evert(g.vs[w]);
      g.link(g.vs[w], g.vs[x]);
    } else if(t == 1) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      g.set_key(g.vs[p], {c, d});
    } else {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      auto sum = g.query_path(g.vs[u], g.vs[v]);
      cout << sum.a * x + sum.b << "\n";
    }
  }
}
