// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite

#include "../../template/template.hpp"

#include "../../structure/bbst/reversible-splay-tree.hpp"
#include "../../structure/segment-tree/affine.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  using pi = Affine< mint >;
  auto f = [](const pi &a, const pi &b) -> pi {
    return pi::op(a, b);
  };
  ReversibleSplayTree< pi > seg(f, pi(1, 0));
  vector< pi > V(N);
  for(int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    V[i] = {a, b};
  }
  auto root = seg.build(V);
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int p;
      mint a, b;
      cin >> p >> a >> b;
      seg.set_element(root, p, pi(a, b));
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      auto ret = seg.query(root, l, r);
      cout << ret.eval(x) << "\n";
    }
  }
}
