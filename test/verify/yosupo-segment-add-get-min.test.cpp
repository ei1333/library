// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicLiChaoTree< int64, -1000000000, 1000000000, infll > dlct;
  for(int i = 0; i < N; i++) {
    int64 l, r, a, b;
    cin >> l >> r >> a >> b;
    dlct.add_segment(l, r, a, b);
  }
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int64 l, r, a, b;
      cin >> l >> r >> a >> b;
      dlct.add_segment(l, r, a, b);
    } else {
      int64 p;
      cin >> p;
      auto ret = dlct.query(p);
      if(ret >= infll) cout << "INFINITY\n";
      else cout << ret << endl;
    }
  }
}

