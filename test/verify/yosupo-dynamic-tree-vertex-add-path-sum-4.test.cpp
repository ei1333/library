// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum

#include "../../template/template.hpp"

#include "../../structure/dynamic-tree/vertex-set-path-sum.hpp"
#include "../../structure/dynamic-tree/dynamic-tree-builder-for-vertex.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicTreeBuilderForVertex< LinkCutTree, VertexSetPathSum > g(N);
  for(int i = 0; i < N; i++) {
    int64 x;
    cin >> x;
    g.set_vertex(i, {x});
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
      int v;
      int64 x;
      cin >> v >> x;
      g.set_key(g.vs[v], {g.vs[v]->info.v + x});
    } else {
      int v, p;
      cin >> v >> p;
      cout << g.query_path(g.vs[p], g.vs[v]).sum << "\n";
    }
  }
}
