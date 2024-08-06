// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum

#include "../../template/template.hpp"

#include "../../structure/segment-tree/segment-tree-beats.hpp"
#include "../../structure/class/range-chmin-chmax-add-range-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  using monoid = RangeChminChmaxAddRangeSum< int64 >;
  vector< monoid::S > vs(N);
  for (auto &v: vs) {
    int64 x;
    cin >> x;
    v = monoid::set(x);
  }
  SegmentTreeBeats seg(monoid(), vs);
  auto id = monoid::id();
  while (Q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t <= 2) {
      int64 x;
      cin >> x;
      if (t == 0) seg.apply(l, r, monoid::chmin(x));
      else if (t == 1) seg.apply(l, r, monoid::chmax(x));
      else if (t == 2) seg.apply(l, r, monoid::add(x));
    } else {
      cout << seg.prod(l, r).sum << "\n";
    }
  }
}
