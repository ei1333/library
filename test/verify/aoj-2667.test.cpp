#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667"

#include "../../template/template.cpp"

#include "../../structure/develop/array-pool.cpp"
#include "../../structure/develop/dual-splay-tree.cpp"
#include "../../structure/develop/link-cut-tree-subtree-dual-semi-group.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  struct Uku {
    int64 sum;
    int e_sz;
  };

  auto f = [](Uku x, const Uku &y) {
    x.sum += y.sum;
    x.e_sz += y.e_sz;
    return x;
  };
  auto g = [](Uku x, const int64 &y) {
    x.sum += x.e_sz * y;
    return x;
  };
  auto h = [](const int64 &x, const int64 &y) {
    return x + y;
  };
  auto lct = get_link_cut_tree_subtree_dual_semi_group< Uku, int64, 300000 >(f, g, h, 0);
  vector< decltype(lct)::Node * > vv(N), ee(N);
  for(int i = 0; i < N; i++) {
    vv[i] = lct.alloc((Uku) {0, 0});
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    ee[i] = lct.alloc((Uku) {0, 1});
    lct.evert(vv[b]);
    lct.link(vv[b], ee[i]);
    lct.link(ee[i], vv[a]);
  }
  for(int i = 0; i < Q; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    if(t == 0) {
      lct.evert(vv[a]);
      lct.expose(vv[b]);
      cout << vv[b]->sum.sum << "\n";
    } else {
      lct.evert(vv[0]);
      lct.subtree_add(vv[a], b);
    }
  }
}
