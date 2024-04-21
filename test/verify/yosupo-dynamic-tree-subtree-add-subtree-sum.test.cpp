// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum

#include "../../template/template.hpp"

#include "../../structure/develop/subtree-add-subtree-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  LCT lct;
  vector< LCT::NP > vs(N);
  for(int i = 0; i < N; i++) {
    T x;
    cin >> x;
    vs[i] = lct.alloc(x);
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
      int v, p;
      T x;
      cin >> v >> p >> x;
      lct.evert(vs[p]);
      lct.set_propagate_subtree(vs[v], x);
    } else {
      int v, p;
      cin >> v >> p;
      lct.evert(vs[p]);
      cout << lct.query_subtree(vs[v]).sum_sum << "\n";
    }
  }
}
