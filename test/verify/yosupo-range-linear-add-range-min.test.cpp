// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_linear_add_range_min

#include "../../template/template.hpp"

#include "../../structure/segment-tree/range-linear-add-range-min-segment-tree.hpp"

int main() {
  int n, q;
  cin >> n >> q;
  vector< int64 > as(n);
  for (auto &a: as) cin >> a;
  RangeLinearAddRangeMinSegmentTree< int64, int64, __int128_t > seg(as, infll);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      seg.apply(l, r, b, c);
    } else {
      cout << seg.prod(l, r) << "\n";
    }
  }
}
