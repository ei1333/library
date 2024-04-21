// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum

#include "../../template/template.hpp"

#include "../../structure/lct/link-cut-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  auto add = [](int64 a, int64 b) { return a + b; };
  auto s = [](int64 a) { return a; };
  auto lct = get_link_cut_tree< int64 >(add, s);

  vector< int64 > A(N);
  cin >> A;

  auto vs = lct.build(A);
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    lct.evert(vs[a]);
    lct.link(vs[a], vs[b]);
  }

  while(Q--) {
    int T;
    cin >> T;
    if(T == 0) {
      int U, V, W, X;
      cin >> U >> V >> W >> X;
      lct.evert(vs[U]);
      lct.cut(vs[V]);
      lct.evert(vs[W]);
      lct.link(vs[W], vs[X]);
    } else if(T == 1) {
      int P, X;
      cin >> P >> X;
      lct.set_key(vs[P], vs[P]->key + X);
    } else {
      int U, V;
      cin >> U >> V;
      cout << lct.query(vs[U], vs[V]) << "\n";
    }
  }
}
