// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite

#include "../../template/template.hpp"

#include "../../structure/develop/vertex-set-path-composite.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  LCT lct;
  vector< LCT::NP > vs(N);
  for(int i = 0; i < N; i++) {
    T a, b;
    cin >> a >> b;
    vs[i] = lct.alloc({a, b});
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
      T c, d;
      cin >> p >> c >> d;
      lct.set_key(vs[p], {c, d});
    } else {
      int u, v;
      T x;
      cin >> u >> v >> x;
      auto info = lct.query_path(vs[u], vs[v]);
      cout << info.a_sum_p * x + info.b_sum_p << "\n";
    }
  }
}
