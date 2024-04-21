// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum

#include "../../template/template.hpp"

#include "../../structure/develop/splay-tree-base.hpp"
#include "../../structure/develop/reversible-splay-tree.hpp"
#include "../../structure/develop/link-cut-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  using LCT = LinkCutTree< RST< int64 > >;

  auto add = [](int64 a, int64 b) { return a + b; };
  auto s = [](int64 a) { return a; };
  LCT lct(add, s, 0);

  vector< int > A(N);
  cin >> A;

  vector< LCT::Node * > vs(N);
  for(int i = 0; i < N; i++) {
    vs[i] = lct.alloc(A[i]);
  }
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
      lct.expose(vs[P]);
      vs[P]->key += X;
      lct.update(vs[P]);
    } else {
      int U, V;
      cin >> U >> V;
      lct.evert(vs[U]);
      lct.expose(vs[V]);
      cout << vs[V]->sum << "\n";
    }
  }
}
