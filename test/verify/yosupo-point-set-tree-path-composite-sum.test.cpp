// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum

#include "../../template/template.hpp"

#include "../../structure/top-tree/top-tree.hpp"

#include "../../structure/top-tree/point-set-tree-path-composite-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  TopTreeBuilder< PointSetTreePathCompositeSum > g(N);
  for(int i = 0; i < N; i++) {
    int a;
    cin >> a;
    g.set_vertex(i, {true, a, 0});
  }
  for (int i = 0; i + 1 < N; i++) {
    int u, v, b, c;
    cin >> u >> v >> b >> c;
    g.add_edge(u, v, {false, b, c});
  }
  g.build();
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int w, x;
      cin >> w >> x;
      g.set_key(g.vs[w], {true, x, 0});
    } else {
      int e, y, z;
      cin >> e >> y >> z;
      g.set_key(g.es[e], {false, y, z});
    }
    int r;
    cin >> r;
    cout << g.query(g.vs[r]).s.val() << "\n";
  }
}
