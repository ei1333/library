// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D

#include "../../template/template.hpp"

#include "../../structure/segment-tree/dual-segment-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  auto h = [](int a, int b) { return b; };
  auto seg = get_dual_segment_tree(N, h, INT_MAX);
  while(Q--) {
    int com;
    cin >> com;
    if(com == 0) {
      int l, r, x;
      cin >> l >> r >> x;
      seg.update(l, r + 1, x);
    } else if(com == 1) {
      int k;
      cin >> k;
      cout << seg[k] << "\n";
    }
  }
}
