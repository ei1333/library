// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_point_get

#include "../../template/template.hpp"

#include "../../structure/segment-tree/dual-segment-tree.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto& a : A) cin >> a;

  using pi = pair< mint, mint >;
  auto g = [](const pi& a, const pi& b) -> pi {
    return {a.first * b.first, a.second * b.first + b.second};
  };
  auto seg = get_dual_segment_tree(N, g, pi(1, 0));
  while(Q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.update(l, r, {b, c});
    } else {
      int i;
      cin >> i;
      auto ret = seg[i];
      cout << ret.first * A[i] + ret.second << endl;
    }
  }
}
