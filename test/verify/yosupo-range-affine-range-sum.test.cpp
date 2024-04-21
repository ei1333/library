// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"

#include "../../structure/segment-tree/lazy-segment-tree.hpp"

using mint = ModInt< 998244353 >;

int main() {
  int N, Q;
  cin >> N >> Q;
  using pi = pair< mint, int >;
  using qi = pair< mint, mint >;
  auto f = [](const pi &a, const pi &b) -> pi {
    return {a.first + b.first, a.second + b.second};
  };
  auto g = [](const pi &a, const qi &b) -> pi {
    return {a.first * b.first + mint(a.second) * b.second, a.second};
  };
  auto h = [](const qi &a, const qi &b) -> qi {
    return {a.first * b.first, a.second * b.first + b.second};
  };
  auto seg = get_lazy_segment_tree(N, f, g, h, pi(0, 0), qi(1, 0));
  for(int i = 0; i < N; i++) {
    mint a;
    cin >> a;
    seg.set(i, pi(a, 1));
  }
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, qi(b, c));
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r).first << "\n";
    }
  }
}
