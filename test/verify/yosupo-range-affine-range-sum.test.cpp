// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../structure/segment-tree/lazy-segment-tree.hpp"
#include "../../structure/class/range-affine-range-sum.hpp"

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  using monoid = RangeAffineRangeSum< mint >;
  vector< monoid::S > vs(N);
  for(int i = 0; i < N; i++) {
    mint a;
    cin >> a;
    vs[i] = {a, 1};
  }
  LazySegmentTree seg(monoid(), vs);
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, {b, c});
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r).first << "\n";
    }
  }
}
