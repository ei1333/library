// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum

#include "../../template/template.hpp"

#include "../../structure/develop/vertex-set-path-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  LCT lct;
  vector< LCT::NP > vs(N);
  for(int i = 0; i < N; i++) {
    T a;
    cin >> a;
    vs[i] = lct.alloc(a);
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    lct.evert(vs[a]);
    lct.link(vs[a], vs[b]);
  }
  while(Q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      lct.evert(vs[u]);
      lct.cut(vs[v]);
      lct.evert(vs[w]);
      lct.link(vs[w], vs[x]);
    } else if(t == 1) {
      int p;
      T x;
      cin >> p >> x;
      lct.set_key(vs[p], lct.get_info(vs[p]).v + x);
    } else {
      int u, v;
      cin >> u >> v;
      cout << lct.query_path(vs[u], vs[v]).sum << "\n";
    }
  }
}
