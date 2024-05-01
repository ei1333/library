// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root

#include "../../template/template.hpp"

#include "../../graph/graph-template.hpp"
#include "../../graph/tree/convert-rooted-tree.hpp"
#include "../../graph/tree/static-top-tree-dp.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

using mint = modint998244353;

struct TreeDPInfo {
  struct Point {
    mint val, num;
  };
  struct Path {
    mint val, num, a, b;
  };

  vector< int > A, B, C;

  TreeDPInfo(int n): A(n), B(n - 1), C(n - 1) {}

  Path vertex(int u) const { return {A[u], 1, 1, 0}; };

  Path add_vertex(Point d, int u) const { return {d.val + A[u], d.num + 1, 1, 0}; };

  Point add_edge(Path d, int e) const { return {d.val * B[e] + d.num * C[e], d.num}; };

  Point rake(Point l, Point r) const { return {l.val + r.val, l.num + r.num}; };

  Path compress(Path p, Path c, int e) const {
    c = {c.val * B[e] + c.num * C[e], c.num, c.a * B[e], c.b * B[e] + C[e]};
    return {p.val + c.val * p.a + c.num * p.b, p.num + c.num, p.a * c.a, p.a * c.b + p.b};
  };
};

int main() {
  int N, Q;
  cin >> N >> Q;
  TreeDPInfo info(N);
  for (auto &a: info.A) cin >> a;
  Graph g(N);
  for (int i = 0; i + 1 < N; i++) {
    int u, v, b, c;
    cin >> u >> v >> b >> c;
    g.add_edge(u, v);
    info.B[i] = b;
    info.C[i] = c;
  }
  g = convert_rooted_tree(g);
  StaticTopTree tree(g);
  StaticTopTreeDP dp(tree, info);
  while (Q--) {
    int t;
    cin >> t;
    TreeDPInfo::Path ret;
    if (t == 0) {
      int w, x;
      cin >> w >> x;
      info.A[w] = x;
      ret = dp.update_vertex(w);
    } else {
      int e, y, z;
      cin >> e >> y >> z;
      info.B[e] = y;
      info.C[e] = z;
      ret = dp.update_edge(e);
    }
    cout << ret.val.val() << "\n";
  }
}
